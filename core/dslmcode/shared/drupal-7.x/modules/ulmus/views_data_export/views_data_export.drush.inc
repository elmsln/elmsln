<?php

/**
 * Implementation of hook_drush_command().
 */
function views_data_export_drush_command() {
  $items = array();

  $items['views-data-export'] = array (
    'aliases' => array (
      'vde',
    ),
    'description' => 'Fully executes a views_data_export display of a view and writes the output to file.',
    'arguments' => array (
      'view_name' => 'The name of the view',
      'display_id' => 'The id of the views_data_export display to execute on the view',
      'output_file' => 'The file to write the results to - will be overwritten if it already exists',
    ),
    'options' => array (
      'arguments' => 'Comma separated list of arguments to be passed to the view.',
      'format' => 'csv,doc,txt,xls or xml. These options are ignored if the display_id passed is a "views_data_export" display.',
      'separator' => 'csv only: What character separates the fields (default:,)',
      'trim-whitespace' => 'csv only: Trim whitespace from either side of fields (default:1)',
      'header-row' => 'csv only: Make the first row a row of headers (default:1)',
      'quote-values' => 'csv only: Surround each field in quotes (default:1)',
    ),
    'examples' => array (
      'drush views-data-export myviewname views_data_export_1 output.csv' => 'Export myviewname:views_data_export_1 and write the output to output.csv in the current directory',
    ),
    'drupal dependencies' => array (
      'views_data_export',
    ),
    'core' => array('7'),
  );

  return $items;
}


/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function views_data_export_drush_help($section) {
  switch ($section) {
    case 'drush:views-data-export':
      return dt("This command may be used to fully execute a views_data_export display of a view, batched if need be, and write the output to a file.");
  }
}

/**
 * Implementation of drush_hook_COMMAND_validate().
 */
function drush_views_data_export_validate() {
  // Because of a bug in the way that Drush 4 computes the name of functions to
  // call from a Drush command, we may end up getting called twice, so we just
  // don't do anything on subsequent invocations.
  static $already_run = FALSE;
  if ($already_run) {
    return;
  }
  $already_run = TRUE;

  $args = drush_get_arguments();
  array_shift($args);

  if (count($args) !== 3) {
    return drush_set_error('ARGUMENTS_REQUIRED', dt('All arguments are required.'));
  }

  if (!$view = views_get_view($args[0])) {
    return drush_set_error('VIEW_DOES_NOT_EXIST', dt('The view !view does not exist.', array ('!view' => $args[0])));
  }

  if (!$view->set_display($args[1])) {
    return drush_set_error('VIEW_DOES_NOT_EXIST', dt('The view !view does not have the !display display.', array ('!view' => $args[0], '!display' => $args[1])));
  }
  else {
    if ($view->current_display != $args[1]) {
      drush_log(dt('Using different display from specified display: @display', array('@display' => $view->current_display)), 'notice');
    }
    drush_set_option('views_data_export_display_id', $view->current_display);
  }

  $format = drush_get_option('format');
  $valid_formats = array('csv', 'doc', 'txt', 'xls', 'xml');
  if (!empty($format) && !in_array($format, $valid_formats)) {
    return drush_set_error('VIEWS_DATA_EXPORT_INVALID_OPTION', dt('The "--format" option is invalid, please supply one of the following: !formats', array('!formats' => implode(', ', $valid_formats))));
  }
}

/**
 * Drush command callback to export a views data to a file.
 *
 * @see drush_views_data_export_validate().
 * @see views_data_export_views_data_export_batch_alter().
 */
function drush_views_data_export($view_name, $display_id, $output_file) {
  // Because of a bug in the way that Drush 4 computes the name of functions to
  // call from a Drush command, we may end up getting called twice, so we just
  // don't do anything on subsequent invocations.
  static $already_run = FALSE;
  if ($already_run) {
    return;
  }
  $already_run = TRUE;

  // Set the display to the one that we computed earlier.
  $display_id = drush_get_option('views_data_export_display_id', 'default');

  $view = views_get_view($view_name);

  // If the given display_id is not views_data_alter then
  // we programatically clone it to a views_data_alter display
  // and then execute that one instead
  if ($view->display[$display_id]->display_plugin != 'views_data_export') {
    //drush_log("Display '$display_id' is not views_data_export. Making one that is and executing that instead =).", 'success');

    $format = drush_get_option('format');
    $settings = array();
    switch ($format) {
      case 'doc':
      case 'xls':
      case 'xml':
      case 'txt':
        $settings['display_options']['style_plugin'] = 'views_data_export_' . $format;
        break;
      case 'csv':
      default:
      $settings['display_options']['style_plugin'] = 'views_data_export_csv';
      if ($separator = drush_get_option('separator')) {
        $settings['display_options']['style_options']['separator'] = $separator;
      }
      if (!$trim = drush_get_option('trim-whitespace')) {
        $settings['display_options']['style_options']['trim'] = 0;
      }
      if (!$header = drush_get_option('header-row')) {
        $settings['display_options']['style_options']['header'] = 0;
      }
      if (!$quote = drush_get_option('quote-values')) {
        $settings['display_options']['style_options']['quote'] = 0;
      }
      // Seperator
    }

    $display_id = _drush_views_data_export_clone_display($view, $display_id, $settings);
  }

  $view->set_display($display_id);

  // We execute the view normally, and take advantage
  // of an alter function to interject later and batch it ourselves

  $options = array();
  // Let's see if the given $output_file is a absolute path.
  if (strpos($output_file, '/') === 0) {
    $options['output_file'] = $output_file;
  }
  else {
    $options['output_file'] = realpath(drush_get_context('DRUSH_OLDCWD', getcwd())) . '/' . $output_file;
  }

  $arguments = drush_get_option('arguments', '');
  if(!empty($arguments) && is_array($arguments)) {
    $arguments = explode(',', $arguments);
  }

  if ($view->display_handler->is_batched()) {
    // This is a batched export, and needs to be handled as such.
    _drush_views_data_export_override_batch($view_name, $display_id, $options);

    $view->execute_display($display_id, $arguments);
  }
  else {
    // This export isn't batched.
    ob_start();
    $view->execute_display($display_id, $arguments);
    // Get the results, and clean the output buffer.
    $result = ob_get_contents();
    // Clean the buffer.
    ob_end_clean();
    // Save the results to file.
    // Copy file over
    if (file_put_contents($options['output_file'], $result)) {
      drush_log("Data export saved to " . $options['output_file'], 'success');
    }
    else {
      drush_set_error('VIEWS_DATA_EXPORT_COPY_ERROR', dt("The file could not be copied to the selected destination"));
    }
  }

}


/**
 * Helper function that indicates that we want to
 * override the batch that the views_data_export view creates
 * on it's initial time through.
 *
 * Also provides a place to stash options that need to stay around
 * until the end of the batch
 */
function _drush_views_data_export_override_batch($view = NULL, $display = NULL, $options = TRUE) {
  static $_views;
  if (isset($view)) {
    $_views[$view][$display] = $options;
  }
  return $_views;
}

/**
 * Implementation of hook_views_data_export_batch_alter()
 */
function views_data_export_views_data_export_batch_alter(&$batch, &$final_destination, &$querystring) {

  // Copy the batch, because we're going to monkey with it, a lot!
  $new_batch = $batch;

  $view_name = $new_batch['view_name'];
  $display_id = $new_batch['display_id'];

  $ok_to_override = _drush_views_data_export_override_batch();

  // Make sure we do nothing if we are called not following the execution of
  // our drush command. This could happen if the file with this function in it
  // is included during the normal execution of the view
  if (!$ok_to_override[$view_name][$display_id]) {
    return;
  }

  $options = $ok_to_override[$view_name][$display_id];

  // We actually never return from the drupal_alter, but
  // use drush's batch system to run the same batch

  // Add a final callback
  $new_batch['operations'][] = array(
    '_drush_views_data_export_batch_finished', array($batch['eid'], $options['output_file']),
  );

  batch_set($new_batch);
  $new_batch =& batch_get();
  // Drush handles the different processes, so instruct BatchAPI not to.
  $new_batch['progressive'] = FALSE;
  // Process the batch using drush.
  drush_backend_batch_process();

  // Instruct the view display plugin that it shouldn't set a batch.
  $batch = array();
}


/**
 * Get's called at the end of the drush batch process that generated our export
 */
function _drush_views_data_export_batch_finished($eid, $output_file, &$context) {
  // Fetch export info
  $export = views_data_export_get($eid);

  // Perform cleanup
  $view = views_data_export_view_retrieve($eid);
  $view->set_display($export->view_display_id);
  $view->display_handler->batched_execution_state = $export;
  $view->display_handler->remove_index();

  // Get path to temp file
  $temp_file = $view->display_handler->outputfile_path();

  // Copy file over
  if (@drush_op('copy', $temp_file, $output_file)) {
    drush_log("Data export saved to " . $output_file, 'success');
  }
  else {
    drush_set_error('VIEWS_DATA_EXPORT_COPY_ERROR', dt("The file could not be copied to the selected destination"));
  }

}


/**
 * Helper function that takes a view and returns a clone of it
 * that has cloned a given display to one of type views_data_export
 *
 * @param &$view
 *   Modified to contain the new display
 *
 * @return
 *   The new display_id
 */
function _drush_views_data_export_clone_display(&$view, $display_id, $settings = array()) {

  // Create the new display
  $new_display_id = _drush_views_data_export_generate_display_id($view, 'views_data_export');
  $view->display[$new_display_id] = clone $view->display[$display_id];

  // Ensure we have settings we'll need for our display
  $default_settings = array (
    'id' => $new_display_id,
    'display_plugin' => 'views_data_export',
    'position' => 99,
    'display_options' => array (
      'style_plugin' => 'views_data_export_csv',
      'style_options' => array(
        'attach_text' => 'CSV',
        'provide_file' => 1,
        'filename' => 'view-%view.csv',
        'parent_sort' => 1,
        'separator' => ',',
        'quote' => 1,
        'trim' => 1,
        'header' => 1,
      ),
      'use_batch' => 'batch',
      'path' => '',
      'displays' => array (
        'default' => 'default',
      ),
    ),
  );
  $settings = array_replace_recursive($default_settings, $settings);

  $view->display[$new_display_id] = (object)array_replace_recursive((array)$view->display[$new_display_id], $settings);

  return $new_display_id;
}


/**
 * Generate a display id of a certain plugin type.
 * See http://drupal.org/files/issues/348975-clone-display.patch
 *
 * @param $type
 *   Which plugin should be used for the new display id.
 */
function _drush_views_data_export_generate_display_id($view, $type) {
  // 'default' is singular and is unique, so just go with 'default'
  // for it. For all others, start counting.
  if ($type == 'default') {
    return 'default';
  }
  // Initial id.
  $id = $type . '_1';
  $count = 1;

  // Loop through IDs based upon our style plugin name until
  // we find one that is unused.
  while (!empty($view->display[$id])) {
    $id = $type . '_' . ++$count;
  }

  return $id;
}

/**
 * If we're using PHP < 5.3.0 then we'll need
 * to define this function ourselves.
 * See: http://phpmyanmar.com/phpcodes/manual/function.array-replace-recursive.php
 */
if (!function_exists('array_replace_recursive')) {
function array_replace_recursive($array, $array1) {
  // Get array arguments
  $arrays = func_get_args();

  // Define the original array
  $original = array_shift($arrays);

  // Loop through arrays
  foreach ($arrays as $array) {
    // Loop through array key/value pairs
    foreach ($array as $key => $value) {
      // Value is an array
      if (is_array($value)) {
        // Traverse the array; replace or add result to original array
        $original[$key] = array_replace_recursive($original[$key], $array[$key]);
      }

      // Value is not an array
      else {
        // Replace or add current value to original array
        $original[$key] = $value;
      }
    }
  }

  // Return the joined array
  return $original;
}
}
