<?php

/**
 * @file
 * Adds a drush command to list users.
 */

/**
 * Implements hook_drush_command().
 */
function user_list_drush_command() {

  $items['user-list'] = array(
    'description' => 'Display a list of users.',
    'aliases' => array('uls'),
    'options' => array(
      'roles' => 'A comma-separated list of roles to filter by',
      'status' => 'Filter by status of the account. Can be active or blocked',
    ),
    'examples' => array(
      'drush user-list --roles=admin,editor' => 'Displays a list of users with the roles admin or editor.',
      'drush user-list --status=blocked' => 'Displays a list of blocked users.',
    ),
    'core' => array(6, 7),
    'aliases' => array('uls'),
  );

  return $items;
}

/**
 * Displays a list of users.
 */
function drush_user_list() {
  // Get options passed.
  $roles = _convert_csv_to_array(drush_get_option('roles'));
  $status = check_plain(strtolower(drush_get_option('status')));

  // The fields to grab from the users tables.
  $user_fields = array(
    'uid',
    'name',
    'mail',
    'status',
  );
  // The $uids array will be used for printing the table.
  $uids  = array();
  $where = NULL;
  $args  = NULL;
  $st    = '';

  if (!empty($status)) {
    if ($status == 'active') {
      $st = '1';
    }
    elseif ($status == 'blocked') {
      $st = '0';
    }
    else {
      unset($st);
      drush_log(dt('You have entered an invalid status. Valid status options are "active" and "blocked. Listing both active and blocked users.'), 'error');
    }
    if (isset($st)) {
      $where = "status = %d";
    }
  }

  // Build the table. This format is the same for both Drupal 6 and 7.
  $header = array('UID', dt('Name'), dt('Email'), dt('Roles'), dt('Status'));
  $rows = array();
  $rows[] = $header;

  $major_version = drush_drupal_major_version();
  if ($major_version == 6) {
    // Get the RIDs of the users with the roles specified.
    if (!empty($roles)) {
      // Find out the rids for the role names specified.
      $placeholder = db_placeholders($roles, 'text');
      $rquery      = drush_db_select('role', 'rid', "name in ($placeholder)", $roles);
      $rids        = array();
      while ($rid = drush_db_fetch_object($rquery)) {
        $rids[] = $rid->rid;
      }

      // Find out the UIDs of the users with the RIDs speficied.
      $placeholder = db_placeholders($rids, 'int');
      $query = drush_db_select('users_roles', 'uid', "rid in ($placeholder)", $rids);
      while ($uid = drush_db_fetch_object($query)) {
        $uids[] = $uid->uid;
      }

      unset($rquery);
      unset($query);

      if (!empty($uids)) {
        $placeholder = db_placeholders($uids, 'int');
        $where = (empty($where)) ? "uid IN ($placeholder)" : $where . " AND uid IN ($placeholder)";
      }
      else {
        return drush_set_error(dt('There were no users found with the roles specified.'));
      }
    }

    $args = array_merge((array) $st, $uids);

    // Get all UIDs.
    $query = drush_db_select('users', $user_fields, $where, $args);

    // Load each users info and add it to the results table.
    while ($user = drush_db_fetch_object($query)) {
      if ($user->uid == '0') {
        continue;
      }
      $user_roles = array();
      // Find out the roles of the user.
      $urquery = drush_db_select('users_roles', 'rid', 'uid = %d', array($user->uid));
      while ($result = drush_db_fetch_object($urquery)) {
        // Find the specific role name.
        $rquery = drush_db_select('role', 'name', 'rid = %d', array($result->rid));
        while ($role = drush_db_fetch_object($rquery)) {
          $user_roles[] = $role->name;
        }
      }
      $user_status = ($user->status) ? 'Active' : 'Blocked';

      drush_print_pipe($user->mail . "\n");

      $user_roles = implode(', ', $user_roles);

      $user_row = array(
        $user->uid,
        $user->name,
        $user->mail,
        $user_roles,
        $user_status,
      );
      $rows[] = $user_row;
    }
  }
  elseif ($major_version == 7) {
    if (!empty($roles)) {
      $rids = array();
      foreach ($roles as $role) {
        // Look up rid.
        $role_object = user_role_load_by_name($role);
        if (!$role_object) {
          drush_log(dt('No role exists with the name "@role"', array('@role' => $role)), 'error');
        }
        else {
          $rids[] = $role_object->rid;
        }
      }
    }
    // SELECT ur.uid,ur.rid,r.name,u.name,u.mail,u.status FROM users u
    // LEFT JOIN users_roles ur ON u.uid=ur.uid
    // LEFT JOIN role r ON r.rid=ur.rid WHERE r.rid IN $rids.
    $query = db_select('users', 'u');
    // Yo dawg, I herd you like JOINs. But we do this here, once, so we don't
    // load unnecessary user objects later.
    $query->join('users_roles', 'ur', 'u.uid = ur.uid');
    $query->join('role', 'r', 'r.rid = ur.rid');
    $query->fields('u', array('uid'));
    $query->fields('u');
    if (!empty($rids)) {
      $query->condition('r.rid', $rids, "IN");
    }
    // The only valid statuses are 1 and 0.
    // empty() is not our friend here.
    $valid_status = array("1","0");
    if (in_array($st, $valid_status)) {
      $query->condition('u.status', $st, "=");
    }
    $result = $query->execute();
    $uids = array();
    while ($record = $result->fetchAssoc()) {
      $uids[] = $record['uid'];
    }
    // This will return an array of user objects.
    $users = user_load_multiple($uids);
    foreach ($users as $user) {
      $user_roles = implode(', ', $user->roles);
      // If $user->status = 1, set it to "Active"; otherwise, "Blocked".
      // I hate this shorthand but it works.
      $user_status = ($user->status) ? 'Active' : 'Blocked';
      // Build the array for each row.
      $user_row = array(
        $user->uid,
        $user->name,
        $user->mail,
        $user_roles,
        $user_status,
      );
      $rows[] = $user_row;
    }
  }

  // If we have at least one row other than the header, print the table.
  if (!empty($rows[1])) {
    // Print the table for both Drupal 6 and 7.
    drush_print_table($rows, TRUE);
  }
  else {
    drush_log(dt('There are no users to display, which is odd.'), 'ok');
  }

}
