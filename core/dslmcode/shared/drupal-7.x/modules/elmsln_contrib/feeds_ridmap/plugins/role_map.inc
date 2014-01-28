<?php

/**
 * @file
 * Allow for mapping values from an external roles system to drupal roles
 */
/**
 * feeds_tamper API definition for drupal role mapping
 */
$plugin = array(
  'form' => 'role_map_form',
  'callback' => 'role_map_callback',
  'name' => 'Drupal roles',
  'multi' => 'single',
  'category' => 'Filter',
  'description' => 'This will allow you to map roles from an external system to Drupal roles',
);

/**
 * Form for building the role map
 */
function role_map_form($importer, $element_key, $settings) {
  $form = array();
  // get all roles except anon
  $roles = user_roles(TRUE);
  // build out a form that allows the user to map values to internal roles listing
  foreach ($roles as $rid => $role) {
    $form['role_map_' . $rid] = array(
      '#type' => 'textfield',
      '#title' => t('Map for @role (rid: @rid)', array('@role' => $role, '@rid' => $rid)),
      '#default_value' => isset($settings['role_map_' . $rid]) ? $settings['role_map_' . $rid] : '',
    );
  }
  return $form;
}

/**
 * Helper function to process the value conversion
 */
function role_map_callback($result, $item_key, $element_key, &$field, $settings) {
  // get all roles except anon
  $roles = user_roles(TRUE);
  foreach ($roles as $rid => $role) {
    // if value matches setting entered, switch it to role ID
    if ($field == $settings['role_map_' . $rid]) {
      $field = $rid;
    }
  }
}
