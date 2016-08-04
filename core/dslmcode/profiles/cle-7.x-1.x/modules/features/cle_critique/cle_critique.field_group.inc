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
  $field_group->identifier = 'group_admin|node|cle_assignment|default';
  $field_group->group_name = 'group_admin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Administrative',
    'weight' => '2',
    'children' => array(
      0 => 'field_cle_sub_type',
      1 => 'field_color',
      2 => 'field_media_requirements',
      3 => 'field_cle_crit_type',
      4 => 'group_critique',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Administrative',
      'instance_settings' => array(
        'id' => '',
        'classes' => '',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_admin|node|cle_assignment|default'] = $field_group;

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
      3 => 'field_critique_date',
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

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_critique|node|cle_assignment|default';
  $field_group->group_name = 'group_critique';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_assignment';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_admin';
  $field_group->data = array(
    'label' => 'Critique',
    'weight' => '34',
    'children' => array(
      0 => 'field_cle_crit_criteria',
      1 => 'field_cle_crit_outline',
      2 => 'field_critique_date',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Critique',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'group-critique field-group-div',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_critique|node|cle_assignment|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_feedback|node|cle_critique|default';
  $field_group->group_name = 'group_feedback';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_critique';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Feedback',
    'weight' => '1',
    'children' => array(
      0 => 'field_cle_crit_feedback',
      1 => 'author',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Feedback',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'cle__feedback',
        'description' => '',
        'show_label' => '1',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_feedback|node|cle_critique|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_pushpin|node|cle_critique|default';
  $field_group->group_name = 'group_pushpin';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'cle_critique';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Critique Pushpin',
    'weight' => '0',
    'children' => array(
      0 => 'field_cle_crit_sub_ref',
    ),
    'format_type' => 'div',
    'format_settings' => array(
      'label' => 'Critique Pushpin',
      'instance_settings' => array(
        'id' => '',
        'classes' => 'cle-killswitch',
        'description' => '',
        'show_label' => '0',
        'label_element' => 'h3',
        'effect' => 'none',
        'speed' => 'fast',
      ),
      'formatter' => 'open',
    ),
  );
  $field_groups['group_pushpin|node|cle_critique|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Administrative');
  t('Critique');
  t('Critique Pushpin');
  t('Feedback');

  return $field_groups;
}
