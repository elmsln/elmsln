<?php

/**
 * @file
 * Generate a EPUB for the print_epub module using the PHPePub library.
 *
 * @ingroup print
 */

/**
 * Find out the version of the PHPePub library.
 *
 * @param string $epub_tool
 *   Filename of the tool to be analysed.
 *
 * @return string
 *   version number of the library
 */
function _print_epub_phpepub_version($epub_tool) {
  if (file_exists(DRUPAL_ROOT . '/' . $epub_tool)) {
    include_once DRUPAL_ROOT . '/' . $epub_tool;

    $phpepub_version_4_plus = strpos($epub_tool, 'autoload.php') !== FALSE;
    if ($phpepub_version_4_plus) {
      return \PHPePub\Core\EPub::VERSION;
    }
    else {
      if (class_exists('EPub')) {
        return EPub::VERSION;
      }
    }
  }

  return 'unknown';
}

/**
 * Implements hook_print_epub_available_libs_alter().
 */
function print_epub_phpepub_print_epub_available_libs_alter(&$epub_tools) {
  module_load_include('inc', 'print', 'includes/print');
  $tools = _print_scan_libs('phpepub', '!^EPub.php$!');

  foreach ($tools as $tool) {
    $epub_tools['print_epub_phpepub|' . $tool] = 'PHPePub (' . dirname($tool) . ')';
  }

  // PHPePub >= 4.0 uses a composer autoloader.
  $tools = _print_scan_libs('phpepub', '!^autoload.php$!');
  foreach ($tools as $tool) {
    if (preg_match('!PHPePub.*?/vendor/autoload.php$!i', $tool)) {
      $epub_tools['print_epub_phpepub|' . $tool] = 'PHPePub (' . dirname(dirname($tool)) . ')';
    }
  }
}
