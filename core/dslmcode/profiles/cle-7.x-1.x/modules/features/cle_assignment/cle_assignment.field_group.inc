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
  $field_group->identifier = 'group_logistics|node|cle_assignment|form';
  $field_group->group_name = 'group_logistics';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Logistics',
    'weight' => '2',
    'children' => array(
      0 => 'field_due_date',
      1 => 'field_visibility',
      2 => 'field_media_requirements',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_logistics|node|cle_assignment|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_order|node|cle_assignment|form';
  $field_group->group_name = 'group_order';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Order',
    'weight' => '1',
    'children' => array(
      0 => 'field_color',
      1 => 'field_number',
      2 => 'field_sub_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Order',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => 'These values help organize the order assignments occur in.  Due dates are not enforced based on order but these values will also make it easier to integrate these assignment directions into other courses.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_order|node|cle_assignment|form'] = $field_group;

  return $export;
}
