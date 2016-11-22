<?php
/**
 * @file
 * Provide Drush integration for release building and dependency building.
 */

/**
 * Helper function to check for modules to fix.
 */
function module_missing_message_fixer_check_modules() {
  $rows = array();
  // These are special modules that have their own patches already.
  // This will help eliminate some of the brute force of this module.
  $special = array(
    'adminimal_theme' => 'https://www.drupal.org/node/2763581',
    'content' => 'https://www.drupal.org/node/2763555',
    'field_collection_table' => 'https://www.drupal.org/node/2764331',
  );
  // Grab all the modules in the system table.
  $query = db_query("SELECT filename, type, name FROM {system}");
  // Go through the query and check to see if the module exists in the directory.
  foreach ($query->fetchAll() as $record) {
    // Grab the checker.
    $check = drupal_get_filename($record->type, $record->name, $record->filename, FALSE);
    // If drupal_get_filename returns null = we got problems.
    if (is_null($check) &&
      $record->name != 'default' &&
      !array_key_exists($record->name, $special)) {
      // Go ahead and set the row if all is well.
      $rows[$record->name] = array(
        'name' => $record->name,
        'type' => $record->type,
        'filename' => $record->filename,
      );
    }
    // Go ahead and print out a special message for the user.
    elseif (array_key_exists($record->name, $special)) {
      // Add exception to this since content module seems to be ubercart sad only.
      if ($record->name == 'content' && !module_exists('ubercart')) {
        $rows[$record->name] = array(
          'name' => $record->name,
          'type' => $record->type,
          'filename' => $record->filename,
        );
      }
      // Everyone else fails into here.
      else {
        // Set the message.
        $msg = t('The @module module has a patch. See <a href="@link" target="_blank">this issue</a> for more information.  It <strong>WILL NOT</strong> be removed by Module Missing Message Fixer.', array(
          '@module' => $record->name,
          '@link' => $special[$record->name],
        ));
        // Now print it!
        drupal_set_message($msg, 'status', FALSE);
      }
    }
  }
  return $rows;
}

/**
 * Implements hook_drush_help().
 */
function module_missing_message_fixer_drush_help($section) {
  switch ($section) {
    case 'module-missing-message-fixer-list':
      $result = dt("Returns a list of modules that have missing messages.");
    case 'module-missing-message-fixer-fix':
      $result = dt("Fixes a specified module that has missing messages. (optional --all)");
  }
  return $result;
}

/**
 * Implements hook_drush_command().
 */
function module_missing_message_fixer_drush_command() {
  $items = array();
  $items['module-missing-message-fixer-list'] = array(
    'description' => dt('Returns a list of modules that have missing messages.'),
    'aliases' => array(
      'mmmfl',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'engines' => array(
      'outputformat' => array(
        'default' => 'table',
        'pipe-format' => 'json',
        'field-labels' => array(
          'name' => 'Name',
          'type' => 'Type',
          'filename' => 'Filename',
        ),
        'require-engine-capability' => array('format-table'),
      ),
    ),
  );
  $items['module-missing-message-fixer-fix'] = array(
    'description' => dt('Fixes modules that have missing messages.'),
    'aliases' => array(
      'mmmff',
    ),
    'arguments' => array(
      'name' => 'The name of the module to fix.',
    ),
    'options' => array(
      'all' => dt('Fixes all module missing messages'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'engines' => array(
      'outputformat' => array(
        'default' => 'table',
        'pipe-format' => 'json',
        'field-labels' => array(
          'name' => 'Name',
          'type' => 'Type',
          'filename' => 'Filename',
        ),
        'require-engine-capability' => array('format-table'),
      ),
    ),
  );
  return $items;
}

/**
 * Drush command.
 *
 * Displays a list of modules that have missing messages.
 */
function drush_module_missing_message_fixer_list() {
  $rows = module_missing_message_fixer_check_modules();
  return $rows;
}

/**
 * Drush command.
 *
 * @param string $name
 *        The name of the module to fix messages for.
 */
function drush_module_missing_message_fixer_fix($name = NULL) {
  $module = array();
  if (drush_get_option('all') !== NULL) {
    $rows = module_missing_message_fixer_check_modules();
    foreach ($rows as $row) {
      $modules[] = $row['name'];
    }
  }
  elseif ($name !== NULL) {
    if (module_exists($name)) {
      $modules[] = $name;
    }
    else {
      drush_log(dt('Module ' . $name . ' was not found.'), 'error');
    }
  }
  else {
    drush_log(dt('Missing input, provide module name or run with --all'), 'error');
  }
  // Delete if there is no modules.
  if (count($modules) > 0) {
    db_delete('system')
      ->condition('name', $modules, 'IN')
      ->execute();
    if (drush_get_option('all') !== NULL) {
      drush_log(dt('All missing references have been removed.'), 'success');
    }
    elseif (isset($name)) {
      if (in_array($name, $modules)) {
        drush_log(dt('Reference to ' . $name . ' (if found) has been removed.'), 'success');
      }
    }
  }
}
