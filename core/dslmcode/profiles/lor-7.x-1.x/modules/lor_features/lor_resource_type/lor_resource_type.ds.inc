<?php
/**
 * @file
 * lor_resource_type.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function lor_resource_type_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|resources|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'resources';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'links' => array(
      'weight' => '24',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '25',
      'label' => 'above',
      'format' => 'default',
    ),
    'author' => array(
      'weight' => '0',
      'label' => 'above',
      'format' => 'author_linked',
    ),
  );
  $export['node|resources|default'] = $ds_fieldsetting;

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|resources|teaser';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'resources';
  $ds_fieldsetting->view_mode = 'teaser';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
      'formatter_settings' => array(
        'link' => '1',
        'wrapper' => 'h2',
        'class' => '',
      ),
    ),
    'links' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'submitted_by' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'ds_post_date_medium',
    ),
  );
  $export['node|resources|teaser'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function lor_resource_type_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|resources|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'resources';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'right' => array(
        0 => 'author',
        5 => 'field_content_area',
        6 => 'field_mathematics',
        7 => 'field_language_arts',
        8 => 'field_social_studies',
        9 => 'field_science',
        10 => 'field_other_content_area',
        11 => 'field_technology',
        12 => 'field_elective_subjects',
        13 => 'field_literacy',
        14 => 'field_language',
        15 => 'field_resource_type',
        16 => 'field_licensing',
        17 => 'field_grade',
        18 => 'field_standards',
        19 => 'field_common_core_math',
        22 => 'field_common_core_la',
        24 => 'field_standards_ngss',
        26 => 'field_tags',
      ),
      'left' => array(
        1 => 'body',
        2 => 'field_learning_target',
        3 => 'field_link',
        4 => 'field_file_upload',
      ),
      'footer' => array(
        20 => 'field_assessment',
        21 => 'field_how_concepts_procedures',
        23 => 'field_student_skills',
        25 => 'field_what_concepts_procedures',
        27 => 'group_rquestions',
        28 => 'field_your_experience',
        29 => 'links',
        30 => 'comments',
        31 => 'group_questions1',
        32 => 'group_question2',
        33 => 'group_questions3',
        34 => 'group_questions4',
        35 => 'group_questions5',
      ),
    ),
    'fields' => array(
      'author' => 'right',
      'body' => 'left',
      'field_learning_target' => 'left',
      'field_link' => 'left',
      'field_file_upload' => 'left',
      'field_content_area' => 'right',
      'field_mathematics' => 'right',
      'field_language_arts' => 'right',
      'field_social_studies' => 'right',
      'field_science' => 'right',
      'field_other_content_area' => 'right',
      'field_technology' => 'right',
      'field_elective_subjects' => 'right',
      'field_literacy' => 'right',
      'field_language' => 'right',
      'field_resource_type' => 'right',
      'field_licensing' => 'right',
      'field_grade' => 'right',
      'field_standards' => 'right',
      'field_common_core_math' => 'right',
      'field_assessment' => 'footer',
      'field_how_concepts_procedures' => 'footer',
      'field_common_core_la' => 'right',
      'field_student_skills' => 'footer',
      'field_standards_ngss' => 'right',
      'field_what_concepts_procedures' => 'footer',
      'field_tags' => 'right',
      'group_rquestions' => 'footer',
      'field_your_experience' => 'footer',
      'links' => 'footer',
      'comments' => 'footer',
      'group_questions1' => 'footer',
      'group_question2' => 'footer',
      'group_questions3' => 'footer',
      'group_questions4' => 'footer',
      'group_questions5' => 'footer',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'header' => array(
        'rheader' => 'rheader',
      ),
      'left' => array(
        'rleft' => 'rleft',
      ),
      'right' => array(
        'rright' => 'rright',
      ),
      'footer' => array(
        'rfooter' => 'rfooter',
      ),
    ),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|resources|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|resources|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'resources';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked_fluid';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'title',
        1 => 'body',
        2 => 'field_learning_target',
        3 => 'field_essential_question',
      ),
      'left' => array(
        4 => 'field_resource_type',
        5 => 'field_grade',
        6 => 'field_language',
        7 => 'field_standards',
        8 => 'field_common_core_math',
        9 => 'field_common_core_la',
        10 => 'field_standards_ngss',
      ),
      'right' => array(
        11 => 'field_content_area',
        12 => 'field_mathematics',
        13 => 'field_language_arts',
        14 => 'field_social_studies',
        15 => 'field_science',
        16 => 'field_other_content_area',
        17 => 'field_technology',
        18 => 'field_elective_subjects',
        19 => 'field_literacy',
        20 => 'field_licensing',
        21 => 'field_tags',
      ),
      'footer' => array(
        22 => 'field_link',
        23 => 'field_file_upload',
        24 => 'field_assessment',
        25 => 'field_student_skills',
        26 => 'field_what_concepts_procedures',
        27 => 'field_how_concepts_procedures',
        28 => 'field_your_experience',
        29 => 'path',
      ),
      'hidden' => array(
        30 => 'flag',
        31 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'header',
      'body' => 'header',
      'field_learning_target' => 'header',
      'field_essential_question' => 'header',
      'field_resource_type' => 'left',
      'field_grade' => 'left',
      'field_language' => 'left',
      'field_standards' => 'left',
      'field_common_core_math' => 'left',
      'field_common_core_la' => 'left',
      'field_standards_ngss' => 'left',
      'field_content_area' => 'right',
      'field_mathematics' => 'right',
      'field_language_arts' => 'right',
      'field_social_studies' => 'right',
      'field_science' => 'right',
      'field_other_content_area' => 'right',
      'field_technology' => 'right',
      'field_elective_subjects' => 'right',
      'field_literacy' => 'right',
      'field_licensing' => 'right',
      'field_tags' => 'right',
      'field_link' => 'footer',
      'field_file_upload' => 'footer',
      'field_assessment' => 'footer',
      'field_student_skills' => 'footer',
      'field_what_concepts_procedures' => 'footer',
      'field_how_concepts_procedures' => 'footer',
      'field_your_experience' => 'footer',
      'path' => 'footer',
      'flag' => 'hidden',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(
      'layout_class' => array(
        'rstyle' => 'rstyle',
      ),
      'left' => array(
        'releft' => 'releft',
      ),
      'right' => array(
        'reright' => 'reright',
      ),
    ),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
    'layout_disable_css' => 0,
  );
  $export['node|resources|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|resources|teaser';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'resources';
  $ds_layout->view_mode = 'teaser';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'title',
        1 => 'submitted_by',
      ),
      'left' => array(
        2 => 'body',
      ),
      'right' => array(
        3 => 'field_resource_type',
        4 => 'field_content_area',
        5 => 'field_grade',
      ),
      'footer' => array(
        6 => 'links',
      ),
    ),
    'fields' => array(
      'title' => 'header',
      'submitted_by' => 'header',
      'body' => 'left',
      'field_resource_type' => 'right',
      'field_content_area' => 'right',
      'field_grade' => 'right',
      'links' => 'footer',
    ),
    'classes' => array(
      'layout_class' => array(
        '' => '',
      ),
      'header' => array(
        'rtheader' => 'rtheader',
      ),
      'left' => array(
        'rtleft' => 'rtleft',
      ),
      'right' => array(
        'rtright' => 'rtright',
      ),
      'footer' => array(
        'rtfooter' => 'rtfooter',
      ),
    ),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|resources|teaser'] = $ds_layout;

  return $export;
}
