<?php

/**
 * @file
 * Administration functions for the uuid module.
 */

/**
 * Menu callback: options for UUID.
 */
function uuid_admin_form() {
  $form = array();

  $form['sync'] = array(
    '#type' => 'fieldset',
    '#title' => t('Synchronization'),
  );

  $form['sync']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Create missing UUIDs'),
    '#submit' => array('uuid_admin_sync_submit'),
  );
  $form['sync']['resync_submit'] = array(
    '#type' => 'submit',
    '#value' => t('Rebuild all UUIDs'),
    '#submit' => array('uuid_admin_resync_submit'),
  );

  return system_settings_form($form);
}

/**
 * Submit handler for the UUID sync.
 */
function uuid_admin_sync_submit() {
  uuid_sync_all();
  drupal_set_message(t('Generated missing UUIDs.'));
}

/**
 * Submit handler for the UUID resync.
 */
function uuid_admin_resync_submit() {
  uuid_resync_all();
  drupal_set_message(t('Recreated all UUIDs.'));
}

/**
 * Page callback to display Devel information about a UUID entity.
 */
function uuid_devel_load_by_uuid($entity_type, $entity) {
  $info = entity_get_info($entity_type);
  if (isset($info['uuid']) && $info['uuid'] == TRUE && !empty($info['entity keys']['uuid'])) {
    // Get the keys for local ID and UUID.
    $uuid_key = $info['entity keys']['uuid'];
    $uuid_entities = entity_uuid_load($entity_type, array($entity->{$uuid_key}));
    return kdevel_print_object(reset($uuid_entities), '$' . $entity_type . '->');
  }
  else {
    return t("This entity doesn't support UUID.");
  }
}
