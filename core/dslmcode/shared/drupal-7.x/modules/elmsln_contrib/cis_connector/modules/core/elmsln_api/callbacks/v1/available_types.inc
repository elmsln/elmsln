<?php

/**
 * Callback to return the node types this user can access.
 * @return array  types that this user name can access if any
 */
function elmsln_api_elmsln_api_callback_available_types() {
  global $_elmsln;
  if (isset($_elmsln['args']['username'])) {
    $username = $_elmsln['args']['username'];
    $account = user_load_by_name($username);
    $types = node_type_get_types();
    // unset the data model items cause they don't matter
    unset($types['cis_course']);
    unset($types['section']);
    $return_types = array();
    // if they have admin rights, just do the whole thing
    if (user_access('administer content types', $account)) {
      $return_types = $types;
    }
    else {
      // loop through types
      foreach ($types as $key => $type) {
        // ensure they have create access
        if (node_access('create', $type->type, $account)) {
          $return_types[$key] = $type;
        }
      }
    }
    return array(
      'types' => $return_types,
      'username' => $username,
      'message' => "available types returned",
    );
  }
  return FALSE;
}
