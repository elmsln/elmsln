<?php

/**
 * @file
 * Drush integration for default config.
 */

/**
 * Implements hook_drush_command().
 */
function defaultconfig_drush_command() {
  $items['defaultconfig-rebuild-all'] = array(
    'description' => "Rebuild all default configurations.",
    'drupal dependencies' => array('defaultconfig'),
    'aliases' => array('dra'),
  );
  return $items;
}

/**
 * Command callback for defaultconfig-rebuild-all.
 */
function drush_defaultconfig_rebuild_all() {
  if (drush_confirm(dt('All configuration will be rebuilt. Do you want to continue?'))) {
    defaultconfig_rebuild_all();
    drush_log(dt('All components have been rebuilt.'), 'ok');
  }
}