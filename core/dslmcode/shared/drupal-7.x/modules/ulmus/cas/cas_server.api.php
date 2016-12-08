<?php

/**
 * @file
 * Documentation for CAS Server API.
 */

/**
 * Return additional CAS attributes when acting as a CAS server.
 *
 * This hook allows modules to add additional CAS attributes to the basic
 * response by the CAS Server module.
 *
 * @param $account
 *   The user being logged in.
 * @param $service
 *   The service URL of the site the user is logging in to.
 * @param $ticket
 *   The login ticket the user provided.
 *
 * @return
 *   An associative array of CAS attributes for the user.
 *
 * @see hook_cas_server_user_attributes_alter()
 */
function hook_cas_server_user_attributes($account, $service, $ticket) {
  $attributes = array();

  // Attributes can be single valued...
  $attributes['color'] = 'blue';

  // ... or multi-valued.
  $attributes['friends'] = array('dries', 'webchick');

  // Or change the response based upon the server.
  if (preg_match("@^http://apple.com/@", $service)) {
    // This data should not be confidential as the service URL is directly
    // supplied by the user and is in no way validated.
    $attributes['friends'] += 'sjobs';
  }

  return $attributes;
}

/**
 * Alter additional CAS attributes to return when a user is authenticated.
 *
 * @param $attributes
 *   CAS attributes, as constructed by hook_cas_server_user_attributes().
 * @param $account
 *   The user being logged in.
 * @param $context
 *   An associative array containing the following key-value pairs, matching the
 *   arguments received by hook_cas_server_user_attributes():
 *   - "service": The service URL of the site the user is logging in to.
 *   - "ticket": The login ticket the user provided.
 *
 * @see hook_cas_server_user_attributes()
 */
function hook_cas_server_user_attributes_alter(&$attributes, $account, $context) {
  //...
}
