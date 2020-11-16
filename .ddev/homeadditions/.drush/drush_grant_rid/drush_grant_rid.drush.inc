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

// Drush 7 dropped support for this way of operating and I don't feel like refactoring
// for something this dumb. Now we support Drush 6 and Drush 7 with this backport
if (!function_exists('_drush_user_get_users_from_options_and_arguments')) {
  function _drush_user_get_users_from_options_and_arguments($users) {
    $uids = drush_get_option_list('uids');
    foreach (array('uid', 'name', 'mail' ) as $user_attr) {
      if ($arg = drush_get_option($user_attr)) {
        foreach(explode(',', $arg) as $search) {
          $uid_query = FALSE;
          switch ($user_attr) {
            case 'uid':
              if (drush_drupal_major_version() >= 7) {
                $uid_query = db_query("SELECT uid FROM {users} WHERE uid = :uid", array(':uid' => $search));
              }
              else {
                $uid_query = db_query("SELECT uid FROM {users} WHERE uid = %d", $search);
              }
              break;
            case 'name':
              if (drush_drupal_major_version() >= 7) {
                $uid_query = db_query("SELECT uid FROM {users} WHERE name = :name", array(':name' => $search));
              }
              else {
                $uid_query = db_query("SELECT uid FROM {users} WHERE name = '%s'", $search);
              }
              break;
            case 'mail':
              if (drush_drupal_major_version() >= 7) {
                $uid_query = db_query("SELECT uid FROM {users} WHERE mail = :mail", array(':mail' => $search));
              }
              else {
                $uid_query = db_query("SELECT uid FROM {users} WHERE mail = '%s'", $search);
              }
              break;
          }
          if ($uid_query !== FALSE) {
            if ($uid = drush_db_result($uid_query)) {
              $uids[] = $uid;
            }
            else {
              drush_set_error("Could not find a uid for $user_attr = $search");
            }
          }
        }
      }
    }
    return array_merge($uids, _drush_user_get_users_from_arguments($users));
  }

  /**
   * Given a comma-separated list of users, return uids
   * for users that match either by uid or email address.
   */
  function _drush_user_get_users_from_arguments($users) {
    $uids = array();
    if ($users !== '') {
      $users = _convert_csv_to_array($users);
      foreach($users as $user) {
        $uid = _drush_user_get_uid($user);
        if ($uid !== FALSE) {
          $uids[] = $uid;
        }
      }
    }
    return $uids;
  }

  /**
   * Get uid(s) from a uid, user name, or email address.
   * Returns a uid, or FALSE if none found.
   */
  function _drush_user_get_uid($search) {
    // We use a DB query while looking for the uid to keep things speedy.
    $uids = array();
    if (is_numeric($search)) {
      if (drush_drupal_major_version() >= 7) {
        $uid_query = db_query("SELECT uid, name FROM {users} WHERE uid = :uid OR name = :name", array(':uid' => $search, ':name' => $search));
      }
      else {
        $uid_query = db_query("SELECT uid, name FROM {users} WHERE uid = %d OR name = '%d'", $search, $search);
      }
    }
    else {
      if (drush_drupal_major_version() >= 7) {
        $uid_query = db_query("SELECT uid, name FROM {users} WHERE mail = :mail OR name = :name", array(':mail' => $search, ':name' => $search));
      }
      else {
        $uid_query = db_query("SELECT uid, name FROM {users} WHERE mail = '%s' OR name = '%s'", $search, $search);
      }
    }
    while ($uid = drush_db_fetch_object($uid_query)) {
      $uids[$uid->uid] = $uid->name;
    }
    switch (count($uids)) {
      case 0:
        return drush_set_error("Could not find a uid for the search term '" . $search . "'!");
        break;
      case 1:
        return array_pop(array_keys($uids));
        break;
      default:
        drush_print('More than one user account was found for the search string "' . $search . '".');
        return(drush_choice($uids, 'Please choose a name:', '!value (uid=!key)'));
    }
  }
}