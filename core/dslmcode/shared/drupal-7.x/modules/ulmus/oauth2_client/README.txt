
This module is a a complement to the module oauth2_server.

*Note:* The modules oauth2_server and oauth2_client have conflicts
with the module oauth2, so they should not be installed at the same
time.

* How to use it

  Define oauth2 clients in your code like this:
  #+BEGIN_EXAMPLE
  /**
   * Implements hook_oauth2_clients().
   */
  function MYMODULE_oauth2_clients() {
    $server_url = 'https://oauth2_server.example.org';
    $client_url = 'https://oauth2_client.example.org';

    // user-password flow
    $oauth2_clients['test1'] = array(
      'token_endpoint' => $server_url . '/oauth2/token',
      'auth_flow' => 'user-password',
      'client_id' => 'test1',
      'client_secret' => 'test1',
      'username' => 'user1',
      'password' => 'user1',
    );

    // client-credentials flow
    $oauth2_clients['test2'] = array(
      'token_endpoint' => $server_url . '/oauth2/token',
      'auth_flow' => 'client-credentials',
      'client_id' => 'test2',
      'client_secret' => 'test2',
    );

    // server-side flow
    $oauth2_clients['test3'] = array(
      'token_endpoint' => $server_url . '/oauth2/token',
      'auth_flow' => 'server-side',
      'client_id' => 'test1',
      'client_secret' => 'test1',
      'authorization_endpoint' => $server_url . '/oauth2/authorize',
      'redirect_uri' => $client_url . '/oauth2/authorized',
    );

    return $oauth2_clients;
  }
  #+END_EXAMPLE

  Then use them like this:
  #+BEGIN_EXAMPLE
    try {
      $oauth2_client = oauth2_client_load('test1');
      $access_token = $oauth2_client->getAccessToken();
    }
    catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'error');
    }
  #+END_EXAMPLE

  The only thing that oauth2_client does is to get an access_token
  from the oauth2_server, so that it can be used for accessing web
  services.


* More about using it

  Another form of usage is like this:
  #+BEGIN_EXAMPLE
    $oauth2_config = array(
      'token_endpoint' => $server_url . '/oauth2/token',
      'auth_flow' => 'user-password',
      'client_id' => 'test1',
      'client_secret' => '12345',
      'username' => $username,
      'password' => $password,
    );
    try {
      $oauth2_client = new OAuth2\Client($oauth2_config, $client_id);
      $access_token = $oauth2_client->getAccessToken();
    }
    catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'error');
    }
  #+END_EXAMPLE

* Custom usage

  Sometimes (or rather often) oauth2 servers have special requirements
  that are different from the OAuth2 standard and different from other
  oauth2 implementations. This client cannot possibly cover all these
  special requirements. In such a case, a possible solution can be to
  extend the class *OAuth2\Client* like this:
  #+BEGIN_EXAMPLE
    <?php
    namespace OAuth2;

    class MyClient extends Client {
      protected function getToken($data) {
        // Implement the custom logic that is needed by the oauth2 server.
      }
    }
  #+END_EXAMPLE

  And then use it like this:
  #+BEGIN_EXAMPLE
    try {
      $oauth2_client = new OAuth2\MyClient($oauth2_config);
      $access_token = $oauth2_client->getAccessToken();
    }
    catch (Exception $e) {
      drupal_set_message($e->getMessage(), 'error');
    }
  #+END_EXAMPLE

* How it works

  An access token and its related data are stored on the session
  ($_SESSION['oauth2_client']['token'][$client_id]), so that it can be
  reused while it is not expired yet. The data that are stored for
  each token are: access_token, expires_in, token_type, scope,
  refresh_token and expiration_time. They are the values that come
  from the oauth2 server, except the last one, which is calculated as
  (REQUEST_TIME + expires_in).

  When the token has expired (expiration_time > time() + 10), a new
  token is requested from the oauth2 server, using the refresh_token.
  If the refresh token fails for some reason (maybe refresh_token
  expired or any other reason), then the whole process of
  authorization is performed from the beginning.

  For the client-credentials and user-password authorization flows
  this does not involve a user interaction with the oauth2 server.

  However, for the server-side flow the user has to authorize again
  the application. This is done in these steps, first the user is
  redirected to the oauth2 server to authorize the application again,
  from there it is redirected back to the application with an
  authorization code, then the application uses the authorization code
  to request a new access token.

  In order to remember the part of the client application that
  initiated the authorization request, a session variable is used:
  $_SESSION['oauth2_client']['redirect'][$state]['uri'].  Then,
  drupal_goto() is used to jump again to that path of the application.

* Integrating with other oauth2 clients

  Other oauth2 clients for Drupal can integrate with oauth2_client.
  This means that they can use the same client that is registered on
  the oauth2_server for the oauth2_client.

  The oauth2_server sends the authorization reply to the redirect_uri
  that is registered for the client. If this client has been
  registered for being used by the module oauth2_client, then its
  redirect_uri is like this:
  https://server.example.org/oauth2/authorized . A reply sent to this
  redirect_uri will be routed to the callback function supplied by
  oauth2_client. So, in general, the other oauth2 clients cannot use
  the same client_id and client_secret that are registered in the
  server. They will have to register their own client_id,
  client_secret and redirect_uri.

  However this is not very convenient. That's why oauth2_client allows
  the other oauth2 clients to use the same client_id and
  client_secret, but the reply has to pass through oauth2_client,
  since redirect_uri sends it there.

  It works like this: Suppose that another oauth2 client starts the
  authentication workflow.  On the parameters of the request it sets
  redirect_uri to the one belonging to oauth2_client (since this is
  the one that is reckognized and accepted by the server). However at
  the same time it notifies oauth2_client that the reply of this
  request should be forwarded to it. It does it by calling the
  function: oauth2_client_set_redirect($state, $redirect).

  The parameter $state is the random parameter that is used on the
  authentication url in order to mittigate CSRF attacks. In this case
  it is used as a key for identifying the authentication request.  The
  parameter $redirect is an associative array that contains the keys:
    - uri: the uri of the oauth2 client that is requesting a
      redirect
    - params: associative array of other parameters that should be
      appended to the uri, along with the $_REQUEST comming from the
      server

  Once another oauth2 client that has been successfully authenticated
  and has received an access_token, it can share it with the
  oauth2_client, so that oauth2_client does not have to repeat the
  authentication process again. It can be done by calling the
  function: oauth2_client_set_token($client_id, $token).
