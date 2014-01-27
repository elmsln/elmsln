<?php
/**
 * @file
 * Provides list of conversion routines.
 *
 * The functions in these conversion routine files correspond to the topics in
 * the category roadmap at http://drupal.org/node/394070 that are marked with
 * a green check mark in the Upgrade column.
 *
 * Copyright 2009-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Returns the list of upgrade sets from all modules.
 */
function _coder_upgrade_upgrades() {
  $upgrades = &drupal_static(__FUNCTION__);

  if (is_null($upgrades)) {
    $upgrades = module_invoke_all('upgrade_info');
  }
  return $upgrades;
}

/**
 * Implements hook_upgrade_info().
 */
function coder_upgrade_upgrade_info() {
  $format = array(
    'title' => t('Coding standards for 6.x and 7.x (parse and rewrite code files using the Grammar Parser) (it is recommended to run this routine before applying core API change routines so that the patch files accurately reflect the routines applied)'),
    'link' => 'http://drupal.org/coding-standards',
    'module' => 'grammar_parser',
    'files' => array(),
  );
  $upgrade = array(
    'title' => t('Core API changes from 6.x to 7.x (also includes coding standards changes from rewrite of code files using the Grammar Parser)'),
    'link' => 'http://drupal.org/node/394070',
    'module' => 'coder_upgrade',
    'files' => array(
      'conversions/begin.inc',
      'conversions/call.inc',
      'conversions/db.inc',
      'conversions/end.inc',
      'conversions/function.inc',
      'conversions/install.inc',
      'conversions/regex.inc',
      'conversions/tool.inc',
    ),
  );
  return array(
    'grammar_parser' => $format,
    'coder_upgrade' => $upgrade,
  );
}
