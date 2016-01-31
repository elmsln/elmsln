<?php

/**
 * Callback to correctly sync remotely set theme values to
 * the active theme of this site
 * @return bool if it was successfully cleared
 */
function elmsln_api_elmsln_api_callback_theme_settings() {
  global $_elmsln;
  // ensure that this sit wants to be synced
  if (isset($_elmsln['args']['values']) && !(variable_get('elmsln_api_sync', 1) === 0)) {
    // get default theme of this site
    $theme = variable_get('theme_default', 'foundation_access');
    // load the settings from there
    $theme_settings = variable_get('theme_' . $theme . '_settings', array());
    $values = $_elmsln['args']['values'];
    // account for sync mode with option to not sync banner
    if (variable_get('elmsln_api_sync', 1) === 2) {
      unset($values['default_logo']);
      unset($values['logo_path']);
    }
    // merge in the settings, remote getting priority
    $theme_settings = array_merge($theme_settings, $values);
    variable_set('theme_' . $theme . '_settings', $theme_settings);
    return array(
      'theme_settings' => TRUE,
      'value' => $theme_settings,
      'message' => "theme settings variable updated successfully",
    );
  }
  return FALSE;
}
