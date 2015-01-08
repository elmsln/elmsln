<?php
/**
 * @file
 * ecd_types.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function ecd_types_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_audits|node|course|form';
  $field_group->group_name = 'group_audits';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Audits',
    'weight' => '2',
    'children' => array(
      0 => 'field_copyright_audit',
      1 => 'field_accessibility_audit',
      2 => 'field_quality_audit',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-audits field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_audits|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_logistics|node|ecd_asset|form';
  $field_group->group_name = 'group_logistics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ecd_asset';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Logistics',
    'weight' => '2',
    'children' => array(
      0 => 'field_course',
      1 => 'field_resource_uuid_bind',
      2 => 'field_source',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-logistics field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_logistics|node|ecd_asset|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_verification|node|ecd_asset|form';
  $field_group->group_name = 'group_verification';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'ecd_asset';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Verification',
    'weight' => '3',
    'children' => array(
      0 => 'field_accessibility_verified',
      1 => 'field_quality_verified',
      2 => 'field_copyright_verified',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-verification field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_verification|node|ecd_asset|form'] = $field_group;

  return $export;
}
