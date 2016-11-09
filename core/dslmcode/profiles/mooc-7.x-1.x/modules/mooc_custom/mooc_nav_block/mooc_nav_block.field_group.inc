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
  $field_group->parent_name = 'group_interface';
  $field_group->data = array(
    'label' => 'Navigation block',
    'weight' => '148',
    'children' => array(
      0 => 'field_mooc_nav_custom_text',
      1 => 'field_mooc_nav_label',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Navigation block',
      'instance_settings' => array(
        'required_fields' => 0,
        'id' => '',
        'classes' => 'group-navigation-block field-group-tab',
        'description' => 'Change settings for the navigation block in the left column',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_navigation_block|node|page|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Navigation block');

  return $field_groups;
}
