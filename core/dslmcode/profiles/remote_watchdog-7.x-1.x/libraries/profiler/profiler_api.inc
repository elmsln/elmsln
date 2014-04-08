<?php

/**
 * @see hook_install_tasks().
 *
 * @param $config
 *   The config array for a Profiler Install Profile.
 */
function profiler_install_tasks($config) {
  return array('profiler_install_profile_complete' => array());
}

/**
 * @see hook_install_tasks_alter().
 *
 * @param $config
 *   The config array for a Profiler Install Profile.
 */
function profiler_install_tasks_alter($config, &$tasks, $install_state) {
  // Replace the modules profile task function with our custom callback.
  $tasks['install_profile_modules']['function'] = 'profiler_install_profile_modules';
}


/**
 * @see install_profile_modules().
 *
 * @param $install_state
 *   An array of information about the current installation state.
 *
 * @return
 *   The batch definition.
 */
function profiler_install_profile_modules(&$install_state) {
  $profile_name = $install_state['parameters']['profile'];
  $config = profiler_v2_load_config($profile_name);

  // Only necessary to override dependencies if there is a base profile.
  if (isset($config['base']) && $config['base']) {
    // This is hacky to say the least, but this way Profiler can implement
    // hook_system_info_alter() to add dependencies. If we don't do this, the
    // dependency sorting will be incorrect and cause errors to display.
    // First step, fill up the module_implements static cache.
    module_implements('system_info_alter');
    $implementations = &drupal_static('module_implements');
    $implementations['system_info_alter']['profiler'] = FALSE;
  }

  return install_profile_modules($install_state);
}

/**
 * Helper to hook_form_install_configure_form_alter().
 */
function profiler_form_install_configure_form_alter($config, &$form, &$form_state) {
  $form['site_information']['site_name']['#default_value'] = $_SERVER['SERVER_NAME'];
}

/**
 * Implements hook_system_info_alter().
 */
function profiler_system_info_alter(&$info, $file, $type) {
  if ($file->name == drupal_get_profile() && isset($info['base'])) {
    $config = profiler_v2_load_config($file->name);
    $config['dependencies'] = profiler_config_reduce($config['dependencies']);
    $info = $config;
  }
}

/**
 * Complete the Profile installation.
 * @param $install_state 
 *   An array of information about the current installation state.
 */
function profiler_install_profile_complete(&$install_state) {
  $profile_name = $install_state['parameters']['profile'];
  $config = profiler_v2_load_config($profile_name);

  // We flush caches at the beginning to ensure that any necessary module
  // tasks, such as Features component rebuilding, is complete before the
  // remaining tasks are run.
  drupal_flush_all_caches();

  // Run any component installations
  profiler_install_components($config);

  // Rebuild key tables/caches
  menu_rebuild();
  if (isset($config['node'])) {
    node_access_rebuild();
  }
  drupal_flush_all_caches();
}

/**
 * Reduce an array of components with mixed keys to its final reduced set of
 * values allowing for later entries to override former entries. Example:
 *
 *   profiler_config_reduce(array('foo', 'bar', 'foo' => 0));
 *
 * Will return the following:
 *
 *   array('bar');
 */
function profiler_config_reduce($data) {
  // We want the string keys at the end of the array, so that they can determine
  // the final setting.
  krsort($data);
  $reduced = array();
  foreach ($data as $key => $value) {
    if (is_int($key)) {
      $reduced[$value] = TRUE;
    }
    elseif (is_string($key)) {
      $reduced[$key] = (bool) $value;
    }
  }
  return array_keys(array_filter($reduced));
}

/**
 * Take an array of arrays and return a single array merging the child arrays.
 * The resulting array can optionally be reduced & made unique.
 *
 * @param array $data
 *   An array of arrays.
 * @param array $excluded_keys
 *   An array of keys to exclude. By default, no keys are excluded.
 * @param boolean $process
 *   Optional. Reduce and make the merged array unique.
 * @return array
 *   A single merged array.
 */
function profiler_config_merge($data, $excluded_keys = array(), $process = TRUE) {
  $merged = array();
  foreach ($data as $key => $value) {
    if (is_array($value) && !in_array($key, $excluded_keys, TRUE)) {
      $merged = array_merge($merged, $process ? profiler_config_reduce($value) : $value);
    }
  }
  return $process ? array_unique($merged) : $merged;
}

/**
 * Returns user 1 for a config, if it exists.
 */
function profiler_config_load_superuser($config) {
  if (isset($config['users'])) {
    foreach ($config['users'] as $account) {
      if ($account['uid'] == 1) {
        return $account;
      }
    }
  }
  return FALSE;
}

/**
 * Install components.
 */
function profiler_install_components($config) {
  if (is_array($config)) {
    $components = profiler_components();
    $identifiers = array();
    foreach ($components as $name => $component) {
      if (!empty($config[$name]) && isset($component['callback'])) {
        if (isset($component['file'])) {
          require_once($component['file']);
        }
        if (function_exists($component['callback'])) {
          $component['callback']($config[$name], $config, $identifiers);
        }
      }
    }
  }
}

/**
 * Invoke module hooks to retrieve component info.
 */
function profiler_components() {
  $components = module_invoke_all('profiler_components');
  drupal_alter('profiler_components', $components);
  uasort($components, 'profiler_components_sort');
  return $components;
}

/**
 * Sort callback for ordering components.
 */
function profiler_components_sort($a, $b) {
  $a = (array)$a + array('weight' => 0);
  $b = (array)$b + array('weight' => 0);
  return $a['weight'] < $b['weight'] ? -1 : 1;
}

/**
 * Implementation of hook_profiler_components() on behalf of system.
 */
function system_profiler_components() {
  return array(
    'theme' => array('callback' => 'profiler_install_theme'),
    'variables' => array('callback' => 'profiler_install_variables'),
  );
}

/**
 * Implementation of hook_profiler_components() on behalf of filter.
 */
function filter_profiler_components() {
  return array(
    'input-formats' => array(
      'callback' => 'profiler_install_input_formats',
      'weight' => 0,
    )
  );
}

/**
 * Implementation of hook_profiler_components() on behalf of node.
 */
function node_profiler_components() {
  return array(
    'nodes' => array(
      'callback' => 'profiler_install_nodes',
      'weight' => 10,
    ),
  );
}

/**
 * Implementation of hook_profiler_components() on behalf of taxonomy.
 */
function taxonomy_profiler_components() {
  return array(
    'terms' => array(
      'callback' => 'profiler_install_terms',
      'weight' => 10,
    ),
  );
}

/**
 * Implementation of hook_profiler_components() on behalf of user.
 */
function user_profiler_components() {
  return array(
    'users' => array(
      'callback' => 'profiler_install_users',
      'weight' => -10,
    ),
  );
}

/**
 * Component install callback for 'theme'.
 */
function profiler_install_theme($theme_name, $config, &$identifiers) {
  theme_enable(array($theme_name));
  variable_set('theme_default', $theme_name);
}

/**
 * Component install callback for 'variables'.
 */
function profiler_install_variables($vars, $config, &$identifiers) {
  foreach($vars as $key => $value) {
    // Handle custom keys.
    if ($key == 'user_admin_role' && $rid = _profiler_role_id_from_name($value)) {
      $value = $rid;
    }
    variable_set($key, $value);
  }
}

/**
 * Component install callback for 'input-formats'.
 */
function profiler_install_input_formats($formats, $config, &$identifiers) {
  foreach ($formats as $format_name => $array) {
    // If the format name is not declared, use the array key.
    if (!isset($array['format'])) {
      $array['format'] = $format_name;
    }
    $format = (object) $array;
    if (filter_format_save($format)) {
      $identifiers['input-formats'][$format_name] = $format;
    }
    if (isset($array['roles'])) {
      $roles = profiler_config_reduce($array['roles']);
      // Enable permissions for these roles.
      $permission = filter_permission_name($format);
      foreach ($roles as $role_name) {
        if ($rid = _profiler_role_id_from_name($role_name)) {
          user_role_grant_permissions($rid, array($permission));
        }
      }
    }
  }
}

/**
 * Component install callback for 'nodes'.
 */
function profiler_install_nodes($nodes, $config, &$identifiers) {
  foreach (array_filter($nodes) as $nid => $properties) {
    if (isset($properties['name'])) {
      $account = user_load(array('name' => $properties['name']));
      if (!$account) {
        drupal_set_message(t('Failed to load Drupal user %user -- node %title not saved.', array('%name' => $properties['name'], '%title' => $properties['title'])), 'error', FALSE);
        continue;
      }
    }
    $default = array(
      'nid' => NULL,
      'title' => '',
      'body' => '',
      'type' => 'page',
      'teaser' => '',
      'log' => '',
      'created' => '',
      'format' => filter_fallback_format(),
      'uid' => !empty($account) ? $account->uid : 0,
    );
    $node = (object) array_merge($default, $properties);
    node_save($node);
  }
}

/**
 * Component install callback for 'terms'.
 */
function profiler_install_terms($terms, $config, &$identifiers) {
  static $vocabs, $vocabs_by_machine_name;
  if (!isset($vocabs)) {
    $vocabs = taxonomy_get_vocabularies();
    foreach ($vocabs as $vid => $vocab) {
      $vocabs_by_machine_name[$vocab->machine_name] = $vid;
    }
  }
  $weight = 0;
  foreach ($terms as $term) {
    // Support the 'vocabulary_machine_name' key for referring to a term's vocabulary
    // by its machine name.
    if (isset($term['vocabulary_machine_name'], $vocabs_by_machine_name[$term['vocabulary_machine_name']])) {
      $term['vid'] = $vocabs_by_machine_name[$term['vocabulary_machine_name']];
    }
    // Sanity checks before creating.
    if (!empty($term['name']) && !empty($term['vid']) && isset($vocabs[$term['vid']])) {
      $term['weight'] = empty($term['weight']) ? $weight++ : $term['weight'];
      //Cast the term as an object, to allow it to be saved properly.
      taxonomy_term_save((object) $term);
    }
  }
}

/**
 * Component install callback for 'users'.
 */
function profiler_install_users($users) {
  foreach (array_filter($users) as $array) {
    $roles = isset($array['roles']) ? $array['roles'] : '';
    // Set the roles.
    $array['roles'] = array();
    $roles = explode(',', $roles);
    foreach ($roles as $name) {
      if ($rid = _profiler_role_id_from_name($name)) {
        $array['roles'][$rid] = $name;
      }
    }

    // Use random password.
    $array['pass'] = empty($array['pass']) ? user_password() : $array['pass'];

    // Load and update the account or create a new one.
    $account = isset($array['uid']) ? user_load($array['uid']) : user_load_by_name($array['name']);
    $account = $account ? $account : new stdClass();
    $account = user_save($account, $array);
  }
}

/**
 * Helper function to select a role id based on role name.
 */
function _profiler_role_id_from_name($role_name) {
  $rids = &drupal_static(__FUNCTION__);

  if (!isset($rids[$role_name])) {
    $query = db_select('role', 'r')
                ->fields('r', array('rid'))
                ->condition('r.name', $role_name);
    $rids[$role_name] = $query->execute()->fetchField();
  }

  return $rids[$role_name];
}
