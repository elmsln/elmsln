<?php
/**
 * @file
 * rubric_feature.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function rubric_feature_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_hidden_data|field_collection_item|field_rubric_criteria|form';
  $field_group->group_name = 'group_hidden_data';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_rubric_criteria';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '3',
    'children' => array(
      0 => 'field_criteria_points',
      1 => 'field_level_assessed',
      2 => 'field_criteria_possible_points',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $export['group_hidden_data|field_collection_item|field_rubric_criteria|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_hidden|field_collection_item|field_rubric_categories|form';
  $field_group->group_name = 'group_hidden';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_rubric_categories';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '4',
    'children' => array(
      0 => 'field_category_feedback',
      1 => 'field_category_points',
      2 => 'field_category_possible_points',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-hidden field-group-html-element',
        'element' => 'div',
        'attributes' => '',
      ),
    ),
  );
  $export['group_hidden|field_collection_item|field_rubric_categories|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_prepopulated_invisible|node|elms_rubric_assessment|form';
  $field_group->group_name = 'group_prepopulated_invisible';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'rubric_submission_assessment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '7',
    'children' => array(
      0 => 'og_group_ref',
      1 => 'field_assessment_points_earned',
      2 => 'field_original_rubric',
    ),
    'format_type' => 'html-element',
    'format_settings' => array(
      'label' => '',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'element' => 'div',
        'attributes' => '',
      ),
      'formatter' => '',
    ),
  );
  $export['group_prepopulated_invisible|node|elms_rubric_assessment|form'] = $field_group;

  return $export;
}
