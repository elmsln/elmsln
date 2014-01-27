<?php
/**
 * @file
 * Provides module conversion form.
 *
 * Copyright 2008-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

module_load_include('inc', 'coder_upgrade', 'conversions/list');

/**
 * Form builder for the module conversion form.
 *
 * The tab contents are assembled in helper functions which allows other modules
 * to "customize" this form directly without resorting to hook_form_alter.
 */
function coder_upgrade_conversions_form($form, &$form_state) {
  // Confirm the necessary module and library are installed.
  $checks_passed = coder_upgrade_library_checks();

  // Set default values.
  list($upgrades, $extensions, $directories, $modules) = coder_upgrade_conversions_form_defaults($form_state);

  // Build the form.
  $form['tabs'] = array(
    '#type' => 'vertical_tabs',
    '#default_tab' => 'edit-directories',
  );
  $form['tabs']['upgrades'] = coder_upgrade_upgrades_build($upgrades);
  $form['tabs']['extensions'] = coder_upgrade_extensions_build($extensions);
  $form['tabs']['directories'] = coder_upgrade_directories_build($directories);
  $form['tabs']['modules'] = coder_upgrade_modules_build($modules);

  $form['convert'] = array(
    '#type' => 'submit',
    '#value' => t('Convert files'),
    '#disabled' => !gplib_version_check(),
  );

  return $form;
}

/**
 * Returns form content for upgrades tab.
 *
 * @param array $upgrades
 *   User selections or default values.
 *
 * @return array
 *   Form item.
 */
function coder_upgrade_upgrades_build(&$upgrades) {
  // Create the list of upgrade options from the coder upgrade plug-ins.
  // Maintain a secondary list based on title only, to make sorting possible.
  $upgrades_all = _coder_upgrade_upgrades();
  foreach ($upgrades_all as $name => $upgrade) {
    $upgrade_options[$name] = isset($upgrade['link']) ? l($upgrade['title'], $upgrade['link']) : $upgrade['title'];
    if (isset($upgrade['description'])) {
      $upgrade_options[$name] .= ' (' . $upgrade['description'] . ')';
    }
    $upgrades_sort[$name] = $upgrade['title'];
  }

  // Sort the upgrades by title.
  asort($upgrades_sort);
  foreach ($upgrades_sort as $name => $upgrade) {
    $upgrades_sort[$name] = $upgrade_options[$name];
  }

  // Build the upgrade list.
  $header = array(
    'category' => array('data' => t('Category'), 'field' => 'category'),
//    'description' => array('data' => t('Description'), 'field' => 'description'),
  );
  $i = 0;
  $rows = array();
  foreach ($upgrades_sort as $name => $upgrade) {
    $row = array();
    $row['category'] = $upgrades_sort[$name];
    $row['description'] = 'Missing';
    $row['#weight'] = ++$i;

    $rows[$name] = $row;
  }
  $upgrade_fs = array(
    '#type' => 'fieldset',
    '#title' => t('Upgrades'),
    '#description' => t('Apply the selected conversion routines ...'),
    '#tree' => TRUE,
  );
  $upgrade_fs['list'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $rows,
    '#default_value' => isset($upgrades) ? $upgrades : array(),
    '#empty' => t('No routines available'),
  );

  return $upgrade_fs;
}

/**
 * Returns form content for file extensions tab.
 *
 * @param array $extensions
 *   User selections or default values.
 *
 * @return array
 *   Form item.
 */
function coder_upgrade_extensions_build(&$extensions) {
  // Build the file extension list.
  $types = array(
    'inc' => 'PHP code files',
    'info' => 'Info files used with module installation',
    'install' => 'PHP code files used with module installation, update and uninstallation',
    'module' => 'PHP code files',
    'php' => 'PHP code files',
    'profile' => 'PHP code files used with site installation',
    'test' => 'SimpleTest files',
    'theme' => 'PHP code files used with theming',
  );
  $header = array(
    'extension' => array('data' => t('Extension'), 'field' => 'extension'),
    'description' => array('data' => t('Description'), 'field' => 'description'),
  );
  $i = 0;
  $rows = array();
  foreach ($types as $key => $description) {
    $row = array();
    $row['extension'] = $key;
    $row['description'] = $description;
    $row['#weight'] = ++$i;

    $rows[$key] = $row;
  }
  $extension_fs = array(
    '#type' => 'fieldset',
    '#title' => t('Extensions'),
    '#description' => t('... to files with the selected file extensions ...'),
    '#tree' => TRUE,
  );
  $extension_fs['list'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $rows,
    '#default_value' => isset($extensions) ? $extensions : array(),
    '#empty' => t('No extensions available'),
  );

  return $extension_fs;
}

/**
 * Returns form content for directories tab.
 *
 * @param array $directories
 *   User selections or default values.
 *
 * @return array
 *   Form item.
 */
function coder_upgrade_directories_build(&$directories) {
  // Build the directory list.
  $deadwood_dir = variable_get('coder_upgrade_dir_old', DEADWOOD_OLD);
  $dirs = coder_upgrade_directory_list();

  $header = array(
    'name' => array('data' => t('Name'), 'field' => 'name'),
    'path' => array('data' => t('Location'), 'field' => 'path'),
  );
  $i = 0;
  $rows = array();
  foreach ($dirs as $dir) {
    $row = array();
    $row['name'] = isset($directories[$dir]) ? l($dir, coder_upgrade_patch_link($dir), array('attributes' => array('target' => '_blank'))) : $dir;
    $row['path'] = $deadwood_dir . '/' . $dir;
    $row['#weight'] = ++$i;

    $rows[$dir] = $row;
  }
  $directory_fs = array(
    '#type' => 'fieldset',
    '#title' => t('Directories'),
    '#description' => t('... residing in the selected directories (beneath the files directory), or ...'),
    '#tree' => TRUE,
  );
  $directory_fs['list'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $rows,
    '#default_value' => isset($directories) ? $directories : array(),
    '#empty' => t('No directories available'),
  );

  return $directory_fs;
}

/**
 * Returns form content for modules tab.
 *
 * @param array $modules
 *   User selections or default values.
 *
 * @return array
 *   Form item.
 */
function coder_upgrade_modules_build(&$modules) {
  // Build the module list.
  $header = array(
    'name' => array('data' => t('Name'), 'field' => 'name'),
    'path' => array('data' => t('Location'), 'field' => 'path'),
  );
  $i = 0;
  $rows = coder_upgrade_module_list();
  foreach ($rows as $key => $row) {
    $rows[$key]['name'] = isset($modules[$key]) ? l($row['name'], coder_upgrade_patch_link($key)) : $row['name'];
    $rows[$key]['#weight'] = ++$i;
  }
  $module_fs = array(
    '#type' => 'fieldset',
    '#title' => t('Modules'),
    '#description' => t('... residing in the selected modules (beneath the drupal directory).'),
    '#tree' => TRUE,
  );
  $module_fs['list'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $rows,
    '#default_value' => isset($modules) ? $modules : array(),
    '#empty' => t('No modules available'),
  );

  return $module_fs;
}

/**
 * Validation handler for the module conversion form.
 */
function coder_upgrade_conversions_form_validate($form, &$form_state) {
  // Set keys to validate.
  $keys = coder_upgrade_selection_types($form_state);
  $count = 0;
  // Validate the user selections.
  $values = $form_state['values'];
  foreach ($values as $key => $list) {
    if (!in_array($key, $keys)) {
      continue;
    }
    $selections = coder_upgrade_selections_extract($list['list']);
    if (in_array($key, array('upgrades', 'extensions')) && !count($selections)) {
      form_set_error($key, t('Please select at least one item in the %item tab.', array('%item' => ucfirst($key))));
    }
    elseif (in_array($key, array('directories', 'modules'))) {
      $count += count($selections);
    }
  }
  // Determine if keys contains both 'directories' and 'modules'.
  $test = array_diff(array('directories', 'modules'), $keys);
  if (!$count && empty($test)) {
    form_set_error($key, t('Please select at least one item in the %item1 or %item2 tabs.', array('%item1' => ucfirst('directories'), '%item2' => ucfirst('modules'))));
  }
}

/**
 * Submit handler for the module conversion form.
 *
 * Execute the selected module conversion code on the selected file types in the
 * selected directories or modules.
 */
function coder_upgrade_conversions_form_submit($form, &$form_state) {
  // Rebuild form with user selections.
  $form_state['rebuild'] = TRUE;

  // Apply conversion routines.
  $success = coder_upgrade_conversions_apply($form_state);
  if ($success) {
    drupal_set_message(t('Module conversion routines were applied.'));
    drupal_set_message(t('Click to view the !log.', array('!log' => l(t('conversion log file'), coder_upgrade_path('log'), array('attributes' => array('target' => '_blank'))))));
    drupal_set_message(t('To view a <strong>patch file</strong>, click on a <strong>Name link</strong> in the Directories and Modules tabs below.'));
  }
  else {
    drupal_set_message(t('Module conversion routines failed to complete.'), 'error');
  }
}

/**
 * Applies the module conversion code.
 *
 * Execute the selected module conversion code on the selected file types in the
 * selected directories or modules.
 *
 * @return boolean
 *   TRUE if conversion code was successful, FALSE otherwise.
 */
function coder_upgrade_conversions_apply($form_state) {
  // Prepare conversion parameters.
  list($upgrades, $extensions, $items) = coder_upgrade_conversions_prepare($form_state);

  // Apply conversion routines.
//   module_load_include('inc', 'coder_upgrade', 'includes/main');
  if (variable_get('coder_upgrade_use_separate_process', FALSE)) {
    // Conversion routines will be run in a separate process.
    drupal_set_message(t('Module conversion routines will run in a separate process.'));
    $path = coder_upgrade_parameters_save($upgrades, $extensions, $items);
    $script = drupal_get_path('module', 'coder_upgrade') . '/scripts/coder_upgrade.run.php';
    $output = coder_upgrade_directory_path('base') . 'coder_upgrade.run.txt';
    $command = "php $script -- file=$path > $output"; // " 2>&1";
    // Execute the command and capture the output.
    exec($command, $errors, $success);
    $success = $success === 0;
    if ($success && !empty($errors)) {
      drupal_set_message(trim(implode("\n", $errors)), 'error');
    }
  }
  else {
    // Conversion routines will be run in the same process.
    module_load_include('inc', 'coder_upgrade', 'includes/main');
    drupal_set_message(t('Module conversion routines will run in the same process.'));
    $success = coder_upgrade_start($upgrades, $extensions, $items);
  }

  return $success;
}

/**
 * Returns the parameters to submit for module conversion.
 */
function coder_upgrade_conversions_prepare($form_state) {
  // Gather the submitted parameters.
  list($upgrades, $extensions, $directories, $modules) = coder_upgrade_selections($form_state);

  // TODO Cache this list so we don't have to query all the files again.
  $upgrades_all = _coder_upgrade_upgrades();
  foreach ($upgrades as $name => $upgrade) {
    $upgrades[$name] = array(
      'module' => isset($upgrades_all[$name]['module']) ? $upgrades_all[$name]['module'] : '',
      'files' => isset($upgrades_all[$name]['files']) ? $upgrades_all[$name]['files'] : array(),
    );
  }

  $old_dir = DRUPAL_ROOT . '/' . coder_upgrade_directory_path('old');
  $new_dir = DRUPAL_ROOT . '/' . coder_upgrade_directory_path('new');

  // Combine directory and module items into a single list.
  // Omit name from key so as to allow for duplicate names.
  // TODO Handle duplicate names when making new conversion directories.
  // Could intersect keys in $directories, $modules; then add counter suffix to new_dir???
  // Use global counter??? Or copy $directories to files/dirs and $modules to files/modules???
  $items = array();

  foreach ($directories as $key => $directory) {
    $items[] = array(
      'name' => $key,
      'old_dir' => $old_dir . $key,
      'new_dir' => $new_dir . $key,
    );
  }

  $last = 'xx_XX';
  $rows = coder_upgrade_module_list();
  foreach ($modules as $key => $module) {
    if (isset($rows[$key])) {
      $row = $rows[$key];
      if (strpos($row['dir'] . '/', $last . '/') === 0) {
        // Omit modules contained in subdirectory of a parent module.
        continue;
      }
      $last = $row['dir'];
      $items[] = array(
        'name' => $key,
        'old_dir' => $row['dir'],
        'new_dir' => $new_dir . $key,
      );
    }
  }

  return array($upgrades, $extensions, $items);
}

/**
 * Saves the runtime parameters to a file for use by script.
 */
function coder_upgrade_parameters_save($upgrades, $extensions, $items) {
  // Add path to upgrades array for use by script.
  foreach ($upgrades as $name => &$upgrade) {
    $upgrade['path'] = drupal_get_path('module', $upgrade['module']);
  }
  // Create paths array.
  $paths = array(
    'files_base' => coder_upgrade_directory_path('', FALSE),
    'libraries_base' => str_replace('/grammar_parser', '', libraries_get_path('grammar_parser')),
    'modules_base' => str_replace('/coder', '', drupal_get_path('module', 'coder')),
  );
  // Create variables array.
  $variables = array(
    'coder_upgrade_dir' => variable_get('coder_upgrade_dir', DEADWOOD_DIR),
    'coder_upgrade_dir_patch' => variable_get('coder_upgrade_dir_patch', DEADWOOD_PATCH),

    'coder_upgrade_replace_files' => variable_get('coder_upgrade_replace_files', FALSE),
    'coder_upgrade_preserve_array_format' => variable_get('coder_upgrade_preserve_array_format', FALSE),
    'coder_upgrade_enable_debug_output' => variable_get('coder_upgrade_enable_debug_output', FALSE),
    'coder_upgrade_enable_parser_debug_output' => variable_get('coder_upgrade_enable_parser_debug_output', FALSE),
    'coder_upgrade_use_separate_process' => variable_get('coder_upgrade_use_separate_process', FALSE),
  );
  // Create parameters array.
  $parameters['paths'] = $paths;
  $parameters['theme_cache'] = coder_upgrade_path('theme_cache');
  $parameters['variables'] = $variables;
  $parameters['upgrades'] = $upgrades;
  $parameters['extensions'] = $extensions;
  $parameters['items'] = $items;

  // Write parameters to file.
  $path = coder_upgrade_path('runtime'); // @todo Use random name and delete afterwards.
  file_put_contents($path, serialize($parameters));

  return $path;
}

/**
 * Sets the default values to display on the module conversions form.
 *
 * @return array
 *   Arrays of default values.
 */
function coder_upgrade_conversions_form_defaults($form_state) {
  // D7: the key is used (and the value is irrelevant); D6: the value.
  $upgrades = array('coder_upgrade' => 1);

  $extensions = array(
    'inc' => TRUE,
    'info' => TRUE,
    'install' => TRUE,
    'module' => TRUE,
//    'php' => FALSE,
//    'profile' => FALSE,
//    'test' => FALSE,
//    'theme' => FALSE,
  );

  $directories = array(); // 'samples' => 1;

  $modules = array();

  if (!isset($form_state['values'])) {
    return array($upgrades, $extensions, $directories, $modules);
  }

  // Set defaults from submitted values.
  return coder_upgrade_selections($form_state);
}

/**
 * Returns all submitted values.
 *
 * @param array $values
 *   Array of $form_state['values'].
 *
 * @return array
 *   Arrays of submitted values.
 */
function coder_upgrade_selections($form_state) {
  // Initialize these as not all may be set by some form users.
  $upgrades = $extensions = $directories = $modules = array();

  // Set keys to validate.
  $keys = coder_upgrade_selection_types($form_state);

  // Build arrays of each user selection type.
  $values = $form_state['values'];
  foreach ($keys as $key) {
    if (isset($values[$key])) {
      $$key = coder_upgrade_selections_extract($values[$key]['list']);
    }
  }
  return array($upgrades, $extensions, $directories, $modules);
}

/**
 * Returns a list of submitted values.
 *
 * @param array $values
 *   Array slice from $form_state['values'].
 *
 * @return array
 *   Array of submitted values.
 */
function coder_upgrade_selections_extract($values) {
  $selections = array();
  foreach ($values as $key => $value) {
    if ($value) {
      $selections[$key] = $key;
    }
  }
  return $selections;
}

/**
 * Returns a list of selection types.
 *
 * @param array $form_state
 *   Array of form state information.
 *
 * @return array
 *   Array of selection types to process.
 */
function coder_upgrade_selection_types($form_state) {
  if (isset($form_state['defaults']) && is_array($form_state['defaults']) && $form_state['defaults']) {
    return $form_state['defaults'];
  }
  return array('upgrades', 'extensions', 'directories', 'modules');
}

/**
 * Returns list of directories in module input directory.
 *
 * @return array
 *   Array of directories in module input directory.
 */
function coder_upgrade_directory_list() {
  $dirs = array();
  $path = coder_upgrade_directory_path('old', FALSE);
  if (!is_dir($path)) {
    // @todo This can happen if the public file system path is changed at
    // 'admin/config/media/file-system'. Add a submit handler on that form,
    // system_file_system_settings, to create directories or move existing ones.
    // Is there an action for this? No hook_path_changed?
    drupal_set_message(t('Module input directory does not exist at @path.', array('@path' => $path)), 'error');
    return $dirs;
  }

  $path = realpath($path);
  if (!$path) {
    // @todo Is this check redundant to above check?
    drupal_set_message(t('Module input directory does not exist at @path.', array('@path' => $path)), 'error');
    return $dirs;
  }

  $dirs = coder_upgrade_scan_directory($path);
  if (!$dirs) {
    drupal_set_message(t('Please place modules to be converted in @path.', array('@path' => $path)), 'error');
  }

  return $dirs;
}

/**
 * Returns list of contributed modules.
 *
 * @param null $core
 *   Indicates whether to return core modules regardless of settings variable.
 * @param integer $status
 *   Indicates status of modules to return.
 *
 * @return array
 *   Array of contributed modules.
 */
function coder_upgrade_module_list($core = NULL, $status = -1) {
  $test = is_null($core) ? variable_get('coder_upgrade_upgrade_core', FALSE) : $core;
  $like = $test ? 'LIKE' : 'NOT LIKE';
  $where = $status == -1 ? '' : 'AND status = :status';

  // Faster to query DB than to rescan files using _system_get_module_data().
  $sql = "SELECT name, filename, type, status, info,
          REPLACE(filename, CONCAT('/', name, '.', type), '') AS directory
          FROM {system}
          WHERE type = 'module'
          AND filename $like 'modules/%'
          $where
          ORDER BY directory, name";
  $default_value = 0;
  $results = db_query($sql, array(':status' => $status));
  $rows = array();
  foreach ($results as $module) {
    $info = unserialize($module->info);
    $row = array();
    $row['name'] = $info['name'];
    $row['path'] = dirname($module->filename); // $module->filename;
    $row['dir'] = $module->directory; // dirname($module->filename);
//    $row['filename'] = $module->filename; // Add this for later calls to module_list().
//    $row['status'] = $module->status;
    // TODO Pull files from this table???
    // Would need to change the conversion code to not read the filesystem.

    $rows[$module->name] = $row;
  }
  return $rows;
}

/**
 * Returns link to patch file.
 *
 * @param string $name
 *   String of the patch filename.
 *
 * @return string
 *   Link to file.
 */
function coder_upgrade_patch_link($name) {
  return 'files/coder_upgrade/patch/' . $name . '.patch';
}

/**
 * Returns patch file wrapped in html tags.
 *
 * @param string $filename
 *   String of the patch filename.
 *
 * @return string
 *   HTML output.
 */
function coder_upgrade_patch_display($filename) {
  echo '<html><head><body><pre>' . check_plain(file_get_contents(coder_upgrade_patch_path($filename))) . '</pre></body></head></html>';
}

/**
 * Returns path to patch file.
 *
 * @param string $filename
 *   String of the patch filename.
 *
 * @return string
 *   Path to file.
 */
function coder_upgrade_patch_path($filename) {
  static $dirname = '';

  if (!$dirname) {
    $dirname = coder_upgrade_directory_path('patch');
  }
  return $dirname . "$filename";
}
