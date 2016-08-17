<?php

/**
 * @file
 * Helper functions for the Able Player module.
 *
 * These functions are intended to be used internally by Able Player and its
 * submodules. This file should neither be loaded in global scope nor relied
 * upon by third-party code.
 */

/**
 * Able Player libraries load render array.
 *
 * Return code to attach the Able Player library to an element using the
 * Libraries API in the '#attached' property of render arrays. With the
 * exception of 'js' and 'css', which are special cases, keys in the '#attached'
 * element of render arrays are treated as function callabacks; the value should
 * be an array of arguments to pass to the callback.
 *
 * Usage:
 *
 *   $element['#attached'] = ableplayer_attach();
 *
 * @return array
 *   Render array to pass to libraries_load.
 */
function ableplayer_attach() {
  $attached = array();
  $compression_level = variable_get('ableplayer_compression_level', 1);

  if ($compression_level === '0') {
    $ableplayer = array('ableplayer', 'source');
  }
  else {
    $ableplayer = array('ableplayer');
  }

  $attached['libraries_load'][] = $ableplayer;
  $attached['css'][] = drupal_get_path('module', 'ableplayer') . '/css/ableplayer.override.css';

  return $attached;
}

/**
 * Get data for populating track elements for Able Player.
 *
 * Given a list of transcript file entities, look up their language in the core
 * language list to get the native language label. This allows the srclang and
 * label attributes to be set on the track element of the field formatter
 * output, which Able Player uses to display a select list of available
 * transcript languages.
 *
 * @param array $track_items
 *   Array of files associated as tracks with a parent file.
 *
 * @return array
 *   Hash of transcript information
 *     - 'code' the ISO language code as used internally by Drupal
 *     - 'label' the native language name as used internally by Drupal
 *     - 'uri' the path to the transcript file
 */
function ableplayer_build_track_list(array $track_items) {
  $tracks = array();
  $entity_translation = module_exists('entity_translation');

  if ($entity_translation) {
    $languages = language_list();
  }

  foreach ($track_items as $item) {
    $code = '';
    $label = '';
    $uri = file_create_url($item['uri']);

    if ($entity_translation && array_key_exists('translations', $item)) {
      $code = $item['translations']->original;
      $label = $languages[$code]->native;
    }

    $tracks[] = array(
      'code' => $code,
      'label' => $label,
      'uri' => $uri,
    );
  }

  return $tracks;
}

/**
 * Able Player default player settings.
 *
 * @return array
 *   Able Player file formatter default settings.
 */
function ableplayer_default_settings() {
  return array(
    'width' => 480,
    'height' => 360,
    'autoplay' => FALSE,
    'preload' => FALSE,
    'show_now_playing' => FALSE,
    'use_transcript_button' => FALSE,
    'lyrics_mode' => FALSE,
    'force_lang' => FALSE,
    'volume' => 0.5,
    'start_time' => 0,
    'seek_interval' => FALSE,
    'transcript_title' => FALSE,
    'lang' => FALSE,
  );
}

/**
 * Helper function to return information about the Able Player installation.
 *
 * Files that are not found installed in the expected location are colletected
 * and returned.
 *
 * @return array
 *   Hash of status information.
 *     - 'error' indicates whether an error was detected via a boolean value.
 *     - 'version' is set to the detected version number of Able Player.
 *     - 'message' set if an error was detected.
 */
function ableplayer_installation_status() {
  $status = array();
  $version = NULL;
  $message = NULL;

  $ableplayer = libraries_detect('ableplayer');

  $files = array_keys(array_merge(
    $ableplayer['files']['js'],
    $ableplayer['files']['css']
  ));

  $missing_files = array();

  foreach ($files as $file) {
    $path = $ableplayer['library path'] . '/' . $file;

    if (!is_file($path) || !is_readable($path)) {
      $missing_files[$path] = t('The file %file was not found.', array('%file' => $path));
    }
  }

  if (!empty($missing_files)) {
    $message = trim(implode(' ', $missing_files));
  }
  elseif (!$ableplayer['installed']) {
    $message = $ableplayer['error message'];
  }
  else {
    $version = $ableplayer['version'];
  }

  $status['error'] = !empty($message);
  $status['version'] = $version;
  $status['message'] = $message;

  return $status;
}

/**
 * Function returns the complete list of mimetypes supported by Able Player.
 *
 * @return array
 *   Able Player supported mimetypes.
 */
function ableplayer_mimetypes() {
  return array(
    ABLEPLAYER_BUNDLE_AUDIO . '/' . ABLEPLAYER_MIME_MPEG,
    ABLEPLAYER_BUNDLE_AUDIO . '/' . ABLEPLAYER_MIME_OGG,
    ABLEPLAYER_BUNDLE_VIDEO . '/' . ABLEPLAYER_MIME_MP4,
    ABLEPLAYER_BUNDLE_VIDEO . '/' . ABLEPLAYER_MIME_WEBM,
  );
}

/**
 * Construct settings array for Able Player file formatter.
 *
 * Build the settings array from the configured values, or use the defaults.
 * The result will be used to configure the display of the Able Player file
 * formatter.
 *
 * @return array
 *   Able Player file formatter view settings.
 */
function ableplayer_set_view_settings($file, $display, $langcode) {
  $options = array();
  $entity_translation = module_exists('entity_translation');

  foreach (array_keys(ableplayer_default_settings()) as $setting) {
    $options[$setting] = isset($file->override[$setting]) ?
      $file->override[$setting] :
      $display['settings'][$setting];
  }

  if (empty($options['lang'])) {
    if ($entity_translation && property_exists($file, 'translations')) {
      $options['lang'] = $file->translations->original;
    }
    else {
      $options['lang'] = $langcode;
    }
  }

  return $options;
}
