<?php
/**
 * @file
 * cle_submission_assessment.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function cle_submission_assessment_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance:
  // 'assessment_entity-submission_evaluation-field_cle_associated_submission'
  $field_instances['assessment_entity-submission_evaluation-field_cle_associated_submission'] = array(
    'bundle' => 'submission_evaluation',
    'default_value' => NULL,
    'default_value_function' => 'entityreference_prepopulate_field_default_value',
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'entityreference',
        'settings' => array(
          'link' => 1,
        ),
        'type' => 'entityreference_label',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'assessment_entity',
    'fences_wrapper' => 'div',
    'field_name' => 'field_cle_associated_submission',
    'label' => 'Associated Submission',
    'required' => 0,
    'settings' => array(
      'behaviors' => array(
        'prepopulate' => array(
          'action' => 'none',
          'action_on_edit' => 0,
          'fallback' => 'none',
          'providers' => array(
            'og_context' => 0,
            'url' => 1,
          ),
          'skip_perm' => 0,
          'status' => 1,
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
      'weight' => 1,
    ),
  );

  // Exported field_instance:
  // 'assessment_entity-submission_evaluation-field_cle_point_value'
  $field_instances['assessment_entity-submission_evaluation-field_cle_point_value'] = array(
    'bundle' => 'submission_evaluation',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'number',
        'settings' => array(
          'decimal_separator' => '.',
          'prefix_suffix' => TRUE,
          'scale' => 0,
          'thousand_separator' => ' ',
        ),
        'type' => 'number_integer',
        'weight' => 1,
      ),
    ),
    'entity_type' => 'assessment_entity',
    'field_name' => 'field_cle_point_value',
    'label' => 'Point value',
    'required' => 0,
    'settings' => array(
      'max' => '',
      'min' => '',
      'prefix' => '',
      'suffix' => '',
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 0,
      'module' => 'number',
      'settings' => array(),
      'type' => 'number',
      'weight' => 2,
    ),
  );

  // Exported field_instance:
  // 'assessment_entity-submission_evaluation-field_cle_status'
  $field_instances['assessment_entity-submission_evaluation-field_cle_status'] = array(
    'bundle' => 'submission_evaluation',
    'default_value' => array(
      0 => array(
        'value' => 'assessment_started',
      ),
    ),
    'deleted' => 0,
    'description' => 'The current status of this assessment',
    'display' => array(
      'default' => array(
        'label' => 'inline',
        'module' => 'list',
        'settings' => array(),
        'type' => 'list_default',
        'weight' => 2,
      ),
    ),
    'entity_type' => 'assessment_entity',
    'fences_wrapper' => 'div',
    'field_name' => 'field_cle_status',
    'label' => 'Status',
    'required' => 1,
    'settings' => array(
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'options',
      'settings' => array(
        'apply_chosen' => '',
      ),
      'type' => 'options_select',
      'weight' => 3,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Associated Submission');
  t('Point value');
  t('Status');
  t('The current status of this assessment');

  return $field_instances;
}
