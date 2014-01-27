<?php

/**
 * @file
 * Redirect interface to linkchecker functionalities.
 */

/**
 * Implements hook_redirect_insert().
 */
function linkchecker_redirect_insert($redirect) {
  linkchecker_redirect_update($redirect);
}

/**
 * Implements hook_redirect_update().
 */
function linkchecker_redirect_update($redirect) {
  // It's unknown if this is a redirect for HTTP/HTTPS or the encoded urls.
  $url_http = url($redirect->source, array('absolute' => TRUE, $redirect->source_options));
  $url_https = url($redirect->source, array('absolute' => TRUE, 'https' => TRUE, $redirect->source_options));

  $urls = array(
    $url_http,
    $url_https,
    rawurldecode($url_http),
    rawurldecode($url_https),
  );

  _linkchecker_redirect_reset($urls);
}

/**
 * Reset last_checked status.
 *
 * @param array $urls
 *   An array of urls that should be checked on next cron run.
 */
function _linkchecker_redirect_reset($urls = array()) {
  $urls = array_unique($urls);

  $num_updated = db_update('linkchecker_link')
    ->condition('urlhash', array_map('drupal_hash_base64', $urls))
    ->condition('fail_count', 0, '>')
    ->condition('status', 1)
    ->fields(array('last_checked' => 0))
    ->execute();

  if ($num_updated) {
    drupal_set_message(t('The link %url will be checked again on the next cron run.', array('%url' => $urls[0])));
  }
}
