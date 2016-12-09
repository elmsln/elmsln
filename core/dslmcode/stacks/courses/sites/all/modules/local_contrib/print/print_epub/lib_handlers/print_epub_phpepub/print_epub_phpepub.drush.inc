<?php

/**
 * @file
 * Provides drush integration for print_epub_phpepub module.
 */

/**
 * The EPUB project download URL.
 */

// URI to the the latest PHPePub version.
define('PHPEPUB_DOWNLOAD_URI', 'https://api.github.com/repos/Grandt/PHPePub/releases/latest');

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
