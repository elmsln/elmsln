<?php
/**
 * @file
 * Drush integration for ELMSLN.
 */
/**
 * Implements hook_drush_command().
 */
function elmsln_core_drush_command() {
  $items['elmsln-change-salt'] = array(
    'description' => dt('This changes the salt used in figuring out passwords on the system.'),
    'aliases' => array('elmsln-salt'),
    'options' => array(),
    'examples' => array(
      'drush elmsln-salt' =>
        'Changes the salt value used to calculate safe passwords. This doesn\'t update them though.',
    ),
  );
  $items['elmsln-rebuild-service-password'] = array(
    'description' => dt('Ensures the password is correct for service accounts based on salt / hash value changes.'),
    'aliases' => array('elmsln-service-pwd'),
    'options' => array(),
    'examples' => array(
      'drush elmsln-service-pwd' =>
        'Updates the service account password',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function elmsln_core_drush_help($section) {
  switch ($section) {
    case 'drush:elmsln-change-salt':
      return dt('Change the salt value used to secure things network wide.');
    case 'drush:elmsln-rebuild-service-password':
      return dt('Rebuild password assoicated to the service account.');
  }
}

/**
 * Drush command callback for elmsln-change-salt.
 */
function drush_elmsln_core_elmsln_change_salt() {
  $cfg = _elmsln_core_get_cfg();
  $fsalt = $cfg['elmsln'] . '/config/SALT.txt';
  $uuid = uuid_generate();
  // sprinkle in some salt from the file system
  file_put_contents($fsalt, $uuid);
  drush_print('The ELMSLN SALT has been updated.');
  if (drush_get_option('verbose')) {
    drush_print($uuid);
  }
}

/**
 * Drush command callback for elmsln-rebuild-service-password.
 */
function drush_elmsln_core_elmsln_rebuild_service_password() {
  // tee up profile to look up the registry about this tool
  $tool = variable_get('install_profile', 'standard');
  $settings = _cis_connector_build_registry($tool);
  // load the account
  $usr = user_load_by_name($settings['user']);
  $tmp = $usr->pass;
  // save this change
  user_save($usr, array('pass' => $settings['pass']));
  drush_print('The ELMSLN service user ' . $settings['user'] . ' password updated to match registry.');
}
