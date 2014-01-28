<?php
/**
 * @file
 * Set some useful defaults prior to form presentation.
 */
 
/**
 * Implements hook_form_FORM_ID_alter().
 *
 * Allows the profile to alter the site configuration form.
 */
if (!function_exists('system_form_install_configure_form_alter')) {
  function system_form_install_configure_form_alter(&$form, $form_state) {
    // Pre-populate the site name with the server name.
    $form['site_information']['site_name']['#default_value'] = 'Online Course';
  }
}

/**
 * Implements hook_form_alter().
 */
if (!function_exists('system_form_install_select_profile_form_alter')) {
  function system_form_install_select_profile_form_alter(&$form, $form_state) {
    // select MOOC install profile by default
    foreach($form['profile'] as $key => $element) {
      $form['profile'][$key]['#value'] = 'mooc';
    }
  }
}