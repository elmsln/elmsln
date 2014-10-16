<?php

/**
 * @file
 * ELMSLN drush plugins.
 *
 * This provides drush utilities that help speed up the pace of testing
 * and development of new stacks and capabilities. These plugins work when
 * you have the ELMSLN developer package and make certain assumptions about
 * the way you have your local file system setup.
 *
 * You need to define $options['elmsln_developer'] in ~/.drush/drushrc.php
 * by providing the path (no trailing slash) to where the elmsln-developer
 * git repo has been checked out.
 *
 */

define('ELMSLN_DSLMCODE', '/github/core/dslmcode');
define('ELMSLN_INSTANCES', '/instances');
define('ELMSLN_SCRIPTS', '/github/scripts');
define('ELMSLN_CORES', ELMSLN_DSLMCODE . '/cores');
define('ELMSLN_PROFILES', ELMSLN_DSLMCODE . '/profiles');
define('ELMSLN_STACKS', ELMSLN_DSLMCODE . '/stacks');
// paths for all D7 shared locations
define('ELMSLN_D7_SHARED', ELMSLN_DSLMCODE . '/shared/drupal-7.x');

/**
 * Implements hook_drush_command().
 */
function elmsln_pm_drush_command() {
  $items = array();
  $items['elmsln-pm-dl'] = array(
    'description' => dt('download a project into the correct location in elmsln\'s setup'),
    'arguments' => array(
      'type' => dt('Type of project (core, module, theme, profile, drush)'),
      'stack' => dt('Tool to provide this functionality for'),
      'project' => dt('The project to download via drush dl invoke'),
    ),
    'options' => array(
      'instance' => dt('allow for downloading projects into their associated instance directory if the name of the instance is supplied.'),
    ),
    'aliases' => array('edl'),
    'examples' => array(
      'drush edl core ulmus drupal' =>
        'download the latest version of core into dslmcode/cores',
      'drush edl module ulmus views' =>
        'Download views into the shared ulmus modules directory',
      'drush edl drush local drush_ecl' =>
        'download entity cache loaded into the elmsln/scripts/drush/local directory.',
      'drush edl theme ulmus meedjum_blog' =>
        'download meedjum_blog install profile into the dslmcode/profiles/meedjum_blog-7.x-1.x directory',
      'drush edl theme courses zen' =>
        'download zen theme into dslmcode/stacks/courses/sites/all/themes/local_contrib',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function elmsln_pm_drush_help($section) {
  switch ($section) {
    case 'drush:elmsln-pm-dl':
      return dt('Download projects into the correct part of the ELMSLN setup.');
  }
}

/**
 * Drush command callback for elmsln-pm-dl.
 */
function drush_elmsln_pm_dl($type, $stack, $project) {
  // sanity check
  if (empty($type) || empty($stack) || empty($project)) {
    drush_log(dt('ELMSLN PM dl requires all three properties in order to function correctly'), 'error');
    return FALSE;
  }
  // ensure we know where the elmsln-developer git repo is
  if (!$elmsln_dev = drush_get_option('elmsln_developer', FALSE)) {
    drush_log(dt('You must define the location of the elmsln developer git repo in your local file system. You can do this by adding something like the following to you ~/.drush/drushrc.php file $options[\'elmsln_developer\'] = \'/full/system/path/to/elmsln-developer\';'), 'error');
    return FALSE;
  }
  switch ($type) {
    case 'core':
      $path = ELMSLN_CORES;
    break;
    case 'profile':
      $path = ELMSLN_PROFILES;
    break;
    case 'drush':
      if (in_array($stack, array('local', 'server'))) {
        $path = ELMSLN_SCRIPTS . '/drush/' . $stack;
      }
      else {
        drush_log(dt('Drush plugins can only be downloaded in this manner to the local or server directories.'), 'error');
        return FALSE;
      }
    break;
    case 'module':
    case 'theme':
      if ($stack == 'ulmus') {
        $path = ELMSLN_D7_SHARED . '/' . $type .'s/' . $stack;
      }
      else {
        $path = ELMSLN_STACKS . '/' . $stack . '/sites/all/' . $type .'s/local_contrib';
      }
    break;
    default:
      drush_log(dt('Unknown project type, don\'t know what to do'), 'error');
      return FALSE;
    break;
  }

  // build the drush command to invoke
  $cmd = array(
    'target' => '@none',
    'command' => 'dl',
    'arguments' => array($project),
    'options' => array(
      'destination' => $path
    ),
  );
  drush_invoke_process($cmd['target'], $cmd['command'], $cmd['arguments'], $cmd['options']);
  return TRUE;
}
