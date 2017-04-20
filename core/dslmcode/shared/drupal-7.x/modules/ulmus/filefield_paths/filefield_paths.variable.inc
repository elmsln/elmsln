<?php

/**
 * @file
 * Contains Variable functions for the File (Field) Paths module.
 */

/**
 * Implements hook_variable_info().
 *
 * @return mixed
 */
function filefield_paths_variable_info() {
  $variables['filefield_paths_temp_location'] = array(
    'title'             => t('Temporary file location'),
    'type'              => 'string',
    'default'           => 'public://filefield_paths',
    'description'       => t('The location that unprocessed files will be uploaded priot to being processed by File (Field) Paths.<br />It is recommended that you use the temporary file system (temporary://) if your server configuration allows for that.'),
    'validate callback' => 'filefield_paths_variable_temp_location_validate',
    'group'             => 'filefield_paths',
  );

  return $variables;
}

/**
 * Validate callback for 'Temporary file location' variable.
 *
 * @param $element
 */
function filefield_paths_variable_temp_location_validate($element) {
  // Add FAPI element keys for standard validation callback.
  $element['#parents'] = array('filefield_paths_temp_location');
  $element['#value'] = $element['value'];

  // Pass element through standard validation callback.
  module_load_include('admin.inc', 'filefield_paths');
  filefield_paths_settings_form_temp_location_validate($element);
}

/**
 * Implements hook_variable_group_info().
 *
 * @return mixed
 */
function filefield_paths_variable_group_info() {
  $groups['filefield_paths'] = array(
    'title'       => t('File (Field) Paths'),
    'description' => t('File (Field) Paths settings.'),
    'access'      => 'administer site configuration',
    'path'        => array(
      'admin/config/media/file-system/filefield-paths'
    ),
  );

  return $groups;
}