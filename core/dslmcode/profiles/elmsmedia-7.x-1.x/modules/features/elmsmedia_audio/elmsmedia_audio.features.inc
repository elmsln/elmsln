<?php
/**
 * @file
 * elmsmedia_audio.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsmedia_audio_ctools_plugin_api($module = NULL, $api = NULL) {
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
 * Implements hook_node_info().
 */
function elmsmedia_audio_node_info() {
  $items = array(
    'audio' => array(
      'name' => t('Audio'),
      'base' => 'node_content',
      'description' => t('Upload sound files'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
