<?php
/**
 * @file
 * cle_assignment.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cle_assignment_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assignment_details|node|cle_assignment|form';
  $field_group->group_name = 'group_assignment_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_assignment_color',
      1 => 'field_assignment_description',
      2 => 'field_assignment_due_date',
      3 => 'field_assignment_feedback',
      4 => 'field_assignment_image',
      5 => 'field_assignment_late_submission',
      6 => 'field_assignment_privacy_setting',
      7 => 'og_group_ref',
      8 => 'title',
      9 => 'options',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-assignment-details field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_assignment_details|node|cle_assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assignment_evidence|node|cle_assignment|form';
  $field_group->group_name = 'group_assignment_evidence';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Evidence',
    'weight' => '1',
    'children' => array(
      0 => 'field_assignment_artifacts',
      1 => 'field_assignment_evidence',
      2 => 'field_elmsln_competencies',
      3 => 'group_critique',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-assignment-evidence field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_assignment_evidence|node|cle_assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assignment_hierarchy|node|cle_assignment|form';
  $field_group->group_name = 'group_assignment_hierarchy';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Hierarchy',
    'weight' => '2',
    'children' => array(
      0 => 'field_assignment_dependencies',
      1 => 'field_assignment_project',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-assignment-hierarchy field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_assignment_hierarchy|node|cle_assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_critique|node|cle_assignment|form';
  $field_group->group_name = 'group_critique';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_assignment_evidence';
  $field_group->data = array(
    'label' => 'Critique',
    'weight' => '24',
    'children' => array(
      0 => 'field_critique_method',
      1 => 'field_critique_outline',
      2 => 'field_critique_privacy',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-critique field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_critique|node|cle_assignment|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Critique');
  t('Details');
  t('Evidence');
  t('Hierarchy');

  return $field_groups;
}
