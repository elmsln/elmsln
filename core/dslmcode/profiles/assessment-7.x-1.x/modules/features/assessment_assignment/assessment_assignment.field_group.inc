<?php
/**
 * @file
 * assessment_assignment.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function assessment_assignment_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_evidence|node|assessment_assignment|form';
  $field_group->group_name = 'group_evidence';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'assessment_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Evidence',
    'weight' => '1',
    'children' => array(
      0 => 'field_elmsln_system',
      1 => 'field_evidence',
      2 => 'field_xapi_statements',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-evidence field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_evidence|node|assessment_assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_logistics|node|assessment_assignment|form';
  $field_group->group_name = 'group_logistics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'assessment_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Logistics',
    'weight' => '3',
    'children' => array(
      0 => 'field_color',
      1 => 'field_grades_course_ref',
      2 => 'field_number',
      3 => 'og_group_ref',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-logistics field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_logistics|node|assessment_assignment|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Evidence');
  t('Logistics');

  return $field_groups;
}
