<?php
/**
 * @file
 * elmsln_core.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsln_core_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function elmsln_core_image_default_styles() {
  $styles = array();

  // Exported image style: elmsln_gray.
  $styles['elmsln_gray'] = array(
    'label' => 'ELMSLN gray',
    'effects' => array(
      3 => array(
        'name' => 'image_desaturate',
        'data' => array(
          '#imageinfo_cache_effect_callback' => 'image_desaturate_effect',
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: elmsln_large.
  $styles['elmsln_large'] = array(
    'label' => 'ELMSLN large',
    'effects' => array(
      6 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1200,
          'height' => '',
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => -9,
      ),
    ),
  );

  // Exported image style: elmsln_medium.
  $styles['elmsln_medium'] = array(
    'label' => 'ELMSLN medium',
    'effects' => array(
      5 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 600,
          'height' => '',
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: elmsln_micro.
  $styles['elmsln_micro'] = array(
    'label' => 'ELMSLN micro',
    'effects' => array(
      7 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 16,
          'height' => 16,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: elmsln_normalize.
  $styles['elmsln_normalize'] = array(
    'label' => 'ELMSLN normalize',
    'effects' => array(
      11 => array(
        'name' => 'imagecache_autorotate',
        'data' => array(
          '#imageinfo_cache_effect_callback' => 'imagecache_autorotate_effect',
        ),
        'weight' => -10,
      ),
      10 => array(
        'name' => 'coloractions_convert',
        'data' => array(
          'format' => 'image/jpeg',
          'quality' => 75,
          '#imageinfo_cache_effect_callback' => 'coloractions_convert_effect',
        ),
        'weight' => -9,
      ),
    ),
  );

  // Exported image style: elmsln_small.
  $styles['elmsln_small'] = array(
    'label' => 'ELMSLN small',
    'effects' => array(
      4 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 300,
          'height' => '',
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: elmsln_thumb.
  $styles['elmsln_thumb'] = array(
    'label' => 'ELMSLN thumb',
    'effects' => array(
      1 => array(
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 64,
          'height' => 64,
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'smartcrop_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}
