<?php

/**
 * @file
 * Provides drush integration for print_pdf_wkhtmltopdf module.
 */

/**
 * The PDF project download URL.
 */
// Since wkhtmltopdf is a binary, a different URL is required for each platform.
define('WKHTMLTOPDF_LNX64_DOWNLOAD_URI', 'http://download.gna.org/wkhtmltopdf/0.12/0.12.3/wkhtmltox-0.12.3_linux-generic-amd64.tar.xz');
define('WKHTMLTOPDF_LNX32_DOWNLOAD_URI', 'http://download.gna.org/wkhtmltopdf/0.12/0.12.3/wkhtmltox-0.12.3_linux-generic-i386.tar.xz');
define('WKHTMLTOPDF_WIN64_DOWNLOAD_URI', 'http://download.gna.org/wkhtmltopdf/0.12/0.12.3.2/wkhtmltox-0.12.3.2_msvc2013-win64.exe');
define('WKHTMLTOPDF_WIN32_DOWNLOAD_URI', 'http://download.gna.org/wkhtmltopdf/0.12/0.12.3.2/wkhtmltox-0.12.3.2_msvc2013-win32.exe');
define('WKHTMLTOPDF_OSX64_DOWNLOAD_URI', 'http://download.gna.org/wkhtmltopdf/0.12/0.12.3/wkhtmltox-0.12.3_osx-cocoa-x86-64.pkg');
define('WKHTMLTOPDF_OSX32_DOWNLOAD_URI', 'http://download.gna.org/wkhtmltopdf/0.12/0.12.3/wkhtmltox-0.12.3_osx-carbon-i386.pkg');

/**
 * Implements hook_drush_command().
 */
function print_pdf_wkhtmltopdf_drush_pdf_libs_alter(&$pdf_libs) {
  $pdf_libs['wkhtmltopdf'] = array(
    'callback' => '_print_pdf_wkhtmltopdf_drush_download_url',
  );
}

/**
 * Discover the correct URL of the package to download.
 *
 * @return string
 *   URL of the file to download, FALSE if not known
 */
function _print_pdf_wkhtmltopdf_drush_download_url() {
  $ret = FALSE;

  switch (drupal_substr(php_uname('s'), 0, 3)) {
    case 'Lin':
      $ret = (php_uname('m') == 'x86_64') ? WKHTMLTOPDF_LNX64_DOWNLOAD_URI : WKHTMLTOPDF_LNX32_DOWNLOAD_URI;
      break;

    case 'Win':
      $ret = WKHTMLTOPDF_WIN32_DOWNLOAD_URI;
      break;

    case 'Dar':
      $ret = (php_uname('m') == 'x86_64') ? WKHTMLTOPDF_OSX64_DOWNLOAD_URI : WKHTMLTOPDF_OSX32_DOWNLOAD_URI;
      break;

    default:
      drush_log(dt('wkhtmltopdf is not supported in this system, please choose another library.'), 'error');
      break;
  }

  return $ret;
}
