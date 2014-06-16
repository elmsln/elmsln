<?php

/**
 * @file
 * Provides class that expires users.
 */

class ExpireUser implements ExpireInterface {

  /**
   * Executes expiration actions for user.
   *
   * @param $account
   *   User object.
   *
   * @param $action
   *   Action that has been executed.
   *
   * @param $skip_action_check
   *   Shows whether should we check executed action or just expire node.
   */
  function expire($account, $action, $skip_action_check = FALSE) {

    if (empty($account->uid)) {
      return;
    }

    $enabled_actions = variable_get('expire_user_actions', array());
    $enabled_actions = array_filter($enabled_actions);

    // Stop further expiration if executed action is not selected by admin.
    if (!in_array($action, $enabled_actions) && !$skip_action_check) {
      return;
    }

    $expire_urls = array();

    // Expire front page.
    $expire_front_page = variable_get('expire_user_front_page', EXPIRE_USER_FRONT_PAGE);
    if ($expire_front_page) {
      $expire_urls = ExpireAPI::getFrontPageUrls();
    }

    // Expire user page.
    $expire_user_page = variable_get('expire_user_user_page', EXPIRE_USER_USER_PAGE);
    if ($expire_user_page) {
      $expire_urls['user-' . $account->uid] = 'user/' . $account->uid;
    }

    // Expire taxonomy term pages.
    $expire_term_pages = variable_get('expire_user_term_pages', EXPIRE_USER_TERM_PAGES);
    if (module_exists('taxonomy') && $expire_term_pages) {
      $urls = ExpireAPI::expireTermPages($account, 'user');
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire user reference's pages.
    $expire_references = variable_get('expire_user_reference_pages', EXPIRE_USER_REFERENCE_PAGES);
    if ((module_exists('node_reference') || module_exists('user_reference') || module_exists('entityreference')) && $expire_references) {
      $traverse_field_collection = module_exists('field_collection') && variable_get('expire_user_reference_field_collection_pages', EXPIRE_USER_REFERENCE_FC_PAGES);
      $urls = ExpireAPI::expireReferences($account, 'user', $traverse_field_collection);
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Expire custom pages.
    $expire_custom = variable_get('expire_user_custom', EXPIRE_USER_CUSTOM);
    if ($expire_custom) {
      $pages = variable_get('expire_user_custom_pages');
      $urls = ExpireAPI::expireCustomPages($pages, array('user' => $account));
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Flush page cache for expired urls.
      ExpireAPI::executeExpiration($expire_urls, 'user', $account);
  }

}
