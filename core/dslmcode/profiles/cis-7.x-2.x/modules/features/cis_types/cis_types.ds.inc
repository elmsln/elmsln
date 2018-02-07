<?php
/**
 * @file
 * cis_types.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function cis_types_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|academic_unit|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'academic_unit';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
        1 => 'field_abbreviation',
        2 => 'field_color',
      ),
      'right' => array(
        3 => 'group_personel',
        5 => 'field_unit_head',
        6 => 'field_coordinators',
      ),
      'footer' => array(
        4 => 'path',
      ),
      'hidden' => array(
        7 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'field_abbreviation' => 'left',
      'field_color' => 'left',
      'group_personel' => 'right',
      'path' => 'footer',
      'field_unit_head' => 'right',
      'field_coordinators' => 'right',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
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
  $export['node|academic_unit|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|course|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'course';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'group_details',
        3 => 'group_resources',
        4 => 'field_ta_instructions',
        5 => 'group_samples',
        7 => 'field_ta_documents',
        12 => 'field_lead_instructor',
        13 => 'field_instructional_designer',
        14 => 'body',
        15 => 'field_long_description',
        16 => 'group_instructors',
        18 => 'group_tas',
        19 => 'field_topics_covered_text',
        21 => 'field_course_readings',
        22 => 'field_inst_instructions',
        23 => 'field_inst_design_doc',
        24 => 'field_inst_delivery_guide',
        25 => 'field_inst_setup_guide',
        26 => 'field_inst_other_documents',
        27 => 'field_author_video',
        28 => 'field_screenshot',
        29 => 'field_method_of_access',
        30 => 'title',
        31 => 'field_course_title',
        32 => 'group_promo_details',
        33 => 'field_banner',
        34 => 'field_credits',
        35 => 'field_first_offered',
        36 => 'field_machine_name',
        37 => 'field_sample_syllabus',
        38 => 'group_text_areas',
        39 => 'field_sample_lesson',
        40 => 'field_display_in_course_list',
        41 => 'field_related_courses',
        42 => 'field_program_classification',
        43 => 'group_screenshots',
        44 => 'field_special_classifications',
        45 => 'field_academic_home',
        46 => 'field_university_bulletin',
        47 => 'field_course_author',
      ),
      'hidden' => array(
        1 => 'group_internal_logistics',
        8 => 'field_elmsln_course_competencies',
        10 => 'field_sis_course_id',
        11 => 'revision_information',
        17 => 'author',
        20 => 'options',
        48 => '_add_existing_field',
      ),
      'footer' => array(
        2 => 'group_offerings',
        6 => 'field_offerings',
        9 => 'path',
      ),
    ),
    'fields' => array(
      'group_details' => 'header',
      'group_internal_logistics' => 'hidden',
      'group_offerings' => 'footer',
      'group_resources' => 'header',
      'field_ta_instructions' => 'header',
      'group_samples' => 'header',
      'field_offerings' => 'footer',
      'field_ta_documents' => 'header',
      'field_elmsln_course_competencies' => 'hidden',
      'path' => 'footer',
      'field_sis_course_id' => 'hidden',
      'revision_information' => 'hidden',
      'field_lead_instructor' => 'header',
      'field_instructional_designer' => 'header',
      'body' => 'header',
      'field_long_description' => 'header',
      'group_instructors' => 'header',
      'author' => 'hidden',
      'group_tas' => 'header',
      'field_topics_covered_text' => 'header',
      'options' => 'hidden',
      'field_course_readings' => 'header',
      'field_inst_instructions' => 'header',
      'field_inst_design_doc' => 'header',
      'field_inst_delivery_guide' => 'header',
      'field_inst_setup_guide' => 'header',
      'field_inst_other_documents' => 'header',
      'field_author_video' => 'header',
      'field_screenshot' => 'header',
      'field_method_of_access' => 'header',
      'title' => 'header',
      'field_course_title' => 'header',
      'group_promo_details' => 'header',
      'field_banner' => 'header',
      'field_credits' => 'header',
      'field_first_offered' => 'header',
      'field_machine_name' => 'header',
      'field_sample_syllabus' => 'header',
      'group_text_areas' => 'header',
      'field_sample_lesson' => 'header',
      'field_display_in_course_list' => 'header',
      'field_related_courses' => 'header',
      'field_program_classification' => 'header',
      'group_screenshots' => 'header',
      'field_special_classifications' => 'header',
      'field_academic_home' => 'header',
      'field_university_bulletin' => 'header',
      'field_course_author' => 'header',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
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
  $export['node|course|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|program|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'program';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'group_details',
        1 => 'title',
        2 => 'field_abbreviation',
        3 => 'field_academic_home',
      ),
      'right' => array(
        4 => 'group_marketing',
        6 => 'field_program_site',
        8 => 'field_twitter',
        9 => 'field_facebook',
      ),
      'footer' => array(
        5 => 'body',
        7 => 'path',
      ),
      'hidden' => array(
        10 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'group_details' => 'left',
      'title' => 'left',
      'field_abbreviation' => 'left',
      'field_academic_home' => 'left',
      'group_marketing' => 'right',
      'body' => 'footer',
      'field_program_site' => 'right',
      'path' => 'footer',
      'field_twitter' => 'right',
      'field_facebook' => 'right',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
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
  $export['node|program|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|service|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'service';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'group_details',
        1 => 'title',
        3 => 'field_distribution',
        5 => 'field_machine_name',
      ),
      'footer' => array(
        4 => 'body',
        8 => 'path',
      ),
      'hidden' => array(
        9 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'group_details' => 'left',
      'title' => 'left',
      'field_distribution' => 'left',
      'body' => 'footer',
      'field_machine_name' => 'left',
      'path' => 'footer',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
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
  $export['node|service|form'] = $ds_layout;

  return $export;
}
