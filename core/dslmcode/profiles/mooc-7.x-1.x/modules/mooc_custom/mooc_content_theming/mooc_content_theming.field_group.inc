<?php
/**
 * @file
 * mooc_content_theming.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function mooc_content_theming_field_group_info() {
  $field_groups = array();

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
    'label' => 'Visual',
    'weight' => '3',
    'children' => array(
      0 => 'field_fa_primary_color',
      1 => 'field_fa_secondary_color',
      2 => 'field_instructional_significance',
      3 => 'field_mooc_image',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Visual',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_visual_identifiers|node|page|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Visual');

  return $field_groups;
}
