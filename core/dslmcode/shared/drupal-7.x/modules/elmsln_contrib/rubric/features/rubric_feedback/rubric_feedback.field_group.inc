<?php
/**
 * @file
 * rubric_feedback.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function rubric_feedback_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_assessment_overall|node|rubric_submission_assessment|form';
  $field_group->group_name = 'group_assessment_overall';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'rubric_submission_assessment';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Overall',
    'weight' => '5',
    'children' => array(
      0 => 'field_assessment_feedback',
      1 => 'field_assessment_points_possible',
      2 => 'field_assessment_points_earned',
      3 => 'field_rubric_feedback_audio',
      4 => 'field_assessment_red_pen',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-assessment-overall field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_assessment_overall|node|rubric_submission_assessment|form'] = $field_group;

  return $export;
}
