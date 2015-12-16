<?php
/**
 * @file
 * mooc_nav_block.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function mooc_nav_block_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_navigation_block|node|page|form';
  $field_group->group_name = 'group_navigation_block';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Navigation Block',
    'weight' => '3',
    'children' => array(
      0 => 'field_mooc_nav_style',
      1 => 'field_mooc_nav_display',
      2 => 'field_mooc_nav_type',
      3 => 'field_mooc_nav_label',
      4 => 'field_mooc_nav_custom_text',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-navigation-block field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_navigation_block|node|page|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Navigation Block');

  return $field_groups;
}
