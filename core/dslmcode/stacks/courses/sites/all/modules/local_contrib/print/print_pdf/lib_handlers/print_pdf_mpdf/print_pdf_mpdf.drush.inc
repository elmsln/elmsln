<?php

/**
 * @file
 * Provides drush integration for print_pdf_mpdf module PDF libraries download.
 */

/**
 * The PDF project download URL.
 */
// URI to the the latest mpdf version.
define('MPDF_DOWNLOAD_URI', 'https://api.github.com/repos/mpdf/mpdf/releases/latest');

/**
 * Implements hook_drush_command().
 */
function print_pdf_mpdf_drush_pdf_libs_alter(&$pdf_libs) {
  $pdf_libs['mpdf'] = array(
    'callback' => '_print_pdf_mpdf_drush_download_url',
  );
}

/**
 * Discover the correct URL of the package to download.
 *
 * @return string
 *   URL of the file to download, FALSE if not known
 */
function _print_pdf_mpdf_drush_download_url() {
  return MPDF_DOWNLOAD_URI;
}
