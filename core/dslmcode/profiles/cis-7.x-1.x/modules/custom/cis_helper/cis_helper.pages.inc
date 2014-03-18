<?php
/**
 * @file
 * User page callbacks for the cis_helper module.
 */

/**
 * Callback for setting up an offering for existing courses.
 */
function cis_helper_add_offering_page($form, $form_state) {
  // allow for access string prepopulation to auto submit
  $course = check_plain(arg(1));
  $semester = check_plain(arg(2));
  $year = check_plain(arg(3));
  $access_string = check_plain(arg(4));
  // ensure all 4 values are set if we're going to auto-populate
  if (!empty($course) && !empty($semester) && !empty($year) && !empty($access_string)) {
    $data = array(
      'context_id' => $access_string,
      'context_label' => $access_string,
      'user_id' => $GLOBALS['user']->name,
      'lis_person_contact_email_primary' => $GLOBALS['user']->mail,
      'lis_person_name_given' => $GLOBALS['user']->field_first_name['und'][0]['value'],
      'lis_person_name_family' => $GLOBALS['user']->field_last_name['und'][0]['value'],
      'roles' => 'Instructor',
      'course' => array(
        'machine_name' => $course,
        'name' => $course,
      ),
      'section' => array(
        'semester' => $semester,
        'year' => $year,
      ),
    );
    // convert to fake LTI launch info since page can handle it
    $options = array(
      'query' => array(
        'lti_launch' => drupal_json_encode($data),
      ),
    );
    // fake an LTI launch to setup the page faster
    drupal_goto('cis-quick-setup', $options);
  }
  // select the course desired
  $form['courses'] = array(
    '#required' => '1',
    '#description' => t('The courses to establish the offering for'),
    '#type' => 'select',
    '#options' => _cis_helper_assemble_entity_list('node', 'course', 'field_machine_name', 'title', array('field_display_in_course_list' => 1)),
    '#title' => t('Course'),
    '#default_value' => $course,
  );
  // list of available semesters for this offering
  $field = field_info_field('field_semester');
  $form['semester'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Semester'),
    '#default_value' => $semester,
  );
  // academic year of this offering
  $field = field_info_field('field_year');
  $form['year'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Year'),
    '#default_value' => $year,
  );
  // access string that can be used for LMS synchronization
  $form['access_string'] = array(
    '#required' => '1',
    '#description' => t('The access string to bind to, this is the primary key for this course section.'),
    '#type' => 'textfield',
    '#title' => t('Access string'),
    '#default_value' => $access_string,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Add offering'),
  );
  return $form;
}

/**
 * Submit handler for cis_helper_add_offering_page.
 */
function cis_helper_add_offering_page_submit($form, $form_state) {
  // context_id is actually access_string
  $access_string = check_plain($form_state['values']['access_string']);
  $data = array(
    'context_id' => $access_string,
    'context_label' => $access_string,
    'user_id' => $GLOBALS['user']->name,
    'lis_person_contact_email_primary' => $GLOBALS['user']->mail,
  );
  // convert to fake LTI launch info since page can handle it
  $options = array(
    'query' => array(
      'lti_launch' => drupal_json_encode($data),
    ),
  );
  // fake an LTI launch to setup the page faster
  drupal_goto('cis-quick-setup', $options);
}

/**
 * Callback for setting up course by knowing access string.
 */
function cis_helper_quick_setup_access_id_page($form, $form_state) {
  // allow for access string prepopulation to auto submit
  $access_string = check_plain(arg(1));
  if (!empty($access_string)) {
    $data = array(
      'context_id' => $access_string,
      'context_label' => $access_string,
      'user_id' => $GLOBALS['user']->name,
      'lis_person_contact_email_primary' => $GLOBALS['user']->mail,
      'lis_person_name_given' => $GLOBALS['user']->field_first_name['und'][0]['value'],
      'lis_person_name_family' => $GLOBALS['user']->field_last_name['und'][0]['value'],
      'roles' => 'Instructor',
    );
    // convert to fake LTI launch info since page can handle it
    $options = array(
      'query' => array(
        'lti_launch' => drupal_json_encode($data),
      ),
    );
    // fake an LTI launch to setup the page faster
    drupal_goto('cis-quick-setup', $options);
  }
  $form['access_string'] = array(
    '#required' => '1',
    '#description' => t('The access string to bind to, this is the primary key for this course section.'),
    '#type' => 'textfield',
    '#title' => t('Access string'),
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Setup access'),
  );
  return $form;
}

/**
 * Submit handler for cis_helper_offering_planning_page.
 */
function cis_helper_quick_setup_access_id_page_submit($form, $form_state) {
  // context_id is actually access_string
  $access_string = check_plain($form_state['values']['access_string']);
  $data = array(
    'context_id' => $access_string,
    'context_label' => $access_string,
    'user_id' => $GLOBALS['user']->name,
    'lis_person_contact_email_primary' => $GLOBALS['user']->mail,
  );
  // convert to fake LTI launch info since page can handle it
  $options = array(
    'query' => array(
      'lti_launch' => drupal_json_encode($data),
    ),
  );
  // fake an LTI launch to setup the page faster
  drupal_goto('cis-quick-setup', $options);
}

/**
 * Callback for offering planning
 */
function cis_helper_offering_planning_page($form, $form_state) {
  // list of available semesters for this offering
  $field = field_info_field('field_semester');
  $form['semester'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Semester'),
  );
  // academic year of this offering
  $field = field_info_field('field_year');
  $form['year'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Year'),
  );
  // select the course desired
  $form['courses'] = array(
    '#required' => '1',
    '#multiple' => '1',
    '#key_type_toggled' => '1',
    '#description' => t('The courses to establish offerings for'),
    '#type' => 'checkboxes',
    '#options' => _cis_helper_assemble_entity_list('node', 'course', 'nid', 'title', array('field_display_in_course_list' => 1)),
    '#multiple_toggle' => '1',
    '#theme' => 'cis_helper_checkbox_table',
    '#title' => t('Course'),
  );
  // list of available campuses to generate sections for this offering
  $field = field_info_field('field_campus');
  $form['campuses'] = array(
    '#required' => '0',
    '#multiple' => '1',
    '#key_type_toggled' => '1',
    '#type' => 'checkboxes',
    '#theme' => 'cis_helper_checkbox_table',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Campus'),
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create planned offerings'),
  );
  return $form;
}

/**
 * Submit handler for cis_helper_offering_planning_page.
 */
function cis_helper_offering_planning_page_submit($form, $form_state) {
  $year = $form_state['values']['year'];
  $semester = $form_state['values']['semester'];
  $courses = entity_load('node', $form_state['values']['courses']);
  foreach ($courses as $nid => $course) {
    $offering = NULL;
    $offerings = array();
    $offering_refs = array();
    // make sure that this course doesn't already have an offering for this semester/year
    if (!empty($course->field_offerings)) {
      foreach ($course->field_offerings[LANGUAGE_NONE] as $offering_ref) {
        $offering_refs[] = $offering_ref['value'];
      }
      $query = new EntityFieldQuery;
      $result = $query
        // select all field collections
        ->entityCondition('entity_type', 'field_collection_item')
        // that are offerings
        ->entityCondition('bundle', 'field_offerings')
        // that have an internal id associated to the current course
        ->propertyCondition('item_id', $offering_refs, 'IN')
        // and semester of the one submitted
        ->fieldCondition('field_semester', 'value', $semester, '=')
        // and year of the one submitted
        ->fieldCondition('field_year', 'value', $year, '=')
        // load as user 1 to ignore access issues for current user
        ->addMetaData('account', user_load(1))
        ->execute();
      // if we had results, set the offering
      if (isset($result['field_collection_item'])) {
        $item = array_keys($result['field_collection_item']);
        $offerings = entity_load('field_collection_item', $item);
        $offering = array_pop($offerings);
      }
    }
    // create an offering if we didn't select one above
    if (is_null($offering)) {
      // now work on the offering
      $offering = entity_create('field_collection_item', array('field_name' => 'field_offerings'));
      // associate this offering to the course
      $offering->setHostEntity('node', $course);
      // set semester
      $offering->field_semester[LANGUAGE_NONE][0]['value'] = $semester;
      // set year
      $offering->field_year[LANGUAGE_NONE][0]['value'] = $year;
      // make sure it isn't archived
      $offering->archived = 0;
      drupal_set_message(t("Created @course offering for @sem @year", array('@course' => $course->title, '@sem' => $semester, '@year' => $year)), 'notice');
    }
    else {
      drupal_set_message(t("@course had an offering listed for @sem @year so it was not created", array('@course' => $course->title, '@sem' => $semester, '@year' => $year)), 'warning');
    }
    // allow for auto section stub-population of sections for campuses
    $campuses = array();
    // convert from null to key values since drupal sends checkboxes oddly
    foreach ($form_state['values']['campuses'] as $code) {
      if ($code != '0' && !empty($code) && $code != '') {
        $campuses[] = $code;
      }
    }
    // if no campuses to build then save offering as a container
    if (empty($campuses)) {
      $offering->save();
    }
    else {
      // build a section for each campus requested, looking for existing
      foreach ($campuses as $key => $campus) {
        $campus_match = NULL;
        $sec_match = NULL;
        // make sure that there's a campus code set
        if ($campus != '') {
          // check for existing references to this offering / campus combo
          $section_refs = array();
          if (isset($offering->field_sections)) {
            foreach ($offering->field_sections[LANGUAGE_NONE] as $section_ref) {
              $section_refs[] = $section_ref['value'];
            }
          }
          $result = array();
          // make sure we have references
          if (!empty($section_refs)) {
            $query = new EntityFieldQuery;
            $result = $query
              // select all field collections
              ->entityCondition('entity_type', 'field_collection_item')
              // that are offerings
              ->entityCondition('bundle', 'field_sections')
              // that have an internal id associated to the current course
              ->propertyCondition('item_id', $section_refs, 'IN')
              // and campus matches this one
              ->fieldCondition('field_campus', 'value', $campus, '=')
              // load as user 1 to ignore access issues for current user
              ->addMetaData('account', user_load(1))
              ->execute();
          }
          // if we had results, set the offering
          if (isset($result['field_collection_item'])) {
            drupal_set_message(t("@course had a section listed for campus @campus for @sem @year so it was not created", array('@course' => $course->title, '@campus' => $campus, '@sem' => $semester, '@year' => $year)), 'warning');
          }
          else {
            // select all offerings for this course, looking for a past one
            $tmprefs = array();
            if (!empty($offering_refs)) {
              $query = new EntityFieldQuery;
              $query
                // select all field collections
                ->entityCondition('entity_type', 'field_collection_item')
                // that are offerings
                ->entityCondition('bundle', 'field_offerings')
                // that have an internal id associated to the current course
                ->propertyCondition('item_id', $offering_refs, 'IN')
                // order by ID descending so most recent is picked
                ->propertyOrderBy('item_id', 'DESC')
                // limit range to 1 item
                ->range(0, 1)
                // load as user 1 to ignore access issues for current user
                ->addMetaData('account', user_load(1));
              // make sure it's not the current one being acted on
              if (isset($offering->item_id) && !is_null($offering->item_id)) {
                $query->propertyCondition('item_id', $offering->item_id, '<>');
              }
              $result = $query->execute();
              $tmpoff = array();
              // if we had results, set the offering
              if (isset($result['field_collection_item'])) {
                $item = array_keys($result['field_collection_item']);
                $tmp = entity_load('field_collection_item', $item);
                $tmpoff = array_pop($tmp);
              }
              // see if this found anything
              // check for existing references to this offering / campus combo
              if (isset($tmpoff->field_sections)) {
                foreach ($tmpoff->field_sections[LANGUAGE_NONE] as $tmpref) {
                  $tmprefs[] = $tmpref['value'];
                }
              }
              // sort just to be safe
              sort($tmprefs);
              $result = array();
              $sec_match = NULL;
              $campus_match = NULL;
              // make sure we have references
              if (!empty($tmprefs)) {
                $query = new EntityFieldQuery;
                $result = $query
                  // select all field collections
                  ->entityCondition('entity_type', 'field_collection_item')
                  // that are offerings
                  ->entityCondition('bundle', 'field_sections')
                  // that have an internal id associated to the current course
                  ->propertyCondition('item_id', $tmprefs, 'IN')
                  // load as user 1 to ignore access issues for current user
                  ->addMetaData('account', user_load(1))
                  ->execute();
                // if we had results, look through them
                if (isset($result['field_collection_item'])) {
                  $item = array_keys($result['field_collection_item']);
                  $past_sections = entity_load('field_collection_item', $item);
                  foreach ($past_sections as $sec) {
                    if ($sec->field_campus['und'][0]['value'] == $campus) {
                      $campus_match = $sec;
                    }
                    else {
                      $sec_match = $sec;
                    }
                  }
                }
              }
            }
            // create the new section container
            $section = entity_create('field_collection_item', array('field_name' => 'field_sections'));
            // associate this section to the offering
            $section->setHostEntity('field_collection_item', $offering);
            // set the campus code
            $section->field_campus[LANGUAGE_NONE][0]['value'] = $campus;
            // see if we found anything worth trying for additional field population
            if (!is_null($campus_match) || !is_null($sec_match)) {
              // give priority to a past campus code match
              if (!is_null($campus_match)) {
                $clone = replicate_clone_entity('field_collection_item', $campus_match);
              }
              else {
                $clone = replicate_clone_entity('field_collection_item', $sec_match);
              }
              // dup data that's possibly useful
              $section->field_welcome_page = $clone->field_welcome_page;
              $section->field_contact_info = $clone->field_contact_info;
              $section->field_resources = $clone->field_resources;
              $section->field_services = $clone->field_services;
            }
            // save section
            $section->save();
            drupal_set_message(t("Created @course campus section @campus for @sem @year", array('@course' => $course->title, '@campus' => $campus, '@sem' => $semester, '@year' => $year)), 'notice');
          }
        }
      }
    }
  }
}

/**
 * Callback for quick setup page to build a lot of elements at once.
 *
 * At the end this will setup a course, offering, section, and service instance
 * on an as needed basis.  This is primarily used for handling LTI launches
 * as they can be rather complex in translation to actual information in CIS.
 */
function cis_helper_quick_setup_page() {
  global $user;
  $form = array();
  // allow for new courses to be created from here
  $options = array('new' => t('New'));
  // build list of node entities from structured EFQ
  $options += _cis_helper_assemble_entity_list('node', 'course', 'field_machine_name', 'title');
  // select the course desired
  $form['course'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#description' => t('The course that this is associated to'),
    '#type' => 'select',
    '#options' => $options,
    '#multiple_toggle' => '1',
    '#default_value' => 'new',
    '#title' => t('Course'),
  );
  // container for settings related to a new course
  $form['new_course'] = array(
    '#description' => t('Settings that only apply to new courses'),
    '#collapsed' => '0',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('New Course settings'),
  );
  // new course name
  $form['new_course']['new_name'] = array(
    '#required' => '0',
    '#description' => t('Name of the new course to create.'),
    '#type' => 'textfield',
    '#title' => t('Course name'),
  );
  // new course name
  $form['new_course']['new_title'] = array(
    '#required' => '0',
    '#description' => t('Title of the new course.'),
    '#type' => 'textfield',
    '#title' => t('Course title'),
  );
  // access level
  $form['new_course']['access'] = array(
    '#required' => '1',
    '#description' => t('How restrictive would you like access to be?'),
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#default_value' => CIS_HELPER_DEFAULT_AUTHENTICATION,
    '#type' => 'select',
    '#options' => array(
      'open' => t('Open course - publicly available'),
      'authenticated' => t('Require login'),
      'lms' => t('Limit access to my students'),
      'code' => t('Activation code'),
    ),
    '#multiple_toggle' => '1',
    '#title' => t('Method of access'),
  );
  $options = _cis_helper_get_instructional_outlines();
  $options[variable_get('file_public_path', conf_path() . '/files') . '/cis_outline_import/'] = t('CIS Outline Import (on server)');
  // add purely administrative options as part of advanced migration
  if (user_access('cis setup admin options')) {
    $options['xml_manifest_import'] = t('Upload..');
  }
  $form['details'] = array(
    '#description' => t('Only modify these if you need to.'),
    '#collapsed' => '0',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('Request details'),
  );
  $form['logistics'] = array(
    '#description' => t('These are required to setup any section effectively'),
    '#collapsed' => '0',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('Section logistics'),
  );
  $form['details']['instructional_outline'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#required' => TRUE,
    '#title' => t('Instructional outline'),
    '#description' => t('This helps in creating a default instructional flow for the course, this just helps provide a starting point.'),
    '#default_value' => drupal_get_path('module', 'cis_helper') . '/instructional_models/' . CIS_HELPER_DEFAULT_CONTENT_OUTLINE,
  );
  if (user_access('cis setup admin options')) {
    $form['details']['xml_manifest_import'] = array(
      '#required' => '0',
      '#description' => t('Use this to import from an XML based version of a course outline.'),
      '#type' => 'managed_file',
      '#size' => '30',
      '#title' => t('XML manifest'),
      '#upload_location' => 'public://xml_manifest_import/',
      '#upload_validators' => array(
        'file_validate_extensions' => array(
          0 => 'xml',
        ),
        'file_validate_size' => array(
          0 => 10485760,
        ),
      ),
    );
  }
  // list of services
  $service_list = _cis_helper_assemble_entity_list('node', 'service', 'nid', 'title');
  // remove anything with (dev) in title
  foreach ($service_list as $key => $name) {
    if (strpos($name, '(dev)')) {
      unset($service_list[$key]);
    }
  }
  $form['details']['services'] = array(
    '#multiple' => TRUE,
    '#required' => TRUE,
    '#key_type_toggled' => '1',
    '#description' => t('The service to deploy for this course'),
    '#type' => 'checkboxes',
    '#options' => $service_list,
    '#multiple_toggle' => '1',
    '#title' => t('Service'),
  );
  // offering container
  $form['details']['offering'] = array(
    '#description' => t('The point in time that this course is being offered'),
    '#collapsed' => '0',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('Offering'),
  );
  // list of available semesters for this offering
  $field = field_info_field('field_semester');
  $form['details']['offering']['semester'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Semester'),
  );
  // academic year of this offering
  $field = field_info_field('field_year');
  $form['details']['offering']['year'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Year'),
  );
  // section container
  $form['details']['section'] = array(
    '#description' => t('Details related to creation of a section'),
    '#collapsed' => '0',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('Section'),
  );
  // section number of record
  $form['details']['section']['number'] = array(
    '#description' => t('Section number supplied by the registrar.'),
    '#type' => 'textfield',
    '#title' => t('Section number'),
  );
  // campus code of record
  $form['details']['section']['campus'] = array(
    '#description' => t('Campus code used to identify where this offering takes place.'),
    '#type' => 'textfield',
    '#title' => t('Campus code'),
  );
  // access strings / primary key for binding access across services
  $form['details']['section']['access_string'] = array(
    '#required' => '0',
    '#description' => t('The access string to bind to, this is the primary key for this course section.'),
    '#type' => 'textfield',
    '#title' => t('Access string'),
  );
  // instructor of record
  $form['details']['section']['instructor'] = array(
    '#required' => '1',
    '#description' => t('Instructor of record for the course'),
    '#type' => 'textfield',
    '#default_value' => $user->name,
    '#title' => t('Instructor of record'),
  );
  // the syllabus to use for the section to be created
  $form['logistics']['syllabus'] = array(
    '#required' => '0',
    '#description' => t('(PDF only) syllabus for the course'),
    '#type' => 'managed_file',
    '#size' => '30',
    '#title' => t('Syllabus'),
    '#upload_location' => 'public://syllabi/',
    '#upload_validators' => array(
      'file_validate_extensions' => array(
        0 => 'pdf',
      ),
      'file_validate_size' => array(
        0 => 10485760,
      ),
    ),
  );
  // the syllabus to use for the section to be created
  $form['logistics']['welcome_letter'] = array(
    '#required' => '0',
    '#description' => t('(PDF only) Welcome letter for the course'),
    '#type' => 'managed_file',
    '#size' => '30',
    '#title' => t('Welcome letter'),
    '#upload_location' => 'public://welcome_letters/',
    '#upload_validators' => array(
      'file_validate_extensions' => array(
        0 => 'pdf',
      ),
      'file_validate_size' => array(
        0 => 10485760,
      ),
    ),
  );
  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create course'),
  );
  return $form;
}

/**
 * Implements hook_submit().
 */
function cis_helper_quick_setup_page_submit($form, $form_state) {
  // load account and values for later
  $account = user_load_by_name($form_state['values']['instructor']);
  $offering = NULL;
  $semester = $form_state['values']['semester'];
  $year = $form_state['values']['year'];
  $instructional_outline = $form_state['values']['instructional_outline'];
  // check for admin settings
  $xml_manifest_import = FALSE;
  if (user_access('cis setup admin options') && $form_state['values']['xml_manifest_import'] != '') {
    // load the file into an object
    $xml_manifest_import = file_load($form_state['values']['xml_manifest_import']);
    // save file
    file_save($xml_manifest_import);
  }
  // load the services node id items into a list
  $services = entity_load('node', $form_state['values']['services']);
  // first step is to create the course if it exists
  if ($form_state['values']['course'] == 'new') {
    $name = check_plain($form_state['values']['new_name']);
    // make course, then we need to generate the ids
    $course = new stdClass();
    $course->type = 'course';
    $course->status = 1;
    $course->revision = 1;
    $course->language = LANGUAGE_NONE;
    // created by the system so root user
    $course->uid = 1;
    $course->title = $name;
    // set course title
    $course->field_course_title[LANGUAGE_NONE][0]['value'] = check_plain($form_state['values']['new_title']);
    // generate machine name
    $mname = preg_replace('/[^a-z0-9_]+/', '', drupal_strtolower($name));
    // max size of machine name is 16
    if (strlen($mname) > 10) {
      $mname = substr($mname, 0, 10);
    }
    $course->field_machine_name[LANGUAGE_NONE][0]['value'] = $mname;
    // method of access
    $course->field_method_of_access[LANGUAGE_NONE][0]['value'] = $form_state['values']['access'];
    node_save($course);
  }
  else {
    // load array of course machine names based on EFQ
    $courses = _cis_helper_assemble_entity_list('node', 'course', 'field_machine_name', 'nid');
    // this will be the entity id for a course
    $etid = $courses[$form_state['values']['course']];
    $course = entity_load_single('node', $etid);
  }
  // check for instructional outline special case for on server import
  if ($instructional_outline == variable_get('file_public_path', conf_path() . '/files') . '/cis_outline_import/') {
    $instructional_outline .= $course->field_machine_name[LANGUAGE_NONE][0]['value'] . '.xml';
  }
  // make sure that this course doesn't already have an offering for this semester/year
  if (!empty($course->field_offerings)) {
    foreach ($course->field_offerings[LANGUAGE_NONE] as $offering_ref) {
      $offering_refs[] = $offering_ref['value'];
    }
    $query = new EntityFieldQuery;
    $result = $query
      // select all field collections
      ->entityCondition('entity_type', 'field_collection_item')
      // that are offerings
      ->entityCondition('bundle', 'field_offerings')
      // that have an internal id associated to the current course
      ->propertyCondition('item_id', $offering_refs, 'IN')
      // and semester of the one submitted
      ->fieldCondition('field_semester', 'value', $semester, '=')
      // and year of the one submitted
      ->fieldCondition('field_year', 'value', $year, '=')
      // load as user 1 to ignore access issues for current user
      ->addMetaData('account', user_load(1))
      ->execute();
    // if we had results, set the offering
    if (isset($result['field_collection_item'])) {
      $item = array_keys($result['field_collection_item']);
      $offerings = entity_load('field_collection_item', $item);
      $offering = array_pop($offerings);
    }
  }
  // create an offering if we didn't select one above
  if (is_null($offering)) {
    // now work on the offering
    $offering = entity_create('field_collection_item', array('field_name' => 'field_offerings'));
    // associate this offering to the course
    $offering->setHostEntity('node', $course);
    // set semester
    $offering->field_semester[LANGUAGE_NONE][0]['value'] = $semester;
    // set year
    $offering->field_year[LANGUAGE_NONE][0]['value'] = $year;
  }
  // now work on the section
  $section = entity_create('field_collection_item', array('field_name' => 'field_sections'));
  // associate this section to the offering
  $section->setHostEntity('field_collection_item', $offering);
  // set the section number
  $section->field_section_number[LANGUAGE_NONE][0]['value'] = $form_state['values']['number'];
  // set the campus code
  $section->field_campus[LANGUAGE_NONE][0]['value'] = $form_state['values']['campus'];
  // set the access string
  $section->field_access_string[LANGUAGE_NONE][0]['value'] = $form_state['values']['access_string'];
  // set the entity reference field (user)
  $section->field_instructor_of_record[LANGUAGE_NONE][0]['target_id'] = $account->uid;
  // set the services in use to the ones just created
  $serv_count = 0;
  foreach ($form_state['values']['services'] as $serv_item) {
    $section->field_services[LANGUAGE_NONE][$serv_count] = array('target_id' => $serv_item);
    $serv_count++;
  }
  // look up past ones
  if ($form_state['values']['course'] != 'new') {
    $offering_refs = array();
    // make sure that this course doesn't already have an offering for this semester/year
    if (!empty($course->field_offerings)) {
      foreach ($course->field_offerings[LANGUAGE_NONE] as $offering_ref) {
        if (isset($offering_ref['value'])) {
          $offering_refs[] = $offering_ref['value'];
        }
      }
      $query = new EntityFieldQuery;
      $result = $query
        // select all field collections
        ->entityCondition('entity_type', 'field_collection_item')
        // that are offerings
        ->entityCondition('bundle', 'field_offerings')
        // that have an internal id associated to the current course
        ->propertyCondition('item_id', $offering_refs, 'IN')
        // and semester of the one submitted
        ->fieldCondition('field_semester', 'value', $semester, '=')
        // and year of the one submitted
        ->fieldCondition('field_year', 'value', $year, '=')
        // load as user 1 to ignore access issues for current user
        ->addMetaData('account', user_load(1))
        ->execute();
      // if we had results, set the offering
      if (isset($result['field_collection_item'])) {
        $item = array_keys($result['field_collection_item']);
        $offerings = entity_load('field_collection_item', $item);
        $offering = array_pop($offerings);
      }
    }
    if (!empty($offering_refs)) {
      $query = new EntityFieldQuery;
      $query
        // select all field collections
        ->entityCondition('entity_type', 'field_collection_item')
        // that are offerings
        ->entityCondition('bundle', 'field_offerings')
        // that have an internal id associated to the current course
        ->propertyCondition('item_id', $offering_refs, 'IN')
        // order by ID descending so most recent is picked
        ->propertyOrderBy('item_id', 'DESC')
        // limit range to 1 item
        ->range(0, 1)
        // load as user 1 to ignore access issues for current user
        ->addMetaData('account', user_load(1));
      // make sure it's not the current one being acted on
      if (isset($offering->item_id) && !is_null($offering->item_id)) {
        $query->propertyCondition('item_id', $offering->item_id, '<>');
      }
      $result = $query->execute();
      $tmpoff = array();
      // if we had results, set the offering
      if (isset($result['field_collection_item'])) {
        $item = array_keys($result['field_collection_item']);
        $tmp = entity_load('field_collection_item', $item);
        $tmpoff = array_pop($tmp);
      }
      // see if this found anything
      // check for existing references to this offering / campus combo
      if (isset($tmpoff->field_sections)) {
        foreach ($tmpoff->field_sections[LANGUAGE_NONE] as $tmpref) {
          $tmprefs[] = $tmpref['value'];
        }
        // sort just to be safe
        sort($tmprefs);
      }
      $result = array();
      $sec_match = NULL;
      $campus_match = NULL;
      // make sure we have references
      if (!empty($tmprefs)) {
        $query = new EntityFieldQuery;
        $result = $query
          // select all field collections
          ->entityCondition('entity_type', 'field_collection_item')
          // that are offerings
          ->entityCondition('bundle', 'field_sections')
          // that have an internal id associated to the current course
          ->propertyCondition('item_id', $tmprefs, 'IN')
          // load as user 1 to ignore access issues for current user
          ->addMetaData('account', user_load(1))
          ->execute();
        // if we had results, look through them
        if (isset($result['field_collection_item'])) {
          $item = array_keys($result['field_collection_item']);
          $past_sections = entity_load('field_collection_item', $item);
          foreach ($past_sections as $sec) {
            if ($sec->field_campus['und'][0]['value'] == $campus) {
              $campus_match = $sec;
            }
            else {
              $sec_match = $sec;
            }
          }
        }
      }
    }
    // see if we found anything worth trying for additional field population
    if (!is_null($campus_match) || !is_null($sec_match)) {
      // give priority to a past campus code match
      if (!is_null($campus_match)) {
        $clone = replicate_clone_entity('field_collection_item', $campus_match);
      }
      else {
        $clone = replicate_clone_entity('field_collection_item', $sec_match);
      }
      // dup data that's possibly useful
      $section->field_welcome_page = $clone->field_welcome_page;
      $section->field_contact_info = $clone->field_contact_info;
      $section->field_resources = $clone->field_resources;
      $section->field_services = $clone->field_services;
    }
  }
  // special handling for files, if added
  $file_check = array('syllabus', 'welcome_letter');
  foreach ($file_check as $file_name) {
    // make sure the file came across
    if ($form_state['values'][$file_name] != '') {
      // load the file into an object
      $file = file_load($form_state['values'][$file_name]);
      // Change status to permanent so it isn't killed on cron clean up
      $file->status = FILE_STATUS_PERMANENT;
      // save file
      file_save($file);
      // silly typecast of file object to array for field happiness
      $file_ary = (array)$file;
      // set the file to be displayed on this field_collection_item
      $file_ary['display'] = 1;
      // field names must match files to check
      $field_name = 'field_' . $file_name;
      // set the section's file field to match file array
      $section->{$field_name}[LANGUAGE_NONE][0] = $file_ary;
    }
  }
  // allow other modules to alter information
  drupal_alter('cis_quick_submit', $section, $offering);
  // save section
  $section->save();
  $instances_created = array();
  // now work on the services if needed
  foreach ($services as $service) {
    $query = new EntityFieldQuery;
    $result = $query
      // select all nodes
      ->entityCondition('entity_type', 'node')
      // that are service instances
      ->entityCondition('bundle', 'service_instance')
      // that match the node id of services
      ->fieldCondition('field_services', 'target_id', $service->nid, '=')
      // and also are associated to the current course
      ->fieldCondition('field_course', 'target_id', $course->nid, '=')
      // query as user 1
      ->addMetaData('account', user_load(1))
      ->execute();
    // verify this service doesn't already exist
    if (count($result) == 0) {
      // make course, then we need to generate the ids
      $instance = new stdClass();
      $instance->type = 'service_instance';
      $instance->status = 1;
      $instance->revision = 1;
      $instance->language = LANGUAGE_NONE;
      // set an easy to read title
      $instance->title = $course->field_machine_name[LANGUAGE_NONE][0]['value'] . ' - ' . $service->field_machine_name[LANGUAGE_NONE][0]['value'];
      // created by the system so root user
      $instance->uid = 1;
      // set the entity reference field to service
      $instance->field_services[LANGUAGE_NONE][0]['target_id'] = $service->nid;
      // set the entity reference field to course
      $instance->field_course[LANGUAGE_NONE][0]['target_id'] = $course->nid;
      // repurpose the general data field
      if (user_access('cis setup admin options') && isset($xml_manifest_import->uri)) {
        $instance->field_service_data[LANGUAGE_NONE][0]['value'] = drupal_realpath($xml_manifest_import->uri);
      }
      else {
        $instance->field_service_data[LANGUAGE_NONE][0]['value'] = getcwd() . '/' . $instructional_outline;
      }
      // this will create the service because of the hook_entity_insert used here
      node_save($instance);
      // create a file based on service name
      $filename = $course->field_machine_name[LANGUAGE_NONE][0]['value'] . '.' . $service->field_machine_name[LANGUAGE_NONE][0]['value'];
      // bring along expected filename that points to the instance data
      $instances_created[$service->field_machine_name[LANGUAGE_NONE][0]['value']] = array(
        'filename' => $filename,
        'instance' => $instance,
        'course' => $course,
        'service' => $service,
      );
    }
  }
  // invoke batch API if not from command line
  if (!empty($instances_created) && !drupal_is_cli()) {
    _cis_helper_batch_add_service_instances($instances_created);
  }
}

/**
 * Batch process to check for creation script's status.
 */
function _cis_helper_batch_add_service_instances($instances_created) {
  // establish the base for the batch call array
  $batch = array(
    'finished' => '_cis_helper_batch_add_service_instances_finished',
    'title' => t('Creating @course', array('@course' => $instances_created[CIS_HELPER_COURSE_SERVICE]['course']->title)),
    'init_message' => t('Waiting for server to start site request..'),
    'progress_message' => t('Step @current out of @total.'),
    'error_message' => t('Request has encountered an error.'),
    'file' => drupal_get_path('module', 'cis_helper') . '/cis_helper.pages.inc',
  );
  // default redirect location in case courses isn't requested
  $redirect = 'cis-quick-setup';
  // add an operation per service instance requested
  foreach ($instances_created as $instance) {
    $filepath = variable_get('cis_job_path', CIS_HELPER_JOB_PATH) . '/' . $instance['filename'];
    // mooc is the starting point distro for a course so account for that
    if ($instance['service']->field_machine_name[LANGUAGE_NONE][0]['value'] == CIS_HELPER_COURSE_SERVICE) {
      $redirect = $instance['service']->field_location[LANGUAGE_NONE][0]['url'] . '/' . $instance['course']->field_machine_name[LANGUAGE_NONE][0]['value'];
      // capture so we can add this last
      $mooc = array('_cis_helper_batch_add_service_instances_process', array($instance['instance'], $instance['course'], $instance['service'], $instance['filename'], $filepath));
    }
    else {
      $batch['operations'][] = array('_cis_helper_batch_add_service_instances_process', array($instance['instance'], $instance['course'], $instance['service'], $instance['filename'], $filepath));
    }
  }
  // move course to the last service created if multiple invoked
  // this makes the eventual redirect more logical
  if (isset($mooc)) {
    $batch['operations'][] = $mooc;
  }
  batch_set($batch);
  batch_process($redirect);
}

/**
 * Batch Operation Callback to test if the step the job is running.
 */
function _cis_helper_batch_add_service_instances_process($service_instance, $course, $service, $filename, $filepath, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['max'] = 180;
  }
  // see if the count down timer is here
  if (isset($context['sandbox']['start_timer'])) {
    $context['sandbox']['timer'] = $context['sandbox']['start_timer'] - time();
  }
  // look for the file, if the filename exists, it hasn't started yet
  // we continue to maintain the waiting message
  if (file_exists($filepath)) {
    $context['message'] = t('Waiting for server to start site request..');
  }
  else {
    // when the filename no longer exists, this means that it's been picked up
    if (file_exists($filepath . '.progress')) {
      $step = file_get_contents($filepath . '.progress');
      // start the timer at 3 minutes
      if (!isset($context['sandbox']['start_timer'])) {
        $context['sandbox']['start_timer'] = strtotime('+3 minutes', time());
        $context['sandbox']['timer'] = $context['sandbox']['start_timer'] - time();
      }
      switch ($step) {
        case 1:
          // scipt started
          $context['message'] = t('Starting error checking..');
        break;
        case 2:
          // right before drush si
          $context['message'] = t('Installing `@service` for `@course`', array('@service' => $service->title, '@course' => $course->title));
        break;
        case 3:
          // right after drush si
          $context['message'] = t('`@service` Installation complete! Verifying install..', array('@service' => $service->title, '@course' => $course->title));
        break;
        case 4:
          // after si cleanup, before drush commands
          $context['message'] = t('Install verification complete! Integration with ELMSLN systems and optimizing your new site.');
          // this is only true the first time step 4 is noticed
          if ($step != $context['sandbox']['step']) {
            // we've seen the overall script take about 3 minutes
            $context['sandbox']['start_timer'] = strtotime('+2 minutes', time());
            $context['sandbox']['progress'] = 60;
          }
        break;
        case 5:
          // after drush commands
          $context['message'] = t('Integration complete! Doing minor clean up and emailing!');
        break;
        case 6:
          // done
          if ($service->field_machine_name[LANGUAGE_NONE][0]['value'] == CIS_HELPER_COURSE_SERVICE) {
            $context['message'] = t('`@service` created successfully! We are redirecting you to `@course` now!', array('@service' => $service->title, '@course' => $course->title));
          }
          else {
            $context['message'] = t('`@service` created successfully!', array('@service' => $service->title));
          }
          $context['sandbox']['progress'] = $context['sandbox']['max'];
        break;
      }
      // don't add time to wait for last step
      if ($step != 6) {
        // make sure that start timer has actually started to set timer
        if (isset($context['sandbox']['start_timer'])) {
          $context['sandbox']['progress'] = $context['sandbox']['max'] - ((int)(date('i', $context['sandbox']['timer']) * 60) + (int)date('s', $context['sandbox']['timer']));
				}
        // make sure we don't go below 0
        if ($context['sandbox']['timer'] > 0) {
          $time_msg = date('i:s', $context['sandbox']['timer']);
        }
        else {
          $time_msg = t('Very soon..');
        }
        $context['message'] .= ' ' . t('Estimated time remaining: @time', array('@time' => $time_msg));
      }
      // switch progress to this step
      $context['sandbox']['step'] = $step;
    }
  }
	// account for timer running down before it's actually done
	if ($context['sandbox']['progress'] == $context['sandbox']['max'] && $step != 6) {
		$context['sandbox']['progress'] = $context['sandbox']['max'] - 1;
	}
  // account for ability for timer to be running but progress file go away
  // if this happens at the exact right moment, the job is finished
  // but will never actually show via the UI that this has happened.
  if (file_exists($filepath . '.processed') && !file_exists($filepath . '.progress')) {
    $context['sandbox']['progress'] = $context['sandbox']['max'];
    $context['finished'] = 1;
  }
  // Inform the batch engine that we are not finished,
  // and provide an estimation of the completion level we reached.
  if ($context['sandbox']['progress'] != $context['sandbox']['max']) {
    $context['finished'] = $context['sandbox']['progress'] / $context['sandbox']['max'];
  }
}

/**
 * Batch 'finished' callback.
 */
function _cis_helper_batch_add_service_instances_finished($success, $results, $operations) {
  if (!$success) {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
    drupal_set_message($message, 'error');
  }
  else {
    // prevent message from printing as this should now be redirecting if it
    // successfully created something
    drupal_get_messages();
  }
}
