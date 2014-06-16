<?php

/**
 * @file
 * Integration with the Rules module.
 */

/**
 * Implements hook_rules_action_info().
 */
function expire_rules_action_info() {
  return array(
    'expire_rules_action_flush_url' => array(
      'label' => t('Clear URL(s) from the page cache.'),
      'group' => 'Expire',
      'parameter' => array(
        'urls' => array(
          'type' => 'text',
          'label' => t('Absolute URL or internal path of page to clear'),
          'description' => t('Enter one value in each line. Examples: http://example.com, http://example.com/node/1, taxonomy/term/10, user/7, &lt;front&gt;.'),
        ),
      ),
      'callbacks' => array(
        'validate' => 'expire_rules_action_flush_url_validation',
      ),
    ),
  );
}

/**
 * Expires pages from cache_page bin.
 *
 * @param $urls
 *   Array with user-defined URLs and internal paths.
 */
function expire_rules_action_flush_url($urls) {
  global $base_url;

  $absolute_urls = array();
  $internal_paths = array();
  $urls = explode("\r\n", $urls);
  foreach ($urls as &$url) {
    if (strpos($url, $base_url) === 0) {
      $absolute_urls[] = trim($url);
    }
    else {
      $internal_paths[] = trim($url);
    }
  }

  if (!empty($internal_paths)) {
    ExpireAPI::executeExpiration($internal_paths);
  }

  if (!empty($absolute_urls)) {
    ExpireAPI::executeExpiration($absolute_urls, '', NULL, TRUE);
  }
}

/**
 * Process value submitted by user in Rules settings.
 */
function expire_rules_action_flush_url_validation($action) {

  // If user uses PHP values in his input, some line ending might be lost.
  // To avoid this bug we should add a whitespace to the end of each value.
  $urls = &$action->settings['urls'];
  $url_parts = explode("\r\n", $urls);
  foreach ($url_parts as &$url) {
    $url = trim($url) . ' ';
  }
  $urls = implode("\r\n", $url_parts);
}
