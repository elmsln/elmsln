<?php

/**
 * @file
 * Default display configuration for the default file types.
 */

/**
 * Implements hook_file_default_displays().
 */
function file_entity_file_default_displays() {
  $file_displays = array();

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'audio__default__file_field_file_audio';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'controls' => 1,
    'controls_list' => array(
      'download' => 'download',
      'remote_playback' => 'remote_playback',
    ),
    'autoplay' => 0,
    'loop' => 0,
    'multiple_file_behavior' => 'tags',
  );
  $file_displays['audio__default__file_field_file_audio'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'audio__preview__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['audio__preview__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'audio__teaser__file_field_file_audio';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'controls' => 1,
    'controls_list' => array(
      'download' => 'download',
      'remote_playback' => 'remote_playback',
    ),
    'autoplay' => 0,
    'loop' => 0,
    'multiple_file_behavior' => 'tags',
  );
  $file_displays['audio__teaser__file_field_file_audio'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'document__default__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['document__default__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'document__preview__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['document__preview__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'document__teaser__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['document__teaser__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__default__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['image__default__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__preview__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['image__preview__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__teaser__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['image__teaser__file_field_file_default'] = $file_display;

  // Enhance the default image displays if the Image module is enabled.
  if (module_exists('image')) {
    // Images should be displayed as unstyled images by default.
    $file_display = new stdClass();
    $file_display->api_version = 1;
    $file_display->name = 'image__default__file_field_image';
    $file_display->weight = 48;
    $file_display->status = TRUE;
    $file_display->settings = array(
      'image_style' => '',
      'image_link' => '',
    );
    $file_displays['image__default__file_field_image'] = $file_display;

    // Image previews should be displayed as image thumbnails by default.
    $file_display = new stdClass();
    $file_display->api_version = 1;
    $file_display->name = 'image__preview__file_field_image';
    $file_display->weight = 48;
    $file_display->status = TRUE;
    $file_display->settings = array(
      'image_style' => 'thumbnail',
      'image_link' => '',
    );
    $file_displays['image__preview__file_field_image'] = $file_display;

    // Image teasers should be displayed as medium images by default.
    $file_display = new stdClass();
    $file_display->api_version = 1;
    $file_display->name = 'image__teaser__file_field_image';
    $file_display->weight = 48;
    $file_display->status = TRUE;
    $file_display->settings = array(
      'image_style' => 'medium',
      'image_link' => 'content',
    );
    $file_displays['image__teaser__file_field_image'] = $file_display;
  }

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__default__file_field_file_video';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'controls' => 1,
    'controls_list' => array(
      'fullscreen' => 'fullscreen',
      'download' => 'download',
      'remote_playback' => 'remote_playback',
    ),
    'autoplay' => 0,
    'playsinline' => 0,
    'loop' => 0,
    'width' => '',
    'height' => '',
    'multiple_file_behavior' => 'tags',
  );
  $file_displays['video__default__file_field_file_video'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__preview__file_field_file_default';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = '';
  $file_displays['video__preview__file_field_file_default'] = $file_display;

  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__teaser__file_field_file_video';
  $file_display->weight = 50;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'controls' => 1,
    'controls_list' => array(
      'fullscreen' => 'fullscreen',
      'download' => 'download',
      'remote_playback' => 'remote_playback',
    ),
    'autoplay' => 0,
    'playsinline' => 0,
    'loop' => 0,
    'width' => '',
    'height' => '',
    'multiple_file_behavior' => 'tags',
  );
  $file_displays['video__teaser__file_field_file_video'] = $file_display;

  return $file_displays;
}
