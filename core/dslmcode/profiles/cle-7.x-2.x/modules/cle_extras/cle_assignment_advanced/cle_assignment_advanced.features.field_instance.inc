<?php
/**
 * @file
 * cle_assignment_advanced.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cle_assignment_advanced_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'node-cle_assignment-field_cle_assign_depend'
  $field_instances['node-cle_assignment-field_cle_assign_depend'] = array(
    'bundle' => 'cle_assignment',
    'default_value' => NULL,
    'default_value_function' => '',
    'deleted' => 0,
    'description' => 'Are there other assignments that are required to be submitted before this one can be submitted?',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 11,
      ),
      'full' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 8,
      ),
      'gradebook_viewer' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 8,
      ),
      'nodeform' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'link' => FALSE,
        ),
        'type' => 'entityreference_label',
        'weight' => 19,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_cle_assign_depend',
    'label' => 'Assignment Dependencies',
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
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 7,
    ),
  );

  // Exported field_instance: 'node-cle_assignment-field_cle_require_submission'
  $field_instances['node-cle_assignment-field_cle_require_submission'] = array(
    'bundle' => 'cle_assignment',
    'default_value' => array(
      0 => array(
        'value' => 'no',
      ),
    ),
    'deleted' => 0,
    'description' => 'Select "Yes" to require students to submit this assignment before being able to view submissions of their peers. This can be for assignments intentionally structured',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 10,
      ),
      'full' => array(
        'label' => 'inline',
        'settings' => array(),
        'type' => 'hidden',
        'weight' => 5,
      ),
      'gradebook_viewer' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 7,
      ),
      'nodeform' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 18,
      ),
    ),
    'entity_type' => 'node',
    'field_name' => 'field_cle_require_submission',
    'label' => 'Require submission to view',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(),
      'type' => 'options_select',
      'weight' => 4,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Are there other assignments that are required to be submitted before this one can be submitted?');
  t('Assignment Dependencies');
  t('Require submission to view');
  t('Select "Yes" to require students to submit this assignment before being able to view submissions of their peers. This can be for assignments intentionally structured');

  return $field_instances;
}
