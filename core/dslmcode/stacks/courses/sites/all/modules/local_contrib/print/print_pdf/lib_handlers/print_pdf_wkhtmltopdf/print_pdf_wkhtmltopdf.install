<?php

/**
 * @file
 * Install, update and uninstall functions for the print_pdf_wkhtmltopdf module.
 *
 * @ingroup print
 */

/**
 * Implements hook_uninstall().
 */
function print_pdf_wkhtmltopdf_uninstall() {
  variable_del('print_pdf_wkhtmltopdf_options');
  variable_del('print_pdf_wkhtmltopdf_use_input_file');
  variable_del('print_pdf_wkhtmltopdf_version');
}

/**
 * Implements hook_requirements().
 */
function print_pdf_wkhtmltopdf_requirements($phase) {
  $requirements = array();
  $t = get_t();
  switch ($phase) {
    // On status report page, make sure that a PDF generation tool is selected.
    case 'runtime':
      $print_pdf_pdf_tool = variable_get('print_pdf_pdf_tool', PRINT_PDF_PDF_TOOL_DEFAULT);
      if (!empty($print_pdf_pdf_tool)) {
        $tool = explode('|', $print_pdf_pdf_tool);

        if (is_file($tool[1]) && is_readable($tool[1])) {
          if (drupal_substr(basename($tool[1], '.exe'), 0, 11) == 'wkhtmltopdf') {
            if (function_exists('is_executable') && !is_executable($tool[1])) {
              $requirements['print_pdf_wkhtmltopdf'] = array(
                'title' => $t('wkhtmltopdf library'),
                'value' => $t('Non-executable permissions'),
                'description' => $t('You must modify the permissions of the wkhtmltopdf file (%file) to make it executable.', array('%file' => $tool[1])),
                'severity' => REQUIREMENT_ERROR,
              );
            }
          }
        }
      }
      break;
  }
  return $requirements;
}
