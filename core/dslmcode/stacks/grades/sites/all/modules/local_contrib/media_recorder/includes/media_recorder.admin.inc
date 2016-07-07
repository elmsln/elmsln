<?php

/**
 * @file
 * Admin only functionality for the media_recorder module.
 */

/**
 * Menu form callback; Display the media_recorder admin form.
 */
function media_recorder_admin_form($form, $form_state) {

  // Check that all libraries exist.
  $required_libraries = array('swfobject', 'recorder.js', 'Recorderjs');
  foreach ($required_libraries as $name) {
    $library = libraries_detect($name);
    if (!$library['installed']) {
      drupal_set_message($library['error message'], 'error');
    }
  }

  $form['media_recorder_time_limit'] = array(
    '#type' => 'textfield',
    '#title' => t('Time Limit'),
    '#description' => t('Time limit in seconds. Defaults to 300 seconds (5 minutes).'),
    '#default_value' => variable_get('media_recorder_time_limit', 300),
    '#element_validate' => array('element_validate_integer_positive'),
    '#required' => TRUE,
  );

  // Recorder upload directory.
  $form['media_recorder_upload_directory'] = array(
    '#type' => 'textfield',
    '#title' => t("File directory for uploaded recordings"),
    '#default_value' => variable_get('media_recorder_upload_directory', ''),
    '#description' => t('Optional subdirectory within the upload destination where files will be stored. Do not include preceding or trailing slashes.'),
  );

  // Recorder upload directory token support.
  if (module_exists('token')) {
    $form['media_recorder_upload_directory']['#description'] .= t('This field also supports tokens.');
    $form['media_recorder_upload_tokens'] = array(
      '#theme' => 'token_tree',
      '#dialog' => TRUE,
    );
  }

  return system_settings_form($form);
}
