<?php

/**
 * @file
 * Provide drush integration for print_pdf module PDF libraries download.
 */

/**
 * Implements hook_drush_command().
 */
function print_pdf_drush_command() {
  $items = array();

  $pdf_libs = array();
  drush_command_invoke_all_ref('drush_pdf_libs_alter', $pdf_libs);

  $items['print-pdf-download'] = array(
    'description' => 'Download and extract a PDF library.',
    'arguments' => array(
      'library' => dt('The PDF library to download. Available choices: !libs.', array('!libs' => implode(', ', array_keys($pdf_libs)))),
    ),
    'options' => array(
      'path' => dt('A path to the download folder. If omitted Drush will use the default location (@path).', array('@path' => 'sites/all/libraries')),
    ),
    'aliases' => array('pdfdl'),
    // No site or config needed.
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
  );

  return $items;
}

/**
 * Implements drush_hook_COMMAND_validate().
 */
function drush_print_pdf_download_validate($library = NULL) {
  if (is_null($library)) {
    $pdf_libs = array();
    drush_command_invoke_all_ref('drush_pdf_libs_alter', $pdf_libs);

    drush_set_error('DRUSH_PDFDL_MISSING_ARG', dt("Usage: drush !cmd <library>\nWhere <library> is one of the following: !libs\n\nTry 'drush !cmd --help' for more information.", array(
      '!cmd' => 'print-pdf-download',
      '!libs' => implode(', ', array_keys($pdf_libs)),
    )));
  }
}

/**
 * Download and extract PDF archive.
 *
 * @param string $library
 *   Library to download.
 */
function drush_print_pdf_download($library) {
  $pdf_libs = array();
  drush_command_invoke_all_ref('drush_pdf_libs_alter', $pdf_libs);

  if (isset($library) && isset($pdf_libs[drupal_strtolower($library)])) {
    $func = $pdf_libs[drupal_strtolower($library)]['callback'];

    $download_url = $func();
    if ($download_url) {
      _print_drush_download_lib($library, $download_url);
    }
  }
  else {
    drush_log(dt('Please specify a PDF library. Available choices: !libs.', array('!libs' => implode(', ', array_keys($pdf_libs)))), 'error');
  }
}
