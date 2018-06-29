<?php

/**
 * @file
 * Contains RestfulOAuth2Authentication and OAuth2ServerRestfulException.
 */

/**
 * A simple OAuth2 authentication type.
 */
class OAuth2ServerRestfulAuthentication extends \RestfulAuthenticationBase {

  /**
   * {@inheritdoc}
   */
  public function authenticate(array $request = array(), $method = \RestfulInterface::GET) {
    if (!$server = variable_get('oauth2_server_restful_server')) {
      return NULL;
    }

    $result = oauth2_server_check_access($server, variable_get('oauth2_server_restful_scope'));
    if ($result instanceof OAuth2\Response) {
      throw new \OAuth2ServerRestfulException($result);
    }
    elseif (is_array($result) && !empty($result['user_id'])) {
      return user_load($result['user_id']);
    }

    return NULL;
  }

  /**
   * {@inheritdoc}
   */
  public function applies(array $request = array(), $method = \RestfulInterface::GET) {
    // Don't attempt to authenticate during a Drush call, for example registry
    // rebuild.
    // @todo perhaps this should be a patch upstream (for the restful module)
    if (drupal_is_cli()) {
      return FALSE;
    }

    return parent::applies($request, $method);
  }
}

/**
 * Adapts exceptions from OAuth2 to RESTful formats.
 */
class OAuth2ServerRestfulException extends \RestfulUnauthorizedException {

  protected $response;

  public function __construct(\OAuth2\Response $response) {
    $this->response = $response;
    $this->code = $response->getStatusCode();
    $this->description = $response->getStatusText();
    $this->message = $response->getResponseBody();
  }

  /**
   * {@inheritdoc}
   */
  public function getHeaders() {
    return $this->response->getHttpHeaders();
  }

}
