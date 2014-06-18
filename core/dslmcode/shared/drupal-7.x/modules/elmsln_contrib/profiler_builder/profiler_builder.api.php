<?php
/**
 * @file
 * Profiler Builder API examples and documentation.
 */

/**
 * Implements hook_profiler_builder_defined_libraries().
 *
 * drush make format:
 *  - [download][url] is defined as [download_url]
 *  - [download][type] is defined as [download_type]
 *  - [download][file_type] is defined as [download_file_type]
 *  - [download][post_data] is defined as [download_post_data]
 *  - [_name] human readable library name for the drush file
 *  - [_local] boolean to determine local or d.o. make file
 * The assumed state is that it is cleared by d.o. packaging white-list.
 *
 * @return $defined_libs
 *   array of libraries that we are aware of.
 */
function hook_profiler_builder_defined_libraries() {
  $defined_libs = array();
   // oauth hasn't cleared packaging script but will soon
  $defined_libs['oauth']['_name'] = t('OAuth Drupal fork');
  $defined_libs['oauth']['_local'] = TRUE;
  $defined_libs['oauth']['download_url'] = "https://github.com/juampy72/OAuth-PHP/archive/master.zip";
  return $defined_libs;
}

/**
 * Implements hook_profiler_builder_defined_libraries_alter().
 *
 * $defined_libs is an array of defined libraries in format above
 */
function hook_profiler_builder_defined_libraries_alter(&$defined_libs) {
  $defined_libs['bootstrap']['destination'] = "themes/contrib/bootstrap";
}

/**
 * Implements hook_profiler_builder_libraries_list_alter().
 *
 * $libraries is an array of selected libraries for this publishing routine
 * $local is a boolean to indicate if this is for local or d.o. based publishing
 * $name is the machine name of the profile to be created
 */
function hook_profiler_builder_libraries_list_alter(&$libraries, $local, $machine_name) {
  // always use profiler dev if enabled
  if (isset($libraries['profiler'])) {
    $libraries['profiler']['_name'] = t('Profiler');
    $libraries['profiler']['download'] = 'http://ftp.drupal.org/files/projects/profiler-7.x-2.x-dev.tar.gz';
  }
  // if this is a local example build to include this non-d.o. capable library
  // bootstrap can't be hosted on d.o. because of licensing issues
  if (isset($libraries['bootstrap'])) {
    // define it if its a local build file
    if ($local) {
      $libraries['bootstrap']['_name'] = t('Twitter Bootstrap');
      $libraries['bootstrap']['directory_name'] = "bootstrap";
      $libraries['bootstrap']['destination'] = "themes/contrib/bootstrap";
      $libraries['bootstrap']['download_url'] = "http://twitter.github.com/bootstrap/assets/bootstrap.zip";
    }
    else {
      // remove it if its a d.o. build file
      unset($libraries['bootstrap']);
    }
  }
}

/**
 * Implements hook_profiler_builder_modules_list_alter().
 */
function hook_profiler_builder_modules_list_alter(&$modules) {
  // remove the cdn module
  unset($modules['cdn']);
}

/**
 * Implements hook_profiler_builder_modules_list_alter().
 */
function hook_profiler_builder_drush_modules_list_alter(&$project_data, $machine_name) {
  // remove all modules listed as part of the distribution
  unset($project_data[$distro_name]);
}

/**
 * Implements hook_profiler_builder_ignore_alter().
 */
function hook_profiler_builder_ignore_alter(&$ignore) {
  // ignore the cdn settings
  $ignore[] = 'cdn_settings';
}

/**
 * Implements hook_profiler_builder_variables_alter().
 */
function hook_profiler_builder_variables_alter(&$variables) {
  // variable values to change
  $change = array(
    'cdn_status' => 0,
  );
  // loop through and change only set values
  foreach ($change as $var => $val) {
    if (isset($variables[$var])) {
      $variables[$var] = $val;
    }
  }
}

/**
 * Implements hook_profiler_builder_info_include().
 *
 * Format of the info include array is:
 *  - keyname needs to be unique
 *  - name is a human readable name for this component
 *  - callback is a function that will return text to place in the file
 * Items added must be available through the profiler API
 * If they aren't you can still add them but they won't do anything
 * @return $includes
 *   an array of types of items to include in packaging.
 */
function hook_profiler_builder_info_include() {
  $includes = array(
    'keyname' => array(
      'name' => t('Variables'),
      'callback' => '_profiler_builder_export_variables',
    ),
    'modules' => array(
      'name' => t('Dependencies'),
      'callback' => '_profiler_builder_export_dependencies',
    ),
  );
  return $includes;
}

/**
 * Implements hook_profiler_builder_info_include_alter().
 */
function hook_profiler_builder_info_include_alter(&$includes) {
  $includes['modules']['callback'] = 'my_new_callback_to_handle_modules';
}

/**
 * Implements hook_profiler_builder_patch_locations().
 */
function hook_profiler_builder_patch_locations() {
  $locations = array(
    'includes',
    'misc',
    'modules',
    'profiles',
  );
  return $locations;
}

/**
 * Implements hook_profiler_builder_patch_locations_alter().
 */
function hook_profiler_builder_patch_locations_alter(&$locations) {
  foreach ($locations as $key => $location) {
    // don't scan profiles directory for patches
    if ($location == 'profiles') {
      unset($locations[$key]);
    }
  }
}

/**
 * Implements hook_profiler_builder_install_file_alter().
 *
 * modify the .install file after profiler builder has assembled it.
 *
 * @param  [string] $output       text of the php file to be created
 * @param  [string] $machine_name Machine name of the profile being requested.
 * @return [null]                 No returned data is expected.
 */
function hook_profiler_builder_install_file_alter($output, $machine_name) {
  // see the profiler_builder_extras module for example usage.
}

/**
 * Implements hook_profiler_builder_profile_prebuild().
 *
 * Allow developers to act just prior to a profile being created.
 *
 * @param  [string] $name                     name of the profile
 * @param  [string] $machine_name             machine name to build
 * @param  [string] $description              description of what's written
 * @param  [bool] $exclusive                  if the profile is exclusive
 * @param  [bool] $profiler                   if we should use profiler library
 * @param  [array] $profiler_includes         whats being included modules, variables, etc
 * @param  [bool] $standard_profile_default   if to use standard profile defaults
 * @param  [bool] $create_admin               if to auto create admin role
 * @param  [array] $libraries                 what libraries to include
 * @param  [array] $patches                   what patches to apply
 * @return [null]                           no return is expected
 */
function hook_profiler_builder_profile_prebuild($name, $machine_name, $description, $exclusive, $profiler, $profiler_includes, $standard_profile_default, $create_admin, $libraries, $patches) {
  // you can act on a profile about to be built. see extras for an example
}

/**
 * Implements hook_profiler_builder_profile_postbuild().
 *
 * Allow developers to act just prior to a profile being delivered to user.
 *
 * @param  [string] $name                     name of the profile
 * @param  [string] $machine_name             machine name to build
 * @param  [string] $description              description of what's written
 * @param  [bool] $exclusive                  if the profile is exclusive
 * @param  [bool] $profiler                   if we should use profiler library
 * @param  [array] $profiler_includes         whats being included modules, variables, etc
 * @param  [bool] $standard_profile_default   if to use standard profile defaults
 * @param  [bool] $create_admin               if to auto create admin role
 * @param  [array] $libraries                 what libraries to include
 * @param  [array] $patches                   what patches to apply
 * @return [null]                           no return is expected
 */
function hook_profiler_builder_profile_postbuild($name, $machine_name, $description, $exclusive, $profiler, $profiler_includes, $standard_profile_default, $create_admin, $libraries, $patches) {
  // you can act on a profile that is about to be delivered to the user / drush
}
