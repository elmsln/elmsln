<?php

/**
 * @file
 * Drush commands for AdvAgg JS minification.
 */

/**
 * @addtogroup 3rd_party_hooks
 * @{
 */

/**
 * Implements hook_drush_help().
 */
function advagg_js_compress_drush_help($command) {
  switch ($command) {
    case 'drush:advagg-jsmin':
      return dt('Run js minification for all js files.');

  }
}

/**
 * Implements hook_drush_command().
 */
function advagg_js_compress_drush_command() {
  $items = array();
  $items['advagg-js-compress'] = array(
    'callback' => 'drush_advagg_js_compress',
    'description' => dt('Run the advagg cron hook.'),
    'core' => array('7+'),
    'arguments' => array(
      'filename' => 'all will do all files, or specify the filename to target that file.',
    ),
    'examples' => array(
      'drush advagg-jsmin' => dt('Minify only the files that need to be done.'),
      'drush advagg-jsmin all' => dt('Minify all js files again.'),
      'drush advagg-jsmin misc/jquery.once.js' => dt('Minify the misc/jquery.once.js file.'),
    ),
    'aliases' => array('advagg-jsmin'),
  );

  return $items;
}

/**
 * @} End of "addtogroup 3rd_party_hooks".
 */

/**
 * Callback function for drush advagg-jsmin.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (advagg) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters.
 *
 * @param string $filename
 *   The filename to compress or all to redo all files.
 */
function drush_advagg_js_compress($filename = '') {
  // Get the redo list.
  list($list, $redo_list) = advagg_js_compress_all_js_files_list();

  // Handle special use cases.
  if (!empty($filename)) {
    // Do all.
    if (strtolower($filename) === 'all') {
      $redo_list = $list;
    }
    else {
      // Do a single file, search for it in the $list.
      $redo_list = array();
      foreach ($list as $values) {
        if ($values['data'] === $filename) {
          $redo_list = array($values);
          break;
        }
      }

      // Let user know if that file was not found.
      if (empty($redo_list)) {
        drush_log(dt('The file @filename was not found.', array(
          '@filename' => $filename,
        )), 'notice');
        return;
      }
    }
  }

  // Return if nothing to do.
  if (empty($redo_list)) {
    drush_log(dt('All of @total js files are already minified.', array(
      '@total' => count($list),
    )), 'ok');
    return;
  }

  // Let user know what will happen.
  drush_log(dt('A total of @redo out of @total js files will be minified.', array(
    '@redo' => count($redo_list),
    '@total' => count($list),
  )), 'ok');

  // Compress js files and cache.
  advagg_js_compress_redo_files($redo_list, 0, TRUE);
}
