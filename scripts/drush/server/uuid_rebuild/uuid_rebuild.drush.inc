<?php

/**
 * @file
 * Drush implementation for the uuid module.
 */

/**
 * Implementats hook_drush_command().
 */
function uuid_rebuild_drush_command() {
  $items = array();
  $items['uuid-recreate-all'] = array(
    'description' => 'Recreates UUIDs for all enabled entities.',
    'aliases' => array('uuid-recreate'),
  );
  return $items;
}

/**
 * Implementats of hook_drush_help().
 */
function uuid_rebuild_drush_help($section) {
  switch ($section) {
    case 'drush:uuid-recreate-all':
      return dt("This command will drop all current UUIDs and recreate them for those content types specified in the module settings for automatic generation.");
  }
}

/**
 * Drush command callback.
 */
function drush_uuid_rebuild_uuid_recreate_all() {
  if (!drush_confirm(dt('Are you sure?'))) {
    return drush_user_abort();
  }
  drush_log(dt('Beginning bulk rebuilding of all UUIDs.'), 'ok');
  uuid_rebuild_resync_all();
}

/**
 * Regenerate all missing UUIDs.
 */
function uuid_rebuild_resync_all() {
  module_invoke_all('uuid_resync');
  // call sync to rebuild all as core resync wipes them all
  module_invoke_all('uuid_sync');
}

/**
 * Implements hook_uuid_resync().
 */
function uuid_rebuild_uuid_resync() {
  // check for UI project and ignore as it'll pick this call up if it exists
  if (!function_exists('uuid_rebuild_ui_uuid_resync')) {
    foreach (entity_get_info() as $entity_type => $info) {
      if (isset($info['uuid']) && $info['uuid'] == TRUE && !empty($info['entity keys']['uuid'])) {
        _uuid_rebuild_empty_table($info['base table'], $info['entity keys']['id'], $info['entity keys']['uuid']);
        if (!empty($info['entity keys']['revision uuid'])) {
          _uuid_rebuild_empty_table($info['revision table'], $info['entity keys']['revision'], $info['entity keys']['revision uuid']);
        }
      }
    }
  }
}

/**
 * Helper function that updates a table to wipe UUIDs
 */
function _uuid_rebuild_empty_table($table, $id_field, $uuid_field) {
  // Fetch empty records.
  $result = db_select($table, 't')
    ->fields('t', array($id_field))
    ->condition(db_or()->condition($uuid_field, '')->isNotNull($uuid_field))
    ->execute();

  // Update empty records.
  foreach ($result as $record) {
    db_update($table)
      ->fields(array($uuid_field => ''))
      ->condition($id_field, $record->{$id_field})
      ->execute();
  }
}
