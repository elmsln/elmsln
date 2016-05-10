<?php
/**
 * @file
 * User page callbacks for the cis_helper module.
 */

function cis_helper_sync_network_roster($node) {
  // @todo pass in a token of some kind
  // issue this against all remote things to tell them to sync up
  $requests = array(
    array(
      'elmsln_module' => 'cis_section',
      'elmsln_callback' => 'sync_roster',
    ),
  );
  _elmsln_api_network_request($requests, '1', TRUE, '/' . $node->field_machine_name['und'][0]['value'] . '/');
  drupal_set_message(t('Course roster has been synced across all services.'), 'status', FALSE);
  drupal_goto('node/' . $node->nid);
}

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
    '#options' => _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'title'),
    '#title' => t('Course'),
    '#default_value' => $course,
  );
  // academic year of this offering
  $field = field_info_field('field_campus');
  $form['campus'] = array(
    '#required' => '1',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Campus'),
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
  $form['actions']['submit_another'] = array(
    '#type' => 'submit',
    '#value' => t('Create and add another'),
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
  // populate form_state for passing to durpal_form_submit of cis-quick-setup
  $state['values']['semester'] = check_plain($form_state['values']['semester']);
  $state['values']['year'] = check_plain($form_state['values']['year']);
  $state['values']['access_string'] = check_plain($form_state['values']['access_string']);
  $state['values']['course'] = check_plain($form_state['values']['courses']);
  $state['values']['campus'] = check_plain($form_state['values']['campus']);
  $state['pass_through'] = TRUE;
  $state['triggering_element']['#parents'][0] = 'submit';

  // fake submit form
  drupal_form_submit('cis_helper_quick_setup_page', $state);
  // if told to just Add
  if ($form_state['values']['op'] == 'Add offering') {
    drupal_goto(check_plain($form_state['values']['courses']) . '/offerings');
  }
  else {
    $vars = array(
      '@string' => $form_state['values']['access_string'],
      '@course' => $form_state['values']['courses'],
      '@semester' => $form_state['values']['semester'],
      '@year' => $form_state['values']['year'],
      '@campus' => $form_state['values']['campus'],
      );
    drupal_set_message(t('Successfully created @course @semester @year @campus offering with access ID @string!', $vars), 'info');
  }
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
 * Submit handler for LTI launch reroute.
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
 * Callback for quick setup page to build a lot of elements at once.
 *
 * At the end this will setup a course, offering, section, and service instance
 * on an as needed basis.  This is primarily used for handling LTI launches
 * as they can be rather complex in translation to actual information in CIS.
 */
function cis_helper_quick_setup_page($form = array(), &$form_state) {
  global $user;
  // allow for new courses to be created from here
  $options = array('new' => t('New'));
  // build list of node entities from structured EFQ
  $options += _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'title');
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
  // support for gitbook
  if (module_exists('gitphp')) {
    $options['git_book_import'] = t('Git outline import');
  }
  $form['details'] = array(
    '#description' => t('What systems would you like to make up your course network?'),
    '#collapsed' => '0',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('Network structure'),
  );
  $form['optional'] = array(
    '#description' => t('Additional settings for setting up logistics'),
    '#collapsed' => '1',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('Additional settings'),
  );
  $form['details']['instructional_outline'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#required' => FALSE,
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
  // add git_book field for import if it exists
  if (module_exists('gitphp')) {
    $form['details']['git_book_import'] = array(
      '#title' => t('GIT repository'),
      '#type' => 'textfield',
      '#description' => t('Enter a .git repo URL'),
      '#required' => '0',
    );
  }
  // list of services
  $service_list = _cis_connector_assemble_entity_list('node', 'service', 'nid', 'title');
  $form['details']['services'] = array(
    '#multiple' => TRUE,
    '#required' => FALSE,
    '#key_type_toggled' => '1',
    '#description' => t("What services would you like to use in this course network?"),
    '#type' => 'checkboxes',
    '#options' => $service_list,
    '#multiple_toggle' => '1',
    '#title' => t('Course network'),
  );
  // section container
  $form['optional']['section'] = array(
    '#description' => t('Details related to creation of a section'),
    '#collapsed' => '1',
    '#type' => 'fieldset',
    '#collapsible' => '1',
    '#title' => t('Section'),
  );
  // list of available semesters for this offering
  $field = field_info_field('field_semester');
  $form['optional']['section']['semester'] = array(
    '#required' => '0',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => array('' => '') + $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Semester'),
  );
  // academic year of this offering
  $field = field_info_field('field_year');
  $form['optional']['section']['year'] = array(
    '#required' => '0',
    '#multiple' => '0',
    '#key_type_toggled' => '1',
    '#type' => 'select',
    '#options' => array('' => '') + $field['settings']['allowed_values'],
    '#multiple_toggle' => '1',
    '#title' => t('Year'),
  );
  // section number of record
  $form['optional']['section']['number'] = array(
    '#description' => t('Section number supplied by the registrar.'),
    '#type' => 'textfield',
    '#title' => t('Section number'),
  );
  // campus code of record
  $form['optional']['section']['campus'] = array(
    '#description' => t('Campus code used to identify where this offering takes place.'),
    '#type' => 'textfield',
    '#title' => t('Campus code'),
  );
  // access strings / primary key for binding access across services
  $form['optional']['section']['access_string'] = array(
    '#required' => '0',
    '#description' => t('The access string to bind to, this is the primary key for this course section.'),
    '#type' => 'textfield',
    '#title' => t('Access string'),
  );
  // the syllabus to use for the section to be created
  $form['optional']['section']['syllabus'] = array(
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
  $form['optional']['section']['welcome_letter'] = array(
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
  $offering = NULL;
  $semester = $form_state['values']['semester'];
  $year = $form_state['values']['year'];
  $campus = $form_state['values']['campus'];
  $instructional_outline = $form_state['values']['instructional_outline'];
  // check for admin settings
  $xml_manifest_import = FALSE;
  if (user_access('cis setup admin options') && $form_state['values']['xml_manifest_import'] != '' && $form_state['values']['xml_manifest_import']['fid'] != 0) {
    // load the file into an object
    $xml_manifest_import = file_load($form_state['values']['xml_manifest_import']);
    // save file
    file_save($xml_manifest_import);
  }
  elseif (user_access('cis setup admin options') && $instructional_outline == 'git_book_import' && $form_state['values']['git_book_import'] != '') {
    $repo = $form_state['values']['git_book_import'];
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
    $mname = preg_replace('/[^a-z0-9]+/', '', drupal_strtolower($name));
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
    $courses = _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'nid');
    // this will be the entity id for a course
    $etid = $courses[$form_state['values']['course']];
    $course = entity_load_single('node', $etid);
  }
  // check for instructional outline special case for on server import
  if ($instructional_outline == variable_get('file_public_path', conf_path() . '/files') . '/cis_outline_import/') {
    $instructional_outline .= $course->field_machine_name[LANGUAGE_NONE][0]['value'] . '.xml';
  }
  // make sure we actually are making an offering / section before delving
  // into any of this. it's not needed for OER for example and doesn't
  // actually match the workflow of setting courses up and building them the
  // first time.
  if (!empty($year) && !empty($semester)) {
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
    $section->field_campus[LANGUAGE_NONE][0]['value'] = $campus;
    // set the access string
    $section->field_access_string[LANGUAGE_NONE][0]['value'] = $form_state['values']['access_string'];
    // set the entity reference field (user)
    $section->field_instructor_of_record[LANGUAGE_NONE][0]['target_id'] = $GLOBALS['user']->uid;
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
          $offering_refs[] = (isset($offering_ref['value']) ? $offering_ref['value'] : '');
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
              if (isset($sec->field_campus['und']) && $sec->field_campus['und'][0]['value'] == $campus) {
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
      if ($form_state['values'][$file_name] != '' && $form_state['values'][$file_name]['fid'] != 0) {
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
  }
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
      elseif (isset($repo)) {
        $instance->field_service_data[LANGUAGE_NONE][0]['value'] = $repo;
      }
      else {
        $instance->field_service_data[LANGUAGE_NONE][0]['value'] = getcwd() . '/' . $instructional_outline;
      }
      // this will create the service because of the hook_entity_insert used here
      node_save($instance);
    }
  }
  // pin prick all
  $requests = array(
    array(
      'method' => 'POST',
      'api' => 1,
      'data' => array(
        'elmsln_module' => 'elmsln_api',
        'elmsln_callback' => 'clear_cache_bin',
        'bin' => 'cis_connector',
      ),
    )
  );
  _elmsln_api_authority_request($requests, TRUE, array('cis'));
  // issue against network
  $requests = array(
    array(
      'elmsln_module' => 'elmsln_api',
      'elmsln_callback' => 'clear_cache_bin',
      'bin' => 'cis_connector',
    )
  );
  // sync section system wide if set
  if (isset($section)) {
    // force session context to be course that's being created
    // otherwise it won't return anything though these calls may go no where
    $_SESSION['cis_course_context'] = $course->field_machine_name[LANGUAGE_NONE][0]['value'];
    $properties = array(
      'title' => $section->field_access_string['und'][0]['value'],
      'section_id' => $section->field_access_string['und'][0]['value'],
      'course' => $course->uuid,
      'active' => _cis_helper_section_is_active($section),
    );
    _elmsln_api_section_sync($properties);
  }
  // allow other forms to ride off this one without forcing a redirect
  if (!isset($form_state['pass_through'])) {
    drupal_goto($course->field_machine_name[LANGUAGE_NONE][0]['value'] . '/service-instances');
  }
}
