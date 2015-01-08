<?php
/**
 * @file
 * harmony_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function harmony_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "taxonomy_display" && $api == "taxonomy_display") {
    return array("version" => "1");
  }
  if ($module == 'metatag' && $api == 'metatag') {
    return array('version' => 1);
  }
}

/**
 * Implements hook_views_api().
 */
function harmony_core_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function harmony_core_flag_default_flags() {
  $flags = array();
  // Exported flag: "Like".
  $flags['harmony_likes'] = array(
    'entity_type' => 'harmony_post',
    'title' => 'Like',
    'global' => 0,
    'types' => array(
      0 => 'harmony_post',
    ),
    'flag_short' => '<span class="count">([harmony_post:flag-harmony-likes-count])</span> <span class="text">Like</span>',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => '<span class="count">([harmony_post:flag-harmony-likes-count])</span> <span class="text">Unlike</span>',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'inline_reply' => 'inline_reply',
      'diff_standard' => 0,
      'token' => 0,
    ),
    'show_as_field' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_contextual_link' => FALSE,
    'module' => 'harmony_core',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}

/**
 * Implements hook_image_default_styles().
 */
function harmony_core_image_default_styles() {
  $styles = array();

  // Exported image style: harmony-20-20.
  $styles['harmony-20-20'] = array(
    'name' => 'harmony-20-20',
    'label' => 'Harmony - Scale and crop to 20px by 20px',
    'effects' => array(
      1 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 20,
          'height' => 20,
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: harmony-32-32.
  $styles['harmony-32-32'] = array(
    'name' => 'harmony-32-32',
    'label' => 'Harmony - Scale and crop to 32px by 32px',
    'effects' => array(
      2 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'image_scale_and_crop_effect',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 32,
          'height' => 32,
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
