<?php
/**
 * @file
 * mooc_content_theming.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_content_theming_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function mooc_content_theming_image_default_styles() {
  $styles = array();

  // Exported image style: mooc_content_banner.
  $styles['mooc_content_banner'] = array(
    'label' => 'mooc_content_banner',
    'effects' => array(
      1 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 980,
          'height' => '',
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
