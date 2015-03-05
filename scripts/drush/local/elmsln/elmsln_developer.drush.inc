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

define('ELMSLN_DSLMCODE', '/system/core/dslmcode');
define('ELMSLN_INSTANCES', '/instances');
define('ELMSLN_SCRIPTS', '/system/scripts');
define('ELMSLN_CORES', ELMSLN_DSLMCODE . '/cores');
define('ELMSLN_PROFILES', ELMSLN_DSLMCODE . '/profiles');
define('ELMSLN_STACKS', ELMSLN_DSLMCODE . '/stacks');
// paths for all D7 shared locations
define('ELMSLN_D7_SHARED', ELMSLN_DSLMCODE . '/shared/drupal-7.x');

/**
 * Implements hook_drush_command().
 */
function elmsln_developer_drush_command() {
  $items = array();
  $items['elmsln-dl'] = array(
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
  // Recreate symlinks for all libraries
  $items['elmsln-symlink-libraries'] = array(
    'description' => dt('Rebuilds the libraries symlinkage. Useful after making changes to the shared libraries directory.'),
    'aliases' => array('elms-sym-libs'),
    'examples' => array(
      'drush elms-sym-libs' => 'correctly symlink all libraries into the stacks in place.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  // add a new stack / tool for use in ELMSLN
  $items['elmsln-add-stack'] = array(
    'description' => dt('Create a new stack / tool and correctly build the symlinks to the (non-existent) instance directory.'),
    'arguments' => array(
      'name' => dt('Name of the stack to build'),
      'profile' => dt('Profile to use currently in the profiles directory.'),
    ),
    'options' => array(
      'stack-instance' => dt('No value needed, if this is a tool instance then pass it in, otherwise the default is that the tool is a standalone.'),
    ),
    'aliases' => array('eas'),
    'examples' => array(
      'drush eas coolstuff' => 'Add a new symlinked drupal core into core/dslmcode/stacks/coolstuff, add a new domain record and correctly point symlinks for deployment specific files like .htaccess and sites/coolstuff.',
      'drush eas intranet openatrium-7.x-1.x' => 'Add a new symlinked drupal core into core/dslmcode/stacks/intranet, add a new domain record and correctly point symlinks for deployment specific files like .htaccess and sites/intranet. Then symlink to openatrium in the profiles directory',
      'drush eas discuss --stack-instance=TRUE' => 'Add symlinked core called discuss and then when making the domain this is an instance based tool instead of pointing right to the assembled core.',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function elmsln_developer_drush_help($section) {
  switch ($section) {
    case 'drush:elmsln-dl':
      return dt('Download projects into the correct part of the ELMSLN setup.');
    case 'drush:elmsln-symlink-libraries':
      return dt('Resymlink the libraries for all stacks.');
    case 'drush:elmsln-add-stack':
      return dt('Create a new tool for use in ELMSLN.');
  }
}

/**
 * Drush command callback for elmsln-dl.
 */
function drush_elmsln_developer_elmsln_dl($type = NULL, $stack = NULL, $project = NULL) {
  // sanity check
  if (empty($type) || empty($stack) || empty($project)) {
    drush_log(dt('ELMSLN dl requires all three properties in order to function correctly. run drush edl --help for details.'), 'error');
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
      'destination' => $elmsln_dev . $path,
    ),
  );
  drush_invoke_process($cmd['target'], $cmd['command'], $cmd['arguments'], $cmd['options']);
  return TRUE;
}

/**
 * Drush command callback for elmsln-symlink-libraries.
 */
function drush_elmsln_developer_elmsln_symlink_libraries() {
  // ensure we know where the elmsln-developer git repo is
  if (!$elmsln_dev = drush_get_option('elmsln_developer', FALSE)) {
    drush_log(dt('You must define the location of the elmsln developer git repo in your local file system. You can do this by adding something like the following to you ~/.drush/drushrc.php file $options[\'elmsln_developer\'] = \'/full/system/path/to/elmsln-developer\';'), 'error');
    return FALSE;
  }
  // get contents of the stacks and shared libraries
  $shared_libraries = $elmsln_dev . ELMSLN_D7_SHARED . '/libraries';
  $libraries = _drush_elmsln_directory_contents($shared_libraries);
  $stacks = _drush_elmsln_directory_contents($elmsln_dev . ELMSLN_STACKS);
  // Look for folders that we want to include in sites/all/libraries
  foreach ($stacks as $stack) {
    $stack_lib = $elmsln_dev . ELMSLN_STACKS . "/$stack/sites/all/libraries";
    $existing = _drush_elmsln_directory_contents($stack_lib);
    foreach ($existing as $current) {
      // unlink all and relink, this avoids cruft being left over
      // while still should fail for things we forcibly are creating
      // a local copy of (like a specific version of underscore.js)
      unlink("$stack_lib/$current");
    }
    // loop through and rebuild
    foreach ($libraries as $library) {
      // if we don't have a link here yet then make one
      if (!is_link("$stack_lib/$library")) {
        $relpath = _drush_elmsln_relpath($shared_libraries, $stack_lib);
        symlink("$relpath/$library", "$stack_lib/$library");
      }
    }
  }
}

/**
 * Drush command callback for elmsln-add-stack.
 */
function drush_elmsln_developer_elmsln_add_stack($name = NULL, $profile = NULL) {
  // sanity check
  if (empty($name)) {
    drush_log(dt('ELMSLN Add Stack requires name of the new stack be defined'), 'error');
    return FALSE;
  }
  // ensure we know where the elmsln-developer git repo is
  if (!$elmsln_dev = drush_get_option('elmsln_developer', FALSE)) {
    drush_log(dt('You must define the location of the elmsln developer git repo in your local file system. You can do this by adding something like the following to you ~/.drush/drushrc.php file $options[\'elmsln_developer\'] = \'/full/system/path/to/elmsln-developer\';'), 'error');
    return FALSE;
  }
  // build the drush command to invoke since we have a path
  $path = $elmsln_dev . ELMSLN_STACKS . '/' . $name;
  $cmd = array(
    'target' => '@none',
    'command' => 'dslm-new',
    'arguments' => array($path),
    'options' => array(
      'interactive' => TRUE,
      'latest' => TRUE,
    ),
  );
  drush_invoke_process($cmd['target'], $cmd['command'], $cmd['arguments'], $cmd['options']);
  // remove _PATCHES from linking over
  unlink($path . '/_PATCHES');
  unlink($path . '/.htaccess');
  unlink($path . '/sites/default/default.settings.php');
  rmdir($path . '/sites/default/files');
  rmdir($path . '/sites/default');
  // symlink htaccess / favicon
  symlink("../../../../config/stacks/$name/.htaccess", "$path/.htaccess");
  symlink("../../../../config/stacks/$name/favicon.ico", "$path/favicon.ico");
  // symlink the sites directory
  symlink("../../../../../config/stacks/$name/sites/$name", "$path/sites/$name");
  symlink("../../../../../config/stacks/$name/sites/default", "$path/sites/default");
  symlink("../../../../../config/stacks/$name/sites/sites.php", "$path/sites/sites.php");
  // copy over the cron.php file
  copy(
    "$elmsln_dev/" . ELMSLN_STACKS . "/courses/sites/cron.php",
    "$path/sites/cron.php"
  );
  // now work against the domains directory to match the stacks
  // in question if this is an instance based tool then we use
  // a directory that will contain things symlinking off. Otherwise
  // we just
  if (!drush_get_option('stack-instance')) {
    symlink("../core/dslmcode/stacks/$name", "$elmsln_dev/system/domains/$name");
  }
  else {
    // copy the structure of the course stack
    mkdir("$elmsln_dev/system/domains/$name");
    $contents = _drush_elmsln_directory_contents("$elmsln_dev/system/domains/courses");
    foreach ($contents as $content) {
      copy(
        "$elmsln_dev/system/domains/courses/$content",
        "$elmsln_dev/system/domains/$name/$content"
      );
    }
    // repoint the symlinks
    symlink("../../config/stacks/$name/.htaccess", "$elmsln_dev/system/domains/$name/.htaccess");
    symlink("../../config/stacks/$name/favicon.ico", "$elmsln_dev/system/domains/$name/favicon.ico");
  }

  // add in profile if specified
  if (!empty($profile)) {
    $tmp = split('-', $profile);
    symlink("./../../../profiles/$profile", "$path/profiles/" . $tmp[0]);
  }
  drush_log(dt('ELMSLN Stack named @name added!', array('@name' => $name)), 'ok');
  return TRUE;
}

/**
 * Helper to return contents of a directory
 * @param  string $path path to a folder on the file system
 * @return array        array of paths that are valid files/folders
 */
function _drush_elmsln_directory_contents($path) {
  // scan directory for items that we can symlink to
  $d = dir($path);
  $folders = array();
  // while we have items, keep reading
  while (FALSE !== ($entry = $d->read())) {
    // Exclude . and .. and Mac .DS_Store file
    if ($entry == '.' || $entry == '..' || $entry == '.DS_Store') {
      continue;
    }
    $folders[] = $entry;
  }
  $d->close();
  return $folders;
}

/**
 * Helpder function to return the relative path between two items
 * @param  string $dest    destination to link to
 * @param  string $root    where we are linking back to
 * @param  string $dir_sep folder seperator
 * @return string          relative path from destination to root
 */
function _drush_elmsln_relpath($dest, $root = '', $dir_sep = '/') {
  // Relative paths aren't supported by symlink() in Windows right now
  // If we're windows, just return the realpath of $path
  // This is only a limitation of the PHP symlink.
  // I don't want to do an exec to mklink because that breaks in the
  // mysysgit shell, which is possibly where many Drush users will be
  // working on Windows.
  if (preg_match('/^win/i', PHP_OS)) {
    return realpath($dest);
  }

  $root = explode($dir_sep, $root);
  $dest = explode($dir_sep, $dest);
  $path = '.';
  $fix = '';
  $diff = 0;
  for ($i = -1; ++$i < max(($rC = count($root)), ($dC = count($dest)));) {
    if (isset($root[$i]) && isset($dest[$i])) {
      if ($diff) {
        $path .= $dir_sep . '..';
        $fix .= $dir_sep . $dest[$i];
        continue;
      }
      if ($root[$i] != $dest[$i]) {
        $diff = 1;
        $path .= $dir_sep . '..';
        $fix .= $dir_sep . $dest[$i];
        continue;
      }
    }
    elseif (!isset($root[$i]) && isset($dest[$i])) {
      for ($j = $i-1; ++$j < $dC;) {
        $fix .= $dir_sep . $dest[$j];
      }
      break;
    }
    elseif (isset($root[$i]) && !isset($dest[$i])) {
      for ($j = $i-1; ++$j < $rC;) {
        $fix = $dir_sep . '..' . $fix;
      }
      break;
    }
  }
  return $path . $fix;
}
