<?php

namespace Drupal\oauth2_server;

use OAuth2\OpenID\Storage\AuthorizationCodeInterface;
use OAuth2\OpenID\Storage\UserClaimsInterface;
use OAuth2\Storage\AccessTokenInterface;
use OAuth2\Storage\ClientCredentialsInterface;
use OAuth2\Storage\JwtBearerInterface;
use OAuth2\Storage\RefreshTokenInterface;
use OAuth2\Storage\UserCredentialsInterface;
use OAuth2\Storage\PublicKeyInterface;

/**
 * Provides Drupal storage (through the underlying Entity API) for the library.
 */
class Storage implements AuthorizationCodeInterface,
  AccessTokenInterface, ClientCredentialsInterface,
  JwtBearerInterface, RefreshTokenInterface,
  UserCredentialsInterface, UserClaimsInterface,
  PublicKeyInterface
{

  /* ClientCredentialsInterface */
  public function checkClientCredentials($client_key, $client_secret = null) {
    $client = $this->getClientDetails($client_key);
    if (!$client) {
      return FALSE;
    }

    return oauth2_server_check_client_secret($client['client_secret'], $client_secret);
  }

  public function isPublicClient($client_key) {
    $client = $this->getClientDetails($client_key);
    return $client && empty($client['client_secret']);
  }

  public function getClientDetails($client_key) {
    $client = oauth2_server_client_load($client_key);
    if ($client) {
      // Return a client array in the format expected by the library.
      $client = array(
        'client_id' => $client->client_key,
        'client_secret' => $client->client_secret,
        'public_key' => $client->public_key,
        // The library expects multiple redirect uris to be separated by
        // a space, but the module separates them by a newline, matching
        // Drupal behavior in other areas.
        'redirect_uri' => str_replace(array("\r\n", "\r", "\n"), ' ', $client->redirect_uri),
      );
    }

    return $client;
  }

  public function getClientScope($client_key) {
    // The module doesn't currently support per-client scopes.
    return NULL;
  }

  public function checkRestrictedGrantType($client_key, $grant_type) {
    $client = oauth2_server_client_load($client_key);
    $server = oauth2_server_load($client->server);
    if (!empty($client->settings['override_grant_types'])) {
      $grant_types = array_filter($client->settings['grant_types']);
      $allow_implicit = !empty($client->settings['allow_implicit']);
    }
    else {
      // Fallback to the global server settings.
      $grant_types = array_filter($server->settings['grant_types']);
      $allow_implicit = !empty($server->settings['allow_implicit']);
    }

    // Implicit flow is enabled by a different setting, so it needs to be
    // added to the check separately.
    if ($allow_implicit) {
      $grant_types['implicit'] = 'implicit';
    }

    return in_array($grant_type, $grant_types);
  }

  /* AccessTokenInterface */
  public function getAccessToken($access_token) {
    $token = oauth2_server_token_load($access_token);
    if (!$token) {
      return FALSE;
    }

    $token_wrapper = entity_metadata_wrapper('oauth2_server_token', $token);

    // If the user is blocked, deny access.
    if ($token->uid && !$token_wrapper->user->status->value()) {
      return FALSE;
    }

    $scopes = array();
    foreach ($token_wrapper->scopes as $scope_wrapper) {
      $scopes[] = $scope_wrapper->name->value();
    }
    // Return a token array in the format expected by the library.
    $token_array = array(
      'server' => $token_wrapper->client->server->raw(),
      'client_id' => $token_wrapper->client->client_key->value(),
      'user_id' => $token->uid ? $token_wrapper->user->uid->value() : NULL,
      'access_token' => $token_wrapper->token->value(),
      'expires' => (int) $token_wrapper->expires->value(),
      'scope' => implode(' ', $scopes),
    );
    if (!empty($token_array['user_id']) && module_exists('uuid')) {
      $token_array['user_uuid'] = $token_wrapper->user->uuid->value();
    }

    // Track last access on the token.
    $this->logAccessTime($token);

    return $token_array;
  }

  /**
   * Track the time the token was accessed.
   *
   * @param \OAuth2ServerToken $token
   */
  protected function logAccessTime(\OAuth2ServerToken $token)
  {
    if ($token->last_access != REQUEST_TIME) {
      $token->last_access = REQUEST_TIME;
      $token->save();
    }
  }

  public function setAccessToken($access_token, $client_key, $uid, $expires, $scope = null) {
    $client = oauth2_server_client_load($client_key);
    if (!$client) {
      throw new \InvalidArgumentException("The supplied client couldn't be loaded.");
    }

    // If no token was found, start with a new entity.
    $token = oauth2_server_token_load($access_token);
    if (!$token) {
      // The username is not required, the "Client credentials" grant type
      // doesn't provide it, for instance.
      if (!$uid || !user_load($uid)) {
        $uid = 0;
      }

      $token = entity_create('oauth2_server_token', array('type' => 'access'));
      $token->client_id = $client->client_id;
      $token->uid = $uid;
      $token->token = $access_token;
    }

    $token->expires = $expires;
    $this->setScopeData($token, $client->server, $scope);

    $status = $token->save();
    return $status;
  }

  /* AuthorizationCodeInterface */
  public function getAuthorizationCode($code) {
    $code = oauth2_server_authorization_code_load($code);
    if ($code) {
      $code_wrapper = entity_metadata_wrapper('oauth2_server_authorization_code', $code);
      $scopes = array();
      foreach ($code_wrapper->scopes as $scope_wrapper) {
        $scopes[] = $scope_wrapper->name->value();
      }
      // Return a code array in the format expected by the library.
      $code = array(
        'server' => $code_wrapper->client->server->raw(),
        'client_id' => $code_wrapper->client->client_key->value(),
        'user_id' => $code_wrapper->user->uid->value(),
        'authorization_code' => $code_wrapper->code->value(),
        'redirect_uri' => $code_wrapper->redirect_uri->value(),
        'expires' => (int) $code_wrapper->expires->value(),
        'scope' => implode(' ', $scopes),
        'id_token' => $code_wrapper->id_token->value(),
      );
      if (module_exists('uuid')) {
        $code['user_uuid'] = $code_wrapper->user->uuid->value();
      }

      // Examine the id_token and alter the OpenID Connect 'sub' property if
      // necessary. The 'sub' property is usually the user's UID, but this is
      // configurable for backwards compatibility reasons. See:
      // https://www.drupal.org/node/2274357#comment-9779467
      $sub_property = variable_get('oauth2_server_user_sub_property', 'uid');
      if (!empty($code['id_token']) && $sub_property != 'uid') {
        $account = $code_wrapper->user->value();
        $desired_sub = $account->$sub_property;
        $parts = explode('.', $code['id_token']);
        $claims = json_decode(oauth2_server_base64url_decode($parts[1]), TRUE);
        if (isset($claims['sub']) && $desired_sub != $claims['sub']) {
          $claims['sub'] = $desired_sub;
          $parts[1] = oauth2_server_base64url_encode(json_encode($claims));
          $code['id_token'] = implode('.', $parts);
        }
      }
    }

    return $code;
  }

  public function setAuthorizationCode($code, $client_key, $uid, $redirect_uri, $expires, $scope = null, $id_token = null) {
    $client = oauth2_server_client_load($client_key);
    if (!$client) {
      throw new \InvalidArgumentException("The supplied client couldn't be loaded.");
    }

    // If no code was found, start with a new entity.
    $authorization_code = oauth2_server_authorization_code_load($code);
    if (!$authorization_code) {
      $user = user_load($uid);
      if (!$user) {
        throw new \InvalidArgumentException("The supplied user couldn't be loaded.");
      }

      $authorization_code = entity_create('oauth2_server_authorization_code', array());
      $authorization_code->client_id = $client->client_id;
      $authorization_code->uid = $uid;
      $authorization_code->code = $code;
      $authorization_code->id_token = $id_token;
    }

    $authorization_code->redirect_uri = $redirect_uri;
    $authorization_code->expires = $expires;
    $this->setScopeData($authorization_code, $client->server, $scope);

    $status = $authorization_code->save();
    return $status;
  }

  public function expireAuthorizationCode($code) {
    $code = oauth2_server_authorization_code_load($code);
    if ($code) {
      $code->delete();
    }
  }

  /* JwtBearerInterface */
  public function getClientKey($client_key, $subject) {
    // While the API supports a key per user (subject), the module only supports
    // one key per client, since it's the simpler and more frequent use case.
    $client = $this->getClientDetails($client_key);
    return $client ? $client['public_key'] : FALSE;
  }

  public function getJti($client_key, $subject, $audience, $expires, $jti) {
    $client = oauth2_server_client_load($client_key);
    if (!$client) {
      // The client_key should be validated prior to this method being called,
      // but the library doesn't do that currently.
      return;
    }

    $data = array(
      ':client_id' => $client->client_id,
      ':subject' => $subject,
      ':jti' => $jti,
      ':expires' => $expires,
    );
    $found = db_query('SELECT 1 FROM {oauth2_server_jti}
                        WHERE client_id = :client_id AND subject = :subject
                          AND jti = :jti AND expires = :expires', $data)->fetchField();
    if ($found) {
      // JTI found, return the data back in the expected format.
      return array(
        'issuer' => $client_key,
        'subject' => $subject,
        'jti' => $jti,
        'expires' => $expires,
      );
    }
  }

  public function setJti($client_key, $subject, $audience, $expires, $jti) {
    $client = oauth2_server_client_load($client_key);
    if (!$client) {
      // The client_key should be validated prior to this method being called,
      // but the library doesn't do that currently.
      return;
    }

    // The audience is not stored because it's always previously validated
    // to match the server's token endpoint url. Therefore, it is redundant.
    db_insert('oauth2_server_jti')
      ->fields(array(
        'client_id' => $client->client_id,
        'subject' => $subject,
        'jti' => $jti,
        'expires' => $expires,
      ))
      ->execute();
  }

  /* UserCredentialsInterface */
  public function checkUserCredentials($username, $password) {
    $account = user_load_by_name($username);
    if (!$account) {
      // An email address might have been supplied instead of the username.
      $account = user_load_by_mail($username);
    }

    if ($account && $account->status) {
      require_once DRUPAL_ROOT . '/' . variable_get('password_inc', 'includes/password.inc');
      return user_check_password($password, $account);
    }

    return FALSE;
  }

  public function getUserDetails($username) {
    $account = user_load_by_name($username);
    if (!$account) {
      // An email address might have been supplied instead of the username.
      $account = user_load_by_mail($username);
    }

    if ($account) {
      return array('user_id' => $account->uid);
    }

    return FALSE;
  }

  /* UserClaimsInterface */
  public function getUserClaims($uid, $scope) {
    $account = user_load($uid);
    if (!$account) {
      throw new \InvalidArgumentException("The supplied user couldn't be loaded.");
    }
    $requested_scopes = explode(' ', trim($scope));

    // The OpenID Connect 'sub' (Subject Identifier) property is usually the
    // user's UID, but this is configurable for backwards compatibility reasons.
    // See: https://www.drupal.org/node/2274357#comment-9779467
    $sub_property = variable_get('oauth2_server_user_sub_property', 'uid');

    // Prepare the default claims.
    $claims = array(
      'sub' => $account->$sub_property,
    );

    if (in_array('email', $requested_scopes)) {
      $claims['email'] = $account->mail;
      $claims['email_verified'] = variable_get('user_email_verification', TRUE);
    }

    if (in_array('profile', $requested_scopes)) {
      if (!empty($account->name)) {
        $claims['name'] = format_username($account);
        $claims['preferred_username'] = $account->name;
      }
      if (!empty($account->timezone)) {
        $claims['zoneinfo'] = $account->timezone;
      }
      if (user_access('access user profiles', drupal_anonymous_user())) {
        $claims['profile'] = url('user/' . $account->uid, array('absolute' => TRUE));
      }
      if ($picture = $this->getUserPicture($account)) {
        $claims['picture'] = $picture;
      }
    }

    // Allow modules to supply additional claims.
    $claims += module_invoke_all('oauth2_server_user_claims', $account, $requested_scopes);

    // Finally, allow modules to alter claims.
    drupal_alter('oauth2_server_user_claims', $claims, $account, $requested_scopes);

    return $claims;
  }

  /* RefreshTokenInterface */
  public function getRefreshToken($refresh_token) {
    $token = oauth2_server_token_load($refresh_token);
    if ($token) {
      $token_wrapper = entity_metadata_wrapper('oauth2_server_token', $token);
      $scopes = array();
      foreach ($token_wrapper->scopes as $scope_wrapper) {
        $scopes[] = $scope_wrapper->name->value();
      }
      // Return a token array in the format expected by the library.
      $token = array(
        'server' => $token_wrapper->client->server->raw(),
        'client_id' => $token_wrapper->client->client_key->value(),
        'user_id' => $token_wrapper->user->uid->value(),
        'refresh_token' => $token_wrapper->token->value(),
        'expires' => (int) $token_wrapper->expires->value(),
        'scope' => implode(' ', $scopes),
      );
      if (module_exists('uuid')) {
        $token['user_uuid'] = $token_wrapper->user->uuid->value();
      }
    }

    return $token;
  }

  public function setRefreshToken($refresh_token, $client_key, $uid, $expires, $scope = null) {
    $client = oauth2_server_client_load($client_key);
    if (!$client) {
      throw new \InvalidArgumentException("The supplied client couldn't be loaded.");
    }

    // If no token was found, start with a new entity.
    $token = oauth2_server_token_load($refresh_token);
    if (!$token) {
      $user = user_load($uid);
      if (!$user) {
        throw new \InvalidArgumentException("The supplied user couldn't be loaded.");
      }

      $token = entity_create('oauth2_server_token', array('type' => 'refresh'));
      $token->client_id = $client->client_id;
      $token->uid = $uid;
      $token->token = $refresh_token;
    }

    $token->expires = $expires;
    $this->setScopeData($token, $client->server, $scope);

    $status = $token->save();
    return $status;
  }

  public function unsetRefreshToken($refresh_token) {
    $token = oauth2_server_token_load($refresh_token);
    if ($token) {
      $token->delete();
    }
  }

  public function unsetAccessToken($access_token) {
    $token = oauth2_server_token_load($access_token);
    if ($token) {
      $token->delete();
    }
  }

  /**
   * Sets the "scopes" entityreference field on the passed entity.
   *
   * @param $entity
   *   The entity containing the "scopes" entityreference field.
   * @param $server
   *   The machine name of the server.
   * @param $scope
   *   Scopes in a space-separated string.
   */
  private function setScopeData($entity, $server, $scope) {
    $entity->scopes = array();
    if ($scope) {
      $scopes = preg_split('/\s+/', $scope);
      $loaded_scopes = oauth2_server_scope_load_multiple($server, $scopes);
      foreach ($loaded_scopes as $loaded_scope) {
        $entity->scopes[LANGUAGE_NONE][] = array(
          'target_id' => $loaded_scope->scope_id,
        );
      }
    }
  }

  /* PublicKeyInterface */
  public function getPublicKey($client_key = null) {
    // The library allows for per-client keys. The module uses global keys
    // that are regenerated every day, following Google's example.
    $keys = oauth2_server_get_keys();
    return $keys['public_key'];
  }

  public function getPrivateKey($client_key = null) {
    // The library allows for per-client keys. The module uses global keys
    // that are regenerated every day, following Google's example.
    $keys = oauth2_server_get_keys();
    return $keys['private_key'];
  }

  public function getEncryptionAlgorithm($client_key = null) {
    return 'RS256';
  }

  /**
   * Get the user's picture to return as an OpenID Connect claim.
   *
   * @param object $account
   *   The user account object.
   *
   * @return string|NULL
   *   An absolute URL to the user picture, or NULL if none is found.
   */
  protected function getUserPicture($account) {
    if (!variable_get('user_pictures', 0)) {
      return NULL;
    }

    // This uses logic from template_preprocess_user_picture().
    if (!empty($account->picture)) {
      if (is_numeric($account->picture)) {
        $account->picture = file_load($account->picture);
      }
      if (!empty($account->picture->uri)) {
        $picture_path = $account->picture->uri;
      }
    }
    else {
      $picture_path = variable_get('user_picture_default', NULL);
    }

    if (empty($picture_path)) {
      return NULL;
    }

    if (module_exists('image') && file_valid_uri($picture_path) && $style = variable_get('user_picture_style', '')) {
      $picture_url = image_style_url($style, $picture_path);
    }
    else {
      $picture_url = url(file_create_url($picture_path), array('absolute' => TRUE));
    }

    return $picture_url;
  }

}
