<?php
/**
 * @file
 * elmsmedia_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsmedia_feature_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function elmsmedia_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function elmsmedia_feature_image_default_styles() {
  $styles = array();

  // Exported image style: image.
  $styles['image'] = array(
    'label' => 'Image',
    'effects' => array(
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1200,
          'height' => '',
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  // Exported image style: image_lightboxed.
  $styles['image_lightboxed'] = array(
    'label' => 'Image Lightboxed',
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 1200,
          'height' => '',
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 2,
      ),
      3 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => '',
          'height' => 800,
          'upscale' => 0,
          '#imageinfo_cache_effect_callback' => 'image_scale_effect',
        ),
        'weight' => 3,
      ),
    ),
  );

  // Exported image style: mediavideo_poster.
  $styles['mediavideo_poster'] = array(
    'label' => 'Mediavideo Poster',
    'effects' => array(
      1 => array(
        'name' => 'image_scale_and_crop',
        'data' => array(
          'width' => 1200,
          'height' => 800,
          '#imageinfo_cache_effect_callback' => 'image_scale_and_crop_effect',
        ),
        'weight' => 1,
      ),
    ),
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function elmsmedia_feature_node_info() {
  $items = array(
    'audio' => array(
      'name' => t('Audio'),
      'base' => 'node_content',
      'description' => t('Upload sound files'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'document' => array(
      'name' => t('Document'),
      'base' => 'node_content',
      'description' => t('Upload a document for embedding elsewhere'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'elmsmedia_image' => array(
      'name' => t('Image'),
      'base' => 'node_content',
      'description' => t('Basic image content type'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'external_video' => array(
      'name' => t('External video'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'svg' => array(
      'name' => t('SVG'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'video' => array(
      'name' => t('Video'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
