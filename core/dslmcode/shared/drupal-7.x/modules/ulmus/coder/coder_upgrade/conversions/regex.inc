<?php
/**
 * @file
 * Miscellaneous conversion routine file for the coder_upgrade module.
 * These routines upgrade text using simple regular expressions.
 *
 * The functions in this conversion routine file correspond to topics in the
 * category roadmap at http://drupal.org/node/394070 that are marked with a
 * green check mark in the Upgrade column.
 *
 * Copyright 2008-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * The upgrades to these items are documented at the following urls.
 *
 * System
 * http://drupal.org/node/224333#moved_statistics_settings
 *
 *
 * Permissions and Access
 * http://drupal.org/node/224333#moved_statistics_settings (DUP System)
 * http://drupal.org/node/224333#php_permissions
 *
 *
 * Menu
 * http://drupal.org/node/224333#admin_path_changes
 *
 *
 * Blocks
 * http://drupal.org/node/224333#block_tables_renamed
 * http://drupal.org/node/224333#custom_block
 *
 *
 * Input Sanitization and Input Formats
 * http://drupal.org/node/224333#filter_urls
 *
 *
 * Taxonomy
 * http://drupal.org/node/224333#taxonomy_tables
 *
 *
 * Form API
 * http://drupal.org/node/224333#fapi_changes
 *
 *
 * File API
 * http://drupal.org/node/224333#remove_FILE_STATUS_TEMPORARY
 *
 *
 * Miscellaneous
 * http://drupal.org/node/224333#watchdog_emerg
 *
 * @param string $file
 *   The text of the file to convert.
 */

/**
 * Implements hook_upgrade_regex_alter().
 *
 * Upgrades text using simple regular expressions.
 */
function coder_upgrade_upgrade_regex_alter(&$file) {
  cdp("inside " . __FUNCTION__);
  $hook = 'regex_simple_changes';
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  coder_upgrade_upgrade_admin_path_changes($from, $to);
  // TODO Intend to do all of these when converting db_query calls.
  coder_upgrade_upgrade_database_tables($from, $to);

  // Replace "use PHP for block visibility" with "use PHP for settings."
  $from[] = '/(\'|")use PHP for block visibility(\'|")/';
  $to[] = "$1use PHP for settings$1";

  // FILE_STATUS_TEMPORARY has been removed.
  $from[] = "/FILE_STATUS_TEMPORARY/";
  $to[] = "~FILE_STATUS_PERMANENT";

  // Renamed WATCHDOG_EMERG to WATCHDOG_EMERGENCY.
  $from[] = '@WATCHDOG_EMERG([^\w])@';
  $to[] = 'WATCHDOG_EMERGENCY$1';

  // $form['#redirect'] and $_REQUEST['destination'] are no longer supported.
  $from[] = '/\$form\[[\'"]#redirect[\'"]\]/';
  $to[] = '$form_state[\'#redirect\']';
  $from[] = '/\$_REQUEST\[[\'"]destination[\'"]\]/';
  $to[] = '$_GET[\'destination\']';

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}

/**
 * Upgrades admin paths.
 *
 * http://drupal.org/node/224333#admin_path_changes
 * http://drupal.org/node/224333#clean_urls_search_paths
 */
function coder_upgrade_upgrade_admin_path_changes(&$from, &$to) {
  $path_conversions = array(
    'admin/reports/settings' => 'admin/config/system/statistics',
    'admin/settings/filters' => 'admin/config/content/filter',
    'admin/build/modules' => 'admin/modules',
    'admin/build/themes' => 'admin/appearance',
    'admin/build/path' => 'admin/config/search/path',
    'admin/content/types' => 'admin/structure/types',
    'admin/content/taxonomy' => 'admin/structure/taxonomy',
    'admin/content/forum' => 'admin/structure/forum',
    'admin/build/testing' => 'admin/config/development/testing',
    'admin/settings/site-maintenance' => 'admin/config/development/maintenance',
    'admin/settings/performance' => 'admin/config/development/performance',
    'admin/settings/filters' => 'admin/config/content/formats',
    'admin/settings/search' => 'admin/config/search/settings',
    'admin/settings/clean-urls' => 'admin/config/search/clean-urls',
    'admin/settings/image' => 'admin/config/media/image',
    'admin/settings' => 'admin/config',
    'admin/build' => 'admin/structure',
  );

  foreach ($path_conversions as $old_path => $new_path) {
    $from[] = "@(['\"])$old_path(/?.*?)(['\"])@";
    $to[] = "$1$new_path$2$1";
  }
}

/**
 * Upgrades database tables.
 */
function coder_upgrade_upgrade_database_tables(&$from, &$to) {
  $table_conversion = array(
    'box' => 'custom_block', // TODO Is this an error?
    'boxes' => 'block_custom',
    'blocks' => 'block',
    'blocks_roles' => 'block_role',
  );
  foreach ($table_conversion as $old_table => $new_table) {
    $from[] = '/\{' . $old_table . '\}/i';
    $to[] = '{' . $new_table . '}';
  }

  // http://drupal.org/node/224333#taxonomy_tables
  // This expression format is more compact than above.
  $from[] = '@({|\'|")(term_data|term_hierarchy|term_node|term_relation|term_synonym|vocabulary)(}|\'|")@';
  $to[] = "$1taxonomy_$2$3";
  $from[] = '@({|\'|")(vocabulary_node_type)s(}|\'|")@';
  $to[] = "$1taxonomy_$2$3";
}

/**
 * Implements hook_upgrade_regex_info_alter().
 *
 * Alters the text of a code file using regular expressions.
 *
 * Module Info / Install
 * http://drupal.org/node/224333#info_core_7 (this anchor does not exist on the chronological page)
 *
 * @param string $file
 *   The text of the file to convert.
 */
function coder_upgrade_upgrade_regex_info_alter(&$file) {
  cdp("inside " . __FUNCTION__);
  $hook = 'info_file';
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  // Info file should specify core = 7.x.
  $from[] = '@^core\s+=\s+.*?$@m';
  $to[] = 'core = 7.x';

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}
