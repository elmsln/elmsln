<?php

/**
 * @file
 * Provides class that expires files.
 */

class ExpireFile implements ExpireInterface {

  /**
   * Executes expiration actions for file.
   *
   * @param $file
   *   File object.
   *
   * @param $action
   *   Action that has been executed.
   *
   * @param $skip_action_check
   *   Shows whether should we check executed action or just expire node.
   */
   function expire($file, $action, $skip_action_check = FALSE) {
    global $base_path;

    if (empty($file->fid)) {
      return;
    }

    $enabled_actions = variable_get('expire_file_actions', array());
    $enabled_actions = array_filter($enabled_actions);

     // Stop further expiration if executed action is not selected by admin.
    if (!in_array($action, $enabled_actions) && !$skip_action_check) {
      return;
    }

    $expire_urls = array();

    // Expire front page.
    $expire_front_page = variable_get('expire_file_front_page', EXPIRE_FILE_FRONT_PAGE);
    if ($expire_front_page) {
      $expire_urls = ExpireAPI::getFrontPageUrls();
    }

    // Expire file url.
    $expire_file_page = variable_get('expire_file_file', EXPIRE_FILE_FILE);
    if ($expire_file_page) {
      $file_url = file_create_url($file->uri);
      $parsed_url = parse_url($file_url);

      // Remove the base path from our url.
      $expire_urls['file-' . $file->fid] = substr($parsed_url['path'], strlen($base_path));
    }

    // Expire custom pages.
    $expire_custom = variable_get('expire_file_custom', EXPIRE_FILE_CUSTOM);
    if ($expire_custom) {
      $pages = variable_get('expire_file_custom_pages');
      $urls = ExpireAPI::expireCustomPages($pages, array('file' => $file));
      $expire_urls = array_merge($expire_urls, $urls);
    }

    // Flush page cache for expired urls.
    ExpireAPI::executeExpiration($expire_urls, 'file', $file);
  }
}
