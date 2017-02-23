<?php
/**
 * @file
 * textbook_mathjax.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function textbook_mathjax_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function textbook_mathjax_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['filters']['filter_mathjax'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => 50,
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_wysiwyg_default_profiles_alter().
 */
function textbook_mathjax_wysiwyg_default_profiles_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['settings']['buttons']['mathjax'] = array(
      'Mathjax' => 1,
    ); /* WAS: '' */
  }
}
