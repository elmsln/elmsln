<?php
/**
 * @file
 * icor_zip.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function icor_zip_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function icor_zip_node_info() {
  $items = array(
    'zip' => array(
      'name' => t('Zip'),
      'base' => 'node_content',
      'description' => t('Supports unzipping an archive to load an index.html in an iFrame.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
