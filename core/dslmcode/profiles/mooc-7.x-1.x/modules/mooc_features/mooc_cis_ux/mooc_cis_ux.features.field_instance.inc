<?php
/**
 * @file
 * mooc_cis_ux.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function mooc_cis_ux_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-section-field_instructional_outlines'
  $field_instances['node-section-field_instructional_outlines'] = array(
    'bundle' => 'section',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'above',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 3,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_instructional_outlines',
    'label' => 'Instructional outlines',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'og_context' => 0,
          'skip_perm' => 0,
          'status' => 1,
        ),
      ),
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Instructional outlines');

  return $field_instances;
}
