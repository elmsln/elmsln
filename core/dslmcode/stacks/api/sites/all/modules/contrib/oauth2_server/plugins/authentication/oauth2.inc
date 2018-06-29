<?php
/**
 * @file
 * Plugin definition for the 'oauth2' RESTful authentication type.
 */

$plugin = array(
  'label' => t('OAuth2'),
  'description' => t('Authenticate requests based on OAuth2'),
  'name' => 'oauth2',
  'class' => 'OAuth2ServerRestfulAuthentication',
);
