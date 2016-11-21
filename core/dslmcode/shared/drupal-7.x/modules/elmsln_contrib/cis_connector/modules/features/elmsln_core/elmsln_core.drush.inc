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
  $items['elmsln-migrate-banner'] = array(
    'description' => dt('Clone locally uploaded banner to correct location in scope CIS'),
    'aliases' => array('elmsln-migrate-banner'),
    'options' => array(),
    'examples' => array(
      'drush elmsln-migrate-banner' =>
        'Copies local banner to correct location in CIS',
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
    case 'drush:elmsln-migrate-banner':
      return dt('Copies local banner to correct location in CIS.');
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
  require_once DRUPAL_ROOT . '/includes/password.inc';
  // tee up profile to look up the registry about this tool
  $tool = elmsln_core_get_profile_key();
  $registry = _cis_connector_build_registry($tool);
  // load the account
  $usr = user_load_by_name($registry['user']);
  // shouldn't be possible but make service account on demand if needed
  if (!$usr) {
    // ensure that user and pass are set
    if (isset($registry['user']) && isset($registry['pass'])) {
      // make sure this account doesn't already exist to avoid an error
      if (!user_load_by_name($registry['user'])) {
        // we know we need to make an account, look for mail address
        if (isset($registry['mail'])) {
          $mail = $registry['mail'];
        }
        else {
          // generate a fake address
          $mail = $registry['user'] . '@' . $registry['user'] . '.' . $registry['user'];
        }
        // assemble a user object
        $fields = array(
          'name' => $registry['user'],
          'mail' => $mail,
          'pass' => $registry['pass'],
          'status' => 1,
          'init' => $GLOBALS['user']->name,
          'roles' => array(
            DRUPAL_AUTHENTICATED_RID => 'authenticated user',
          ),
        );
        // load the service account role
        $rname = 'SERVICE ACCOUNT';
        if ($srole = user_role_load_by_name($rname)) {
          $fields['roles'][$srole->rid] = $rname;
        }
        // load the administrator role to ensure webservices can get data needed
        $aname = 'administrator';
        if ($arole = user_role_load_by_name($aname)) {
          $fields['roles'][$arole->rid] = $aname;
        }
        // the first parameter is left blank so a new user is created
        $usr = user_save('', $fields);
        $precheck = FALSE;
      }
    }
  }
  else {
    $precheck = user_check_password($registry['pass'], $usr);
    user_save($usr, array('pass' => $registry['pass'], 'init' => ''));
  }
  // see if password changed
  if (user_check_password($registry['pass'], $usr) && $precheck) {
    drush_print('The ELMSLN service user ' . $registry['user'] . ' loaded but no change was made.');
  }
  else {
    drush_print('The ELMSLN service user ' . $registry['user'] . ' password updated to match registry.');
  }
}

/**
 * Drush command callback for elmsln-migrate-banner.
 */
function drush_elmsln_core_elmsln_migrate_banner() {
  global $elmslncfg;
  $current = drupal_realpath(theme_get_setting('logo_path'));
  // only migrate if something was set
  if (!empty($current)) {
    // build the remote banner URI unless it's missing
    $uri = 'elmslnauthority://cis/banners';
    $bannerdir = _elmsln_core_realpath($uri);
    if (!is_dir($bannerdir)) {
      mkdir($bannerdir);
    }
    $banner = $bannerdir . '/' . _cis_connector_course_context() . '.jpg';
    if (!file_exists($banner)) {
      if (file_exists($current)) {
        // copy it over cause we have both
        copy($current, $banner);
        @chmod($banner, 0664);
        @chown($banner, $elmslncfg['wwwuser']);
      }
      else {
        drush_print('Current banner could not be found:' . $current);
      }
    }
    else {
      drush_print('Banner already exists in CIS, no reason to migrate.');
    }
  }
  else {
    drush_print('Nothing to migrate, needs a banner to function');
  }
}
