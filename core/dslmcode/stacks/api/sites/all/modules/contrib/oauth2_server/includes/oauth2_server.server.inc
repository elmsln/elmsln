<?php

/**
 * Entity class representing the oauth2_server entity type.
 */
class OAuth2Server extends Entity {

  /**
   * The machine name of the server.
   *
   * @var string
   */
  public $name;

  /**
   * The label of the server.
   *
   * @var string
   */
  public $label;

  /**
   * An array of settings.
   *
   * @var array
   */
  public $settings = array(
    'default_scope' => '',
    'enforce_state' => TRUE,
    'allow_implicit' => FALSE,
    'use_openid_connect' => FALSE,
    'use_crypto_tokens' => FALSE,
    'store_encrypted_token_string' => FALSE,
    'require_exact_redirect_uri' => TRUE,
    'grant_types' => array(
      'authorization_code' => 'authorization_code',
      'refresh_token' => 'refresh_token',
    ),
    'access_lifetime' => 3600,
    'id_lifetime' => 3600,
    'refresh_token_lifetime' => 1209600,
  );

  public function __construct($values = array()) {
    parent::__construct($values, 'oauth2_server');
  }
}
