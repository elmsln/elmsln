<?php
/**
 * @file
 * node_reference_highlight_glossary.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function node_reference_highlight_glossary_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function node_reference_highlight_glossary_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function node_reference_highlight_glossary_node_info() {
  $items = array(
    'nrhi_term' => array(
      'name' => t('Term'),
      'base' => 'node_content',
      'description' => t('Glossary term'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
