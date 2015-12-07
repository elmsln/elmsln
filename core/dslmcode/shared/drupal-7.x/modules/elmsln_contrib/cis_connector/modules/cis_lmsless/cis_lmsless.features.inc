<?php
/**
 * @file
 * cis_lmsless.features.inc
 */

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
          'width' => 26,
          'height' => 26,
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
