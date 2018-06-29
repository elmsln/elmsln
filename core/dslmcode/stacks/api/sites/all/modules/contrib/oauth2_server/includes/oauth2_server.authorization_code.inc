<?php

/**
 * Entity class representing the oauth2_server_authorization_code entity type.
 */
class OAuth2ServerAuthorizationCode extends Entity {

  /**
   * The id of the associated client.
   *
   * @var integer
   */
  public $client_id;

  /**
   * The uid of the resource owner.
   *
   * @var integer
   */
  public $uid;

  /**
   * The code.
   *
   * @var string
   */
  public $code;

  /**
   * The absolute URI to redirect to after authorization.
   *
   * @var string
   */
  public $redirect_uri;

  /**
   * The Unix timestamp when the code expires.
   *
   * @var integer
   */
  public $expires;

  /**
   * The id_token, if OpenID Connect was used.
   *
   * @var string
   */
  public $id_token;

  public function __construct($values = array()) {
    parent::__construct($values, 'oauth2_server_authorization_code');
  }
}
