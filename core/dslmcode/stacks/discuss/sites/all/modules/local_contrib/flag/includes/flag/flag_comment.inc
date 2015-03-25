<?php

/**
 * @file
 * Contains the flag_comment class.
 */

/**
 * Implements a comment flag.
 */
class flag_comment extends flag_entity {
  function options() {
    $options = parent::options();
    $options += array(
      'access_author' => '',
    );
    return $options;
  }

  /**
   * Options form extras for comment flags.
   */
  function options_form(&$form) {
    parent::options_form($form);

    $form['access']['access_author'] = array(
      '#type' => 'radios',
      '#title' => t('Flag access by content authorship'),
      '#options' => array(
        '' => t('No additional restrictions'),
        'comment_own' => t('Users may only flag own comments'),
        'comment_others' => t('Users may only flag comments by others'),
        'node_own' => t('Users may only flag comments of nodes they own'),
        'node_others' => t('Users may only flag comments of nodes by others'),
      ),
      '#default_value' => $this->access_author,
      '#description' => t("Restrict access to this flag based on the user's ownership of the content. Users must also have access to the flag through the role settings."),
    );
  }

  function type_access_multiple($entity_ids, $account) {
    $access = array();

    // If all subtypes are allowed, we have nothing to say here.
    if (empty($this->types)) {
      return $access;
    }

    // Ensure node types are granted access. This avoids a
    // node_load() on every type, usually done by applies_to_entity_id().
    $query = db_select('comment', 'c');
    $query->innerJoin('node', 'n', 'c.nid = n.nid');
    $result = $query
      ->fields('c', array('cid'))
      ->condition('c.cid', $entity_ids, 'IN')
      ->condition('n.type', $this->types, 'NOT IN')
      ->execute();
    foreach ($result as $row) {
      $access[$row->nid] = FALSE;
    }

    return $access;
  }

  function get_entity_id($comment) {
    // Store the comment object in the static cache, to avoid getting it
    // again unneedlessly.
    $this->remember_entity($comment->cid, $comment);
    return $comment->cid;
  }

  function get_labels_token_types() {
    return array_merge(array('comment', 'node'), parent::get_labels_token_types());
  }

  function replace_tokens($label, $contexts, $options, $entity_id) {
    if ($entity_id) {
      if (($comment = $this->fetch_entity($entity_id)) && ($node = node_load($comment->nid))) {
        $contexts['node'] = $node;
        $contexts['comment'] = $comment;
      }
    }
    return parent::replace_tokens($label, $contexts, $options, $entity_id);
  }

  function get_flag_action($entity_id) {
    $flag_action = parent::get_flag_action($entity_id);
    $comment = $this->fetch_entity($entity_id);
    $flag_action->content_title = $comment->subject;
    $flag_action->content_url = $this->_flag_url("comment/$comment->cid", "comment-$comment->cid");
    return $flag_action;
  }

  function get_relevant_action_objects($entity_id) {
    $comment = $this->fetch_entity($entity_id);
    return array(
      'comment' => $comment,
      'node' => node_load($comment->nid),
    );
  }
}
