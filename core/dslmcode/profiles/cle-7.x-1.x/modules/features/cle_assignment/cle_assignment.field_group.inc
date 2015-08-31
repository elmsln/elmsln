<?php
/**
 * @file
 * cle_assignment.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cle_assignment_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|cle_assignment|gradebook_viewer';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_due_date',
      1 => 'field_media_requirements',
      2 => 'field_number',
      3 => 'field_sub_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-details field-group-fieldset',
      ),
    ),
  );
  $export['group_details|node|cle_assignment|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_due_date|node|cle_assignment|form';
  $field_group->group_name = 'group_due_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Due Date',
    'weight' => '19',
    'children' => array(
      0 => 'field_due_date',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-due-date field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_due_date|node|cle_assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_logistics|node|cle_assignment|form';
  $field_group->group_name = 'group_logistics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Logistics',
    'weight' => '20',
    'children' => array(
      0 => 'field_color',
      1 => 'field_number',
      2 => 'field_sub_number',
      3 => 'field_submission_type',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-logistics field-group-tab',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $export['group_logistics|node|cle_assignment|form'] = $field_group;

  return $export;
}
