<?php
/**
 * @file
 * Node module integration.
 */

/**
 * Implements hook_custom_formatters_devel_generate_info() on behalf of
 * node.module.
 */
function node_custom_formatters_devel_generate_info() {
  return array(
    'node' => array(
      'process callback' => 'custom_formatters_node_devel_generate_process',
    ),
  );
}

/**
 * Process callback for Node Devel Generate integration.
 */
function custom_formatters_node_devel_generate_process($form_state) {
  module_load_include('inc', 'devel_generate', 'devel_generate');

  $object = new stdClass();
  $object->nid = mt_rand(1, 100);
  $object->type = $form_state['values']['preview']['bundle'];
  $object->uid = $GLOBALS['user']->uid;
  $type = node_type_get_type($object);
  $object->title = $type->has_title ? devel_create_greeking(mt_rand(2, rand(4, 10)), TRUE) : '';
  $object->revision = mt_rand(0, 1);
  $object->promote = mt_rand(0, 1);

  devel_generate_set_language(array(), $object);

  $object->created = REQUEST_TIME;

  // Populate all core fields on behalf of field.module
  module_load_include('inc', 'devel_generate', 'devel_generate.fields');
  devel_generate_fields($object, $form_state['values']['preview']['entity_type'], $object->type);

  return $object;
}
