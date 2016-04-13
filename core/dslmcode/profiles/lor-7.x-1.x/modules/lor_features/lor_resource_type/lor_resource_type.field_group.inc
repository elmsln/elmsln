<?php
/**
 * @file
 * lor_resource_type.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function lor_resource_type_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_question2|node|resources|default';
  $field_group->group_name = 'group_question2';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resources';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rquestions';
  $field_group->data = array(
    'label' => 'Student prerequisite skills and knowledge',
    'weight' => '39',
    'children' => array(
      0 => 'field_student_skills',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'Student prerequisite skills and knowledge',
      'instance_settings' => array(
        'classes' => 'group-question2 field-group-accordion-item baccordion-item',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_question2|node|resources|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_questions1|node|resources|default';
  $field_group->group_name = 'group_questions1';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resources';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rquestions';
  $field_group->data = array(
    'label' => 'How are the standards/objectives assessed?',
    'weight' => '38',
    'children' => array(
      0 => 'field_assessment',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'How are the standards/objectives assessed?',
      'instance_settings' => array(
        'classes' => 'group-questions1 field-group-accordion-item baccordion-item',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_questions1|node|resources|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_questions3|node|resources|default';
  $field_group->group_name = 'group_questions3';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resources';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rquestions';
  $field_group->data = array(
    'label' => 'How is the concept or procedure explained or demonstrated?',
    'weight' => '40',
    'children' => array(
      0 => 'field_how_concepts_procedures',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'How is the concept or procedure explained or demonstrated?',
      'instance_settings' => array(
        'classes' => 'group-questions3 field-group-accordion-item baccordion-item',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_questions3|node|resources|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_questions4|node|resources|default';
  $field_group->group_name = 'group_questions4';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resources';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rquestions';
  $field_group->data = array(
    'label' => 'What concepts or procedures are being explained or demonstrated in this lesson object?',
    'weight' => '41',
    'children' => array(
      0 => 'field_what_concepts_procedures',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'What concepts or procedures are being explained or demonstrated in this lesson object?',
      'instance_settings' => array(
        'classes' => 'group-questions4 field-group-accordion-item baccordion-item',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_questions4|node|resources|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_questions5|node|resources|default';
  $field_group->group_name = 'group_questions5';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resources';
  $field_group->mode = 'default';
  $field_group->parent_name = 'group_rquestions';
  $field_group->data = array(
    'label' => 'What was your experience, both successes and challenges, using this lesson object with your students?',
    'weight' => '42',
    'children' => array(
      0 => 'field_your_experience',
    ),
    'format_type' => 'accordion-item',
    'format_settings' => array(
      'label' => 'What was your experience, both successes and challenges, using this lesson object with your students?',
      'instance_settings' => array(
        'classes' => 'group-questions5 field-group-accordion-item baccordion-item',
      ),
      'formatter' => 'closed',
    ),
  );
  $field_groups['group_questions5|node|resources|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_rquestions|node|resources|default';
  $field_group->group_name = 'group_rquestions';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'resources';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Questions',
    'weight' => '23',
    'children' => array(
      0 => 'group_questions1',
      1 => 'group_question2',
      2 => 'group_questions3',
      3 => 'group_questions4',
      4 => 'group_questions5',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'label' => 'Questions',
      'instance_settings' => array(
        'classes' => 'group-rquestions field-group-accordion baccordion',
        'description' => '',
        'effect' => 'bounceslide',
      ),
    ),
  );
  $field_groups['group_rquestions|node|resources|default'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('How are the standards/objectives assessed?');
  t('How is the concept or procedure explained or demonstrated?');
  t('Questions');
  t('Student prerequisite skills and knowledge');
  t('What concepts or procedures are being explained or demonstrated in this lesson object?');
  t('What was your experience, both successes and challenges, using this lesson object with your students?');

  return $field_groups;
}
