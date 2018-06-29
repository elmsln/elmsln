<?php

/**
 * Entity class representing the oauth2_token entity type.
 */
class OAuth2ServerToken extends Entity {

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
   * The type of the token (access, refresh).
   *
   * @var string
   */
  public $type;

  /**
   * The token.
   *
   * @var string
   */
  public $token;

  /**
   * The Unix timestamp when the token expires.
   *
   * @var integer
   */
  public $expires;

  /**
   * The Unix timestamp when the token was last used.
   *
   * @var integer
   */
  public $last_access;

  /**
   * The Unix timestamp when the token was created.
   *
   * @var integer
   */
  public $created;

  public function __construct($values = array()) {
    parent::__construct($values, 'oauth2_server_token');
  }
}
