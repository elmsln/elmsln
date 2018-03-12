<?php

/**
 * Implements hook_features_export_options().
 */
function wysiwyg_features_export_options() {
  $profiles = array();

  // Get human-readable name from filter module.
  $formats = filter_formats();

  foreach (array_keys(wysiwyg_profile_load_all()) as $format) {
    // Text format may vanish without deleting the wysiwyg profile.
    if (isset($formats[$format])) {
      $profiles[$format] = $formats[$format]->name;
    }
  }
  return $profiles;
}

/**
 * Implements hook_features_export().
 */
function wysiwyg_features_export($data, &$export, $module_name = '') {
  $pipe = array();

  // The wysiwyg_default_formats() hook integration is provided by the
  // features module so we need to add it as a dependency.
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['wysiwyg'] = 'wysiwyg';

  foreach ($data as $name) {
    if ($profile = wysiwyg_get_profile($name)) {
      // Add profile to exports.
      $export['features']['wysiwyg'][$profile->format] = $profile->format;

      // Chain filter format for export.
      $pipe['filter'][] = $profile->format;
    }
  }

  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function wysiwyg_features_export_render($module, $data, $export = NULL) {
  $code = array();
  $code[] = '  $profiles = array();';
  $code[] = '';

  foreach ($data as $name) {
    if ($profile = wysiwyg_get_profile($name)) {
      $profile = (array) $profile;
      $profile_export = features_var_export($profile, '  ');
      $profile_identifier = features_var_export($profile['format']);
      $code[] = "  // Exported profile: {$profile['format']}.";
      $code[] = "  \$profiles[{$profile_identifier}] = {$profile_export};";
      $code[] = "";
    }
  }

  $code[] = '  return $profiles;';
  $code = implode("\n", $code);
  return array('wysiwyg_default_profiles' => $code);
}

/**
 * Implements hook_features_revert().
 */
function wysiwyg_features_revert($module) {
  return wysiwyg_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function wysiwyg_features_rebuild($module) {
  if ($defaults = features_get_default('wysiwyg', $module)) {
    foreach ($defaults as $profile) {
      $profile = is_object($profile) ? (array) $profile : $profile;
      if (empty($profile['settings']['_profile_preferences'])) {
        if (!empty($profile['preferences'])) {
          $settings = &$profile['preferences'];
        }
        else {
          // Importing an older profile, move state to its own section.
          $settings = &$profile['settings'];
        }

        $preferences = array(
          'add_to_summaries' => (!empty($settings['add_to_summaries']) ? $settings['add_to_summaries'] : FALSE),
          'default' => $settings['default'],
          'show_toggle' => $settings['show_toggle'],
          'user_choose' => $settings['user_choose'],
          'version' => (!empty($settings['version']) ? $settings['version'] : NULL),
        );
        unset($settings['add_to_summaries'],
          $settings['default'],
          $settings['show_toggle'],
          $settings['user_choose'],
          $settings['version'],
          $profile['preferences']
        );

        if (!empty($settings['library'])) {
          $preferences['library'] = $settings['library'];
          unset($settings['library']);
        }

        $editor = wysiwyg_get_editor($profile['editor']);
        if (empty($preferences['version']) && !empty($editor['installed'])) {
          $preferences['version'] = $editor['installed version'];
        }

        $profile['settings']['_profile_preferences'] = $preferences;
      }

      db_merge('wysiwyg')
        ->key(array('format' => $profile['format']))
        ->fields(array(
          'editor' => $profile['editor'],
          'settings' => serialize($profile['settings']),
        ))
        ->execute();
      // Clear the editing caches.
      if (module_exists('ctools')) {
        ctools_include('object-cache');
        ctools_object_cache_clear_all('wysiwyg_profile', 'format' . $profile['format']);
      }
      cache_clear_all('wysiwyg_profile:format' . $profile['format'], 'cache');
    }
    wysiwyg_profile_cache_clear();
  }
}
