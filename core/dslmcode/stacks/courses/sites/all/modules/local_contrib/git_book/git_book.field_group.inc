<?php
/**
 * @file
 * git_book.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function git_book_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_git_advanced|node|git_book|form';
  $field_group->group_name = 'group_git_advanced';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'git_book';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Advanced git settings',
    'weight' => '3',
    'children' => array(
      0 => 'field_git_branch',
      1 => 'field_git_push',
      2 => 'field_git_commit',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-git-advanced field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_git_advanced|node|git_book|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Advanced git settings');

  return $field_groups;
}
