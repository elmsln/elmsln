<?php

/**
 * Init install profile functions on behalf of the caller.
 */
function profiler_v2($profile_name) {
  $code =
<<<EOT
if (!function_exists('{$profile_name}_install_tasks')) {
  function {$profile_name}_install_tasks() {
    include_once('profiler_api.inc');
    return profiler_install_tasks(profiler_v2_load_config('{$profile_name}'));
  }
}

if (!function_exists('{$profile_name}_install_tasks_alter')) {
  function {$profile_name}_install_tasks_alter(&\$tasks, \$install_state) {
    include_once('profiler_api.inc');
    return profiler_install_tasks_alter(profiler_v2_load_config('{$profile_name}'), \$tasks, \$install_state);
  }
}

if (!function_exists('{$profile_name}_form_install_configure_form_alter')) {
  function {$profile_name}_form_install_configure_form_alter(&\$form, \$form_state) {
    include_once('profiler_api.inc');
    return profiler_form_install_configure_form_alter(profiler_v2_load_config('{$profile_name}'), \$form, \$form_state);
  }
}
EOT;
  eval($code);
}

/**
 * Load the config for a particular Install profile.
 *
 * @param $profile_name
 *   The machine name of the Install profile.
 * @return
 *   The Install profiles info file configuration, as an array.
 */
function profiler_v2_load_config($profile_name, $parsed = TRUE) {
  $config = &drupal_static(__FUNCTION__);

  if (!isset($config[$profile_name])) {
    $config[$profile_name] = _profiler_load_config($profile_name);
  }

  return $config[$profile_name];
}

/**
 * Helper to profiler_v2_load_config().
 *
 * @param $profile_name
 *   The machine name of the Install profile.
 * @param $parsed
 *   Whether to return the config of the install profile as a string or as a
 *   parsed array. Used primarily as an internal flag for managing inheritance.
 */
function _profiler_load_config($profile_name, $parsed = TRUE) {
  $file = "./profiles/{$profile_name}/{$profile_name}.info";
  $data = is_file($file) ? file_get_contents($file) : '';
  if ($data && $info = drupal_parse_info_format($data)) {
    if (!empty($info['base']) && is_string($info['base'])) {
      $data = _profiler_load_config($info['base'], FALSE) . "\n" . $data;
    }
  }
  return $parsed ? drupal_parse_info_format($data) : $data;
}
