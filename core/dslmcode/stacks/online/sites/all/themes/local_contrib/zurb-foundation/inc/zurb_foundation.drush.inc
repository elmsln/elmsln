<?php
/**
 * @file
 * Contains functions only needed for drush integration.
 */

/**
 * Implementation of hook_drush_command().
 */
function zurb_foundation_drush_command() {
  $items = array();

  $items['foundation-sub-theme'] = array(
    'description' => 'Create a ZURB foundation sub-theme',
    'aliases' => array('fst'),
    'arguments' => array(
      'name'         => 'Your sub-theme name.',
      'machine_name' => 'A machine-readable name for your theme, optional only  [a-z, 0-9] ',
    ),
    'options' => array(
      'description'  => 'Your sub-theme description.',
      'machine-name' => '[a-z, 0-9] A machine-readable name for your theme.',
      //'name'         => 'A name for your theme.',
      //'without-rtl'  => 'Remove all RTL stylesheets.',
    ),
    'examples' => array(
      'drush fst "custom theme name"' => 'Create a sub-theme with the default options.',
      'drush fst "foo bar" "foo_bar"  --description="My supersweet awesome theme"' => 'Create a sub-theme with additional options.',
    ),
  );

  return $items;
}

/**
 * Create a Zurb foundation sub-theme.
 */
function drush_zurb_foundation_foundation_sub_theme($name = NULL, $machine_name = NULL, $description = NULL) {
  if (empty($name)) {
    drush_set_error(dt("Please provide a name for the sub-theme.\nUSAGE:\tdrush fst [name] [machine_name !OPTIONAL] [description !OPTIONAL]\n"));
    return;
  }
  //Filter everything but letters, numbers, underscores, and hyphens
  $machine_name = !empty($machine_name) ? preg_replace('/[^a-z0-9_-]+/', '', strtolower($machine_name)) : preg_replace('/[^a-z0-9_-]+/', '', strtolower($name));
  // Eliminate hyphens
  $machine_name = str_replace('-', '_', $machine_name);

  // Find theme paths.
  $zurb_path = drush_locate_root() . '/' . drupal_get_path('theme', 'zurb_foundation');
  $subtheme_path = dirname($zurb_path) . '/' . $machine_name;

  // Make a fresh copy of the subtheme.
  $s = drush_copy_dir("$zurb_path/STARTER/", $subtheme_path);
  if (empty($s)) {
    return;
  }

  // Copy JS files from base theme to sub-theme. We copy them now instead of
  // including them by default to keep the base theme small and also to avoid
  // having to update the Foundation JS in two places every time a new version
  // is released.
  drush_copy_dir("{$zurb_path}/js/", "{$subtheme_path}/js/", FILE_EXISTS_MERGE);

  // Rename files and fill in the theme machine name
  drush_op('rename', "$subtheme_path/STARTER.info.txt", "$subtheme_path/$machine_name.info");
  drush_op('rename', "$subtheme_path/css/custom.css", "$subtheme_path/css/$machine_name.css");
  drush_op('rename', "$subtheme_path/scss/custom.scss", "$subtheme_path/scss/$machine_name.scss");
  drush_op('rename', "$subtheme_path/js/scripts.js", "$subtheme_path/js/$machine_name.js");
  // Update the .info file
  drush_op('zurb_foundation_file_str_replace', "$subtheme_path/$machine_name.info", 'ZURB Foundation Sub-theme Starter', "$name");
  // Change the name of the theme
  if (!empty($description))
    drush_op('zurb_foundation_file_str_replace', "$subtheme_path/$machine_name.info", 'Custom sub-theme, inherits from the Foundation base theme read <a href="http://foundation.zurb.com/docs/index.php">framework documentation</a>', "$description");
  // Create the template.php file with replaced theme name
  drush_op('zurb_foundation_file_str_replace', "$subtheme_path/template.php", 'STARTER', "$machine_name");
  // Rename the .info reference to the custom css file
  drush_op('zurb_foundation_file_str_replace', "$subtheme_path/$machine_name.info", 'custom.css', "$machine_name.css");
  // Rename the .info reference to the custom js file
  drush_op('zurb_foundation_file_str_replace', "$subtheme_path/$machine_name.info", 'scripts.js', "$machine_name.js");
  // Rename the Drupal behavior name in the custom js file.
  drush_op('zurb_foundation_file_str_replace', "$subtheme_path/js/$machine_name.js", 'STARTER', "$machine_name");
  // Rename functions in template.php
  drush_op('zurb_foundation_file_str_replace', "$subtheme_path/template.php", 'STARTER', "$machine_name");
  // Rename functions in theme-settings.php
  drush_op('zurb_foundation_file_str_replace', "$subtheme_path/theme-settings.php", 'STARTER', "$machine_name");

  // Notify user of the newly created theme.
  drush_print(dt("\n!name sub-theme was created in !path. \n",
    array(
      '!name' => $name,
      '!path' => $subtheme_path,
    )
  ));
  drush_pm_enable_validate($machine_name);
  drush_pm_enable($machine_name);
}

/**
 * Internal helper: Replace strings in a file.
 */
function zurb_foundation_file_str_replace($file_path, $find, $replace) {
  $file_contents = file_get_contents($file_path);
  $file_contents = str_replace($find, $replace, $file_contents);
  file_put_contents($file_path, $file_contents);
}

/**
 * Implements hook_drush_help().
 */
function zurb_foundation_drush_help($section) {
  switch ($section) {
    case 'drush:foundation-sub-theme':
      return dt("Create a ZURB foundation custom sub-theme.");
  }
}
