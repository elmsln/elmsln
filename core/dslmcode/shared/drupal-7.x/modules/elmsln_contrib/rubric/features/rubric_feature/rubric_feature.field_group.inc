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
  $field_group->identifier = 'group_assessment_type|node|elms_rubric|form';
  $field_group->group_name = 'group_assessment_type';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'elms_rubric';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Assessment Type',
    'weight' => '2',
    'children' => array(
      0 => 'field_rubric_assessment_type',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Assessment Type',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-assessment-type field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_assessment_type|node|elms_rubric|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|field_collection_item|field_rubric_categories|default';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_rubric_categories';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '2',
    'children' => array(
      0 => 'field_category_details',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'classes' => 'group-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_details|field_collection_item|field_rubric_categories|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|field_collection_item|field_rubric_categories|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_rubric_categories';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '2',
    'children' => array(
      0 => 'field_category_details',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_details|field_collection_item|field_rubric_categories|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|field_collection_item|field_rubric_criteria|default';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_rubric_criteria';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '1',
    'children' => array(
      0 => 'field_criteria_details',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'classes' => 'group-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_details|field_collection_item|field_rubric_criteria|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|field_collection_item|field_rubric_criteria|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_rubric_criteria';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '1',
    'children' => array(
      0 => 'field_criteria_details',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_details|field_collection_item|field_rubric_criteria|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|elms_rubric|default';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'elms_rubric';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '1',
    'children' => array(
      0 => 'field_rubric_content',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'classes' => 'group-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_details|node|elms_rubric|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_feedback_wrapper|field_collection_item|field_rubric_levels|form';
  $field_group->group_name = 'group_feedback_wrapper';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_rubric_levels';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Feedback',
    'weight' => '8',
    'children' => array(
      0 => 'field_default_feedback',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Feedback',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => 'group-feedback-wrapper field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $export['group_feedback_wrapper|field_collection_item|field_rubric_levels|form'] = $field_group;

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
        'id' => 'field_collection_item_field_rubric_criteria_form_group_hidden_data',
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
        'id' => 'field_collection_item_field_rubric_categories_form_group_hidden',
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
        'id' => 'node_rubric_submission_assessment_form_group_prepopulated_invisible',
      ),
      'formatter' => '',
    ),
  );
  $export['group_prepopulated_invisible|node|elms_rubric_assessment|form'] = $field_group;

  return $export;
}
