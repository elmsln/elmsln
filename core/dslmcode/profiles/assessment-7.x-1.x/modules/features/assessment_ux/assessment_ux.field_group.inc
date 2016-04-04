<?php
/**
 * @file
 * assessment_ux.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function assessment_ux_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_grade_debug|assessment_item|graded_item|default';
  $field_group->group_name = 'group_grade_debug';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Debug',
    'weight' => '7',
    'children' => array(
      0 => 'field_remote_item_uuid',
      1 => 'field_grades_instructor',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-grade-debug field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_grade_debug|assessment_item|graded_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_grade_debug|assessment_item|graded_item|gradebook_viewer';
  $field_group->group_name = 'group_grade_debug';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Debug',
    'weight' => '7',
    'children' => array(
      0 => 'field_remote_item_uuid',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-grade-debug field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_grade_debug|assessment_item|graded_item|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_grade_tabgroup|assessment_item|graded_item|default';
  $field_group->group_name = 'group_grade_tabgroup';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tabgroup',
    'weight' => '0',
    'children' => array(
      0 => 'group_grade_debug',
      1 => 'group_gradesdetails',
      2 => 'group_gradesassignment',
      3 => 'group_gradessubmission',
      4 => 'group_gradesstudent',
      5 => 'group_gradesassessment',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-grade-tabgroup field-group-htabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_grade_tabgroup|assessment_item|graded_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_grade_tabgroup|assessment_item|graded_item|gradebook_viewer';
  $field_group->group_name = 'group_grade_tabgroup';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Tabgroup',
    'weight' => '0',
    'children' => array(
      0 => 'group_grade_debug',
      1 => 'group_gradesdetails',
      2 => 'group_gradesassignment',
      3 => 'group_gradessubmission',
      4 => 'group_gradesstudent',
      5 => 'group_gradesassessment',
    ),
    'format_type' => 'htabs',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'classes' => 'group-grade-tabgroup field-group-htabs',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_grade_tabgroup|assessment_item|graded_item|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesassessment|assessment_item|graded_item|default';
  $field_group->group_name = 'group_gradesassessment';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Assessment',
    'weight' => '3',
    'children' => array(
      0 => 'field_grades_point_value',
      1 => 'field_assessment_status',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesassessment field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesassessment|assessment_item|graded_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesassessment|assessment_item|graded_item|gradebook_viewer';
  $field_group->group_name = 'group_gradesassessment';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Assessment',
    'weight' => '3',
    'children' => array(
      0 => 'field_grades_point_value',
      1 => 'field_assessment_status',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesassessment field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesassessment|assessment_item|graded_item|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesassignment|assessment_item|graded_item|default';
  $field_group->group_name = 'group_gradesassignment';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Assignment',
    'weight' => '5',
    'children' => array(
      0 => 'field_assignment_ref',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesassignment field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesassignment|assessment_item|graded_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesassignment|assessment_item|graded_item|gradebook_viewer';
  $field_group->group_name = 'group_gradesassignment';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Assignment',
    'weight' => '5',
    'children' => array(
      0 => 'field_assignment_ref',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesassignment field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesassignment|assessment_item|graded_item|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesdetails|assessment_item|graded_item|default';
  $field_group->group_name = 'group_gradesdetails';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '6',
    'children' => array(
      0 => 'og_group_ref',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesdetails field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesdetails|assessment_item|graded_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesdetails|assessment_item|graded_item|gradebook_viewer';
  $field_group->group_name = 'group_gradesdetails';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '6',
    'children' => array(
      0 => 'og_group_ref',
      1 => 'field_grades_instructor',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesdetails field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesdetails|assessment_item|graded_item|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesstudent|assessment_item|graded_item|default';
  $field_group->group_name = 'group_gradesstudent';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Student',
    'weight' => '4',
    'children' => array(
      0 => 'field_grades_student',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesstudent field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesstudent|assessment_item|graded_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradesstudent|assessment_item|graded_item|gradebook_viewer';
  $field_group->group_name = 'group_gradesstudent';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Student',
    'weight' => '4',
    'children' => array(
      0 => 'field_grades_student',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradesstudent field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradesstudent|assessment_item|graded_item|gradebook_viewer'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradessubmission|assessment_item|graded_item|default';
  $field_group->group_name = 'group_gradessubmission';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Submission',
    'weight' => '2',
    'children' => array(
      0 => 'field_remote_submission',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradessubmission field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradessubmission|assessment_item|graded_item|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gradessubmission|assessment_item|graded_item|gradebook_viewer';
  $field_group->group_name = 'group_gradessubmission';
  $field_group->entity_type = 'assessment_item';
  $field_group->bundle = 'graded_item';
  $field_group->mode = 'gradebook_viewer';
  $field_group->parent_name = 'group_grade_tabgroup';
  $field_group->data = array(
    'label' => 'Submission',
    'weight' => '2',
    'children' => array(
      0 => 'field_remote_submission',
    ),
    'format_type' => 'htab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-gradessubmission field-group-htab',
        'id' => '',
      ),
    ),
  );
  $field_groups['group_gradessubmission|assessment_item|graded_item|gradebook_viewer'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Assessment');
  t('Assignment');
  t('Debug');
  t('Details');
  t('Student');
  t('Submission');
  t('Tabgroup');

  return $field_groups;
}
