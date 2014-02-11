<?php
/**
 * @file
 * cis_helpdesk_issue.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cis_helpdesk_issue_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_administrative|node|cis_helpdesk_issue|default';
  $field_group->group_name = 'group_administrative';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cis_helpdesk_issue';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Administrative',
    'weight' => '3',
    'children' => array(
      0 => 'field_cis_hd_notes',
      1 => 'field_cis_hd_resolved_by',
      2 => 'field_cis_hd_status',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Administrative',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_administrative|node|cis_helpdesk_issue|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_administrative|node|cis_helpdesk_issue|form';
  $field_group->group_name = 'group_administrative';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cis_helpdesk_issue';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Administrative',
    'weight' => '1',
    'children' => array(
      0 => 'field_cis_hd_notes',
      1 => 'field_cis_hd_status',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Administrative',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_administrative|node|cis_helpdesk_issue|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cis_hd_user_context|node|cis_helpdesk_issue|default';
  $field_group->group_name = 'group_cis_hd_user_context';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cis_helpdesk_issue';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'User Context',
    'weight' => '0',
    'children' => array(
      0 => 'field_cis_hd_course',
      1 => 'field_cis_hd_section',
      2 => 'field_cis_hd_specs',
      3 => 'field_cis_hd_where',
      4 => 'field_cis_hd_who',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'User Context',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_cis_hd_user_context|node|cis_helpdesk_issue|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cis_hd_user_context|node|cis_helpdesk_issue|form';
  $field_group->group_name = 'group_cis_hd_user_context';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cis_helpdesk_issue';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'User Context',
    'weight' => '0',
    'children' => array(
      0 => 'field_cis_hd_course',
      1 => 'field_cis_hd_section',
      2 => 'field_cis_hd_specs',
      3 => 'field_cis_hd_where',
      4 => 'field_cis_hd_who',
      5 => 'field_cis_hd_service',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'User Context',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_cis_hd_user_context|node|cis_helpdesk_issue|form'] = $field_group;

  return $export;
}
