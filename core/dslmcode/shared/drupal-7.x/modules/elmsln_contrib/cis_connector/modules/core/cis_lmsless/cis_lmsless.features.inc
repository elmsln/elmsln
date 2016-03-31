<?php
/**
 * @file
 * cis_lmsless.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_lmsless_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function cis_lmsless_image_default_styles() {
  $styles = array();

  // Exported image style: foundation_access_lmsless_bar.
  $styles['foundation_access_lmsless_bar'] = array(
    'label' => 'Foundation Access lmsless bar',
    'effects' => array(
      1 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 40,
          'height' => 40,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: foundation_access_profile.
  $styles['foundation_access_profile'] = array(
    'label' => 'Foundation Access Profile',
    'effects' => array(
      2 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 220,
          'height' => 220,
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
