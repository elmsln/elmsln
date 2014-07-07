<?php
/**
 * @file
 * This file holds the logic for drush commands of
 * the display cache module.
 */

/**
 * Implements hook_drush_cache_clear().
 */
function display_cache_drush_cache_clear(&$type) {
  $type = $type + array('display-cache' => '_display_cache_clear_cache');
}
