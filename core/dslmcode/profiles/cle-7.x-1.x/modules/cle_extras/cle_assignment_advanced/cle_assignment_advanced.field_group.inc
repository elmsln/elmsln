<?php
/**
 * @file
 * cle_assignment_advanced.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cle_assignment_advanced_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_adv_submission_settings|node|cle_assignment|form';
  $field_group->group_name = 'group_adv_submission_settings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Advanced submission settings',
    'weight' => '10',
    'children' => array(
      0 => 'field_cle_require_submission',
      1 => 'field_cle_assign_depend',
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
  $export['group_adv_submission_settings|node|cle_assignment|form'] = $field_group;

  return $export;
}
