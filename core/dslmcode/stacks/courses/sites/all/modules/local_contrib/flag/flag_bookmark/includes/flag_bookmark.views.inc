<?php

/**
 * @file
 * Views plugins for the flag bookmark module.
 */

/**
 * Implements hook_views_plugins().
 */
function flag_bookmark_views_plugins() {
  return array(
    'argument validator' => array(
      'flag_bookmark_plugin_owner_perm' => array(
        'title' => t("Current user ID matches argument value"),
        'handler' => 'flag_bookmark_plugin_validate_user',
        'path' => drupal_get_path('module', 'flag_bookmark') . '/plugins',
      ),
    ),
  );
}
