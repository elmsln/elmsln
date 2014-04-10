<?php

/**
 * @file
 * Process all form values. Uses multiple other include files and helper
 * functions to handle various operations.
 */
global $path_to_at_core;
$path_to_at_core = drupal_get_path('theme', 'adaptivetheme');

// Helper functions for processing the page layout and font families.
include($path_to_at_core . '/inc/forms/at_core.submit.builders.inc');

/**
 * Custom submit function - this mostly builds and saves stylesheets for
 * various features such as the responsive layout and font styles.
 *
 * @param $form
 * @param $form_state
 */
function at_core_settings_submit($form, &$form_state) {
  global $path_to_at_core;

  // Set form_state values into one variable
  $values = $form_state['values'];

  // Get the active theme name, $theme_key will return the admin theme
  $theme_name = $form_state['build_info']['args'][0];

  // Set values for our three possible paths to the generated files
  $public_files = 'public://adaptivetheme/' . $theme_name . '_files';
  $theme_directory = drupal_get_path('theme', $theme_name) . '/generated_files';
  $custom_path = $values['custom_files_path'];

  // Set the path variable to the right path
  if ($values['global_files_path'] === 'public_files') {
    $path = $public_files;
  }
  elseif ($values['global_files_path'] === 'theme_directory') {
    $path = $theme_directory;
  }
  elseif ($values['global_files_path'] === 'custom_path') {
    $path = $custom_path;
  }
  $values['path'] = $path;

  // Set up the files directory for the generated files
  file_prepare_directory($path, FILE_CREATE_DIRECTORY);
  variable_set('theme_' . $theme_name . '_files_directory', $path);

  // Include processing for automagical info builder
  require_once($path_to_at_core . '/inc/forms/at_core.submit.info.inc');
  at_core_submit_info($values, $theme_name, $path);

  // Include processing for page & panels layouts, and responsive styles
  require_once($path_to_at_core . '/inc/forms/at_core.submit.responsive.inc');
  at_core_submit_reponsive($values, $theme_name, $path);

  if ($values['enable_extensions'] === 1) {
    // Include processing for fonts
    if (isset($values['enable_font_settings']) && $values['enable_font_settings'] === 1) {
      require_once($path_to_at_core . '/inc/fonts.inc');
      require_once($path_to_at_core . '/inc/forms/at_core.submit.fonts.inc');
      at_core_submit_fonts($values, $theme_name, $path);
    }
    // Include processing for Custom CSS
    if (isset($values['enable_custom_css']) && $values['enable_custom_css'] === 1) {
      require_once($path_to_at_core . '/inc/forms/at_core.submit.customcss.inc');
      at_core_submit_custom_css($values, $theme_name, $path);
    }
    // Include processing for the Menu Toggle
    if (isset($values['enable_menu_toggle']) && $values['enable_menu_toggle'] === 1) {
      require_once($path_to_at_core . '/inc/forms/at_core.submit.menutoggle.inc');
      at_core_submit_menu_toggle($values, $theme_name, $path);
    }
    // Set variables for device detection environment
    variable_set('at_detection', isset($values['detection']) ? $values['detection'] : FALSE);
    variable_set('at_browscap_detect', isset($values['browscap_detect']) ? $values['browscap_detect'] : FALSE);
    variable_set('at_mobile_detect', isset($values['mobile_detect']) ? $values['mobile_detect'] : FALSE);
  }

  // Color inc save
  if (module_exists('color')) {
    if (isset($values['at-color']) && $values['at-color'] == TRUE) {
      require_once($path_to_at_core . '/inc/forms/at_core.submit.color.inc');
      at_core_submit_color($values, $theme_name, $path);
    }
  }

  // Change query-strings on css/js files to enforce reload for all users.
  _drupal_flush_css_js();

  // Clear the aggregated file caches to update changes
  if (variable_get('preprocess_css', '') == 1) {
    drupal_clear_css_cache();
  }
  if (variable_get('preprocess_js', '') == 1) {
    drupal_clear_js_cache();
  }
}
