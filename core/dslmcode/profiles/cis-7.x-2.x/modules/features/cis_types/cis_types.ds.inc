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
      'right' => array(
        0 => 'group_administrative',
        4 => 'field_ta_instructions',
        6 => 'group_resources',
        7 => 'field_ta_documents',
        13 => 'group_instructors',
        14 => 'field_inst_instructions',
        15 => 'field_inst_design_doc',
        16 => 'field_inst_delivery_guide',
        17 => 'field_inst_setup_guide',
        18 => 'field_inst_other_documents',
        19 => 'group_tas',
        20 => 'field_method_of_access',
        21 => 'field_display_in_course_list',
        22 => 'field_lead_instructor',
        23 => 'field_instructional_designer',
      ),
      'left' => array(
        1 => 'group_details',
        2 => 'group_samples',
        9 => 'body',
        10 => 'field_long_description',
        11 => 'field_topics_covered_text',
        12 => 'field_course_readings',
        24 => 'field_author_video',
        25 => 'field_banner',
        26 => 'field_screenshot',
        27 => 'title',
        28 => 'field_course_title',
        29 => 'field_machine_name',
        30 => 'field_program_classification',
        31 => 'field_academic_home',
        32 => 'group_promo_details',
        33 => 'field_credits',
        34 => 'field_first_offered',
        35 => 'field_sample_syllabus',
        36 => 'field_sample_lesson',
        37 => 'group_text_areas',
        38 => 'group_screenshots',
        39 => 'field_related_courses',
        40 => 'field_special_classifications',
        41 => 'field_university_bulletin',
        42 => 'field_course_author',
      ),
      'footer' => array(
        3 => 'path',
        5 => 'field_offerings',
        8 => 'group_offerings',
      ),
      'hidden' => array(
        43 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'group_administrative' => 'right',
      'group_details' => 'left',
      'group_samples' => 'left',
      'path' => 'footer',
      'field_ta_instructions' => 'right',
      'field_offerings' => 'footer',
      'group_resources' => 'right',
      'field_ta_documents' => 'right',
      'group_offerings' => 'footer',
      'body' => 'left',
      'field_long_description' => 'left',
      'field_topics_covered_text' => 'left',
      'field_course_readings' => 'left',
      'group_instructors' => 'right',
      'field_inst_instructions' => 'right',
      'field_inst_design_doc' => 'right',
      'field_inst_delivery_guide' => 'right',
      'field_inst_setup_guide' => 'right',
      'field_inst_other_documents' => 'right',
      'group_tas' => 'right',
      'field_method_of_access' => 'right',
      'field_display_in_course_list' => 'right',
      'field_lead_instructor' => 'right',
      'field_instructional_designer' => 'right',
      'field_author_video' => 'left',
      'field_banner' => 'left',
      'field_screenshot' => 'left',
      'title' => 'left',
      'field_course_title' => 'left',
      'field_machine_name' => 'left',
      'field_program_classification' => 'left',
      'field_academic_home' => 'left',
      'group_promo_details' => 'left',
      'field_credits' => 'left',
      'field_first_offered' => 'left',
      'field_sample_syllabus' => 'left',
      'field_sample_lesson' => 'left',
      'group_text_areas' => 'left',
      'group_screenshots' => 'left',
      'field_related_courses' => 'left',
      'field_special_classifications' => 'left',
      'field_university_bulletin' => 'left',
      'field_course_author' => 'left',
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
      'right' => array(
        2 => 'group_urls',
        6 => 'field_location',
        7 => 'field_data_location',
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
      'group_urls' => 'right',
      'field_distribution' => 'left',
      'body' => 'footer',
      'field_machine_name' => 'left',
      'field_location' => 'right',
      'field_data_location' => 'right',
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
