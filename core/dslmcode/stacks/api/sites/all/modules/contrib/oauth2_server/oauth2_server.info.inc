<?php

/**
 * @file
 * Provides Entity metadata integration.
 */

class OAuth2ServerScopeMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['server'] = array(
      'label' => t("Server"),
      'type' => 'oauth2_server',
      'description' => t("The parent server."),
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'server',
    );
    // Make the description translatable.
    $properties['description']['translatable'] = TRUE;
    $properties['description']['i18n string'] = TRUE;

    return $info;
  }
}

class OAuth2ServerClientMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    $properties['server'] = array(
      'label' => t("Server"),
      'type' => 'oauth2_server',
      'description' => t("The parent server."),
      'setter callback' => 'entity_property_verbatim_set',
      'required' => TRUE,
      'schema field' => 'server',
    );
    return $info;
  }
}

class OAuth2ServerTokenMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    unset($properties['client_id']);
    $properties['client'] = array(
      'label' => t("Client"),
      'type' => 'oauth2_server_client',
      'description' => t("The associated client."),
      'getter callback' => 'oauth2_server_get_properties',
      'setter callback' => 'oauth2_server_set_properties',
      'required' => TRUE,
      'schema field' => 'client_id',
    );
    unset($properties['uid']);
    $properties['user'] = array(
      'label' => t("User"),
      'type' => 'user',
      'description' => t("The resource owner."),
      'getter callback' => 'oauth2_server_get_properties',
      'setter callback' => 'oauth2_server_set_properties',
      'required' => TRUE,
      'schema field' => 'uid',
    );

    $expires = !empty($properties['expires']) ? $properties['expires'] : array();
    $properties['expires'] = array(
      'type' => 'date',
      'setter callback' => 'entity_property_verbatim_set',
      'description' => t('The time when the token expires.'),
    ) + $expires;

    $last_access = !empty($properties['last_access']) ? $properties['last_access'] : array();
    $properties['last_access'] = array(
        'type' => 'date',
        'setter callback' => 'entity_property_verbatim_set',
        'label' => t('Last access'),
        'description' => t('The time the token was last used.'),
      ) + $last_access;

    $created = !empty($properties['created']) ? $properties['created'] : array();
    $properties['created'] = array(
        'type' => 'date',
        'setter callback' => 'entity_property_verbatim_set',
        'description' => t('The time the token was created.'),
      ) + $created;

    return $info;
  }
}

class OAuth2ServerAuthorizationCodeMetadataController extends EntityDefaultMetadataController {

  public function entityPropertyInfo() {
    $info = parent::entityPropertyInfo();
    $properties = &$info[$this->type]['properties'];

    unset($properties['client_id']);
    $properties['client'] = array(
      'label' => t("Client"),
      'type' => 'oauth2_server_client',
      'description' => t("The associated client."),
      'getter callback' => 'oauth2_server_get_properties',
      'setter callback' => 'oauth2_server_set_properties',
      'required' => TRUE,
      'schema field' => array('client_id'),
    );
    unset($properties['uid']);
    $properties['user'] = array(
      'label' => t("User"),
      'type' => 'user',
      'description' => t("The resource owner."),
      'getter callback' => 'oauth2_server_get_properties',
      'setter callback' => 'oauth2_server_set_properties',
      'required' => TRUE,
      'schema field' => 'uid',
    );

    $expires = !empty($properties['expires']) ? $properties['expires'] : array();
    $properties['expires'] = array(
      'type' => 'date',
      'setter callback' => 'entity_property_verbatim_set',
      'description' => t('The time when the token expires.'),
    ) + $expires;

    return $info;
  }
}
