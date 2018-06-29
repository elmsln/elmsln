<?php
/**
 * @file
 * The programing interface provided by the module oauth2_client.
 */

/**
 * Define oauth2 clients.
 *
 * @return Array
 *   Associative array of oauth2 clients.
 */
function hook_oauth2_clients() {
  global $base_url;
  $server_url = 'https://oauth2_server.example.org';

  $oauth2_clients = array();

  // Using user-password flow.
  $oauth2_clients['test1'] = array(
    'token_endpoint' => $server_url . '/oauth2/token',
    'auth_flow' => 'user-password',
    'client_id' => 'client1',
    'client_secret' => 'secret1',
    'username' => 'user1',
    'password' => 'pass1',
  );

  // Using client-credentials flow.
  $oauth2_clients['test2'] = array(
    'token_endpoint' => $server_url . '/oauth2/token',
    'auth_flow' => 'client-credentials',
    'client_id' => 'client2',
    'client_secret' => 'secret2',
  );

  // Using server-side flow.
  $oauth2_clients['test3'] = array(
    'token_endpoint' => $server_url . '/oauth2/token',
    'auth_flow' => 'server-side',
    'client_id' => 'client3',
    'client_secret' => 'secret3',
    'authorization_endpoint' => $server_url . '/oauth2/authorize',
    'redirect_uri' => $base_url . '/oauth2/authorized',
  );

  return $oauth2_clients;
}

/**
 * Load an oauth2 client.
 *
 * @param string $name
 *   Name of the client.
 *
 * @return OAuth2\Client
 *   Returns an OAuth2\Client object
 *
 * Example:
 *   $test1 = oauth2_client_load('test1');
 *   $access_token = $test1->getAccessToken();
 */
function oauth2_client_load($name);

/**
 * Return the redirect_uri of oauth2_client.
 */
function oauth2_client_get_redirect_uri() {
  return url('oauth2/authorized', array('absolute' => TRUE));
}

/**
 * Set a redirect request.
 *
 * This can be used by other oauth2 clients to integrate with
 * oauth2_client, i.e. to use the same client that is registered
 * on the server for the oauth2_client.
 *
 * The oauth2_server sends the authorization reply to the
 * redirect_uri that is registered for the client, which is
 * the one corresponding to oauth2_client. If another oauth2
 * client would like to get this authorization reply, it has
 * to set a redirect request with this function, and then
 * oauth2_client will forward the reply to it.
 *
 * @param string $state
 *   The random parameter that is used on the authentication url
 *   in order to mittigate CSRF attacks. In this case it is used
 *   as a key for identifying the authentication request.
 *
 * @param array $redirect
 *  Associative array that contains the keys:
 *   - 'uri': the uri of the oauth2 client that is requesting a redirect
 *   - 'params': associative array of other parameters that should be
 *     appended to the uri, along with the $_REQUEST
 *
 * Example:
 *   $state = md5(uniqid(rand(), TRUE));
 *   $hybridauth_config['state'] = $state;
 *   $hybridauth_config['redirect_uri'] = oauth2_client_get_redirect_uri();
 *   oauth2_client_set_redirect($state, array(
 *       'uri' => 'hybridauth/endpoint',
 *       'params' => array(
 *         'hauth.done' => 'DrupalOAuth2',
 *       )
 *     ));
 */
function oauth2_client_set_redirect($state, $redirect) {
  OAuth2\Client::setRedirect($state, $redirect);
}

/**
 * Share an access token with oauth2_client.
 *
 * Another oauth2 client that has been successfully authenticated
 * and has received an access_token, can share it with oauth2_client,
 * so that oauth2_client does not have to repeat the authentication
 * process again.
 *
 * Example:
 *   $client_id = $hybridauth->api->client_id;
 *   $token = array(
 *     'access_token' => $hybridauth->api->access_token,
 *     'refresh_token' => $hybridauth->api->refresh_token,
 *     'expires_in' => $hybridauth->api->access_token_expires_in,
 *     'expiration_time' => $hybridauth->api->access_token_expires_at,
 *     'scope' => $hybridauth->scope,
 *   );
 *   $token_endpoint = $oauth2->api->token_endpoint;
 *   $client_id = $oauth2->api->client_id;
 *   $auth_flow = 'server-side';
 *   $id = md5($token_endpoint . $client_id . $auth_flow);
 *   oauth2_client_set_token($id, $token);
 */
function oauth2_client_set_token($client_id, $token) {
  OAuth2\Client::storeToken($client_id, $token);
}

/**
 * Returns the access token of the oauth2_client for the given $client_id.
 */
function oauth2_client_get_token($client_id) {
  return OAuth2\Client::loadToken($client_id);
}
