<?php

/**
 * Callback for importing the schedule.
 */
function cis_user_import_form($form, $form_state) {
  $course = _cis_connector_course_context();
  $form['course'] = array(
    '#required' => '1',
    '#description' => t('The course and offering to add this roster to.'),
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
  $created = 0;
  $updated = 0;
  $state['values']['semester'] = check_plain($form_state['values']['semester']);
  $state['values']['year'] = check_plain($form_state['values']['year']);
  $state['values']['access_string'] = $file->uuid;
  $state['values']['course'] = check_plain($form_state['values']['course']);
  $state['values']['campus'] = check_plain($form_state['values']['campus']);
  $state['pass_through'] = TRUE;
  $state['triggering_element']['#parents'][0] = 'submit';
  // fake submit form
  module_load_include('inc', 'cis_helper', 'cis_helper.pages');
  drupal_form_submit('cis_helper_quick_setup_page', $state);
}
