<?php

/**
 * @file
 * Drush implementation for the uuid module.
 */

/**
 * Implementats hook_drush_command().
 */
function drush_grant_rid_drush_command() {
  $items = array();
  $items['user-grant-rid'] = array(
    'description' => 'Grant user an RID',
    'aliases' => array('ugrid'),
    'arguments' => array(
      'rid' => 'The rid to grant',
      'users' => '(optional) A comma delimited list of uids, user names, or email addresses.',
    ),
    'required-arguments' => 1,
    'examples' => array(
      'drush user-grant-rid 4 5,user3 --uid=2,3 --name=someguy,somegal --mail=billgates@microsoft.com' =>
        'Add rid 4 to the accounts with name, id, or email 5 or user3, uids 2 and 3, names someguy and somegal, and email address of billgates@microsoft.com',
    ),
    'options' => array(
      'uid' => 'A comma delimited list of uids',
      'name' => 'A comma delimited list of user names',
      'mail' => 'A comma delimited list of user mail addresses',
    ),
  );
  $items['user-remove-rid'] = array(
    'description' => 'Remove a role from the specified user accounts.',
    'aliases' => array('urrid'),
    'arguments' => array(
      'rid' => 'The name of the role to remove',
      'users' => '(optional) A comma delimited list of uids, user names, or email addresses.',
    ),
    'required-arguments' => 1,
    'examples' => array(
      'drush user-remove-rid 4 5,user3 --uid=2,3 --name=someguy,somegal --mail=billgates@microsoft.com' =>
        'Remove the rid 4 from the accounts with name, id, or email 5 or user3, uids 2 and 3, names someguy and somegal, and email address of billgates@microsoft.com',
    ),
    'options' => array(
      'uid' => 'A comma delimited list of uids',
      'name' => 'A comma delimited list of user names',
      'mail' => 'A comma delimited list of user mail addresses',
    ),
  );
  return $items;
}

/**
 * Implementats of hook_drush_help().
 */
function drush_grant_rid_drush_help($section) {
  switch ($section) {
    case 'drush:user-grant-rid':
      return dt("Grant user role based on rid instead of name.");
    case 'drush:user-remove-rid':
      return dt("Remove user role based on rid instead of name.");
  }
}

/**
 * Add a rid to the specified user accounts.
 */
function drush_drush_grant_rid_user_grant_rid($rid_input, $users = '') {
  $uids = _drush_user_get_users_from_options_and_arguments($users);
  if (!empty($uids)) {
    if (drush_drupal_major_version() >= 7) {
      $rid_query = db_query("SELECT rid FROM {role} WHERE rid = :rid", array(':rid' => $rid_input));
    }
    else {
      $rid_query = db_query("SELECT rid FROM {role} WHERE rid = '%s'", $rid_input);
    }
    if ($rid = drush_db_result($rid_query)) {
      drush_op('user_multiple_role_edit', $uids, 'add_role', $rid);
      foreach($uids as $uid) {
        drush_log(dt("Added rid !rid to uid !uid", array('!rid' => $rid, '!uid' => $uid)), 'success');
      }
    }
    else {
      return drush_set_error(dt("There is no rid !rid", array('!rid' => $rid_input)));
    }
  }
  else {
    return drush_set_error("Could not find any valid uids!");
  }
}

/**
 * Remove a role from the specified user accounts.
 */
function drush_drush_grant_rid_user_remove_rid($rid_input, $users = '') {
  $uids = _drush_user_get_users_from_options_and_arguments($users);
  if (!empty($uids)) {
    if (drush_drupal_major_version() >= 7) {
      $rid_query = db_query("SELECT rid FROM {role} WHERE rid = :rid", array(':rid' => $rid_input));
    }
    else {
      $rid_query = db_query("SELECT rid FROM {role} WHERE rid = '%s'", $rid_input);
    }
    if ($rid = drush_db_result($rid_query)) {
      drush_op('user_multiple_role_edit', $uids, 'remove_role', $rid);
      foreach($uids as $uid) {
        drush_log(dt("Removed rid !rid from uid !uid", array('!rid' => $rid, '!uid' => $uid)), 'success');
      }
    }
    else {
      return drush_set_error(dt("There is no rid: !rid", array('!rid' => $rid_input)));
    }
  }
  else {
    return drush_set_error("Could not find any valid uids!");
  }
}