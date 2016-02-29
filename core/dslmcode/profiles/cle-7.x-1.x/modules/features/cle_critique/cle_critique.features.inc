<?php
/**
 * @file
 * cle_critique.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_critique_ctools_plugin_api($module = NULL, $api = NULL) {
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
function cle_critique_node_info() {
  $items = array(
    'cle_critique' => array(
      'name' => t('Critique'),
      'base' => 'node_content',
      'description' => t('A critique of the work in question, generally a peer critique though anyone could use this.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
