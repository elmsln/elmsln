<?php
/**
 * @file dslm drush commands
 */

DEFINE('DSLM_PATH', dirname(__FILE__));

require_once DSLM_PATH . '/lib/dslm.class.php';

/**
 * Implementation of hook_drush_help().
 */
function dslm_drush_help($section) {
  switch ($section) {
    case 'meta:dslm:title':
      return dt('DSLM (Drupal Symlink Manager)');
    case 'meta:dslm:summary':
      return dt('Drupal symlink management Drush commands.');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function dslm_drush_command() {
  $items = array();

  // Global dslm arguments
  $arguments = array(
    'dslm-base' => 'Change the dslm base directory'
  );

  $release_options = array(
    'latest' => 'Use the latest release(stable) version of core and/or profile.',
    'dev' => 'Use the latest dev version of core and/or profile.',
    'current' => 'Use the "current" symlink of core and profile, if it exists.',
  );

  $items['dslm'] = array(
    'description' => 'DSLM BASE information',
    'arguments' => $arguments,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'options' => array(
      'format' => 'Passes through drush_format instead of drush_log',
    ),
  );

  $items['dslm-info'] = array(
    'description' => 'DSLM site information',
    'arguments' => $arguments,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'options' => array(
      'format' => 'Passes through drush_format instead of drush_log.',
    ),
  );

  $items['dslm-cores'] = array(
    'description' => 'DSLM Show Cores',
    'arguments' => $arguments,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'options' => array(
      'format' => 'Passes through drush_format instead of drush_log.',
    ),
  );

  $items['dslm-profiles'] = array(
    'description' => 'DSLM Show Profiles',
    'arguments' => $arguments,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
    'options' => array(
      'format' => 'Passes through drush_format instead of drush_log.',
    ),
  );

  $items['dslm-new'] = array(
    'description' => 'DSLM  New Site',
    'arguments' => $arguments,
    // @TODO Wire up a --skip-sites-default option as well
    'options' => $release_options,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  $items['dslm-switch-core'] = array(
    'description' => 'DSLM  Switch Core',
    'arguments' => $arguments,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'options' => $release_options,
  );

  $profile_release_options = array_merge($release_options,
    array('upgrade' => 'Attempt to upgrade already symlinked profile to new version.',)
  );

  $items['dslm-add-profile'] = array(
    'description' => 'DSLM Add Profile',
    'arguments' => $arguments,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
    'options' => $profile_release_options,
  );

  $items['dslm-remove-profile'] = array(
    'description' => 'DSLM Remove Profile',
    'arguments' => $arguments,
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_ROOT,
  );

  return $items;
}

/**
 * Command callback. Displays a list of available cores.
 */
function drush_dslm() {
  // Bootstrap dslm, this grabs the instantiated and configured dslm library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }
  if (!$info = $dslm->dslmInfo()) {
    return drush_set_error($dslm->lastError());
  }
  $out = 'DSLM BASE: ' . $info['dslm_base'] . "\n";
  $out .= 'DIRECTORY: ' . $info['directory'];

  if ($format = drush_get_option('format', FALSE)) {
    drush_print(drush_format($info, '', $format));
  }
  else {
    drush_log(trim($out), 'ok');
  }
  return TRUE;
}


/**
 * Command callback. Displays the dslm information for a site.
 */
function drush_dslm_info() {
  // Bootstrap dslm, this grabs the instantiated and configured DSLM library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }

  // Iterate through the cores array and print them out
  if (!$info = $dslm->siteInfo()) {
    return drush_set_error($dslm->lastError());
  }

  $log = "Core: {$info['core']}\n";
  $info['core'] = $info['core'];
  if (!empty($info['profiles'])) {
    $log .= "Managed Profiles: ";
    foreach ($info['profiles'] as $profile => $versions) {
      $log .= "$profile-" . implode(', ', $versions);
      $info['profiles'][$profile][] = $versions;
    }
  }

  if ($format = drush_get_option('format', FALSE)) {
    drush_print(drush_format($info, '', $format));
  }
  else {
    // Render the display
    drush_log(trim($log), 'ok');
  }

  return TRUE;
}

/**
 * Command callback. Displays a list of available cores.
 */
function drush_dslm_cores() {
  // Bootstrap dslm, this grabs the instantiated and configured dslm library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }

  // Pull cores
  $cores = $dslm->getCores();

  // Iterate through the cores array and print them out
  foreach ($cores['all'] as $key => $core) {
    $out .= "$core\n";
    $info['cores'][$core] = $core;
  }

  if ($format = drush_get_option('format', FALSE)) {
    drush_print(drush_format($info, '', $format));
  }
  else {
    drush_log(trim($out), 'ok');
  }
  return TRUE;
}

/**
 * Command callback. Displays a list of available profiles.
 */
function drush_dslm_profiles() {
  // Bootstrap dslm, this grabs the instantiated and configured dslm library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }

  // Pull the profiles
  $profiles = $dslm->getProfiles();

  // Iterate through the profiles array and print them out
  foreach ($profiles as $name => $profile) {
    $out .= "$name:\n";
    foreach($profile['all'] as $version) {
      $out .= "  $version\n";
      $info['profiles'][$name][] = $version;
    }
  }

  if ($format = drush_get_option('format', FALSE)) {
    drush_print(drush_format($info, '', $format));
  }
  else {
    drush_log(trim($out), 'ok');
  }
  return TRUE;
}

/**
 * Command callback. Creates a new dslm Drupal site.
 */
function drush_dslm_new() {
  // Pull the args
  $args = drush_get_arguments();
  if (!isset($args[1])) {
    return drush_set_error(dt('Please provide destination for your DSLM site.'));
  }
  else {
    $site_dest = $args[1];
  }

  // Bootstrap dslm, this grabs the instantiated and configured Dslm library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }

  // Set the profile and core, either supplied on the CLI, set with --latest, or will prompt
  if (drush_get_option('latest', FALSE)) {
    $latest = $dslm->latestCores();
    $core = $latest['release'];
  }
  elseif (drush_get_option('dev', FALSE)) {
    $latest = $dslm->latestCores();
    $core = $latest['dev'];
  }
  elseif (drush_get_option('current', FALSE)) {
    $core = 'current';
  }
  else {
    $core = isset($args[2]) ? $args[2] : FALSE;
  }

  // If we still don't have a core string try to get on iteractively
  if (!$core) {
    $core_list = $dslm->getCores();
    $pick_core = drush_choice($core_list['all']);
    if ($pick_core === FALSE) {
      return FALSE;
    }
    $core = $core_list['all'][$pick_core];
  }

  if (!$res = $dslm->newSite($site_dest, $core)) {
    return drush_set_error($dslm->lastError());
  }
  else {
    drush_log(dt('Your site has been linked in !dir.', array('!dir' => $site_dest)), 'success');
    return TRUE;
  }
}

/**
 * Command callback. Prompts the user to switch the dslm core.
 */
function drush_dslm_switch_core() {
  // Bootstrap dslm, this grabs the instantiated and configured Dslm library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }

  $args = drush_get_arguments();
  $core = isset($args[1]) ? $args[1] : FALSE;

  if (!$core && drush_get_option('current', FALSE)) {
    $core = 'current';
  }

  // If we still don't have a core string try to get on iteractively
  if (!$core) {
    $core_list = $dslm->getCores();
    $pick_core = drush_choice($core_list['all']);
    if (!$pick_core) {
      return FALSE;
    }
    $core = $core_list['all'][$pick_core];
  }

  $run = $dslm->switchCore($core);
  if (!$run) {
    return drush_set_error($dslm->lastError());
  }
  else {
    // @todo: get $dslm->newSite to return validated switch information rather than TRUE
    //  for reporting here.
    drush_log('The links have been switched.', 'success');
    return TRUE;
  }
}

/**
 * Command callback. Adds a profile
 */
function drush_dslm_add_profile() {
  // Bootstrap dslm, this grabs the instantiated and configured Dslm library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }

  $args = drush_get_arguments();

  // Get a list of profiles
  $profiles = $dslm->getProfiles();

  // Get the profile name via args or interactively
  $profile_name = isset($args[1]) ? $args[1] : FALSE;

  if (drush_get_option('current', FALSE)) {
    $profile_version = 'current';
  }

  // Version might be coming through the profile_name as in my_profile-1.2
  if (!isset($profile_version)) {
    list($profile_name, $profile_version) = explode('-', $profile_name);
  }

  if (!$profile_name) {
    $choices = array();
    foreach ($profiles as $k => $v) {
      $choices[$k] = $k;
    }
    $profile_name = drush_choice($choices);
    if (!$profile_name || !isset($profiles[$profile_name])) {
      return FALSE;
    }
  }
  if ($profile_name && !$profiles[$profile_name]) {
    return drush_set_error(dt('Invalid profile name given.'));
  }

  // If profile version not provided as single string with name, check arg 2
  // as in "drush dslm-add-profile my_profile 1.2"
  $profile_version = isset($args[2]) ? $args[2] : $profile_version;

  if (drush_get_option('latest', FALSE)) {
    $latest = $dslm->latestProfiles($profile_name);
    $profile_version = $latest['release'];
  }
  elseif (drush_get_option('dev', FALSE)) {
    $latest = $dslm->latestProfiles($profile_name);
    $profile_version = $latest['dev'];
  }

  // If we still dont have a version number, prompt the user with the
  // available options.
  if (!$profile_version) {
    $choices = array();
    foreach ($profiles[$profile_name]['all'] as $k => $v) {
      $choices[$v] = $v;
    }
    $profile_version = drush_choice($choices);
  }

  // Validate that the profile name and version matches a dslm managed profile.
  if (!in_array($profile_version, $profiles[$profile_name]['all'])) {
    return drush_set_error(dt('Invalid profile version given.'));
  }

  // Determine if we are upgrading a currently managed dslm profile.
  $upgrade = drush_get_option('upgrade', FALSE);

  // Run the DSLM manageProfile method to add the profile or deal with an error
  if ($dslm->manageProfile($profile_name, $profile_version, FALSE, $upgrade)) {
    if ($upgrade) {
      drush_log(dt('The DSLM profile !profile has been upgraded to version !version.', array('!profile' => $profile_name, '!version' => $profile_version)), 'success');
    }
    else {
      drush_log(dt('The DSLM profile !profile-!version has been added.', array('!profile' => $profile_name, '!version' => $profile_version)), 'success');
    }
  }
  else {
    return drush_set_error($dslm->lastError());
  }
}

/**
 * Command callback. Removes a profile.
 */
function drush_dslm_remove_profile() {
  // Bootstrap dslm, this grabs the instantiated and configured Dslm library object
  if (!$dslm = _dslm_bootstrap()) {
    return FALSE;
  }

  if (!$info = $dslm->siteInfo()) {
    return drush_set_error($dslm->lastError());
  }

  $args = drush_get_arguments();

  // Get the profile name via args or interactively.
  $profile_name = isset($args[1]) ? $args[1] : FALSE;

  // Version might be coming through the profile_name as in my_profile-1.2, we only
  // care about the name here.
  list($profile_name, $profile_version) = explode('-', $profile_name);

  if (!$profile_name) {
    if (!empty($info['profiles'])) {
      foreach ($info['profiles'] as $profile => $versions) {
        $choices[$profile] = $profile;
      }
      $profile_name = drush_choice($choices);
    }
    else {
      return drush_set_error(dt('No DSLM profiles available to be removed.'));
    }
  }

  if ($dslm->removeProfile($profile_name)) {
    drush_log(dt('The DSLM profile !profile has been removed.', array('!profile' => $profile_name)), 'success');
  }
  else {
    return drush_set_error($dslm->lastError());
  }
}

/**
 * Internal bootstrap function
 * @return object
 *  Returns an instantiated Dslm object
 */
function _dslm_bootstrap() {
  if (!$base = _dslm_get_base()) {
    return drush_set_error(dt('Please set a DSLM Drupal base in order for DSLM commands to work.'));
  }

  // Instantiate the dslm object
  $dslm = new Dslm($base);

  // If the base is bad on construct an error will be set
  if ($last_error = $dslm->lastError()) {
    return drush_set_error($last_error);
  }

  return $dslm;
}

/**
 * Internal helper function to get the dslm drupal base folder
 * Reads the following locations in order:
 * - The cli switch --dslm-base=base
 * - The drushrc.php file $conf['dslm_base'] = base;
 * - The dslm_BASE system environment variable
 * @return string
 *  Returns a base path or FALSE
 */
function _dslm_get_base() {
  // Initialize an empty base.
  $base = '';

  // Try to get a base from one of the appropriate sources
  if ($base_check = drush_get_option('dslm-base', FALSE)) {
    // We have this wet with --dslm-base on the cli
    $base = $base_check;
  }
  elseif ($base_check = drush_get_option('dslm_base', FALSE)) {
    // We have this set in the drushrc.php file
    $base = $base_check;
  }
  else {
    // Last ditch is tp ise the environment variable if it's set.
    if (isset($_ENV['DSLM_BASE'])) {
      $base = $_ENV['DSLM_BASE'];
    } else {
      // If we got here and there wasn't an environment variable set, bail
      return FALSE;
    }
  }

  // PHP doesn't resolve ~ as the home directory.
  if (isset($_SERVER['HOME'])) {
    $base = preg_replace('/^\~/', $_SERVER['HOME'], $base);
  }

  return $base;
}
