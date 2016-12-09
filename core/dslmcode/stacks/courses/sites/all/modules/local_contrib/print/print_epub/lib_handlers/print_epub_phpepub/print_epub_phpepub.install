<?php

/**
 * @file
 * Install, update and uninstall functions for the print_epub_phpepub module.
 *
 * @ingroup print
 */

/**
 * Implements hook_requirements().
 */
function print_epub_phpepub_requirements($phase) {
  $requirements = array();
  $t = get_t();
  switch ($phase) {
    // At runtime, make sure that a EPUB generation tool is selected.
    case 'runtime':
      $print_epub_epub_tool = variable_get('print_epub_epub_tool', PRINT_EPUB_EPUB_TOOL_DEFAULT);

      if (!empty($print_epub_epub_tool)) {
        $tool = explode('|', $print_epub_epub_tool);

        if (is_file($tool[1]) && is_readable($tool[1])) {
          if (basename($tool[1]) == 'EPub.php') {
            $version = _print_epub_phpepub_version($tool[1]);

            $requirements['print_epub_tool_version'] = array(
              'title' => $t('Printer, email and EPUB versions - EPUB generation library'),
              'value' => $t('PHPePub') . ' ' . $version,
            );
          }
        }
      }
      break;
  }
  return $requirements;
}
