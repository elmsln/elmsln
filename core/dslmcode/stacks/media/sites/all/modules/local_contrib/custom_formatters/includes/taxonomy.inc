<?php
/**
 * @file
 * Taxonomy module integration.
 */

/**
 * Implements hook_custom_formatters_devel_generate_info() on behalf of
 * taxonomy.module.
 */
function taxonomy_custom_formatters_devel_generate_info() {
  return array(
    'taxonomy_term' => array(
      'process callback' => 'custom_formatters_taxonomy_term_devel_generate_process',
    ),
  );
}

/**
 * Process callback for Taxonomy term Devel Generate integration.
 */
function custom_formatters_taxonomy_term_devel_generate_process($form_state) {
  module_load_include('inc', 'devel_generate', 'devel_generate');

  $vocab = taxonomy_vocabulary_machine_name_load($form_state['values']['preview']['bundle']);

  $object = new stdClass();
  $object->tid = mt_rand(1, 100);
  $object->vid = $vocab->vid;
  $object->name = devel_generate_word(mt_rand(2, 12));
  $object->description = "description of {$object->name}";
  $object->format = filter_fallback_format();
  $object->weight = mt_rand(0, 10);
  $object->vocabulary_machine_name = $form_state['values']['preview']['bundle'];
  $object->language = LANGUAGE_NONE;

  // Populate all core fields on behalf of field.module
  module_load_include('inc', 'devel_generate', 'devel_generate.fields');
  devel_generate_fields($object, 'taxonomy_term', $object->vocabulary_machine_name);

  return $object;
}
