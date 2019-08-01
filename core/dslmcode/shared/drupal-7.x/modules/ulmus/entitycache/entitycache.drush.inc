<?php

/**
 * @file
 * Drush hooks for integration with entitycache.
 */

/**
 * Implements hook_drush_cache_clear().
 */
function entitycache_drush_cache_clear(&$types) {
  $entities = entity_get_info();
  foreach ($entities as $type => $info) {
    if (isset($info['entity cache']) && $info['entity cache']) {
      // You can't pass paramters to the callbacks in $types, so create an
      // anonymous function for each specific bin.
      $lamdba = create_function('', "return cache_clear_all('*', 'cache_entity_" . $type . "', TRUE);");
      $types['entitycache-' . str_replace('_', '-', $type)] = $lamdba;
    }
  }
}
