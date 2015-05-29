<?php
/**
 * @file
 * cis_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "delta" && $api == "delta") {
    return array("version" => "3");
  }
  if ($module == "flexslider" && $api == "flexslider_default_preset") {
    return array("version" => "1");
  }
  if ($module == "path_breadcrumbs" && $api == "path_breadcrumbs") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
  if ($module == "video_embed_field" && $api == "default_video_embed_styles") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function cis_ux_image_default_styles() {
  $styles = array();

  // Exported image style: cis_course_mobile.
  $styles['cis_course_mobile'] = array(
    'name' => 'cis_course_mobile',
    'label' => 'cis_course_mobile',
    'effects' => array(
      13 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'imageinfo_cache_effect_router',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 275,
          'height' => 115,
          '#imageinfo_cache_effect_callback' => 'imageinfo_cache_effect_router',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: cis_invisible.
  $styles['cis_invisible'] = array(
    'name' => 'cis_invisible',
    'label' => 'cis_invisible',
    'effects' => array(
      12 => array(
        'label' => 'Scale and crop',
        'help' => 'Scale and crop will maintain the aspect-ratio of the original image, then crop the larger dimension. This is most useful for creating perfectly square thumbnails without stretching the image.',
        'effect callback' => 'imageinfo_cache_effect_router',
        'dimensions callback' => 'image_resize_dimensions',
        'form callback' => 'image_resize_form',
        'summary theme' => 'image_resize_summary',
        'module' => 'image',
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1,
          'height' => 1,
          '#imageinfo_cache_effect_callback' => 'imageinfo_cache_effect_router',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: course_author_thumb.
  $styles['course_author_thumb'] = array(
    'name' => 'course_author_thumb',
    'label' => 'course_author_thumb',
    'effects' => array(
      2 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'imageinfo_cache_effect_router',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 95,
          'height' => 95,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'imageinfo_cache_effect_router',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: course_block_thumb.
  $styles['course_block_thumb'] = array(
    'name' => 'course_block_thumb',
    'label' => 'course_block_thumb',
    'effects' => array(
      4 => array(
        'label' => 'Scale and Smart Crop',
        'help' => 'Similar to "Scale And Crop", but preserves the portion of the image with the most entropy.',
        'effect callback' => 'imageinfo_cache_effect_router',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'smartcrop',
        'name' => 'smartcrop_scale_and_crop',
        'data' => array(
          'width' => 275,
          'height' => 115,
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'imageinfo_cache_effect_router',
        ),
        'weight' => 2,
      ),
    ),
  );

  // Exported image style: course_thumb.
  $styles['course_thumb'] = array(
    'name' => 'course_thumb',
    'label' => 'course_thumb',
    'effects' => array(
      1 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'imageinfo_cache_effect_router',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 270,
          'height' => 220,
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'imageinfo_cache_effect_router',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: people_headshot.
  $styles['people_headshot'] = array(
    'name' => 'people_headshot',
    'label' => 'people_headshot',
    'effects' => array(
      10 => array(
        'label' => 'Focus Scale And Crop',
        'help' => 'Scale and crop based on data provided by <em>ImageField Focus</em>.',
        'effect callback' => 'imageinfo_cache_effect_router',
        'form callback' => 'imagefield_focus_scale_and_crop_form',
        'summary theme' => 'imagefield_focus_scale_and_crop_summary',
        'module' => 'imagefield_focus',
        'name' => 'imagefield_focus_scale_and_crop',
        'data' => array(
          'width' => 720,
          'height' => 580,
          'strength' => 'high',
          'fallback' => 'smartcrop',
          '#imageinfo_cache_effect_callback' => 'imageinfo_cache_effect_router',
        ),
        'weight' => -10,
      ),
      11 => array(
        'label' => 'Scale',
        'help' => 'Scaling will maintain the aspect-ratio of the original image. If only a single dimension is specified, the other dimension will be calculated.',
        'effect callback' => 'imageinfo_cache_effect_router',
        'dimensions callback' => 'image_scale_dimensions',
        'form callback' => 'image_scale_form',
        'summary theme' => 'image_scale_summary',
        'module' => 'image',
        'name' => 'image_scale',
        'data' => array(
          'width' => 720,
          'height' => 580,
          'upscale' => 1,
          '#imageinfo_cache_effect_callback' => 'imageinfo_cache_effect_router',
        ),
        'weight' => -9,
      ),
    ),
  );

  return $styles;
}
