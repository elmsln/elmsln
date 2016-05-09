<?php
/**
 * @file
 * cis_types.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cis_types_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_access|field_collection_item|field_sections|form';
  $field_group->group_name = 'group_access';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Access Duration',
    'weight' => '1',
    'children' => array(
      0 => 'field_access_dates',
      1 => 'field_access_string',
      2 => 'field_course_start',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Access Duration',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_access|field_collection_item|field_sections|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_administrative|field_collection_item|field_sections|form';
  $field_group->group_name = 'group_administrative';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Administrative',
    'weight' => '2',
    'children' => array(
      0 => 'field_cis_ops',
      1 => 'field_course_archive',
      2 => 'group_setup',
      3 => 'group_teachers',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Administrative',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-administrative field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_administrative|field_collection_item|field_sections|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_administrative|node|course|form';
  $field_group->group_name = 'group_administrative';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Administrative',
    'weight' => '0',
    'children' => array(
      0 => 'field_display_in_course_list',
      1 => 'field_instructional_designer',
      2 => 'field_lead_instructor',
      3 => 'field_method_of_access',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Administrative',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-administrative field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_administrative|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_archives|field_collection_item|field_offerings|form';
  $field_group->group_name = 'group_archives';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_offerings';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Archives',
    'weight' => '2',
    'children' => array(
      0 => 'field_course_archive',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-archives field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_archives|field_collection_item|field_offerings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_course_files|field_collection_item|field_sections|form';
  $field_group->group_name = 'group_course_files';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_syllabus';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '14',
    'children' => array(
      0 => 'field_syllabus',
      1 => 'field_welcome_letter',
      2 => 'field_syllabus_text_based',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-course-files field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_course_files|field_collection_item|field_sections|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|course|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '1',
    'children' => array(
      0 => 'field_academic_home',
      1 => 'field_course_title',
      2 => 'field_machine_name',
      3 => 'field_program_classification',
      4 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_details|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|program|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_abbreviation',
      1 => 'field_academic_home',
      2 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-details field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_details|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_details|node|service|form';
  $field_group->group_name = 'group_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'service';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '0',
    'children' => array(
      0 => 'field_distribution',
      1 => 'field_machine_name',
      2 => 'title',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-details field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_details|node|service|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_files|field_collection_item|field_sections|full';
  $field_group->group_name = 'group_files';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Files',
    'weight' => '5',
    'children' => array(
      0 => 'field_welcome_letter',
    ),
    'format_type' => 'accordion',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-files field-group-accordion',
      ),
    ),
  );
  $field_groups['group_files|field_collection_item|field_sections|full'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_instructors|node|course|form';
  $field_group->group_name = 'group_instructors';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_resources';
  $field_group->data = array(
    'label' => 'Instructors',
    'weight' => '13',
    'children' => array(
      0 => 'field_inst_delivery_guide',
      1 => 'field_inst_design_doc',
      2 => 'field_inst_instructions',
      3 => 'field_inst_other_documents',
      4 => 'field_inst_setup_guide',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Instructors',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-instructors field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_instructors|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_marketing|node|program|form';
  $field_group->group_name = 'group_marketing';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'program';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Marketing',
    'weight' => '4',
    'children' => array(
      0 => 'field_facebook',
      1 => 'field_program_site',
      2 => 'field_twitter',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-marketing field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_marketing|node|program|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_offerings|node|course|form';
  $field_group->group_name = 'group_offerings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Offerings',
    'weight' => '5',
    'children' => array(
      0 => 'field_offerings',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Offerings',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-offerings field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_offerings|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personel|node|academic_unit|form';
  $field_group->group_name = 'group_personel';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'academic_unit';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personel',
    'weight' => '3',
    'children' => array(
      0 => 'field_coordinators',
      1 => 'field_unit_head',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-personel field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_personel|node|academic_unit|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_promo_details|node|course|form';
  $field_group->group_name = 'group_promo_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_samples';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '46',
    'children' => array(
      0 => 'field_course_author',
      1 => 'field_credits',
      2 => 'field_first_offered',
      3 => 'field_related_courses',
      4 => 'field_sample_lesson',
      5 => 'field_sample_syllabus',
      6 => 'field_special_classifications',
      7 => 'field_university_bulletin',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Details',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-promo-details field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_promo_details|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_resources|node|course|form';
  $field_group->group_name = 'group_resources';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Resources',
    'weight' => '4',
    'children' => array(
      0 => 'group_instructors',
      1 => 'group_tas',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Resources',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-resources field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_resources|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_samples|node|course|form';
  $field_group->group_name = 'group_samples';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Promotional',
    'weight' => '2',
    'children' => array(
      0 => 'group_screenshots',
      1 => 'group_text_areas',
      2 => 'group_promo_details',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Promotional',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-samples field-group-fieldset',
        'description' => 'Fields related to the promotion of the course and marketing on this website.',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_samples|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_screenshots|node|course|form';
  $field_group->group_name = 'group_screenshots';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_samples';
  $field_group->data = array(
    'label' => 'Visuals',
    'weight' => '51',
    'children' => array(
      0 => 'field_author_video',
      1 => 'field_banner',
      2 => 'field_screenshot',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Visuals',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-screenshots field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_screenshots|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_sections|field_collection_item|field_offerings|form';
  $field_group->group_name = 'group_sections';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_offerings';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Sections',
    'weight' => '1',
    'children' => array(
      0 => 'field_sections',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-sections field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_sections|field_collection_item|field_offerings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_semester|field_collection_item|field_offerings|form';
  $field_group->group_name = 'group_semester';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_offerings';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Semester',
    'weight' => '0',
    'children' => array(
      0 => 'field_semester',
      1 => 'field_year',
    ),
    'format_type' => 'tab',
    'format_settings' => array(
      'formatter' => 'closed',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-semester field-group-tab',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_semester|field_collection_item|field_offerings|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_setup|field_collection_item|field_sections|form';
  $field_group->group_name = 'group_setup';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_administrative';
  $field_group->data = array(
    'label' => 'Setup',
    'weight' => '2',
    'children' => array(
      0 => 'field_campus',
      1 => 'field_schedule_number',
      2 => 'field_section_number',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Setup',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_setup|field_collection_item|field_sections|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_syllabus|field_collection_item|field_sections|form';
  $field_group->group_name = 'group_syllabus';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Semester Logistics',
    'weight' => '0',
    'children' => array(
      0 => 'field_resources',
      1 => 'field_services',
      2 => 'group_course_files',
      3 => 'group_text_areas',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Semester Logistics',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $field_groups['group_syllabus|field_collection_item|field_sections|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_tas|node|course|form';
  $field_group->group_name = 'group_tas';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_resources';
  $field_group->data = array(
    'label' => 'Teaching Assistants',
    'weight' => '19',
    'children' => array(
      0 => 'field_ta_documents',
      1 => 'field_ta_instructions',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Teaching Assistants',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-tas field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_tas|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_teachers|field_collection_item|field_sections|form';
  $field_group->group_name = 'group_teachers';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_administrative';
  $field_group->data = array(
    'label' => 'Teachers',
    'weight' => '3',
    'children' => array(
      0 => 'field_instructor_of_record',
      1 => 'field_teaching_assistants',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Teachers',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => '',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_teachers|field_collection_item|field_sections|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_text_areas|field_collection_item|field_sections|form';
  $field_group->group_name = 'group_text_areas';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_syllabus';
  $field_group->data = array(
    'label' => 'Text areas',
    'weight' => '15',
    'children' => array(
      0 => 'field_contact_info',
      1 => 'field_welcome_page',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-text-areas field-group-fieldset',
        'required_fields' => 1,
      ),
    ),
  );
  $field_groups['group_text_areas|field_collection_item|field_sections|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_text_areas|node|course|form';
  $field_group->group_name = 'group_text_areas';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'course';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_samples';
  $field_group->data = array(
    'label' => 'Text areas',
    'weight' => '50',
    'children' => array(
      0 => 'body',
      1 => 'field_course_readings',
      2 => 'field_long_description',
      3 => 'field_topics_covered_text',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Text areas',
      'instance_settings' => array(
        'required_fields' => 0,
        'classes' => ' group-text-areas field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_text_areas|node|course|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_urls|node|service|form';
  $field_group->group_name = 'group_urls';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'service';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'URLs',
    'weight' => '1',
    'children' => array(
      0 => 'field_data_location',
      1 => 'field_location',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => 'group-urls field-group-fieldset',
        'required_fields' => 1,
        'id' => '',
      ),
    ),
  );
  $field_groups['group_urls|node|service|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_wholething|field_collection_item|field_sections|full';
  $field_group->group_name = 'group_wholething';
  $field_group->entity_type = 'field_collection_item';
  $field_group->bundle = 'field_sections';
  $field_group->mode = 'full';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Whole thing',
    'weight' => '0',
    'children' => array(),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => ' group-wholething field-group-fieldset',
      ),
    ),
  );
  $field_groups['group_wholething|field_collection_item|field_sections|full'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Access Duration');
  t('Administrative');
  t('Archives');
  t('Details');
  t('Files');
  t('Instructors');
  t('Marketing');
  t('Offerings');
  t('Personel');
  t('Promotional');
  t('Resources');
  t('Sections');
  t('Semester');
  t('Semester Logistics');
  t('Setup');
  t('Teachers');
  t('Teaching Assistants');
  t('Text areas');
  t('URLs');
  t('Visuals');
  t('Whole thing');

  return $field_groups;
}
