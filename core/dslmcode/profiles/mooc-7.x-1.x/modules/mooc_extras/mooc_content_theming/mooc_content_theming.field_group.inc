<?php
/**
 * @file
 * mooc_content_theming.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function mooc_content_theming_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_visual_identifiers|node|page|form';
  $field_group->group_name = 'group_visual_identifiers';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Visual identifiers',
    'weight' => '3',
    'children' => array(
      0 => 'field_mooc_image',
      1 => 'field_mooc_color',
      2 => 'field_instructional_significance',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-visual-identifiers field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_visual_identifiers|node|page|form'] = $field_group;

  return $export;
}
