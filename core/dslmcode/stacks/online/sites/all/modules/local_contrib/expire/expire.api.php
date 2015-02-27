<?php

/**
 * @file
 * API documentation for Cache Expiration module.
 */

/**
 * Provides possibility to flush pages for external cache storages.
 *
 * @param $urls
 *   List of internal paths and/or absolute URLs that should be flushed.
 *
 *   Example of array (when base url include option is enabled):
 *   array(
 *     'node/1' => 'http://example.com/node/1',
 *     'news' => 'http://example.com/news',
 *   );
 *
 *   Example of array (when base url include option is disabled):
 *   array(
 *     'node/1' => 'node/1',
 *     'news' => 'news',
 *   );
 *
 * @param $wildcards
 *   Array with wildcards implementations for each internal path.
 *   Indicates whether should be executed wildcard cache flush.
 *
 *   Example:
 *   array(
 *     'node/1' => FALSE,
 *     'news' => TRUE,
 *   );
 *
 * @param $object_type
 *  Name of object type ('node', 'comment', 'user', etc).
 *
 * @param $object
 *   Object (node, comment, user, etc) for which expiration is executes.
 *
 * @see expire.api.inc
 */
function hook_expire_cache($urls, $wildcards, $object_type, $object) {
  module_load_include('inc', 'purge');
  foreach ($urls as $url) {
    $full_path = url($url, array('absolute' => TRUE));
    purge_urls($full_path, $wildcards);
  }
}

/**
 * Provides possibility to change urls before they are expired.
 *
 * @param $urls
 *   List of internal paths and/or absolute URLs that should be flushed.
 *
 *   Example of array:
 *   array(
 *     'node-1' => 'node/1',
 *     'reference-user-17' => 'user/17',
 *   );
 *
 * @param $object_type
 *  Name of object type ('node', 'comment', 'user', etc).
 *
 * @param $object
 *   Object (node, comment, user, etc) for which expiration is executes.
 *
 * @param $absolute_urls_passed
 *   Indicates whether absolute urls were passed (TRUE or FALSE).
 *   Currently this flag can be set to TRUE only from drush command or rules action.
 *
 * @see expire.api.inc
 */
function hook_expire_cache_alter(&$urls, $object_type, $object, $absolute_urls_passed) {
  if (!$absolute_urls_passed && isset($urls['node-1'])) {
    unset($urls['node-1']); // Do not expire node with nid 1.
  }
}

/**
 * Provides possibility to change urls right before they are expired.
 *
 * @param $urls
 *   List of internal paths and/or absolute URLs that should be flushed.
 *
 *   Example of array (when base url include option is enabled):
 *   array(
 *     'node/1' => 'http://example.com/node/1',
 *     'news' => 'http://example.com/news',
 *   );
 *
 *   Example of array (when base url include option is disabled):
 *   array(
 *     'node/1' => 'node/1',
 *     'news' => 'news',
 *   );
 *
 * @param $object_type
 *  Name of object type ('node', 'comment', 'user', etc).
 *
 * @param $object
 *   Object (node, comment, user, etc) for which expiration is executes.
 *
 * @see expire.api.inc
 */
function hook_expire_urls_alter(&$urls, $object_type, $object) {
  if ($object_type == 'node' && isset($urls['node-' . $object->nid])) {
    $urls['node-' . $object->nid] = 'custom-url';
  }
}
