<?php
/**
 * @file
 * cle_critique.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cle_critique_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cle_critique|node|cle_assignment|form';
  $field_group->group_name = 'group_cle_critique';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Critique',
    'weight' => '4',
    'children' => array(
      0 => 'field_cle_crit_criteria',
      1 => 'field_cle_crit_outline',
      2 => 'field_cle_crit_type',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_cle_critique|node|cle_assignment|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Critique');

  return $field_groups;
}
