<?php
/**
 * @file
 * elmsmedia_h5p.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function elmsmedia_h5p_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|h5p_content|full';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'h5p_content';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_cis_course_ref',
      1 => 'field_tagging',
      2 => 'og_group_ref',
      3 => 'field_accessible_fallback',
      4 => 'field_figurelabel_ref',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-details field-group-fieldset elmsln-right-float-column',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_details|node|h5p_content|full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Details');

  return $field_groups;
}
