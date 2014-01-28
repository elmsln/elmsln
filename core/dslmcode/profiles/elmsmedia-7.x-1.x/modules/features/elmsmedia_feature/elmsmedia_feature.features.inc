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
    'video' => array(
      'name' => t('video'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
