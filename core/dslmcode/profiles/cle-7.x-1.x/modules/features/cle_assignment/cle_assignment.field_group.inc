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
  $field_group->identifier = 'group_adv_submission_settings|node|cle_assignment|nodeform';
  $field_group->group_name = 'group_adv_submission_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'nodeform';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Advanced submission settings',
    'weight' => '7',
    'children' => array(
      0 => 'field_visibility',
      1 => 'og_group_ref',
      2 => 'field_cle_assign_depend',
      3 => 'field_cle_require_submission',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-adv-submission-settings field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_adv_submission_settings|node|cle_assignment|nodeform'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assignment_description|node|cle_assignment|gradebook_viewer';
  $field_group->group_name = 'group_assignment_description';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Assignment Description',
    'weight' => '3',
    'children' => array(
      0 => 'body',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Assignment Description',
      'instance_settings' => array(
        'classes' => 'group-assignment-description field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_assignment_description|node|cle_assignment|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|cle_assignment|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '2',
    'children' => array(
      0 => 'group_logistics',
      1 => 'group_due_date',
      2 => 'group_requirements',
      3 => 'group_permissions',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-details field-group-htabs',
      ),
    ),
  );
  $export['group_details|node|cle_assignment|form'] = $field_group;

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
      0 => 'field_color',
      1 => 'field_due_date',
      2 => 'field_media_requirements',
      3 => 'field_number',
      4 => 'field_sub_number',
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

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_logistics|node|cle_assignment|gradebook_viewer';
  $field_group->group_name = 'group_logistics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Logistics',
    'weight' => '1',
    'children' => array(
      0 => 'field_visibility',
      1 => 'field_cle_assign_depend',
      2 => 'field_cle_require_submission',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Logistics',
      'instance_settings' => array(
        'classes' => 'group-logistics field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_logistics|node|cle_assignment|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_permissions|node|cle_assignment|form';
  $field_group->group_name = 'group_permissions';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Permissions',
    'weight' => '18',
    'children' => array(
      0 => 'field_visibility',
      1 => 'field_cle_require_submission',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-permissions field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_permissions|node|cle_assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_requirements|node|cle_assignment|form';
  $field_group->group_name = 'group_requirements';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_details';
  $field_group->data = array(
    'label' => 'Requirements',
    'weight' => '17',
    'children' => array(
      0 => 'field_media_requirements',
      1 => 'field_cle_assign_depend',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-requirements field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_requirements|node|cle_assignment|form'] = $field_group;

  return $export;
}
