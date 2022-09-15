<?php

/**
 * @file
 * Contains export plugin definition for http response headers.
 */

$plugin = array(
  'schema' => 'http_response_headers',
  'access' => 'administer http response headers',

  'menu' => array(
    'menu prefix' => 'admin/config/system',
    'menu item' => 'http-response-headers',
    'menu title' => 'HTTP response headers',
    'menu description' => 'Administer HTTP response header rules',
  ),

  'title singular' => t('http response header rule'),
  'title singular proper' => t('HTTP response header rule'),
  'title plural' => t('http response header rules'),
  'title plural proper' => t('HTTP response header rules'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'http_response_headers_ui_form',
    'submit' => 'http_response_headers_ui_form_submit',
  ),
);
