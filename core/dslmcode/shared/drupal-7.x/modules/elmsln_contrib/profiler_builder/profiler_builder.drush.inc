<?php

/**
 * @file
 * Drush integration for Profiler Builder module.
 */

/**
 * Implements hook_drush_command().
 */
function profiler_builder_drush_command() {
  $items['generate-distro'] = array(
    'description' => dt('Build a profile / distribution package based on active site'),
    'arguments' => array(
      'name' => dt('The location to place the profile, this will usually be in the profiles directory though you could use this tool just to make the tar faster.'),
    ),
    'options' => array(
      'untar' => dt('Untar the tar package that profiler builder creates automatically.'),
    ),
    'aliases' => array('distro'),
    'examples' => array(
      'drush generate-distro stuff' => 'Build an installation profile for creating a distribution called stuff.',
      'drush distro things --untar' => 'Build a distribution with installation profile things and untar the resulting directory',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function profiler_builder_drush_help($section) {
  switch ($section) {
    case 'drush:generate-distro':
      return dt('Build the installation profile nessecary to recreate your site');
  }
}

/**
 * Drush command callback for generate-distro.
 */
function drush_profiler_builder_generate_distro($name) {
  module_load_include('inc', 'profiler_builder', 'profiler_builder.admin');
  $build_array = array();
  $profile_name = variable_get('site_name', $name);
  $machine_name = $name;
  $description = variable_get('site_slogan', $name);
  $exclusive = TRUE;
  $profiler = FALSE;
  // allow for definitions of other things to export
  $profiler_includes = _profiler_builder_get_includes();
  foreach ($profiler_includes as $key => $include) {
    $includes[$key] = $include['name'];
  }
  // unset variables, relying on features distro packaging these
  if (isset($includes['variables'])) {
    unset($includes['variables']);
  }
  $build_array['profiler_includes'] = $includes;
  $build_array['create_admin'] = TRUE;
  $build_array['standard_profile'] = FALSE;
  // only list libraries capabilities if libraries module exists
  if (module_exists('libraries')) {
    // get all known libraries
    $libraries = libraries_get_libraries();
    // convert path locations to keys only
    foreach ($libraries as $key => $val) {
      $libraries[$key] = $key;
    }
    $build_array['libraries'] = $libraries;
  }
  $patches = array();
  // find .patch files in install
  $tmp = _profiler_builder_get_patches();
  // convert file array to patch array
  foreach ($tmp as $key => $patch) {
    $patch_project = '';
    $path_ary = explode('/', $key);
    foreach ($path_ary as $path_arg => $val) {
      // look for modules key in path, project name is next
      if (($val == 'modules' || $val == 'themes' || $val == 'libraries') && isset($path_ary[($path_arg+1)]) && $path_ary[($path_arg+1)] != $patch->filename) {
        $patch_project = $path_ary[($path_arg+1)];
      }
    }
    // make sure project was found
    if (empty($patch_project)) {
      // test for possible core patches
      $core_locations = array(
        'includes',
        'misc',
        'modules',
        'scripts',
        'themes',
      );
      // search for core patch in core directories
      foreach ($core_locations as $directory) {
        $patch_found = array();
        $patch_found = file_scan_directory('./' . $directory, '/.*\\' . $patch->filename . '$/');
        // if we found something this is a core patch
        if (!empty($patch_found)) {
          $patch_project = 'drupal';
        }
      }
      // couldn't calculate accurately, set to key unless root
      if (empty($patch_project)) {
        if ($key == './' . $patch->filename) {
          $patch_project = 'drupal';
        }
        else {
          $patch_project = $key;
        }
      }
    }
    $patches[$patch->name] = $patch->filename;
  }
  // no patches detected
  if (count($patches) > 0) {
    $build_array['patches'] = $patches;
  }
  $profiler_includes = $build_array['profiler_includes'];
  // add libraries if libraries API is installed
  if (isset($build_array['libraries'])) {
    $libraries = $build_array['libraries'];
  }
  else {
    $libraries = array();
  }
  // add patches if any exist
  if (isset($build_array['patches'])) {
    $patches = $build_array['patches'];
  }
  else {
    $patches = array();
  }
  // check if we should use standard profile setup routine
  if ($build_array['standard_profile']) {
    $standard_profile_default = _profiler_builder_standard_profile_default();
  }
  else {
    $standard_profile_default = '';
  }
  // check if we should create an admin role
  if ($build_array['create_admin']) {
    $create_admin = _profiler_builder_create_admin();
  }
  else {
    $create_admin = '';
  }
  // files relevant to the build
  $drush_args = _profiler_builder_build_profile($name, $machine_name, $description, $exclusive, $profiler, $profiler_includes, $standard_profile_default, $create_admin, $libraries, $patches);
  $error = FALSE;
  // check for untar option
  if (drush_get_option('untar')) {
    // try to make the directory to place files in
    if (is_dir("profiles/$name") || mkdir("profiles/$name")) {
      // loop through files and add them to their location in the profile
      foreach ($drush_args['source_files'] as $file => $contents) {
        if (!file_put_contents("profiles/$name/$file", $contents)) {
          drush_log(dt("Unable to write file @file", array('@file' => $file)), 'error');
          $error = TRUE;
        }
      }
      $mkdirs = array(
        'libraries',
        'modules',
        'modules/custom',
        'modules/contrib',
        "modules/{$name}_features",
        'themes',
        'themes/custom',
        'themes/contrib',
      );
      // loop through and make directories
      foreach ($mkdirs as $dir) {
        $dir_to_make = "profiles/$name/$dir";
        if (!is_dir($dir_to_make)) {
          if (!mkdir($dir_to_make)) {
            drush_log(dt("Unable to write folder @folder into the profile directory, may already exist", array('@folder' => $dir_to_make)), 'warning');
          }
        }
      }
      // if profiler is in libraries, copy to new location
      if (module_exists('libraries')) {
        $libraries = libraries_get_libraries();
        // copy profiler to correct location if it is set
        if (isset($libraries['profiler'])) {
          _profiler_builder_rcopy($libraries['profiler'], "profiles/$name/libraries/profiler");
        }
      }
    }
    else {
      drush_log(dt("Unable to write folder @folder into the profiles directory", array('@folder' => $name)), 'error');
      $error = TRUE;
    }
  }
  elseif (file_put_contents($drush_args['tar_name'], $drush_args['tar'])) {
    drush_log(dt("Wrote .tar file @file to current directory", array('@file' => $drush_args['tar_name'])), 'ok');
    $error = TRUE;
  }
  else {
    drush_log(dt("Unable to write @file to current directory", array('@file' => $drush_args['tar_name'])), 'error');
    $error = TRUE;
  }
  if (!$error) {
    drush_log(dt("Profile @folder created successfully!", array('@folder' => $name)), 'ok');
  }
}

/**
 * Recursively copy files and directories.
 */
function _profiler_builder_rcopy($source, $destination) {
  if (is_dir($source)) {
    mkdir($destination);
    $files = scandir($source);
    foreach ($files as $file) {
      if ($file != "." && $file != "..") {
        _profiler_builder_rcopy("$source/$file", "$destination/$file");
      }
    }
  }
  elseif (file_exists($source)) {
    copy($source, $destination);
  }
}
