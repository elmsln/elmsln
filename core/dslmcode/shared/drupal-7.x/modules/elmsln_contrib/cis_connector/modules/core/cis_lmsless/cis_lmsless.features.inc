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
      18 => array(
        'name' => 'imagecache_autorotate',
        'data' => array(
          '#imageinfo_cache_effect_callback' => 'imagecache_autorotate_effect',
        ),
        'weight' => -10,
      ),
      19 => array(
        'name' => 'coloractions_convert',
        'data' => array(
          'format' => 'image/jpeg',
          'quality' => 75,
          '#imageinfo_cache_effect_callback' => 'coloractions_convert_effect',
        ),
        'weight' => -9,
      ),
      17 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 40,
          'height' => 40,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: foundation_access_profile.
  $styles['foundation_access_profile'] = array(
    'label' => 'Foundation Access Profile',
    'effects' => array(
      22 => array(
        'name' => 'imagecache_autorotate',
        'data' => array(
          '#imageinfo_cache_effect_callback' => 'imagecache_autorotate_effect',
        ),
        'weight' => -10,
      ),
      21 => array(
        'name' => 'coloractions_convert',
        'data' => array(
          'format' => 'image/jpeg',
          'quality' => 75,
          '#imageinfo_cache_effect_callback' => 'coloractions_convert_effect',
        ),
        'weight' => -9,
      ),
      20 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 220,
          'height' => 220,
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => -8,
      ),
    ),
  );

  // Exported image style: foundation_access_user_bg.
  $styles['foundation_access_user_bg'] = array(
    'label' => 'Foundation access user bg',
    'effects' => array(
      24 => array(
        'name' => 'imagecache_autorotate',
        'data' => array(
          '#imageinfo_cache_effect_callback' => 'imagecache_autorotate_effect',
        ),
        'weight' => -10,
      ),
      25 => array(
        'name' => 'coloractions_convert',
        'data' => array(
          'format' => 'image/jpeg',
          'quality' => 75,
          '#imageinfo_cache_effect_callback' => 'coloractions_convert_effect',
        ),
        'weight' => -9,
      ),
      23 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 280,
          'height' => 210,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => -8,
      ),
    ),
  );

  return $styles;
}
