<?php
/**
 * @file
 * ecd_types.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ecd_types_ctools_plugin_api($module = NULL, $api = NULL) {
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
function ecd_types_node_info() {
  $items = array(
    'cis_system' => array(
      'name' => t('System'),
      'base' => 'node_content',
      'description' => t('Systems used in ELMS Learning Network as reported by CIS.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'ecd_asset' => array(
      'name' => t('Asset'),
      'base' => 'node_content',
      'description' => t('An asset is an item that needs certification / validation to be part of a full compliance audit. It is associated to a Course in some manner'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
