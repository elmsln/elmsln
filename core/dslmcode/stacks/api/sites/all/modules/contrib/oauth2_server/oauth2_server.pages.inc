<?php

/**
 * @file
 * Page callbacks for the OAuth2 Server module.
 */

/**
 * Page callback: Authenticates the user and redirect back to the client
 * with an authorization code.
 */
function oauth2_server_authorize_page() {
  global $user;

  module_invoke_all('oauth2_server_pre_authorize');

  // Save the parameters in session so that they can be fetched later.
  $parameters = drupal_get_query_parameters();
  if (!empty($parameters['client_id']) || !empty($parameters['response_type'])) {
    $_SESSION['oauth2_server_authorize'] = $parameters;
  }

  // The user is not logged in. Redirect to login.
  if (!user_is_logged_in()) {
    $query = array(
      'destination' => 'oauth2/authorize',
    );
    drupal_goto('user/login', array('query' => $query));
  }
  // If there isn't an OAuth2 authorization in progress, redirect to the front
  // page and exit.
  elseif (empty($_SESSION['oauth2_server_authorize'])) {
    drupal_goto();
  }

  $request = new OAuth2\Request($_SESSION['oauth2_server_authorize']);

  $client_id = $request->query('client_id');
  $client = NULL;
  $server = NULL;
  // Get the client and use it to load the server and initialize the server.
  if ($client_id) {
    $client = oauth2_server_client_load($client_id);
    if ($client) {
      $server = oauth2_server_load($client->server);
    }
  }

  // Initialize the server.
  $oauth2_server = oauth2_server_start($server);

  // Automatic authorization is enabled for this client. Finish authorization.
  // handleAuthorizeRequest() will call validateAuthorizeRequest().
  $response = new OAuth2\Response();
  if ($client && $client->automatic_authorization) {
    unset($_SESSION['oauth2_server_authorize']);
    $oauth2_server->handleAuthorizeRequest($request, $response, TRUE, $user->uid);
    return oauth2_server_send_response($response);
  }
  else {
    // Validate the request.
    if (!$oauth2_server->validateAuthorizeRequest($request, $response)) {
      // Clear the parameters saved in the session to avoid reusing them when
      // doing an other request while logged in.
      unset($_SESSION['oauth2_server_authorize']);
      return oauth2_server_send_response($response);
    }

    // Determine the scope for this request.
    $scope_util = new Drupal\oauth2_server\Scope($server);
    if (!$scope = $scope_util->getScopeFromRequest($request)) {
      $scope = $scope_util->getDefaultScope();
    }
    // Convert the scope string to a set of entities.
    $scope_names = explode(' ', $scope);
    $scopes = oauth2_server_scope_load_multiple($server->name, $scope_names);

    // Show the authorize form.
    return drupal_get_form('oauth2_server_authorize_form', $client, $server, $scopes);
  }
}

/**
 * Form callback: Returns the authorize form.
 *
 * @param $client
 *   The client entity for this request.
 * @param $server
 *   The server entity for this request.
 * @param $scopes
 *   An array of scope entities representing scopes to be granted by the user.
 */
function oauth2_server_authorize_form($form, &$form_state, $client, $server, $scopes) {
  drupal_set_title(t('Authorize @client to use your account?', array('@client' => $client->label)));

  $list = array(
    'title' => t('This application will be able to:'),
    'items' => array(),
    'type' => 'ul',
  );
  foreach ($scopes as $scope) {
    $list['items'][] = array('data' => $scope->getTranslation('description'));
  }

  $form['scopes'] = array(
    '#markup' => theme('item_list', $list),
  );
  $form['authorize'] = array(
    '#type' => 'submit',
    '#value' => t('Yes, I authorize this request.'),
    '#authorized' => TRUE,
  );
  $form['cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#authorized' => FALSE,
  );

  return $form;
}

/**
 * Submit callback for oauth2_server_authorize_form.
 *
 * Completes authorization and redirects back to the client.
 */
function oauth2_server_authorize_form_submit($form, &$form_state) {
  global $user;

  // A login happened. Create the request with parameters from the session.
  if (!empty($_SESSION['oauth2_server_authorize'])) {
    $request = new OAuth2\Request($_SESSION['oauth2_server_authorize']);
    unset($_SESSION['oauth2_server_authorize']);
  }
  else {
    $request = OAuth2\Request::createFromGlobals();
  }

  $authorized = $form_state['triggering_element']['#authorized'];
  $server = $form_state['build_info']['args'][1];
  // Finish the authorization request.
  $response = new OAuth2\Response();
  $oauth2_server = oauth2_server_start($server);
  $oauth2_server->handleAuthorizeRequest($request, $response, $authorized, $user->uid);
  return oauth2_server_send_response($response);
}

/**
 * Page callback: exchanges an authorization code for an access token.
 */
function oauth2_server_token_page() {
  $request = OAuth2\Request::createFromGlobals();
  $server = oauth2_server_from_request($request);

  $response = new OAuth2\Response();
  $server->handleTokenRequest($request, $response);

  // Allow other modules to act before the token response is sent.
  module_invoke_all('oauth2_server_token', $server, $request, $response);

  return oauth2_server_send_response($response);
}

/**
 * Page callback: revoke a token.
 */
function oauth2_server_revoke_page() {
  $request = OAuth2\Request::createFromGlobals();
  $server = oauth2_server_from_request($request);
  $response = new OAuth2\Response();

  if (!method_exists($server, 'handleRevokeRequest')) {
    watchdog('oauth2_server', 'Version >= 1.8.0 of the oauth2-server-php library is required for revoke requests', array(), WATCHDOG_ERROR);
    $response->setStatusCode(500);
  }
  else {
    $server->handleRevokeRequest($request, $response);
  }

  return oauth2_server_send_response($response);
}

/**
 * Page callback: Returns information about the provided token.
 *
 * @param $token
 *   The token to verify.
 *
 * @return
 *   404 if the token was not found or has expired.
 *   Otherwise, if a valid token was found, a json encoded array with the keys:
 *     - client_id: The client ID who issued the token.
 *     - user_id: The username of the resource owner, or NULL if not known.
 *     - access_token: The access token.
 *     - expires: The unix timestamp of token expiration.
 *     - scope: Scopes in a space-separated string.
 */
function oauth2_server_tokens_page($token) {
  drupal_page_is_cacheable(FALSE);

  // Initialize the storage and try to load the requested token.
  $storage = new Drupal\oauth2_server\Storage();
  $token = $storage->getAccessToken($token);
  // No token found. Stop here.
  if (!$token || $token['expires'] <= time()) {
    $response = new OAuth2\Response(array(), 404);
    return oauth2_server_send_response($response);
  }

  // Return the token, without the server and client_id keys.
  unset($token['server']);
  return drupal_json_output($token);
}

/**
 * Page callback: returns claims about the authenticated end-user.
 */
function oauth2_server_userinfo() {
  $request = OAuth2\Request::createFromGlobals();
  $server = oauth2_server_from_request($request);
  $response = new OAuth2\Response();
  $server->handleUserInfoRequest($request, $response);
  return oauth2_server_send_response($response);
}

/**
 * Page callback: Returns the server's certificates.
 *
 * Clients use this callback to get the public key certificates used to verify
 * encrypted tokens (JWT Access token, OpenID Connect) sent by the server.
 *
 * @return
 *   An array of X.509 certificates.
 */
function oauth2_server_certificates_page() {
  drupal_page_is_cacheable(FALSE);

  $keys = oauth2_server_get_keys();
  $certificates = array();
  $certificates[] = $keys['public_key'];
  return drupal_json_output($certificates);
}
