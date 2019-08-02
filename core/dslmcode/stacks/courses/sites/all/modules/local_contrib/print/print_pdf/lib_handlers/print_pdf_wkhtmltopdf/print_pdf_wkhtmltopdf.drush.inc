<?php

/**
 * @file
 * Provides drush integration for print_pdf_wkhtmltopdf module.
 */

/**
 * The PDF project download URL.
 */
// Since wkhtmltopdf is a binary, a different URL is required for each platform.
define('WKHTMLTOPDF_LNX64_DOWNLOAD_URI', 'https://github.com/wkhtmltopdf/wkhtmltopdf/releases/download/0.12.4/wkhtmltox-0.12.4_linux-generic-amd64.tar.xz');
define('WKHTMLTOPDF_LNX32_DOWNLOAD_URI', 'https://github.com/wkhtmltopdf/wkhtmltopdf/releases/download/0.12.4/wkhtmltox-0.12.4_linux-generic-i386.tar.xz');
define('WKHTMLTOPDF_WIN64_DOWNLOAD_URI', 'https://downloads.wkhtmltopdf.org/0.12/0.12.5/wkhtmltox-0.12.5-1.msvc2015-win64.exe');
define('WKHTMLTOPDF_WIN32_DOWNLOAD_URI', 'https://downloads.wkhtmltopdf.org/0.12/0.12.5/wkhtmltox-0.12.5-1.msvc2015-win32.exe');
define('WKHTMLTOPDF_OSX64_DOWNLOAD_URI', 'https://downloads.wkhtmltopdf.org/0.12/0.12.5/wkhtmltox-0.12.5-1.macos-cocoa.pkg');
define('WKHTMLTOPDF_OSX32_DOWNLOAD_URI', 'https://downloads.wkhtmltopdf.org/0.12/0.12.5/wkhtmltox-0.12.5-1.macos-carbon.pkg');

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
      drush_log(dt('Please note that generic Linux builds are no longer being generated. See https://wkhtmltopdf.org/downloads.html.'), 'warning');
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
