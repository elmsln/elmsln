<?php
/**
 * @file
 * cle_project.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cle_project_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_hierarchy|node|cle_project|form';
  $field_group->group_name = 'group_hierarchy';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Hierarchy',
    'weight' => '1',
    'children' => array(
      0 => 'field_project_steps',
      1 => 'field_project_dependencies',
      2 => 'field_project_parent',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-hierarchy field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_hierarchy|node|cle_project|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_project_details|node|cle_project|form';
  $field_group->group_name = 'group_project_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_project';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_project_color',
      1 => 'field_project_description',
      2 => 'field_project_due_date',
      3 => 'field_project_image',
      4 => 'field_assignment_late_submission',
      5 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-project-details field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_project_details|node|cle_project|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Details');
  t('Hierarchy');

  return $field_groups;
}
