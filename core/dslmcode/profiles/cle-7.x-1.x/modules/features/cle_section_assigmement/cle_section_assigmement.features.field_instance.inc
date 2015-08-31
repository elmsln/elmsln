<?php
/**
 * @file
 * cle_section_assigmement.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cle_section_assigmement_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-section-field_cle_assignments'
  $field_instances['node-section-field_cle_assignments'] = array(
    'bundle' => 'section',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'fences_wrapper' => 'div',
    'field_name' => 'field_cle_assignments',
    'label' => 'Assignments',
    'required' => 0,
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
        'apply_chosen' => 0,
      ),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assignments');

  return $field_instances;
}
