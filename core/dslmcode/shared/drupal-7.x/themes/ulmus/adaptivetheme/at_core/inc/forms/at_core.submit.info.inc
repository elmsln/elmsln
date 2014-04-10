<?php

/**
 * @file
 * Automagical Info file builder
 *
 * This is the theme info backed up to a file. Its formatted and holds all
 * current values - useful for migration or simply capturing the current
 * theme settings as defaults.
 */
function at_core_submit_info($values, $theme_name, $path) {
  $theme_settings = $values;
  if ($theme_settings) {
    $dynamic_settings_info = array();
    $static_settings_info = array();
    $lt = list_themes();
    foreach ($lt as $key => $value) {
      if ($theme_name == $key) {
        $this_themes_info = $lt[$theme_name]->info;
        foreach ($this_themes_info as $k => $v) {
          // Basic info - name, desc, base theme, release, core, engine and screenshot
          if ($k == 'name') {
            $static_settings_info[] = 'name = ' . $v;
          }
          if ($k == 'description') {
            $v = $v ? $v : $theme_name . ' is rocking the hardest!';
            $static_settings_info[] = 'description = ' . $v;
          }
          if ($k == 'base theme') {
            $static_settings_info[] = 'base theme = ' . $v;
          }
          if ($k == 'release') {
            $static_settings_info[] = 'release = ' . $v;
          }
          if ($k == 'core') {
            $static_settings_info[] = 'core = 7.x';
          }
          if ($k == 'engine') {
            $static_settings_info[] = 'engine = phptemplate';
          }
          if ($k == 'screenshot') {
            $static_settings_info[] = 'screenshot = screenshot.png';
          }
          // Stylesheets
          if ($k == 'stylesheets' && !empty($k)) {
            foreach ($v as $media_target => $stylesheet_file) {
              foreach ($stylesheet_file as $stylesheet_file_name => $stylesheet_file_path) {
                $static_settings_info[] = "stylesheets[$media_target][] = $stylesheet_file_name";
              }
            }
          }
          // IE Stylesheets
          if ($k == 'ie_stylesheets' && !empty($k)) {
            foreach ($v as $media_target => $condition) {
              foreach ($condition as $conditional_comment => $condition_file) {
                foreach ($condition_file as $conditional_file_path) {
                  $static_settings_info[] = "ie_stylesheets[$media_target][$conditional_comment][] = $conditional_file_path";
                }
              }
            }
          }
          // Scripts
          if ($k == 'scripts' && !empty($k)) {
            foreach ($v as $script => $file) {
              $static_settings_info[] = "scripts[] = $script";
            }
          }
          // IE Scripts
          if ($k == 'ie_scripts' && !empty($k)) {
            foreach ($v as $condition => $condition_file) {
              foreach ($condition_file as $conditional_file_path) {
                $static_settings_info[] = "ie_scripts[$condition][] = $conditional_file_path";
              }
            }
          }
          // Regions
          if ($k == 'regions') {
            foreach ($v as $name => $label) {
              $static_settings_info[] = "regions[$name] = $label";
            }
          }
          // Features
          if ($k == 'features') {
            foreach ($v as $feature_key => $feature) {
              $static_settings_info[] = "features[] = $feature";
            }
          }
        }
      }
    }
    if (!empty($static_settings_info)) {
      $static_settings = implode("\n", $static_settings_info);
    }
    // Might need to check this and add some more exclusions
    $exclusions = array(
      'var',
      'default_logo',
      'logo_path',
      'logo_upload',
      'default_favicon',
      'favicon_path',
      'favicon_upload',
      'submit',
      'form_build_id',
      'form_token',
      'form_id',
      'check',
      'output',
      'op',
      'scheme',
      'palette',
      'theme',
      'info',
      'at-layout__active_tab',
      'at-settings__active_tab',
      'at__active_tab',
      'header_upload' // noggin setting
    );
    foreach ($theme_settings as $setting_name => $setting_value) {
      if ($setting_name == 'global_gutter_width') {
        if (empty($setting_value)) {
          $exclusions[] = 'global_gutter_width';
        }
      }
      if (isset($setting_value) && $setting_value !== '<none>' && !in_array($setting_name, $exclusions)) {
        if (empty($setting_value) && !is_numeric($setting_value)) {
          $setting_value = "''";
        }
        $dynamic_settings_info[] = "settings[$setting_name] = $setting_value";
      }
    }
    if (!empty($dynamic_settings_info)) {
      $dynamic_settings_info = $dynamic_settings_info ? $dynamic_settings_info : "''";
      $dynamic_settings = implode("\n", $dynamic_settings_info);
    }
    if (!empty($static_settings_info) && !empty($dynamic_settings_info)) {
      $combined_values = $static_settings . "\n" . $dynamic_settings; // ideally run a sanity check but all of them convert entities
      $filepath = $path . '/' . $theme_name . '_settings.info.txt';
      file_unmanaged_save_data($combined_values, $filepath, FILE_EXISTS_REPLACE);
    }
  }
}
