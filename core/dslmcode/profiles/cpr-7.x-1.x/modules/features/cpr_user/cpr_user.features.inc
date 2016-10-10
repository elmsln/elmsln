<?php
/**
 * @file
 * cpr_user.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cpr_user_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function cpr_user_image_default_styles() {
  $styles = array();

  // Exported image style: people_user_profile.
  $styles['people_user_profile'] = array(
    'label' => 'people user profile',
    'effects' => array(
      1 => array(
        'name' => 'imagefield_focus_scale_and_crop',
        'data' => array(
          'width' => 300,
          'height' => 300,
          'strength' => 'high',
          '#imageinfo_cache_effect_callback' => 'imagefield_focus_scale_and_crop_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
