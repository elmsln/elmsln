<?php

/**
 * @file
 * Form and utility functions for exporting theme settings.
 */

/**
 * Exports theme settings.
 */
function magic_export_settings($form, &$form_state, $theme) {
  $form_state['theme'] = $theme;
  $path = drupal_get_path('theme', $theme);
  $info = drupal_parse_info_file("$path/$theme.info");

  drupal_set_title(t('Export theme settings for @theme', array('@theme' => $info['name'])));

  $info['settings'] = !empty($info['settings']) ? $info['settings'] : array();
  $info['settings'] = variable_get('theme_' . $theme . '_settings', $info['settings']);

  $form['info'] = array(
    '#type' => 'textarea',
    '#title' => t("Export for the theme's .info file", array('@theme' => $theme)),
    '#description' => t("Make any changes you want and submit the form to overwrite the theme's .info file. Note: this will not overwrite settings set within the database, but will only allow documentation within code of settings."),
    '#rows' => 20,
    '#default_value' => _magic_build_info_file($info),
  );

  $form['settings'] = array(
    '#type' => 'textarea',
    '#title' => t('Export for settings.php'),
    '#description' => t('For a permanent settings override, manually copy and paste this into your settings.php file. If you do this, you cannot change the settings with the UI any longer. You may choose to only write some of the settings here, and not include everything in the settings.php.'),
    '#default_value' => _magic_build_settings_php_export($info, $theme),
  );

  $form['actions']['#type'] = 'actions';
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t("Write to the theme's .info file", array('@theme' => $theme)),
  );

  return $form;
}

/**
 * Submit handler for the theme settings export form.
 */
function magic_export_settings_submit($form, &$form_state) {
  $info = $form_state['values']['info'];
  $theme = $form['theme']['#value'];
  $path = drupal_get_path('theme', $theme);

  // Only mark that the settings have updated if the file saved.
  if (!file_unmanaged_save_data($info, "$path/$theme.info", FILE_EXISTS_REPLACE)) {
    drupal_set_message(t("The theme's .info file could not be saved, an error has occurred."), 'error');
    return;
  }

  // Since we exported the file, we want to delete the settings variable. This
  // will get remade whenever we want to edit the settings in the future, but
  // can always be re-removed.
  variable_del("theme_{$theme}_settings");

  // Rebuild the system .info file information.
  system_rebuild_theme_data();

  drupal_set_message(t("The theme's .info file has been updated."));

  $form_state['redirect'] = "admin/appearance/settings/$theme";
}

/**
 * Helper function to build the contents of the .info file.
 *
 * This function will take the current theme information, and create the export
 * based upon the current info file and settings saved within the database.
 *
 * @param array $array
 *   An array of all the current theme settings to be parsed.
 * @param string $prefix
 *   (Optional)
 *
 * @return string
 *   The full, prettified .info file.
 */
function _magic_build_info_file($array, $prefix = '') {
  $regions = array(
    'stylesheets' => 'Stylesheets',
    'regions' => 'Regions',
    'settings' => 'Settings',
    'scripts' => 'Scripts',
    'modernizr' => 'Modernizr',
  );

  $info = '';
  foreach ($array as $key => $value) {
    if (isset($regions[$key])) {
      $info .= "\n";
      $info .= "; ========================================\n";
      $info .= "; $regions[$key]\n";
      $info .= "; ========================================\n";
      $info .= "\n";
    }

    if (is_array($value)) {
      $info .= _magic_build_info_file($value, (empty($prefix) ? $key : "{$prefix}[{$key}]"));
    }
    else {
      $info .= $prefix ? ("{$prefix}[$key]") : $key;
      $info .= " = " . str_replace("'", "\'", $value) . "\n";
    }
  }

  return $info;
}

/**
 * A helper function to print the theme settings withing settings.php.
 *
 * @param array $array
 *   An array of the current settings saved.
 * @param string $theme
 *   The theme key we are building the export for.
 *
 * @return string
 *   The theme's settings array prepared for the settings.php file.
 */
function _magic_build_settings_php_export($array, $theme) {
  $export = '';

  foreach ($array['settings'] as $name => $value) {
    $export .= "\$conf['magic']['$theme']['$name'] = " . var_export($value, TRUE) . ";\n";
  }

  return $export;
}
