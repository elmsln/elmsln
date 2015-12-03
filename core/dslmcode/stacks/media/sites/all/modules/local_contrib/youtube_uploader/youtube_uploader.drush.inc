<?php

/**
 * @file
 * Drush integration for Youtube Uploader.
 */

/**
 * The Youtube Uploader plugin URI.
 */
define('GOOGLE_API_CLIENT_PHP_URL', 'https://github.com/google/google-api-php-client/archive/master.zip');
define('GOOGLE_CORS_UPLOAD_URL', 'https://raw.githubusercontent.com/youtube/api-samples/master/javascript/cors_upload.js');

/**
 * Implements hook_drush_command().
 */
function youtube_uploader_drush_command() {
  $items = array();

  // The key in the $items array is the name of the command.
  $items['ytu-libraries'] = array(
    'callback' => 'drush_youtube_uploader_plugins',
    'description' => dt("Download the GOOGLE API and JS libraries."),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Google libraries. If omitted Drush will use the default location.'),
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 */
function youtube_uploader_drush_help($section) {
  switch ($section) {
    case 'drush:ytu-libraries':
      return dt("Downloads the Google libraries, default location is sites/all/libraries.");
  }
}

/**
 * Implements drush_hook_post_pm_enable().
 */
function drush_youtube_uploader_post_pm_enable() {
  if (drush_confirm(dt('Do you want to install the libraries (in sites/all/libraries) ?'))) {
    drush_youtube_uploader_plugins();
  }
}

/**
 * Command to download the Youtube Uploader plugins.
 */
function drush_youtube_uploader_plugins() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $init_path = $args[0];
  }
  else {
    $init_path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($init_path)) {
    drush_log($init_path, 'ok');
    drush_op('mkdir', $init_path, '0755', TRUE);
    drush_log(dt('Directory @path was created', array('@path' => $init_path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($init_path);

  // Download the php client.
  if ($filepath = drush_download_file(GOOGLE_API_CLIENT_PHP_URL)) {
    $filename = basename($filepath);
    $dirname = basename($filepath, '.zip');

    // Remove any existing google-api-php-client library directory.
    if (is_dir($dirname) || is_dir('google-api-php-client')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('google-api-php-client', TRUE);
      drush_log(dt('A existing google-api-php-client library was deleted from @path', array('@path' => $init_path)), 'notice');
    }

    // Decompress the archive.
    drush_tarball_extract($filename);
    drush_move_dir('google-api-php-client-master', 'google-api-php-client', TRUE);
    $dirname = 'google-api-php-client';
  }

  if (is_dir($dirname)) {
    drush_log(dt('google-api-php-client library has been installed in @path', array('@path' => $init_path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the google-api-php-client library to @path', array('@path' => $init_path)), 'error');
  }

  // Download the js file.
  $dirname = 'google-api-cors-upload';
  if (!is_dir($dirname)) {
    drush_op('mkdir', $dirname);
  }

  if ($filepath = drush_download_file(GOOGLE_CORS_UPLOAD_URL)) {
    $fc = file_get_contents($filepath);
    file_put_contents("google-api-cors-upload/cors_upload.js", $fc);
  }

  if (is_file('cors_upload.js')) {
    drush_log(dt('google-api-cors-upload library has been installed in @path', array('@path' => $init_path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the google-api-cors-upload library to @path', array('@path' => $init_path)), 'error');
  }

  chdir($olddir);

}
