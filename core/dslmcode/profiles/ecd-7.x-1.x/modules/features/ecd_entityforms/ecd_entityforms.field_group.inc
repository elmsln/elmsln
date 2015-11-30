<?php
/**
 * @file
 * ecd_entityforms.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ecd_entityforms_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_justification|entityform|course_access_request|form';
  $field_group->group_name = 'group_justification';
  $field_group->entity_type = 'entityform';
  $field_group->bundle = 'course_access_request';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Justification',
    'weight' => '4',
    'children' => array(
      0 => 'field_documentation',
      1 => 'field_written_justification',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-justification field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_justification|entityform|course_access_request|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_justification|entityform|system_access_request|form';
  $field_group->group_name = 'group_justification';
  $field_group->entity_type = 'entityform';
  $field_group->bundle = 'system_access_request';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Justification',
    'weight' => '4',
    'children' => array(
      0 => 'field_documentation',
      1 => 'field_written_justification',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-justification field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_justification|entityform|system_access_request|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_request_details|entityform|course_access_request|form';
  $field_group->group_name = 'group_request_details';
  $field_group->entity_type = 'entityform';
  $field_group->bundle = 'course_access_request';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Request Details',
    'weight' => '3',
    'children' => array(
      0 => 'field_course_access',
      1 => 'field_duration',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-request-details field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_request_details|entityform|course_access_request|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_request_details|entityform|system_access_request|form';
  $field_group->group_name = 'group_request_details';
  $field_group->entity_type = 'entityform';
  $field_group->bundle = 'system_access_request';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Request Details',
    'weight' => '3',
    'children' => array(
      0 => 'field_duration',
      1 => 'field_ecd_systems',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-request-details field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_request_details|entityform|system_access_request|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Justification');
  t('Request Details');

  return $field_groups;
}
