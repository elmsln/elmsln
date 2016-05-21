<?php

/**
 * Callback for importing the schedule.
 */
function cis_user_import_form($form, $form_state) {
  // the schedule
  //$form['markup'] = array('#markup' => t('FILE FORMAT: _ for spaces') . '<br/>');
  $course = _cis_connector_course_context();
  $form['course'] = array(
    '#required' => '1',
    '#description' => t('The courses to establish the offering for'),
    '#type' => 'select',
    '#options' => _cis_connector_assemble_entity_list('node', 'course', 'nid', 'title'),
    '#title' => t('Course'),
    '#default_value' => $course,
  );
  // @todo need to add support for section so that we can tie this to a section file field somehow
  // file import
  $form['user_import_file'] = array(
    '#required' => '1',
    '#description' => t('Users in csv format'),
    '#type' => 'managed_file',
    '#size' => '30',
    '#title' => t('Users'),
    '#upload_location' => 'public://user_import_files/',
    '#upload_validators' => array(
      'file_validate_extensions' => array(
        0 => 'csv',
      ),
      'file_validate_size' => array(
        0 => 10485760,
      ),
    ),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import Users'),
  );

  return $form;
}

/**
 * Submit handler for importing users
 */
function cis_user_import_form_submit($form, $form_state) {
  // process the file we got
  $file = file_load($form_state['values']['user_import_file']);
  $location = drupal_realpath($file->uri);
  # header can be variable this way
  $header = NULL;
  $fcontent = file_get_contents($location);
  $created = 0;
  $updated = 0;
  // convert csv items to an array format
  $rows = _cis_user_csv_to_array($fcontent, $header);
  foreach ($rows as $row) {
    // user didn't load, let's make one
    $role = user_role_load_by_name($row['role']);
    // try and load the account first
    // @ignore druplart_conditional_assignment
    if (!$account = user_load_by_name($row['username'])) {
      $fields = array(
        'name' => $row['username'],
        'mail' => $row['email'],
        'pass' => user_password(20),
        'status' => 1,
        'roles' => array(
          DRUPAL_AUTHENTICATED_RID => 'authenticated user',
          $role->rid => $role->name,
        ),
      );
      // the first parameter is left blank so a new user is created
      $account = user_save('', $fields);
      $created++;
    }
    else {
      // only save role if it is new
      if (!isset($account->roles[$role->rid])) {
        $account->roles[$role->rid] = $role->name;
        user_save($account);
        $updated++;
      }
    }
  }
  // @todo ship around the course network once we have section
  drupal_set_message(t('@count processed, @created accounts created, @updated accounts updated', array('@count' => count($rows), '@created' => $created, '@updated' => $updated)), 'status');
}


