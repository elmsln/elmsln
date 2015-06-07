<?php
/**
 * @file
 * elmsln_authcache.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function elmsln_authcache_defaultconfig_features() {
  return array(
    'elmsln_authcache' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function elmsln_authcache_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'authcache_mimetype';
  $strongarm->value = 'text/html
text/javascript
text/plain
application/xml
application/atom+xml
';
  $export['authcache_mimetype'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'authcache_pagecaching';
  $strongarm->value = array(
    0 => array(
      'option' => '0',
      'pages' => 'user*
node/add/*
node/*/edit
node/*/track
tracker*
comment/edit*
civicrm*
cart*
checkout*
system/files/*
system/temporary*
file/ajax/*
js/admin_menu/cache/*
',
      'noadmin' => 1,
      'roles' => array(
        'custom' => '1',
        'roles' => array(
          1 => '1',
          2 => '2',
          135574917 => '135574917',
          6065076 => '6065076',
          66784200 => '66784200',
          67296478 => '67296478',
          75987638 => '75987638',
          166149871 => '166149871',
          90720314 => '90720314',
        ),
      ),
    ),
  );
  $export['authcache_pagecaching'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'authcache_roles';
  $strongarm->value = array(
    1 => '1',
    2 => '2',
    135574917 => '135574917',
    6065076 => '6065076',
    66784200 => '66784200',
    67296478 => '67296478',
    75987638 => '75987638',
    166149871 => '166149871',
    90720314 => '90720314',
  );
  $export['authcache_roles'] = $strongarm;

  return $export;
}
