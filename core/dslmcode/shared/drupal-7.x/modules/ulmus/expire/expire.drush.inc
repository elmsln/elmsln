<?php
// $Id$

/**
 * @file
 * This is the drush integration for the expire module
 */

/**
 * Implementation of hook_drush_command().
 */
function expire_drush_command() {
  $items['expire-url'] = array(
    'description' => "Expire fully qualified URLs.",
    'arguments' => array(
      'urls' => 'URLs to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-url http://example.com/testpage.html' => 'Expire a single URL.',
      'drush xu http://example.com/ http://test.com/logo.jpg' => 'Expire multiple URLs.',
    ),
    'aliases' => array('xu'),
    'drupal dependencies' => array('expire'),
    'callback' => 'drush_expire_url'
  );
  $items['expire-path'] = array(
    'description' => "Expire a drupal path.",
    'arguments' => array(
      'paths' => 'A list drupal paths to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-path node/123' => 'Expire a single drupal path.',
      'drush expire-path FRONT' => 'Expire the front page.',
      'drush xp FRONT node/234 contact' => 'Expire multiple drupal paths.',
    ),
    'aliases' => array('xp'),
    'drupal dependencies' => array('expire'),
    'callback' => 'drush_expire_path'
  );
  $items['expire-node'] = array(
    'description' => "Expire a node by node-id.",
    'arguments' => array(
      'nids' => 'Numeric node-ids to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-node 2 24 612' => 'Expire drupal nodes by node id',
    ),
    'aliases' => array('xn'),
    'drupal dependencies' => array('expire'),
    'callback' => 'drush_expire_nid'
  );
  return $items;
}

/**
 * Callback for expire-url drush command.
 * @param string $urls a space separated list of paths.
 */
function drush_expire_url() {
  $full_urls = array();
  $full_urls = drush_get_arguments();
  unset($full_urls[0]);
  // Process Full URLs
  // hook_expire_cache
  $modules = module_implements('expire_cache');
  foreach ($modules as $module) {
    module_invoke($module, 'expire_cache', $full_urls);
  }
  watchdog('expire', 'Output: !urls <br /> Modules Using hook_expire_cache(): !modules', array(
    '!urls' => expire_print_r($full_urls),
    '!modules' => expire_print_r($modules),
  ));
}

/**
 * Callback for expire-path drush command.
 * @param string $urls a space separated list of paths.
 */
function drush_expire_path() {
  global $base_path;
  $internal = array();
  $paths = array();
  $paths = drush_get_arguments();
  unset($paths[0]);
  foreach ($paths as $path) {
    // Strip base path from path.
    $path_nobase = preg_replace('/^' . preg_quote($base_path, '/') .'/i', '', $path);
    if ($path == 'FRONT') {
      $internal[] = variable_get('site_frontpage', 'node');
    }
    else {
      $normal = expire_normal_path_check($path_nobase);
      if (is_array($normal)) {
        $internal[] = $path;
      }
      else {
        $normal = drupal_get_normal_path($path_nobase);
        $internal[] = $normal;
      }
    }
  }
  $flushed = expire_cache_derivative($internal);
}

/**
 * Callback for expire-node drush command.
 * @param string $nids a space separated list of paths.
 */
function drush_expire_nid() {
  $nids = drush_get_arguments();
  unset($nids[0]);
  foreach ($nids as $nid) {
    if (is_numeric($nid)) {
      $node = node_load($nid);
      expire_node($node);
    }
  }
}
