<?php
/**
 * @file
 * harmony_atjs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function harmony_atjs_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "atjs" && $api == "default_atjs_listener") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_field_default_field_instances_alter().
 */
function harmony_atjs_field_default_field_instances_alter(&$data) {
  if (isset($data['harmony_post-harmony_post-field_harmony_text'])) {
    $data['harmony_post-harmony_post-field_harmony_text']['widget']['settings']['atjs_fieldset'] = array(
      'atjs' => 1,
      'atjs_listeners' => array(
        'harmony_users' => 'harmony_users',
      ),
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function harmony_atjs_filter_default_formats_alter(&$data) {
  if (isset($data['harmony_filtered'])) {
    $data['harmony_filtered']['filters']['atjs'] = array(
      'settings' => array(
        'atjs_listeners' => array(
          'harmony_users' => 'harmony_users',
        ),
      ),
      'status' => 1,
      'weight' => -44,
    ); /* WAS: '' */
  }
}
