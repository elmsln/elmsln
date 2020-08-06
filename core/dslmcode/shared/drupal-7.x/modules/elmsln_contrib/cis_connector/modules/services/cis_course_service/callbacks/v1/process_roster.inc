<?php

/**
 * Callback to sync sections and roster of users with network.
 */
function cis_course_service_elmsln_api_callback_process_roster() {
  global $_elmsln;
    // build accounts from the roster
    if (isset($_elmsln['args']['roster'])) {
      // attempt to deserialize
      $roster = @unserialize($_elmsln['args']['roster']);
      foreach ((array)$roster as $section => $user) {
        foreach ((array)$user as $name => $user_data) {
          // Separate role name from user data.
          if (is_string($user_data)) {
            $role_name = $user_data;
            $user_data = array('role' => $role_name);
          }
          else {
            $role_name = $user_data['role'];
          }
          $role = user_role_load_by_name($role_name);
          // If we have no role, use the authenticated user role.
          if (!isset($role->rid) || empty($role->rid) || $role->rid == 0) {
            $role->rid = 2;
            $role->name = 'authenticated user';
            $og_role = FALSE;
          }
          // Otherwise fine the corresponding OG Role.
          else {
            $og_role = _cis_section_og_role_load_by_name($role_name);
          }
          // short hand for the pieces we care about from above
          $role_id = $role->rid;
          $group_id = $og_role ? $og_role->rid : NULL;
          // Attempt to load the account.
          $account = user_load_by_name($name);
          // If it doesn't exist, create it.
          if (!$account) {
            $values = array(
              'name' => $name,
              'status' => 1,
              'roles' => array($role_id => $role_name),
            ) + (array)$user_data;
            unset($values['role']);

            // Generate a random password if we don't have one.
            if (!isset($values['pass'])) {
              $values['pass'] = user_password(20);
            }

            // allow other projects to update part of the user
            drupal_alter('cis_section_user_insert', $values, $user_data);

            // the first parameter is left blank so a new user is created
            $account = user_save('', $values);
          }
          // Otherwise, check our sync details.
          else {
            $save_user = FALSE;
            $edit = array();
            // Add the role if it doesn't already exist.
            if (!isset($account->roles[$role_id])) {
              $account->roles[$role_id] = $role_name;
              $save_user = TRUE;
            }

            // If we were given an email or password and they differ, update them.
            if (isset($user_data['mail']) && $account->mail != $user_data['mail']) {
              $account->mail = $user_data['mail'];
              $save_user = TRUE;
            }
            if (isset($user_data['pass']) && $account->pass != $user_data['pass']) {
              $account->pass = $user_data['pass'];
              $save_user = TRUE;
            }

            // Update the data, if provided.
            if (isset($user_data['data']) && $account->data != $user_data['data']) {
              $edit['data'] = $user_data['data'];
              $save_user = TRUE;
            }

            if ($save_user) {
              user_save($account, $edit);
            }
          }
          // add group membership
          $values = array(
            'entity_type' => 'user',
            'entity' => $account,
            'field_name' => 'og_user_node',
          );
          $gid = _cis_section_load_section_by_id($section);
          og_group('node', $gid, $values);
          // give them the special staff role if it exists
          if ($group_id) {
            _cis_section_og_role_grant('node', $gid, $account->uid, $group_id, 'update');
          }

          // allow other things to react to an account being processed
          // via this job
          drupal_alter('cis_section_account_processed', $account, $user_data);
        }
      }
    }
    return array(
      'process_roster' => TRUE,
      'roster' => $roster,
      'message' => "Roster processed",
    );
}
