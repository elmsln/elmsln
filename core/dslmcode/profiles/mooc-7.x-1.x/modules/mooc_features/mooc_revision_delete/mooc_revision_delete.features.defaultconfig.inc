<?php
/**
 * @file
 * mooc_revision_delete.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function mooc_revision_delete_defaultconfig_features() {
  return array(
    'mooc_revision_delete' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function mooc_revision_delete_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'revision_delete';
  $strongarm->value = array(
    'mooc_container' => 'mooc_container',
    'page' => 'page',
    'section' => 0,
    'noderevisiondeletetest' => 0,
  );
  $export['revision_delete'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'revision_delete_age';
  $strongarm->value = '63072000';
  $export['revision_delete_age'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'revision_delete_frequency';
  $strongarm->value = '86400';
  $export['revision_delete_frequency'] = $strongarm;

  return $export;
}
