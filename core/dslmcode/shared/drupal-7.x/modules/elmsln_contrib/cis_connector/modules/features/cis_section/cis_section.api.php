<?php
/**
 * @file
 * CIS Section API
 *
 * Note, passing `force_roster_sync` via cron will force
 * rosters to sync up. Also passing cis_contact will email
 * someone automatically if they are added via a forced sync
 * routine. This is useful for notifying someone that
 * previously didn't have access and triggered an access
 * denied that they now have access to the system.
 */

/**
 * Implements hook_cis_section_activate().
 *
 * Allow for activing when a new section is activated.
 * this example is penn state's implementation to use a section being
 * active to talk to angel, our primary lms.. for now.
 *
 * Return is an array of callback functions to allow for easier
 * alteration based on the context of the situation.
 */
function hook_section_activate() {
  return array('_cis_section_activate_callback');
}

/**
 * Example callback for activating a section
 *
 * There is a developer attribute that you can set
 * on nodes to make sure that syncs don't happen
 * when they might not need to.  If you detect that
 * you need to update a section without actually
 * running the activate hook (for example), you
 * can test for $node->_ignore_sync being set.
 * This is implemented below and in cis_section.module
 */
function _cis_section_activate_callback($node) {
  if (!isset($node->_ignore_sync)) {
    // grab section id
    $section = array($node->field_section_id['und'][0]['value']);
    // pull the roster together for this section
    $roster = cis_section_assemble_roster($section, TRUE);
    // build the user accounts
    watchdog('roster', 'Roster synced for section @section', array('@section' => $node->field_section_id['und'][0]['value']));
    _cis_section_create_accounts($roster);
    drupal_set_message(t('Roster synced for section @section', array('@section' => $node->field_section_id['und'][0]['value'])));
  }
}

/**
 * Implements hook_cis_section_deactivate().
 *
 * Allow for activing when a section is deactivated.
 */
function hook_cis_section_deactivate() {
  return array('deactivate_callback');
}

/**
 * Implements hook_cis_section_build_roster().
 *
 * @param  string $section is a unique identifier for asking a roster
 *
 * @return array  keyed with userid => role
 * $roster[$member['user_id']] = $member['course_rights'];
 */
function hook_cis_section_build_roster($section) {
  // user name => role id, you'll want
  return array(
    'name' => 'student',
    'name2' => 'student',
    'name3' => 'instructor',
    'name4' => 'student',
  );
}

/**
 * Implements hook_cis_section_build_roster_alter().
 *
 * Allow for modification of the roster after initial processing.
 * This is how cis_devel is able to present roster results
 * @param  array &$roster assembled roster for a section
 * @param  string $section is a unique identifier for asking a roster
 */
function hook_cis_section_build_roster_alter(&$roster, $section) {

}

/**
 * Implements hook_cis_section_user_insert_alter().
 *
 * Allow modification of the user object just prior to insert
 * when the method used to create the user is section activation.
 *
 * This example shows how psu populates an email address automatically.
 */
function hook_cis_section_user_insert_alter(&$fields, $userdata) {
  $fields['mail'] = _utility_module_name_to_email($fields['name']);
  $fields['init'] = $fields['mail'];
}

/**
 * Implements hook_cis_section_account_processed_alter().
 *
 * Allow for things to react to a user account being processed by this system.
 * This is used by the CPR system to take "data" from Canvas and store it
 * so that it can be referenced by every place else the user goes via their
 * central profile object.
 */
function hook_cis_section_account_processed_alter(&$account, $userdata) {

}

/**
 * Implements hook_cis_section_list_alter().
 *
 * Allow for modification of the system reported section list.
 */
function hook_cis_section_list_alter(&$sections) {
  // add a section called default
  $sections['default'] = t('Default');
}
