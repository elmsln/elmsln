<?php

/**
 * @file
 * Default display configuration for the default file types.
 */

/**
 * Implements hook_file_default_displays().
 */
function media_file_default_displays() {
  $file_displays = array();

  // Audio previews should be displayed using a large filetype icon.
  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'audio__preview__file_field_media_large_icon';
  $file_display->weight = 49;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'media_thumbnail',
  );
  $file_displays['audio__preview__file_field_media_large_icon'] = $file_display;

  // Document previews should be displayed using a large filetype icon.
  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'document__preview__file_field_media_large_icon';
  $file_display->weight = 49;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'media_thumbnail',
  );
  $file_displays['document__preview__file_field_media_large_icon'] = $file_display;

  // Image previews should be displayed using a large filetype icon.
  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'image__preview__file_field_media_large_icon';
  $file_display->weight = 49;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'media_thumbnail',
  );
  $file_displays['image__preview__file_field_media_large_icon'] = $file_display;

  // Video previews should be displayed using a large filetype icon.
  $file_display = new stdClass();
  $file_display->api_version = 1;
  $file_display->name = 'video__preview__file_field_media_large_icon';
  $file_display->weight = 49;
  $file_display->status = TRUE;
  $file_display->settings = array(
    'image_style' => 'media_thumbnail',
  );
  $file_displays['video__preview__file_field_media_large_icon'] = $file_display;

  return $file_displays;
}

/**
 * Implements hook_file_default_displays_alter().
 */
function media_file_default_displays_alter(&$file_displays) {
  // Image previews should be displayed using the media image style.
  if (isset($file_displays['image__preview__file_field_image'])) {
    $file_displays['image__preview__file_field_image']->settings['image_style'] = 'media_thumbnail';
  }
}
