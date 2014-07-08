<?php

/**
 * @file
 * drush integration for print_epub_phpepub module EPUB libraries download.
 */

/**
 * The EPUB project download URL
 */

// URI to the the latest PHPePub version.. Hardcoded version unfortunately
define('PHPEPUB_DOWNLOAD_URI', 'https://github.com/Grandt/PHPePub/tarball/2.04');

/**
 * Implements hook_drush_command().
 */
function print_epub_phpepub_drush_epub_libs_alter(&$epub_libs) {
  $epub_libs['phpepub'] = array(
    'callback' => '_print_epub_phpepub_drush_download_url',
  );
}

/**
 * Discover the correct URL of the package to download.
 *
 * @return string
 *   URL of the file to download, FALSE if not known
 */
function _print_epub_phpepub_drush_download_url() {
  return PHPEPUB_DOWNLOAD_URI;
}
