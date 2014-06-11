<?php

/**
 * @file
 * Provides class that expires comments.
 */

class ExpireComment implements ExpireInterface {

  /**
   * Executes expiration actions for comment.
   *
   * @param $comment
   *   Comment object.
   *
   * @param $action
   *   Action that has been executed.
   *
   * @param $skip_action_check
   *   Shows whether should we check executed action or just expire node.
   */
  function expire($comment, $action, $skip_action_check = FALSE) {

    // Some comment actions may be executed one after another. To avoid
    // duplicate flushes we should check whether cache was already flushed.
    static $cache_flushed = FALSE;
    if ($cache_flushed) {
      return;
    }

    if (empty($comment->cid) || empty($comment->nid)) {
      return;
    }

    // Load node for this comment.
    $node = node_load($comment->nid);
    if (empty($node->type)) {
      return;
    }

    // See if cache settings was overridden for this node type.
    $settings_overridden = variable_get('expire_comment_override_defaults_' . $node->type);

    $variable_suffix = '';
    if (!empty($settings_overridden)) {
      // If page cache settings was overridden for this node type we
      // should add "_[NODE-TYPE]" to every variable name we use here.
      $variable_suffix = '_' . $node->type;
    }

    $enabled_actions = variable_get('expire_comment_actions' . $variable_suffix, array());
    $enabled_actions = array_filter($enabled_actions);

    // Stop further expiration if executed action is not selected by admin.
    if (!in_array($action, $enabled_actions) && !$skip_action_check) {
      return;
    }

    $expire_urls = array();

    // Expire front page.
    $expire_front_page = variable_get('expire_comment_front_page' . $variable_suffix, EXPIRE_COMMENT_FRONT_PAGE);
    if ($expire_front_page) {
      $expire_urls = ExpireAPI::getFrontPageUrls();
    }

    // Expire comment page.
    $expire_comment_page = variable_get('expire_comment_comment_page' . $variable_suffix, EXPIRE_COMMENT_COMMENT_PAGE);
    if ($expire_comment_page) {
      $expire_urls['comment-' . $comment->cid] = 'comment/' . $comment->cid;
    }

    // Expire comment's node page.
    $expire_node_page = variable_get('expire_comment_node_page' . $variable_suffix, EXPIRE_COMMENT_NODE_PAGE);
    if ($expire_node_page) {
      $expire_urls['node-' . $comment->nid] = 'node/' . $comment->nid;
    }

    // Expire comment's node term pages.
    $expire_node_term_pages = variable_get('expire_comment_node_term_pages' . $variable_suffix, EXPIRE_COMMENT_NODE_TERM_PAGES);
    if (module_exists('taxonomy') && $expire_node_term_pages) {
      $urls = ExpireAPI::expireTermPages($node, 'node');
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire comment's references.
    $expire_references = variable_get('expire_comment_reference_pages' . $variable_suffix, EXPIRE_COMMENT_REFERENCE_PAGES);
    if ((module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) && $expire_references) {
      $urls = ExpireAPI::expireReferences($comment, 'comment');
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire comment's node references.
    $expire_node_references = variable_get('expire_comment_node_reference_pages' . $variable_suffix, EXPIRE_COMMENT_NODE_REFERENCE_PAGES);
    if ((module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) && $expire_node_references) {
      $traverse_field_collection = module_exists('field_collection') && variable_get('expire_comment_node_reference_field_collection_pages' . $variable_suffix, EXPIRE_COMMENT_NODE_REFERENCE_FC_PAGES);
      $urls = ExpireAPI::expireReferences($node, 'node', $traverse_field_collection);
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire custom pages.
    $expire_custom = variable_get('expire_comment_custom' . $variable_suffix, EXPIRE_COMMENT_CUSTOM);
    if ($expire_custom) {
      $pages = variable_get('expire_comment_custom_pages' . $variable_suffix);
      $urls = ExpireAPI::expireCustomPages($pages, array('comment' => $comment));
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Flush page cache for expired urls.
    ExpireAPI::executeExpiration($expire_urls, 'comment', $comment);

    // Mark cache flushed as true, to avoid duplicate cache flushes in some cases.
    $cache_flushed = TRUE;
  }

}
