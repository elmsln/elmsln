<?php

/**
 * @file
 *
 * Administration functions for the File (Field) Paths module.
 */

/**
 * @param $form
 * @param $form_state
 * @return mixed
 */
function filefield_paths_settings_form($form, $form_state) {
  $form['filefield_paths_temp_location'] = array(
    '#title'            => t('Temporary file location'),
    '#type'             => 'textfield',
    '#default_value'    => variable_get('filefield_paths_temp_location', 'public://filefield_paths'),
    '#description'      => t('The location that unprocessed files will be uploaded priot to being processed by File (Field) Paths.<br />It is recommended that you use the temporary file system (temporary://) if your server configuration allows for that.'),
    '#element_validate' => array('filefield_paths_settings_form_temp_location_validate'),
  );

  return system_settings_form($form);
}

/**
 * Validation callback for 'Temporary file location' setting.
 *
 * @param $element
 * @param $form_state
 * @return bool
 */
function filefield_paths_settings_form_temp_location_validate($element, $form_state) {
  $scheme = file_uri_scheme($element['#value']);
  if (!$scheme) {
    form_error($element, t('Invalid file location. You must include a file stream wrapper (e.g., public://).'));
    return FALSE;
  }

  if (!file_stream_wrapper_valid_scheme($scheme)) {
    form_error($element, t('Invalid file stream wrapper.'));
    return FALSE;
  }

  if ((!is_dir($element['#value']) || !is_writable($element['#value'])) && !file_prepare_directory($element['#value'], FILE_CREATE_DIRECTORY | FILE_MODIFY_PERMISSIONS)) {
    form_error($element, t('File location can not be created or is not writable.'));
    return FALSE;
  }
}