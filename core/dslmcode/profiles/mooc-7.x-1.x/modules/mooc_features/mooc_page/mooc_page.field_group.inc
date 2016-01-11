<?php
/**
 * @file
 * mooc_page.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function mooc_page_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cis_tag_group|node|page|form';
  $field_group->group_name = 'group_cis_tag_group';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'page';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tags',
    'weight' => '3',
    'children' => array(
      0 => 'field_cis_tag',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'label' => 'Tags',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-cis-tag-group field-group-tab',
        'description' => '',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_cis_tag_group|node|page|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Tags');

  return $field_groups;
}
