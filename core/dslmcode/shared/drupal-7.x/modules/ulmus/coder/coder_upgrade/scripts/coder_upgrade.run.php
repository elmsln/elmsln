<?php
/**
 * @file
 * Invokes the Coder Upgrade conversion routines as a separate process.
 *
 * Using this script:
 * - helps to minimize the memory usage by the web interface process
 * - helps to avoid hitting memory and processing time limits by the PHP process
 * - enables a batch processing workflow
 *
 * Parameters to this script:
 * @param string $path
 *   Path to a file containing runtime parameters
 *
 * The parameters should be stored as the serialized value of an associative
 * array with the following keys:
 * - paths: paths to files and modules
 * - theme_cache: path to core theme information cache
 * - variables: variables used by coder_upgrade
 * - upgrades: array to be passed to coder_upgrade_start()
 * - extensions: ditto
 * - items: ditto
 *
 * @see coder_upgrade_conversions_prepare()
 * @see coder_upgrade_parameters_save()
 * @see coder_upgrade_start()
 *
 * To execute this script, save the following shell script to a file and execute
 * the shell script from the root directory of your Drupal installation. If you
 * have changed the default coder_upgrade output directory name, then modify
 * this script accordingly.
 *
 * #!/bin/sh
 *
 * MODULES_DIRECTORY=[fill this in, e.g. all or mysite]
 * FILES_DIRECTORY=[fill this in, e.g. default or mysite]
 * CODER_UPGRADE_DIRECTORY=coder_upgrade [unless you changed it]
 * SCRIPT=sites/$MODULES_DIRECTORY/modules/coder/coder_upgrade/scripts/coder_upgrade.run.php
 * RUNTIME=sites/$FILES_DIRECTORY/files/$CODER_UPGRADE_DIRECTORY/runtime.txt
 * OUTPUT=sites/$FILES_DIRECTORY/files/$CODER_UPGRADE_DIRECTORY/coder_upgrade.run.txt
 *
 * php $SCRIPT -- file=$RUNTIME > $OUTPUT 2>&1
 *
 * Alternatively, replace the bracketed items in the following command and
 * execute it from the root directory of your Drupal installation.
 *
 * php sites/[modules_directory]/modules/coder/coder_upgrade/scripts/coder_upgrade.run.php \
 *  -- file=sites/[files_directory]/files/coder_upgrade/runtime.txt \
 *  > sites/[files_directory]/files/coder_upgrade/coder_upgrade.run.txt 2>&1
 *
 * Copyright 2009-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

// Save memory usage for printing later (when code is loaded).
$usage = array();
save_memory_usage('start', $usage);

/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

ini_set('display_errors', 1);
ini_set('memory_limit', '128M');
ini_set('max_execution_time', 180);
set_error_handler("error_handler");
set_exception_handler("exception_handler");

// Read command line arguments.
$path = extract_arguments();
if (is_null($path)) {
  echo 'No path to parameter file';
  return 2;
}

// Load runtime parameters.
$parameters = unserialize(file_get_contents($path));

// Extract individual array items by key.
foreach ($parameters as $key => $variable) {
  $$key = $variable;
}
save_memory_usage('load runtime parameters', $usage);

// Set global variables (whose names do not align with extracted parameters).
$_coder_upgrade_variables = $variables;
$_coder_upgrade_files_base = $paths['files_base'];
$_coder_upgrade_libraries_base = $paths['libraries_base'];
$_coder_upgrade_modules_base = $paths['modules_base'];

// Load core theme cache.
$_coder_upgrade_theme_registry = array();
if (is_file($theme_cache)) {
  $_coder_upgrade_theme_registry = unserialize(file_get_contents($theme_cache));
}
save_memory_usage('load core theme cache', $usage);

// Load coder_upgrade bootstrap code.
$path = $_coder_upgrade_modules_base . '/coder/coder_upgrade';
$files = array(
  'coder_upgrade.inc',
  'includes/main.inc',
  'includes/utility.inc',
);
foreach ($files as $file) {
  require_once DRUPAL_ROOT . '/' . $path . "/$file";
}

coder_upgrade_path_clear('memory');
print_memory_usage($usage);

// $trace_base = DRUPAL_ROOT . '/' . $_coder_upgrade_files_base . '/coder_upgrade/coder_upgrade_';
// $trace_file = $trace_base . '1.trace';
// xdebug_start_trace($trace_file);
coder_upgrade_memory_print('load coder_upgrade bootstrap code');
// xdebug_stop_trace();

// Apply conversion functions.
$success = coder_upgrade_start($upgrades, $extensions, $items);

// $trace_file = $trace_base . '2.trace';
// xdebug_start_trace($trace_file);
coder_upgrade_memory_print('finish');
// xdebug_stop_trace();

return $success ? 0 : 1;

/**
 * Returns command line arguments.
 *
 * @return mixed
 *   String or array of command line arguments.
 */
function extract_arguments() {
  switch (php_sapi_name()) {
    case 'apache':
    case 'apache2handler': // This is the value when running curl.
      if (!isset($_GET['file'])) {
        echo 'file parameter is not set';
        return;
      }
      $filename = $_GET['file'];
      $action = isset($_GET['action']) ? $_GET['action'] : '';
      break;

    case 'cli':
      $skip_args = 2;
      if ($_SERVER['argc'] == 2) {
        $skip_args = 1;
      }
      elseif ($_SERVER['argc'] < 2) {
        echo 'CLI-1: file parameter is not set' . "\n";
        return;
      }
      foreach ($_SERVER['argv'] as $index => $arg) {
        // First two arguments are usually script filename and '--'.
        // Sometimes the '--' is omitted.
        if ($index < $skip_args) continue;
        list($key, $value) = explode('=', $arg);
        $arguments[$key] = $value;
      }
      if (!isset($arguments['file'])) {
        echo 'CLI-2: file parameter is not set' . "\n";
        return;
      }
      $filename = $arguments['file'];
      $action = isset($arguments['action']) ? $arguments['action'] : '';
      break;
  }
  return $filename;
}

/**
 * Saves memory usage for printing later.
 *
 * @param string $step
 *   A string describing the code step when the memory usage is gathered.
 *
 * @return mixed
 *   String or array of command line arguments.
 */
function save_memory_usage($step, &$usage) {
  $usage[] = $step;
  $usage[] = 'Peak: ' . number_format(memory_get_peak_usage(TRUE), 0, '.', ',') . ' bytes';
  $usage[] = 'Curr: ' . number_format(memory_get_usage(TRUE), 0, '.', ',') . ' bytes';
  $usage[] = '';
  $usage[] = '';
}

function print_memory_usage($usage) {
  $text = 'Missing memory usage information';
  if (is_array($usage)) {
    $text = implode("\n", $usage);
  }
  coder_upgrade_path_print(coder_upgrade_path('memory'), $text);
}

function exception_handler($e) {
  try {
    // ... normal exception stuff goes here
  }
  catch (Exception $e) {
    print get_class($e) . " thrown within the exception handler. Message: " . $e->getMessage() . " on line " . $e->getLine();
  }
}

function error_handler($code, $message, $file, $line) {
  if (0 == error_reporting()) {
    return;
  }
  throw new ErrorException($message, 0, $code, $file, $line);
}
