<?php
/**
 * @file
 * Provides menu items.
 *
 * Copyright 2008-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Implements hook_menu().
 */
function _coder_upgrade_menu() {
  // Conversion items.
  $items['admin/config/development/coder/upgrade'] = array(
    'title' => 'Upgrade',
    'description' => 'Convert module code from version 6.x to 7.x.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('coder_upgrade_conversions_form'),
    'access arguments' => array('administer code conversions'),
    'type' => MENU_LOCAL_TASK,
    'file' => 'includes/conversion.inc',
  );

  // Run items.
  $items['admin/config/development/coder/upgrade/run'] = array(
    'title' => 'Run',
    'type' => MENU_DEFAULT_LOCAL_TASK,
  );

  // Settings related items.
  $items['admin/config/development/coder/upgrade/settings'] = array(
    'title' => 'Settings',
    'description' => 'Configure the module conversion suite.',
    'page callback' => 'drupal_get_form',
    'page arguments' => array('coder_upgrade_settings_form'),
    'access arguments' => array('administer site configuration'),
    'type' => MENU_LOCAL_TASK,
    'file' => 'includes/settings.inc',
  );

  // Patch files.
  $items['files/coder_upgrade/patch/%'] = array(
    'title' => 'Patches',
    'description' => 'Display patch file.',
    'page callback' => 'coder_upgrade_patch_display',
    'page arguments' => array(3),
    'access arguments' => array('administer code conversions'),
    'type' => MENU_CALLBACK,
    'file' => 'includes/conversion.inc',
  );

  return $items;
}
