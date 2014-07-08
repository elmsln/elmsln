<?php

/**
 * @file
 * drush integration for print_pdf_tcpdf module PDF libraries download.
 */

/**
 * The PDF project download URL
 */

// TCPDF is in sourceforge, and nicely provides a link to the latest version
define('TCPDF_DOWNLOAD_URI', 'http://sourceforge.net/projects/tcpdf/files/latest');

/**
 * Implements hook_drush_command().
 */
function print_pdf_tcpdf_drush_pdf_libs_alter(&$pdf_libs) {
  $pdf_libs['tcpdf'] = array(
    'callback' => '_print_pdf_tcpdf_drush_download_url',
  );
}

/**
 * Discover the correct URL of the package to download.
 *
 * @return string
 *   URL of the file to download, FALSE if not known
 */
function _print_pdf_tcpdf_drush_download_url() {
  return TCPDF_DOWNLOAD_URI;
}
