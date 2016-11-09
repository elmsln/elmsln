<?php
/**
 * @file
 * elmsmedia_static_content.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsmedia_static_content_ctools_plugin_api($module = NULL, $api = NULL) {
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
function elmsmedia_static_content_node_info() {
  $items = array(
    'static_content' => array(
      'name' => t('Static content'),
      'base' => 'node_content',
      'description' => t('This is a simple piece of static content, useful for making accessible fallback content and content that\'s referenced in multiple places.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
