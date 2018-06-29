<?php

/**
 * @file
 * Hooks provided by the OAuth2 Server module.
 */

/**
 * Execute operations before oauth2_server_authorize() main logic.
 *
 * Allow modules to perform additional operations at the very beginning of
 * the OAuth2 authorize callback.
 */
function hook_oauth2_server_pre_authorize() {
  // Make sure we're not in the middle of a running operation.
  if (empty($_SESSION['oauth2_server_authorize'])) {
    global $user;
    // Ensure that the current session is killed before authorize.
    module_invoke_all('user_logout', $user);
    // Destroy the current session, and reset $user to the anonymous user.
    session_destroy();
  }
}

/**
 * Execute operations before OAuth2 Server sends a token response.
 *
 * @param \OAuth2Server|NULL $server
 * @param \OAuth2\Request $request
 * @param \OAuth2\Response $response
 */
function hook_oauth2_server_token($server, \OAuth2\Request $request, \OAuth2\Response $response) {
  // Example: if the response is not successful, log a message.
  if ($response->getStatusCode() != 200) {
    watchdog('mymodule', 'Failed token response from server @server: @code @body', array(
      '@server' => $server ? $server->name : NULL,
      '@code' => $response->getStatusCode(),
      '@body' => $response->getResponseBody(),
    ));
  }
}

/**
 * Alter user claims about the provided account.
 *
 * The provided claims can be included in the id_token and / or returned from
 * the /oauth2/UserInfo endpoint.
 *
 * Groups of claims are returned based on the requested scopes. No group
 * is required, and no claim is required.
 *
 * @param array &$claims
 *   Existing claims provided by OAuth2 Server or other modules.
 * @param object $account
 *   The user account for which claims should be returned.
 * @param array $requested_scopes
 *   The requested scopes.
 *
 * @see hook_oauth2_server_user_claims()
 *
 * @see http://openid.net/specs/openid-connect-core-1_0.html#ScopeClaims
 */
function hook_oauth2_server_user_claims_alter(&$claims, $account, $requested_scopes) {
  $wrapper = entity_metadata_wrapper('user', $account);

  // Example: add the birthday from a custom field, if the 'profile' scope is
  // requested.
  if (in_array('profile', $requested_scopes) && !empty($wrapper->field_birthday)) {
    $claims['birthdate'] = date('0000-m-d', strtotime($wrapper->field_birthday->value()));
  }

  // Example: add the phone number from a custom field, if the 'phone' scope is
  // requested.
  if (in_array('phone', $requested_scopes) && !empty($wrapper->field_phone)) {
    $claims += array(
      'phone_number' => date('0000-m-d', strtotime($wrapper->field_phone->value())),
      'phone_number_verified' => FALSE,
    );
  }
}

/**
 * Provide new user claims.
 *
 * @param object $account
 *   The user account for which claims should be returned.
 * @param array $requested_scopes
 *   The requested scopes.
 *
 * @see hook_oauth2_server_user_claims_alter()
 *
 * @return array
 *   An array of new user claims.
 */
function hook_oauth2_server_user_claims($account, $requested_scopes) {
  $claims = array();
  if (in_array('profile', $requested_scopes)) {
    $claims['custom_claim'] = $account->custom_property;
  }

  return $claims;
}

/**
 * Alter the list of available grant types.
 *
 * @param array &$grant_types
 *   The grant types available for any OAuth2 servers. Each grant type is an
 *   array containing a 'name' and a 'class'. The 'class' is the name of a grant
 *   type class that implements \OAuth2\GrantType\GrantTypeInterface.
 */
function hook_oauth2_server_grant_types_alter(&$grant_types) {
  $grant_types['custom_grant_type'] = array(
    'name' => t('Custom grant type'),
    'class' => 'MyModuleCustomGrantType',
  );
}

/**
 * Returns the default scope for the provided server.
 *
 * Invoked by OAuth2_Scope_Drupal.
 * If no hook implementation returns a default scope for the current server,
 * then the one from $server->settings['default_scope'] is used.
 *
 * This hook runs on "authorize" and "token" requests and has access to the
 * client_id in $_GET (for "authorize") or via
 * oauth2_server_get_client_credentials() (for "token").
 * Note that client_id in this case corresponds to $client->client_key.
 *
 * @param OAuth2Server $server
 *   The server entity.
 *
 * @return string[]
 *   An array of default scopes (their machine names).
 */
function hook_oauth2_server_default_scope(OAuth2Server $server) {
  // For the "test" server, grant the user any scope he has access to.
  $default_scopes = array();

  if ($server->name == 'test') {
    $query = new EntityFieldQuery();
    $query->entityCondition('entity_type', 'oauth2_server_scope');
    $query->propertyCondition('server', $server->name);
    $query->addTag('oauth2_server_scope_access');
    $query->addMetaData('oauth2_server', $server);
    $results = $query->execute();

    if ($results) {
      $scope_ids = array_keys($results['oauth2_server_scope']);
      $scopes = entity_load('oauth2_server_scope', $scope_ids);
      foreach ($scopes as $scope) {
        $default_scopes[] = $scope->name;
      }
    }
  }

  return $default_scopes;
}

/**
 * An example hook_entity_query_alter() implementation for scope access.
 */
function example_entity_query_alter($query) {
  global $user;

  // This is an EFQ used to get all scopes available to the user
  // (inside the Scope class, or when showing the authorize form, for instance).
  if (!empty($query->tags['oauth2_server_scope_access'])) {
    $server = $query->metaData['oauth2_server'];

    // On the "test" server only return scopes that have the current user
    // in an example "users" entityreference field.
    if ($server->name == 'test' && $user->uid) {
      $query->fieldCondition('users', 'target_id', $user->uid);
    }
  }

  // This is an EFQ used to get all exportable scopes.
  if (!empty($query->tags['oauth2_server_scope_export'])) {
    $server = $query->metaData['oauth2_server'];

    // On the "test" server only export scopes assigned to admin.
    if ($server->name == 'test') {
      $query->fieldCondition('users', 'target_id', 1);
    }
  }
}
