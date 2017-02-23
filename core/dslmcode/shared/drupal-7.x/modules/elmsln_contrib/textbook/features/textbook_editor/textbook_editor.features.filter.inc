<?php
/**
 * @file
 * textbook_editor.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function textbook_editor_filter_default_formats() {
  $formats = array();

  // Exported format: Textbook.
  $formats['textbook_editor'] = array(
    'format' => 'textbook_editor',
    'name' => 'Textbook',
    'cache' => 0,
    'status' => 1,
    'weight' => -10,
    'filters' => array(
      'video_filter' => array(
        'weight' => -48,
        'status' => 1,
        'settings' => array(
          'video_filter_width' => 854,
          'video_filter_height' => 480,
          'video_filter_autoplay' => 0,
          'video_filter_related' => 0,
          'video_filter_html5' => 1,
        ),
      ),
      'filter_htmlcorrector' => array(
        'weight' => -45,
        'status' => 1,
        'settings' => array(),
      ),
      'ckeditor_link_filter' => array(
        'weight' => -44,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
