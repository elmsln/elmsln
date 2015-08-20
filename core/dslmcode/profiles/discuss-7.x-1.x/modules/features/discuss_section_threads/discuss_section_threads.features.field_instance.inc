<?php
/**
 * @file
 * discuss_section_threads.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function discuss_section_threads_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-section-field_harmony_threads'
  $field_instances['node-section-field_harmony_threads'] = array(
    'bundle' => 'section',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => 'The threads that this section responses to',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 4,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_harmony_threads',
    'label' => 'Threads',
    'required' => 1,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'status' => 0,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 31,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('The threads that this section responses to');
  t('Threads');

  return $field_instances;
}
