<?php

/**
 * @file
 * Drush commands for CAS.
 */

/**
 * Implements hook_drush_command().
 */
function cas_drush_command() {
  $items = array();
  $items['cas-user-add-role'] = array(
    'callback' => 'cas_drush_user_add_role',
    'description' => 'Add a role to the specified CAS usernames.',
    'arguments' => array(
      'role' => 'The name of the role to add',
      'users' => '(optional) A comma delimited list of CAS user names.',
    ),
    'required-arguments' => 1,
    'examples' => array(
      'drush cas-user-add-role "power user" casuser1,casuser2' =>
        'Add the "power user" role to the accounts with CAS user names casuser1 and casuser2.',
    ),
  );
  $items['cas-user-create'] = array(
    'callback' => 'cas_drush_user_create',
    'description' => dt('Create a CAS user account with the specified CAS username.'),
    'arguments' => array(
      'cas_name' => 'The CAS username of the account to add',
    ),
    'required-arguments' => TRUE,
    'examples' => array(
      'drush cas-user-create newcasuser' => 'Create a new user with CAS username newcasuser',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function cas_drush_help($section) {
  switch ($section) {
    case 'drush:cas-user-create':
      return dt('Create a CAS user account with the specified CAS username.');
    case 'drush:cas-user-add-role':
      return dt('Add a role to the specified CAS usernames.');
  }
}

/**
 * Creates a new CAS user account.
 */
function cas_drush_user_create($cas_name) {
  // @todo: Handle additional options for setting other user attributes.
  $account = cas_user_load_by_name($cas_name);
  if ($account === FALSE) {
    if (!drush_get_context('DRUSH_SIMULATE')) {
      $options = array('invoke_cas_user_presave' => TRUE);
      $new_user_object = cas_user_register($cas_name, $options);
      if ($new_user_object !== FALSE) {
        $user_fields = array('cas_name', 'uid', 'name', 'mail', 'status');
        $new_user_object = (array) $new_user_object;
        $new_user_object = array_intersect_key($new_user_object, array_flip($user_fields));
        $new_user_object = drush_key_value_to_array_table($new_user_object);
        drush_print_table($new_user_object);
      }
      else {
        drush_set_error(dt('Could not create a new user account with CAS username @cas_name.', array('@cas_name' => $cas_name)));
      }
    }
  }
  else {
    drush_set_error(dt('There is already a user account with CAS username @cas_name.', array('@cas_name' => $cas_name)));
  }
}

/**
 * Add a role to the specified CAS user accounts.
 */
function cas_drush_user_add_role($role, $users = '') {
  $uids = cas_drush_user_get_users_from_arguments($users);
  if (drush_drupal_major_version() >= 7) {
    $rid_query = db_query("SELECT rid FROM {role} WHERE name = :role", array(':role' => $role));
  }
  else {
    $rid_query = db_query("SELECT rid FROM {role} WHERE name = '%s'", $role);
  }
  if (!empty($uids)) {
    if ($rid = drush_db_result($rid_query)) {
      drush_op('user_multiple_role_edit', $uids, 'add_role', $rid);
      foreach ($uids as $uid) {
        drush_log(dt("Added the !role role to uid !uid", array('!role' => $role, '!uid' => $uid)), 'success');
      }
    }
    else {
      return drush_set_error(dt("There is no role named: !role", array('!role' => $role)));
    }
  }
  else {
    return drush_set_error("Could not find any valid uids!");
  }
}

/**
 * Look up user ids from a comma-separated list of CAS usernames.
 *
 * @param $users string
 *   Comma separated list of CAS usernames.
 *
 * @return array
 *   An array of user ids corresponding to the given CAS usernames. Unknown
 *   CAS usernames are ignored.
 */
function cas_drush_user_get_users_from_arguments($users) {
  $uids = array();
  if ($users !== '') {
    $users = explode(',', $users);
    foreach ($users as $user) {
      $account = cas_user_load_by_name($user);
      if ($account) {
        $uids[] = $account->uid;
      }
    }
  }
  return $uids;
}
