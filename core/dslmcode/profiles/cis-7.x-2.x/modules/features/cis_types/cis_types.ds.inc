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
        1 => 'group_samples',
        2 => 'group_administrative',
        5 => 'field_ta_instructions',
        7 => 'field_ta_documents',
        10 => 'body',
        12 => 'field_long_description',
        15 => 'field_topics_covered_text',
        16 => 'field_course_readings',
        17 => 'field_inst_instructions',
        18 => 'field_inst_design_doc',
        19 => 'field_inst_delivery_guide',
        20 => 'field_inst_setup_guide',
        21 => 'field_inst_other_documents',
        22 => 'field_lead_instructor',
        23 => 'field_instructional_designer',
        24 => 'group_instructors',
        25 => 'group_tas',
        26 => 'group_resources',
        27 => 'field_author_video',
        28 => 'field_screenshot',
        29 => 'field_method_of_access',
        30 => 'title',
        31 => 'field_course_title',
        32 => 'group_promo_details',
        33 => 'field_banner',
        34 => 'field_credits',
        35 => 'field_machine_name',
        36 => 'field_first_offered',
        37 => 'field_display_in_course_list',
        38 => 'field_sample_syllabus',
        39 => 'group_text_areas',
        40 => 'field_sample_lesson',
        41 => 'field_program_classification',
        42 => 'group_screenshots',
        43 => 'field_related_courses',
        44 => 'field_academic_home',
        45 => 'field_special_classifications',
        46 => 'field_university_bulletin',
        47 => 'field_course_author',
      ),
      'footer' => array(
        3 => 'path',
        4 => 'group_offerings',
        6 => 'field_offerings',
      ),
      'hidden' => array(
        8 => 'revision_information',
        9 => 'hidden_nodes',
        11 => 'author',
        13 => 'book',
        14 => 'options',
        48 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'group_details' => 'header',
      'group_samples' => 'header',
      'group_administrative' => 'header',
      'path' => 'footer',
      'group_offerings' => 'footer',
      'field_ta_instructions' => 'header',
      'field_offerings' => 'footer',
      'field_ta_documents' => 'header',
      'revision_information' => 'hidden',
      'hidden_nodes' => 'hidden',
      'body' => 'header',
      'author' => 'hidden',
      'field_long_description' => 'header',
      'book' => 'hidden',
      'options' => 'hidden',
      'field_topics_covered_text' => 'header',
      'field_course_readings' => 'header',
      'field_inst_instructions' => 'header',
      'field_inst_design_doc' => 'header',
      'field_inst_delivery_guide' => 'header',
      'field_inst_setup_guide' => 'header',
      'field_inst_other_documents' => 'header',
      'field_lead_instructor' => 'header',
      'field_instructional_designer' => 'header',
      'group_instructors' => 'header',
      'group_tas' => 'header',
      'group_resources' => 'header',
      'field_author_video' => 'header',
      'field_screenshot' => 'header',
      'field_method_of_access' => 'header',
      'title' => 'header',
      'field_course_title' => 'header',
      'group_promo_details' => 'header',
      'field_banner' => 'header',
      'field_credits' => 'header',
      'field_machine_name' => 'header',
      'field_first_offered' => 'header',
      'field_display_in_course_list' => 'header',
      'field_sample_syllabus' => 'header',
      'group_text_areas' => 'header',
      'field_sample_lesson' => 'header',
      'field_program_classification' => 'header',
      'group_screenshots' => 'header',
      'field_related_courses' => 'header',
      'field_academic_home' => 'header',
      'field_special_classifications' => 'header',
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
