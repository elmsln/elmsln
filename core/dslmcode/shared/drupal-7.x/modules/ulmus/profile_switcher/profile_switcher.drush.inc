<?php
/**
 * @file
 * drush integration for Profie Switcher
 */

/**
 * Implementation of hook_drush_help().
 */
function profile_switcher_drush_help($section) {
  switch ($section) {
    case 'drush:profile-switch':
      return dt('Switch the profile of a drupal site from one profile to another');
    break;
  }
}

/**
 * Implements hook_drush_command().
 */
function profile_switcher_drush_command() {
  $items = array();
  $items['profile-switch'] = array(
  'callback' => 'profile_switcher_profile_switch',
    'description' => dt('Switch the profile used by a drupal site from one to another. You probably should know what your doing and why if you run this.'),
    'aliases' => array('proswitch'),
    'arguments' => array(
      'profile' => dt('The install profile to switch to'),
    ),
    'examples' => array(
      'drush profile-switch minimal' =>
        dt('switch the site install profile to minimal'),
      'drush cook switch --env-profile=minimal --y' =>
        dt('switch site install profile to minimal, ensure dependencies are met, enable / install the profile, rebuild caches, etc.'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );
  return $items;
}

/**
 * Callback for profile-switch drush command.
 */
function profile_switcher_profile_switch($profile) {
  // make sure profile is actually a valid profilein this stack
  $profiles = profile_switcher_find_profiles();
  if (!isset($profiles[$profile])) {
    drush_log(dt('You must select a valid profile to switch to.'), 'error');
    return FALSE;
  }
  // set up the form array
  $form_state = array();
  $form_state['values'] = array(
    'profile_switcher_profile_old' => drupal_get_profile(),
    'profile_switcher_profile' => $profile,
  );
  // required for forced submission
  $form_state['values']['op'] = t('Save configuration');
  // try and "submit" the form
  drupal_form_submit('profile_switcher_admin_settings', $form_state);
}

