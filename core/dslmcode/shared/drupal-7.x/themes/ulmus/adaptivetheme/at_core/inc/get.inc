<?php

/**
 * @file
 * Provides frequently used functions that get theme info, settings and
 * other data.
 */

/**
 * Retrieve a setting for the current theme or for a given theme.
 *
 * AT's stripped down optimized version of theme_get_setting().
 * Why? Because it wayfasterbetter, emphasis on the faster which is really the
 * only valid reason to do something as stupid as this, and it is faster,
 * considerably faster. Doing this wiped 100ms off page generation time.
 *
 * @param $setting_name
 * @param null $theme
 * @see http://api.drupal.org/api/drupal/includes!theme.inc/function/theme_get_setting/7
 */
function at_get_setting($setting_name, $theme = NULL) {
  $cache = &drupal_static(__FUNCTION__, array());

  // If no key is given, use the current theme if we can determine it.
  if (!isset($theme)) {
    $theme = !empty($GLOBALS['theme_key']) ? $GLOBALS['theme_key'] : '';
  }

  if (empty($cache[$theme])) {

    // Get the values for the theme-specific settings from the .info files
    if ($theme) {
      $themes = list_themes();
      $theme_object = $themes[$theme];

      // Create a list which includes the current theme and all its base themes.
      if (isset($theme_object->base_themes)) {
        $theme_keys = array_keys($theme_object->base_themes);
        $theme_keys[] = $theme;
      }
      else {
        $theme_keys = array($theme);
      }

      foreach ($theme_keys as $theme_key) {
        if (!empty($themes[$theme_key]->info['settings'])) {
          $cache[$theme] = $themes[$theme_key]->info['settings'];
        }
      }

      // Get the saved theme-specific settings from the database.
      $cache[$theme] = array_merge($cache[$theme], variable_get('theme_' . $theme . '_settings', array()));
    }
  }

  return isset($cache[$theme][$setting_name]) ? $cache[$theme][$setting_name] : NULL;
}

/**
 * Return the info file array for a particular theme, usually the active theme.
 * Simple wrapper function for list_themes().
 *
 * @param $theme_name
 */
function at_get_info($theme_name) {
  $info = &drupal_static(__FUNCTION__, array());
  if (empty($info)) {
    $lt = list_themes();
    foreach ($lt as $key => $value) {
      if ($theme_name == $key) {
        $info = $lt[$theme_name]->info;
      }
    }
  }

  return $info;
}

/**
 * Returns an array keyed by theme name.
 *
 * Return the all the info file data for a particular theme including base
 * themes. Parts of this function are shamelessly ripped from Drupal core's
 * _drupal_theme_initialize().
 *
 * @param $theme_name, usually the active theme.
 */
function at_get_info_trail($theme_name) {
  $info_trail = &drupal_static(__FUNCTION__, array());
  if (empty($info_trail)) {
    $lt = list_themes();

    // First check for base themes and get info
    $base_theme = array();
    $ancestor = $theme_name;
    while ($ancestor && isset($lt[$ancestor]->base_theme)) {
      $ancestor = $lt[$ancestor]->base_theme;
      $base_theme[] = $lt[$ancestor];
    }
    foreach ($base_theme as $base) {
      $info_trail[$base->name]['info'] = $base->info;
    }

    // Now the active theme
    $info_trail[$theme_name]['info'] = $lt[$theme_name]->info;
  }

  return $info_trail;
}

/**
 * Return lists of CSS files to unset.
 *
 * This returns a very small amount of data (< 10kb), but is very expensive
 * to get which is why its cached in the database. Without caching the theme
 * settings page takes at least 8 seconds to load if the Unset CSS extension
 * is enabled, and thats no fun.
 *
 * @param $theme_name, usually the active theme.
 */
function at_get_css_files($theme_name) {
  $styles = &drupal_static(__FUNCTION__, array());
  if (empty($styles)) {
    if ($cache = cache_get('at_get_css_files')) {
      $styles = $cache->data;
    }
    else {

      // Contrib module
      $module_data = system_rebuild_module_data();
      foreach ($module_data as $module => $data) {
        if ($data->status && !empty($data->info['stylesheets'])) {
          foreach ($data->info['stylesheets'] as $media => $content) {
            foreach ($content as $file) {
              $styles[$file] = array(
                'type' => 'contrib',
                'source' => $module,
              );
            }
          }
        }
      }

      // Libraries
      if (module_exists('libraries')) {
        $libraries = libraries_get_libraries();
        $extension = 'css';
        foreach ($libraries as $lib) {
          $files = file_scan_directory($lib, '/\.' . $extension . '$/', array('recurse' => TRUE));
          $libraries[$lib] = $files;
        }
        foreach ($libraries as $lib_key => $library) {
          if (is_array($library) && !empty($library)) {
            foreach ($library as $lib_file) {
              $styles[$lib_file->uri] = array(
                'type' => 'library',
                'source' => $lib_file->uri,
              );
            }
          }
        }
      }

      // Theme info defined files
      $info_data = at_get_info_trail($theme_name);
      foreach ($info_data as $provider => $theme_info) {
        foreach ($theme_info as $this_info => $info) {
          if ($this_info == 'info') {
            // AT Core defined
            if (isset($info['unset_core'])) {
              foreach ($info['unset_core'] as $module_path => $description) {
                $styles[$module_path] = array(
                  'type' => 'unset_core',
                  'source' => $description,
                );
              }
            }
            // Active theme defined explicit excludes
            if (isset($info['unset_css'])) {
              foreach ($info['unset_css'] as $module_path => $description) {
                $styles[$module_path] = array(
                  'type' => 'user_defined',
                  'source' => $description,
                );
              }
            }
            // Active theme and ancestors, never show in admin
            foreach ($info['stylesheets'] as $media => $stylesheets) {
              foreach ($stylesheets as $file => $path) {
                $styles[$path] = array(
                  'type' => 'theme',
                  'source' => $provider,
                );
              }
            }
          }
        }
      }

      cache_set('at_get_css_files', $styles, 'cache');
    }
  }

  return $styles;
}

/**
 * Return a device context.
 * Wrapper for mobile_detect_get_object() and
 * browscap_get_browser().
 */
function at_get_browser() {
  $browser = &drupal_static(__FUNCTION__, array());
  if (empty($browser)) {
    $browser['is_mobile'] = NULL;
    $browser['is_tablet'] = NULL;

    if (function_exists('mobile_detect_get_object')) {
      $detect = mobile_detect_get_object();
      if ($detect) {
        $browser['is_mobile'] = $detect->isMobile();
        $browser['is_tablet'] = $detect->isTablet();
      }
    }
    else if (function_exists('browscap_get_browser')) {
      $browscap = browscap_get_browser();
      if ($browscap) {
        if (filter_var($browscap['ismobiledevice'], FILTER_VALIDATE_BOOLEAN) == TRUE) {
          $browser['is_mobile'] = TRUE;
        }
      }
    }
  }

  return $browser;
}
