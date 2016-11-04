<?php
/**
 * @file
 * elmsmedia_image_gallery.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsmedia_image_gallery_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_image_default_styles().
 */
function elmsmedia_image_gallery_image_default_styles() {
  $styles = array();

  // Exported image style: image_gallery_square.
  $styles['image_gallery_square'] = array(
    'label' => 'Image gallery Square',
    'effects' => array(
      1 => array(
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

/**
 * Implements hook_node_info().
 */
function elmsmedia_image_gallery_node_info() {
  $items = array(
    'image_gallery' => array(
      'name' => t('Image gallery'),
      'base' => 'node_content',
      'description' => t('Create a gallery of images to display together.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
