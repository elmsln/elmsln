<?php
/**
 * @file
 * CIS Service Connection Drush functions.
 */

/**
 * Implementats hook_drush_command().
 */
function cis_service_connection_drush_command() {
  $items = array();
  $items['cis-send-cron-key'] = array(
    'description' => 'Send Cron key back to CIS',
    'aliases' => array('cis-sck'),
  );
  return $items;
}

/**
 * Implementats of hook_drush_help().
 */
function cis_service_connection_drush_help($section) {
  switch ($section) {
    case 'drush:cis-send-cron-key':
      return dt("Send the CRON key back to cis based on the UUID in this system.");
  }
}

/**
 * Drush command callback.
 */
function drush_cis_service_connection_cis_send_cron_key() {
  // @todo run everywhere in a drup after we get the data domains figured out
  $select = array(
    'type' => 'service_instance',
    'uuid' => variable_get('cis_service_instance_uuid', ''),
  );
  // send back the cron key for the service instance based on UUID
  $data = array(
    'field_cron_key' => variable_get('cron_key', ''),
  );
  // set the data in the CIS
  _cis_connection_set_data($select, $data);
}
