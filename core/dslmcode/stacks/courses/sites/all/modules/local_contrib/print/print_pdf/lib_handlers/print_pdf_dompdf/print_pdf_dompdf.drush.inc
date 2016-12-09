<?php

/**
 * @file
 * Provide drush integration for print_pdf_dompdf module PDF libraries download.
 */

/**
 * The PDF project download URL.
 */
// URI to the the latest dompdf version.
define('DOMPDF_DOWNLOAD_URI', 'https://api.github.com/repos/dompdf/dompdf/releases/latest');

/**
 * Implements hook_drush_command().
 */
function print_pdf_dompdf_drush_pdf_libs_alter(&$pdf_libs) {
  $pdf_libs['dompdf'] = array(
    'callback' => '_print_pdf_dompdf_drush_download_url',
  );
}

/**
 * Discover the correct URL of the package to download.
 *
 * @return string
 *   URL of the file to download, FALSE if not known
 */
function _print_pdf_dompdf_drush_download_url() {
  return DOMPDF_DOWNLOAD_URI;
}
