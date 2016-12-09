<?php

/**
 * @file
 * Documentation for CAS API.
 */

/**
 * Modify CAS user properties before the user is logged in.
 *
 * Allows modules to alter the CAS username and account creation permissions
 * after the CAS username is returned from phpCAS::getUser().
 *
 * Modules implementing this hook may wish to alter 'name' if the CAS server
 * returns user names which contain excess information or are not directly
 * machine readable. This field is not the Drupal name of the user. Instead,
 * this is used to load a Drupal user via the mapping in the {cas_user} table.
 *
 * The 'login' parameter controls whether the user is able to login. By
 * default this will be set to TRUE, but modules may set this flag to FALSE
 * to deny the user login access. For example, one might want to only allow
 * login access to members of a certain LDAP group. This verification is in
 * addition to the standard feature which lets you block users.
 *
 * The 'register' parameter controls whether an account should be created if
 * the user does not already have a Drupal account. Defaults to the value of
 * "Should Drupal user accounts be automatically created?" in the CAS module
 * settings. This setting is ignored if 'login' is set to FALSE.
 *
 * If multiple modules implement this hook, the values set by the last module
 * to execute this hook will be used. Therefore, it is good practice to only
 * set the 'login' and 'register' flags to FALSE, rather than the output of
 * a function. This prevents accidentally allowing a user to login when another
 * module had already denied access.
 *
 * @param $cas_user
 *   An associative array, with the following keys:
 *   - 'name': The CAS machine-readable user name.
 *   - 'login': If TRUE, the user will be allowed to login to an existing
 *     Drupal account.
 *   - 'register': If TRUE, the user will be allowed to register a Drupal
 *     account if one does not already exist. If 'login' is FALSE, this
 *     setting will be ignored.
 *   - 'attributes': If phpCAS is new enough to support getAttributes and the
 *     CAS server supports SAML attributes, this consists of an associative
 *     array of attribute names and values; otherwise it is an empty array.
 */
function hook_cas_user_alter(&$cas_user) {
  // Alter the CAS username. The CAS server returned a compound name like
  //   it:johndoe:10.10.1.2:200805064255
  // and so we extract the actual user name of 'johndoe'.
  $parts = explode(':', $cas_user['name'], 3);
  $cas_user['name'] = $parts[1];

  // Allow logins only for users in a certain LDAP group.
  if (!_ldap_is_member_group($cas_user['name'], 'admins')) {
    $cas_user['login'] = FALSE;
  }

  // Allow registrations only for a certain class of users.
  if (!_ldap_user_has_home_directory($cas_user['name'])) {
    $cas_user['register'] = FALSE;
  }
}

/**
 * A CAS user has authenticated and the login is about to be finalized.
 *
 * This allows modules to react to a CAS user logging in and alter their
 * account properties. For example, modules may want to synchronize Drupal
 * user roles or profile information with LDAP properties.
 *
 * If you would like to synchronize information only for new accounts, you may
 * examine the value of $account->login which will be 0 if the user has never
 * logged in before.
 *
 * The 'cas_user' key in $edit contains all information returned from
 * hook_cas_user_alter().
 *
 * The CAS module promises to call user_save() and user_login_finalize() with
 * this $edit data.
 *
 * @param $edit
 *   An array of values corresponding to the Drupal user to be created.
 * @param $account
 *   A Druapl user object.
 */
function hook_cas_user_presave(&$edit, $account) {
  $cas_name = $edit['cas_user']['name'];

  // Look up the user's real name using LDAP.
  $ldap_connection = ldap_connect('ldap.example.com', 389);
  $ldap_result = ldap_search($ldap_connection, 'ou=people', 'uid=' . $cas_name, array('cn'), 0, 1);
  $entries = ldap_get_entries($ldap_connection, $ldap_result);
  $attributes = $entries[0];

  if (!empty($attributes['cn'])) {
    $edit['name'] = $attributes['cn'];
  }
}

/**
 * Modify phpCAS authentication properties.
 *
 * This is called after phpCAS has been configured with the basic server
 * properties, but before phpCAS::forceAuthentication() is called.
 *
 * Users will generally not need to implement this hook, as most phpCAS
 * configuration options are already provided in the CAS module UI.
 *
 * There are no parameters, instead the module should directly call the
 * functions in the phpCAS namespace.
 */
function hook_cas_phpcas_alter() {
  // Set a custom server login URL.
  phpCAS::setServerLoginURL('https://login.example.com/cas/login');
}
