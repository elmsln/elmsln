<?php

/**
 * @file
 * Per-page CDN integration statistics functionality.
 */

function cdn_touch_file_form($form, &$form_state) {
  // All arguments after the first two are in fact the different parts of the
  // file path that is being passed in.
  $additional_args = array_slice(func_get_args(), 2);
  $filepath = implode('/', $additional_args);

  // Store the page we should redirect to after the file has been touched, or
  // upon cancellation.
  if (!isset($form_state['storage']['redirect'])) {
    $form_state['storage']['redirect'] = (isset($_SERVER['HTTP_REFERER'])) ? $_SERVER['HTTP_REFERER'] : '<front>';
  }

  if (!file_exists($filepath)) {
    drupal_set_message(t('The file %filepath does not exist and thus could not be touched.', array('%filepath' => $filepath)), 'error');
    drupal_goto($form_state['storage']['redirect']);
  }
  else {
    $form_state['filepath'] = $filepath;
    return confirm_form(
      array(
        'filepath' => array(
          '#type'   => 'value',
          '#markup' => $filepath,
        ),
        'redirect' => array(
          '#type'   => 'value',
          '#markup' => $form_state['storage']['redirect'],
        ),
      ),
      t('Are you sure you want to touch %filepath?', array('%filepath' => $filepath)),
      $form_state['storage']['redirect'],
      t('This action cannot be undone, but is completely harmless. Touching a file merely means that its last modification date will be updated to \'right now\'.'),
      t('Touch file'),
      t('Cancel')
    );
  }
}

function cdn_touch_file_form_submit($form, &$form_state) {
  $filepath = $form_state['filepath'];
  if (touch(_cdn_get_absolute_path($filepath))) {
    drupal_set_message(t('Successfully touched %filepath.', array('%filepath' => $filepath)));
  }
  else {
    drupal_set_message(t('Failed to touch %filepath. Likely you do not have sufficient permissions.', array('%filepath' => $filepath)));
  }
  drupal_goto($form_state['storage']['redirect']);
}


//----------------------------------------------------------------------------
// Private functions.

/**
 * Collects per-page CDN integration statistics.
 *
 * @param $file
 *   The local file path.
 * @param $file_cdn_url
 *   The URL to the file on the CDN if it exists, FALSE otherwise.
 * @param $server
 *   The server the file exists on.
 * @param $time
 *   The time it took to get the current CDN URL.
 * @return
 *   Only if no parameters were passed: the collected statistics.
 */
function _cdn_devel_page_stats($file = FALSE, $file_cdn_url = FALSE, $server = FALSE, $time = FALSE) {
  static $files;
  static $file_count;
  static $cdn_file_count;
  static $synced_files_per_server_count;
  static $total_time;
  static $synced_files;
  static $unsynced_files;

  if (!isset($file_count)) {
    $files = array();
    $file_count = 0;
    $cdn_file_count = 0;
    $synced_files_per_server_count = array();
    $total_time = 0;
    $synced_files = array();
    $unsynced_files = array();
  }

  // If the function is called with parameters set, save the statistics. If no
  // parameters are passed, return the collected statistics.
  if ($file && !array_key_exists($file, $files)) {
    $files[$file] = TRUE;
    $file_count++;
    $total_time += $time;

    if ($file_cdn_url !== FALSE) {
      $cdn_file_count++;

      $synced_files[] = array(
        'file'          => $file,
        'absolute path' => _cdn_get_absolute_path($file),
        'cdn_url'       => $file_cdn_url,
        'server'        => ($server === FALSE) ? '' : $server,
      );

      // $server is only set in advanced mode.
      if ($server !== FALSE) {
        if (!array_key_exists($server, $synced_files_per_server_count)) {
          $synced_files_per_server_count[$server] = 0;
        }
        $synced_files_per_server_count[$server]++;
      }
    }
    else {
      $unsynced_files[] = $file;
    }
  }
  elseif (!$file) {
    return array(
      $file_count,
      $cdn_file_count,
      $synced_files_per_server_count,
      $total_time,
      $synced_files,
      $unsynced_files,
    );
  }
}

/**
 * Maps a file URI (or shipped file path) to an absolute path.
 *
 * @param string $uri
 *   A file URI or shipped file path.
 * @return string
 *   The absolute path.
 */
function _cdn_get_absolute_path($uri) {
  static $drupal_root_path;

  if (!isset($drupal_root_path)) {
    $drupal_root_path = dirname('.');
  }

  $absolute_path = '';
  if (file_uri_scheme($uri)) {
    if ($wrapper = file_stream_wrapper_get_instance_by_uri($uri)) {
      $absolute_path = $wrapper->realpath();
    }
  }
  else {
    $absolute_path = realpath($drupal_root_path . '/' . $uri);
  }
  return $absolute_path;
}
