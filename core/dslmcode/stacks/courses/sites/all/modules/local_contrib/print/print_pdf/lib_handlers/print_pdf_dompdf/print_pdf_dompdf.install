<?php

/**
 * @file
 * Install, update and uninstall functions for the print_pdf_dompdf module.
 *
 * @ingroup print
 */

/**
 * Implements hook_uninstall().
 */
function print_pdf_dompdf_uninstall() {
  variable_del('print_pdf_dompdf_unicode');
  variable_del('print_pdf_dompdf_font_subsetting');
}

/**
 * Implements hook_requirements().
 */
function print_pdf_dompdf_requirements($phase) {
  $requirements = array();
  $t = get_t();
  switch ($phase) {
    // On status report page, make sure that a PDF generation tool is selected.
    case 'runtime':
      $print_pdf_pdf_tool = variable_get('print_pdf_pdf_tool', PRINT_PDF_PDF_TOOL_DEFAULT);
      $tool = explode('|', $print_pdf_pdf_tool);
      if (is_array($tool) && ($tool[0] === 'print_pdf_dompdf')) {
        $version = print_pdf_dompdf_pdf_tool_version($tool[1]);

        // If version is older than 0.6.2, raise warning, except if if is
        // disabled in config.
        if ((version_compare($version, '0.6.2', '<')) && !variable_get('print_pdf_dompdf_secure_06', FALSE)) {
          $requirements['print_pdf_dompdf'] = array(
            'title' => $t('dompdf library'),
            'value' => $t('Possibly insecure release'),
            'description' => $t("dompdf versions prior to 0.6.2 are insecure. Make sure you run at least dompdf 0.6.2. If you are running dompdf 0.6.2, set print_pdf_dompdf_secure_06 to TRUE in settings.php to hide this warning."),
            'severity' => REQUIREMENT_WARNING,
          );
        }
      }
      break;
  }
  return $requirements;
}
