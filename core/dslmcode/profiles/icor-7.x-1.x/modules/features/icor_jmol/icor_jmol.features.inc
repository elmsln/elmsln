<?php
/**
 * @file
 * icor_jmol.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function icor_jmol_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function icor_jmol_node_info() {
  $items = array(
    'jmol' => array(
      'name' => t('Jmol'),
      'base' => 'node_content',
      'description' => t('An open-source Java/Javascript viewer for chemical structures in 3D.  See http://jmol.sourceforge.net/ for more information.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
