<?php

/**
 * @file
 * drush integration for print_epub module EPUB libraries download.
 */

/**
 * Implements hook_drush_command().
 */
function print_epub_drush_command() {
  $items = array();

  $epub_libs = array();
  drush_command_invoke_all_ref('drush_epub_libs_alter', $epub_libs);

  $items['print-epub-download'] = array(
    'description' => 'Download and extract a EPUB library.',
    'arguments' => array(
      'library' => dt('The EPUB library to download. Available choices: !libs.', array('!libs' => implode(', ', array_keys($epub_libs)))),
    ),
    'options' => array(
      'path' => dt('A path to the download folder. If omitted Drush will use the default location (@path).', array('@path' => 'sites/all/libraries')),
    ),
    'aliases' => array('epubdl'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT, // No site or config needed.
  );

  return $items;
}

/**
 * Implements of drush_hook_COMMAND_validate().
 */
function drush_print_epub_download_validate($library = NULL) {
  if (is_null($library)) {
    $epub_libs = array();
    drush_command_invoke_all_ref('drush_epub_libs_alter', $epub_libs);

    drush_set_error('DRUSH_EPUBDL_MISSING_ARG', dt("Usage: drush !cmd <library>\nWhere <library> is one of the following: !libs\n\nTry 'drush !cmd --help' for more information.", array('!cmd' => 'print-epub-download', '!libs' => implode(', ', array_keys($epub_libs)))));
  }
}

/**
 * Download and extract EPUB archive.
 *
 * @param string $library
 *   library to download
 */
function drush_print_epub_download($library) {
  $epub_libs = array();
  drush_command_invoke_all_ref('drush_epub_libs_alter', $epub_libs);

  if (isset($library) && isset($epub_libs[drupal_strtolower($library)])) {
    $func = $epub_libs[drupal_strtolower($library)]['callback'];

    $download_url = $func();
    if ($download_url) {
      _print_drush_download_lib($library, $download_url);
    }
  }
  else {
    drush_log(dt('Please specify a EPUB library. Available choices: !libs.', array('!libs' => implode(', ', array_keys($epub_libs)))), 'error');
  }
}
