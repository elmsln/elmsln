<?php

/**
 * @file
 * Common drush functions for the print submodules.
 */

/**
 * Download and extract the lib.
 *
 * @param string $library
 *   Library to download.
 * @param string $url
 *   URL of the file to download.
 */
function _print_drush_download_lib($library, $url) {
  $path = drush_get_option('path');
  if (empty($path)) {
    $path = drush_get_context('DRUSH_DRUPAL_ROOT') . '/sites/all/libraries/' . $library;
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Chdir to the download location.
  $olddir = getcwd();
  drush_op('chdir', $path);

  // Warn about an existing dir.
  if (is_dir($library)) {
    drush_log(dt('An existing @library was overwritten at @path', array('@library' => $library, '@path' => $path . '/' . $library)), 'notice');
  }

  if (preg_match('!api.github.com/repos/.*/releases/latest!', $url)) {
    $url = _print_drush_github_latest_url($url);
  }

  // Download the archive.
  $filename = _print_drush_download_file($url);
  if ($filename) {
    $extract_ret = _print_drush_download_extract($filename);
    if ($extract_ret) {
      // Remove the archive.
      drush_op('unlink', $filename);
      drush_log(dt('@file has been downloaded and extracted in @path', array('@file' => $filename, '@path' => $path)), 'success');
    }
    else {
      drush_log(dt('@file has been downloaded to @path, but extract failed. Check that you have the necessary program installed, and if necessary extract it manually.',
                array('@file' => $filename, '@path' => $path)), 'warning');
    }
  }
  else {
    drush_log(dt('Drush was unable to download @library to @path', array('@library' => $library, '@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  drush_op('chdir', $olddir);
}

/**
 * Get filename of latest from github.
 *
 * @param string $github_url
 *   The github URL to the latest project release.
 *
 * @return string
 *   The URL to the latest file release.
 */
function _print_drush_github_latest_url($github_url) {
  $filename = _print_drush_download_file($github_url);
  $contents = file_get_contents($filename);
  drush_op('unlink', $filename);
  $json = json_decode($contents);
  if (isset($json->assets[0])) {
    $download_url = $json->assets[0]->browser_download_url;
  }
  else {
    // Try the zipball_url.
    $download_url = $json->zipball_url;
  }

  return $download_url;
}

/**
 * Download a file using wget or curl.
 *
 * Adapted from a function in drush/includes/drush.inc to support 302 redirects.
 *
 * @param string $download_url
 *   The path to the file to download.
 *
 * @return string
 *   The filename that was downloaded, or NULL if the file could not be
 *   downloaded.
 */
function _print_drush_download_file($download_url) {
  if (!drush_get_context('DRUSH_SIMULATE')) {
    $wget_ret = drush_shell_exec("wget -nv --content-disposition %s", $download_url);
    if ($wget_ret) {
      // Get the filename of the saved file from the output.
      $wget_out = explode('"', array_shift(drush_shell_exec_output()));
      $filename = $wget_out[1];
    }
    else {
      $tempnam = uniqid('print_drush_');

      $curl_ret = drush_shell_exec("curl -s -L -o %s %s -w '%%{url_effective}'", $tempnam, $download_url);
      if ($curl_ret) {
        // File was downloaded with the temporary name.
        // Find the effective name.
        $filename = explode('/', array_shift(drush_shell_exec_output()));
        $filename = array_pop($filename);

        // Rename file from tempname to effective name.
        if (!drush_op('rename', $tempnam, './' . $filename)) {
          $filename = $tempnam;
        }
      }
      else {
        $filename = FALSE;
      }
    }
  }
  else {
    $filename = basename($download_url);
  }

  return $filename;
}

/**
 * Helper to extract the downloaded zip/tar archive.
 *
 * @param string $filename
 *   Filename of the file to extract.
 *
 * @return bool
 *   TRUE on success, FALSE on failure
 */
function _print_drush_download_extract($filename) {
  $arch_ret = FALSE;

  if (drush_op('is_file', $filename)) {
    $mime_type = drush_op('mime_content_type', $filename);
    switch ($mime_type) {
      case 1:
        $arch_ret = TRUE;
        break;

      case 'application/zip':
        // Decompress the zip archive.
        $arch_ret = drush_shell_exec('unzip -qq -o %s', $filename);
        // ZIP archives usually get the access rights wrong.
        drush_log(dt('@filename is a Zip file. Check the access permissions of the extracted files.', array('@filename' => $filename)), 'warning');
        break;

      case 'application/x-gzip':
        // Decompress the tar gz archive.
        $arch_ret = drush_shell_exec('tar xzf %s', $filename);
        break;

      case 'application/x-bzip2':
        // Decompress the tar bz2 archive.
        $arch_ret = drush_shell_exec('tar xjf %s', $filename);
        break;

      case 'application/x-xz':
        // Decompress the tar xz archive.
        $arch_ret = drush_shell_exec('tar xJf %s', $filename);
        break;

      default:
        drush_log(dt('Unknown MIME type: @type', array('@type' => $mime_type)), 'error');
    }
  }
  else {
    drush_log(dt('@filename not found.', array('@filename' => $filename)), 'error');
  }

  return $arch_ret;
}
