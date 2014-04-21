<?php
/**
 * @file
 * mooc_outline_link.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_outline_link_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function mooc_outline_link_strongarm_alter(&$data) {
  if (isset($data['book_allowed_types'])) {
    $data['book_allowed_types']->value['0'] = 'mooc_link'; /* WAS: 'page' */
    $data['book_allowed_types']->value['1'] = 'page'; /* WAS: '' */
  }
}

/**
 * Implements hook_node_info().
 */
function mooc_outline_link_node_info() {
  $items = array(
    'mooc_link' => array(
      'name' => t('Link'),
      'base' => 'node_content',
      'description' => t('External link while in the outline of the course.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
