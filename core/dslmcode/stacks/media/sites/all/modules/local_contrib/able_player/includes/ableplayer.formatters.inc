<?php

/**
 * @file
 * Formatter settings for Able Player file display.
 */

/**
 * Implements hook_file_formatter_info().
 */
function ableplayer_file_formatter_info() {
  module_load_include('inc', 'ableplayer', 'includes/ableplayer');

  $formatters = array();

  $formatters['ableplayer'] = array(
    'label' => t('Able Player'),
    'description' => t(
      'Render an audio or video file with Able Player.'),
    'file types' => array(ABLEPLAYER_BUNDLE_AUDIO, ABLEPLAYER_BUNDLE_VIDEO),
    'mime types' => ableplayer_mimetypes(),
    'default settings' => ableplayer_default_settings(),
    'view callback' => 'ableplayer_file_formatter_ableplayer_view',
    'settings callback' => 'ableplayer_file_formatter_ableplayer_settings',
  );

  return $formatters;
}

/**
 * Implements hook_file_formatter_FORMATTER_view().
 *
 * This is a recommended callback naming scheme, not a true hook function.
 */
function ableplayer_file_formatter_ableplayer_view($file, $display, $langcode) {
  module_load_include('inc', 'ableplayer', 'includes/ableplayer');

  $tracks = array();

  switch ($file->filemime) {

    case ABLEPLAYER_BUNDLE_AUDIO . '/' . ABLEPLAYER_MIME_MPEG:
    case ABLEPLAYER_BUNDLE_AUDIO . '/' . ABLEPLAYER_MIME_OGG:
    case ABLEPLAYER_BUNDLE_VIDEO . '/' . ABLEPLAYER_MIME_MP4:
    case ABLEPLAYER_BUNDLE_VIDEO . '/' . ABLEPLAYER_MIME_WEBM:
      $uri = file_create_url($file->uri);

      $transcript_items = field_get_items('file', $file, 'ableplayer_transcript');
      $tracks['transcripts'] = ($transcript_items) ?
        ableplayer_build_track_list($transcript_items) : array();

      $description_items = field_get_items('file', $file, 'ableplayer_description');
      $tracks['descriptions'] = ($description_items) ?
        ableplayer_build_track_list($description_items) : array();

      $chapters_items = field_get_items('file', $file, 'ableplayer_chapters');
      $tracks['chapters'] = ($chapters_items) ?
        ableplayer_build_track_list($chapters_items) : array();

      break;

    case ABLEPLAYER_BUNDLE_VIDEO . '/' . ABLEPLAYER_MIME_YOUTUBE:
      $uri = $file->uri;

      break;

  }

  $element = array(
    '#theme' => 'ableplayer',
    '#id' => $file->fid,
    '#uri' => $uri,
    '#mimetype' => $file->filemime,
    '#tracks' => $tracks,
    '#options' => ableplayer_set_view_settings($file, $display, $langcode),
    '#attached' => ableplayer_attach(),
  );

  return $element;
}

/**
 * Implements hook_file_formatter_FORMATTER_settings().
 *
 * This is a recommended callback naming scheme, not a true hook function.
 */
function ableplayer_file_formatter_ableplayer_settings($form, &$form_state, $settings) {
  $element = array();

  $element['width'] = array(
    '#title' => t('Width'),
    '#type' => 'textfield',
    '#type' => 'textfield',
    '#default_value' => $settings['width'],
    '#description' => t(
      'Width of the media player in pixels. For video, this value should reflect
      the target width of the media itself.'),
    '#size' => 6,
    '#required' => TRUE,
    '#element_validate' => array('ableplayer_validate_dimensions'),
  );

  $element['height'] = array(
    '#title' => t('Height'),
    '#type' => 'textfield',
    '#default_value' => $settings['height'],
    '#description' => t(
      'Height of the video in pixels. If not provided will default to 360.'),
    '#size' => 6,
    '#required' => TRUE,
    '#element_validate' => array('ableplayer_validate_dimensions'),
  );

  $element['preload'] = array(
    '#title' => t('Preload video'),
    '#type' => 'select',
    '#default_value' => $settings['preload'],
    '#options' => array(
      'metadata' => t('metadata'),
      'auto' => t('auto'),
    ),
    '#empty_value' => '',
    '#description' => t(
      'Tells the browser how much media to download when the page loads. If the
      media is the central focus of the web page, use preload=“auto”, which
      instructs the browser to download as much of the media as possible. If the
      media is not a central focus, downloading the entire media resource can
      consume valuable bandwidth, so preload=“metadata” would be a better
      option.'),
  );

  $element['autoplay'] = array(
    '#title' => t('Autoplay video on load'),
    '#type' => 'checkbox',
    '#default_value' => $settings['autoplay'],
    '#description' => t(
      'Play media automatically when page loads. For accessibility reasons, this
      is not recommended unless user is sure to expect media to automatically
      start. For example, autoplay could reasonably be used in conjunction with
      data-start-time in a media search application.'),
  );

  $element['show_now_playing'] = array(
    '#title' => t('Show now playing'),
    '#type' => 'checkbox',
    '#default_value' => $settings['show_now_playing'],
    '#description' => t(
      'include "Selected track" section within player; only applies when a
      playlist is present.'),
  );

  $element['use_transcript_button'] = array(
    '#title' => t('Disable transcript button'),
    '#type' => 'checkbox',
    '#default_value' => $settings['use_transcript_button'],
    '#description' => t(
      'Check to exclude transcript button from controller.  If using the
      data-transcript-div attribute to write the transcript to an external
      container (e.g., on a dedicated transcript page), you might not want users
      to be able to toggle the transcript off.'),
  );

  $element['lyrics_mode'] = array(
    '#title' => t('Lyrics mode'),
    '#type' => 'checkbox',
    '#default_value' => $settings['lyrics_mode'],
    '#description' => t(
      'Forces a line break between and within captions in the transcript.'),
  );

  $element['force_lang'] = array(
    '#title' => t('Force language'),
    '#type' => 'checkbox',
    '#default_value' => $settings['force_lang'],
    '#description' => t(
      "Force the player to use the value of data-lang as the player language.
      Otherwise, the player language will be set as follows, in order of
      precedence: 1) the language of the web page or user's web browser if
      either is known and if there is a matching translation file; 2) the value
      of data-lang if provided; 3) English."),
  );

  $element['volume'] = array(
    '#title' => t('Volume'),
    '#type' => 'textfield',
    '#default_value' => $settings['volume'],
    '#size' => 6,
    '#description' => t(
      'Set the default volume (0 to 1; default is 0.5 to avoid overpowering
      screen reader audio).'),
    '#element_validate' => array('ableplayer_validate_volume'),
  );

  $element['start_time'] = array(
    '#title' => t('Start time'),
    '#type' => 'textfield',
    '#default_value' => $settings['start_time'],
    '#size' => 6,
    '#description' => t(
      'Time at which you want the audio to start playing (in seconds).'),
  );

  $element['seek_interval'] = array(
    '#title' => t('Seek interval'),
    '#type' => 'textfield',
    '#default_value' => $settings['seek_interval'],
    '#size' => 6,
    '#description' => t(
      'Interval (in seconds) of forward and rewind buttons. By default, seek
      interval is calculated to be 1/10 of the duration of media.'),
  );

  $element['transcript_title'] = array(
    '#title' => t('Transcript title'),
    '#type' => 'textfield',
    '#default_value' => $settings['transcript_title'],
    '#size' => 18,
    '#description' => t('Override default transcript title (default is
    "Transcript", or "Lyrics" if the data-lyrics-mode attribute is present).'),
  );

  return $element;
}

/**
 * Validate that video dimensions are numbers or "auto".
 */
function ableplayer_validate_dimensions($element, &$form_state, $form) {
  $options = array(
    'options' => array(
      'min_range' => 0,
    ),
  );

  if (filter_var($element['#value'], FILTER_VALIDATE_INT, $options) === FALSE) {
    form_error($element, t(
      'The value entered for @dimension is invalid. Please insert a positive integer (pixels).',
      array('@dimension' => $element['#title'])));
  }
}

/**
 * Validate that the volume is a number between 0 and 1 inclusive.
 */
function ableplayer_validate_volume($element, &$form_state, $form) {
  if (!empty($element['#value'])) {
    if (!is_numeric($element['#value']) || $element['#value'] < 0 || $element['#value'] > 1) {
      form_error($element, t(
        'The value entered for @volume is invalid. Please insert a number between 0 and 1.',
        array('@volume' => $element['#title'])));
    }
  }
}

/**
 * Validate that the seek interval is a number.
 */
function ableplayer_validate_seek_interval($element, &$form_state, $form) {
  if (!empty($element['#value'])) {
    if (filter_var($element['#value'], FILTER_VALIDATE_FLOAT) === FALSE || $element['#value'] < 0) {
      form_error($element, t(
        'The value entered for @seek is invalid. Please insert a number (seconds).',
        array('@seek' => $element['#title'])));
    }
  }
}

/**
 * Validate that the start time setting is an integer and greater than 0.
 */
function ableplayer_validate_start_time($element, &$form_state, $form) {
  $options = array(
    'options' => array(
      'min_range' => 0,
    ),
  );

  if (!empty($element['#value'])) {
    if (filter_var($element['#value'], FILTER_VALIDATE_INT, $options) === FALSE) {
      form_error($element, t(
        'The value entered for @start is invalid. Please insert a positive integer (seconds).',
        array('@start' => $element['#title'])));
    }
  }
}
