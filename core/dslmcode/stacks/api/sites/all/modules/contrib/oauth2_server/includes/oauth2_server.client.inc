<?php

/**
 * Entity class representing the oauth2_server_client entity type.
 */
class OAuth2ServerClient extends Entity {

  /**
   * The machine name of the parent server.
   *
   * @var string
   */
  public $server;

  /**
   * The label of the client.
   *
   * @var string
   */
  public $label;

  /**
   * The client key.
   *
   * @var string
   */
  public $client_key;

  /**
   * The client secret.
   *
   * @var string
   */
  public $client_secret;

  /**
   * The public key.
   *
   * Used to decode the JWT when the "JWT bearer" grant type is used.
   *
   * @var string
   */
  public $public_key;

  /**
   * The absolute URI to redirect to after authorization.
   *
   * @var string
   */
  public $redirect_uri;

  /**
   * Whether authorization should be completed without user confirmation.
   *
   * @var boolean
   */
  public $automatic_authorization = FALSE;

  /**
   * An array of settings.
   *
   * Used to override server-level settings.
   *
   * @var array
   */
  public $settings = array(
    'override_grant_types' => FALSE,
    'allow_implicit' => FALSE,
    'grant_types' => array(
      'authorization_code' => 'authorization_code',
      'refresh_token' => 'refresh_token',
    ),
  );

  public function __construct($values = array()) {
    parent::__construct($values, 'oauth2_server_client');
  }
}
