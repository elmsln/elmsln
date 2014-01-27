<?php
/**
 * @file
 * Manages application of conversion routines, logging, and patch file creation.
 *
 * The functions in these conversion routine files correspond to the topics in
 * the category roadmap at http://drupal.org/node/394070 that are marked with
 * a green check mark in the Upgrade column.
 *
 * Copyright 2008-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Prepares conversion environment and starts conversion loop.
 *
 * @param array $upgrades
 *   Array of upgrade sets to apply.
 * @param array $extensions
 *   Array of file types to convert based on extension.
 * @param array $items
 *   Array of directories containing the files to convert.
 * @param boolean $recursive
 *   Indicates whether to recurse the subdirectories of each $item.
 *
 * @return boolean
 *   Indicates whether the conversion code was successfully applied.
 */
function coder_upgrade_start($upgrades, $extensions, $items, $recursive = TRUE) {
  // Declare global variables.
  global $_coder_upgrade_log, $_coder_upgrade_debug, $_coder_upgrade_module_name, $_coder_upgrade_replace_files, $_coder_upgrade_class_files;
//  global $_coder_upgrade_dirname; // Not used.

  // Check lists in case this function is called apart from form submit.
  if (!is_array($upgrades) || empty($upgrades)) {
    return FALSE;
  }
  if (!is_array($extensions) || empty($extensions)) {
    return FALSE;
  }
  if (!is_array($items) || empty($items)) {
    return FALSE;
  }

  $_coder_upgrade_log = TRUE;
  if ($_coder_upgrade_log) {
    // Clear the log file.
    coder_upgrade_path_clear('log');
    if (!variable_get('coder_upgrade_use_separate_process', FALSE)) {
      coder_upgrade_path_clear('memory');
    }
    coder_upgrade_memory_print('initial');
  }
  // Set debug output preference.
  $_coder_upgrade_debug = variable_get('coder_upgrade_enable_debug_output', FALSE);
  if ($_coder_upgrade_debug) {
    // Clear the debug file.
    coder_upgrade_path_clear('debug');
  }

  // Load code.
  coder_upgrade_load_code($upgrades);
  coder_upgrade_load_parser();

  // Set file replacement parameter.
  $_coder_upgrade_replace_files = variable_get('coder_upgrade_replace_files', FALSE);
  // Initialize list of class files.
  $_coder_upgrade_class_files = array();

  // Loop on items.
  foreach ($items as $item) {
    $_coder_upgrade_module_name = '';
//    $_coder_upgrade_dirname = $item['old_dir'];

    if (!isset($_SERVER['HTTP_USER_AGENT']) || strpos($_SERVER['HTTP_USER_AGENT'], 'simpletest') === FALSE) {
      // Process the directory before conversion routines are applied.
      // Note: if user agent is not set, then this is being called from CLI.
      coder_upgrade_convert_begin($item);
    }

    // Call main conversion loop.
    coder_upgrade_convert_dir($upgrades, $extensions, $item, $recursive);

    // Apply finishing touches to the directory.
    // Swap directories if files are replaced.
    $new_dir = $_coder_upgrade_replace_files ? $item['old_dir'] : $item['new_dir'];
    coder_upgrade_convert_end($new_dir);

    // Make a patch file.
    coder_upgrade_make_patch_file($item, $_coder_upgrade_replace_files);
  }

  return TRUE;
}

/**
 * Loads upgrade routine code files.
 *
 * @param array $upgrades
 *   Array of upgrade sets to apply.
 */
function coder_upgrade_load_code(&$upgrades) {
  global $_coder_upgrade_upgrade_modules;
  $_coder_upgrade_upgrade_modules = array();

  foreach ($upgrades as $name => $upgrade) {
    $_coder_upgrade_upgrade_modules[] = $upgrade['module'];
    if (isset($upgrade['path']) && !empty($upgrade['path'])) {
      // This is being run as a separate process outside of Drupal.
      $path = DRUPAL_ROOT . '/' . $upgrade['path'];
    }
    else {
      $path = DRUPAL_ROOT . '/' . drupal_get_path('module', $upgrade['module']);
    }
    if (isset($upgrade['files']) && !empty($upgrade['files'])) {
      foreach ($upgrade['files'] as $file) {
        require_once $path . '/' . $file;
      }
    }
    elseif (file_exists($path . '/' . $upgrade['module'] . '.upgrade')) {
      // Default file name is module.upgrade in the module's root directory.
      require_once $path . '/' . $upgrade['module'] . '.upgrade';
    }
  }
  coder_upgrade_memory_print('load upgrade code');
}

/**
 * Loads grammer parser code files.
 */
function coder_upgrade_load_parser() {
  static $parser_loaded = FALSE;
  if (!$parser_loaded) {
    $parser_loaded = TRUE;
    // Include parser files.
    libraries_load('grammar_parser');
    coder_upgrade_memory_print('load parser code');
  }
}

/**
 * Processes the directory before conversion routines are applied.
 *
 * This hook can be used to cache information needed by other routines.
 * Example: core changes need to know about hook_theme or hook_menu to make
 * theme changes and form API changes.
 *
 * @param array $item
 *   Array of a directory containing the files to convert.
 */
function coder_upgrade_convert_begin($item) {
  $dirname = $item['old_dir'];
  coder_upgrade_log_print("\n*************************");
  coder_upgrade_log_print('Pre-processing the directory => ' . $dirname);
  coder_upgrade_log_print("*************************");
  coder_upgrade_log_print("Calling hook_upgrade_begin_alter");
  drupal_alter('upgrade_begin', $item);
  coder_upgrade_log_print("Completed hook_upgrade_begin_alter");
}

/**
 * Applies finishing touches to the directory of converted files.
 *
 * @param string $dirname
 *   The name of the directory with the converted files.
 */
function coder_upgrade_convert_end($dirname) {
//  $dirname = $item['old_dir'];
  coder_upgrade_log_print("\n*************************");
  coder_upgrade_log_print('Post-processing the directory => ' . $dirname);
  coder_upgrade_log_print("*************************");
  coder_upgrade_log_print("Calling hook_upgrade_end_alter");
  drupal_alter('upgrade_end', $dirname);
  coder_upgrade_log_print("Completed hook_upgrade_end_alter");
}

/**
 * Converts files in a directory.
 *
 * @param array $upgrades
 *   Array of upgrade sets to apply.
 * @param array $extensions
 *   Array of file types to convert based on extension.
 * @param array $item
 *   Array of a directory containing the files to convert.
 * @param boolean $recursive
 *   Indicates whether to recurse the subdirectories of $item.
 */
function coder_upgrade_convert_dir($upgrades, $extensions, $item, $recursive = TRUE) {
  global $_coder_upgrade_filename; // Not used by this module, but other modules may find it useful.
  static $ignore = array(/*'.', '..', '.bzr', '.git', '.svn',*/ 'CVS');
  global $_coder_upgrade_module_name, $_coder_upgrade_replace_files;

  $dirname = $item['old_dir'];
  $new_dirname = $item['new_dir'];

  // Create an output directory we can write to.
  if (!is_dir($new_dirname)) {
    mkdir($new_dirname);
    chmod($new_dirname, 0757);
  }
  else {
    coder_upgrade_clean_directory($new_dirname);
  }

  if (!in_array($dirname, $ignore)) {
    coder_upgrade_log_print("\n*************************");
    coder_upgrade_log_print('Converting the directory => ' . $dirname);
    coder_upgrade_log_print("*************************");
  }

  // Determine module name.
  coder_upgrade_module_name($dirname, $item);
  $_coder_upgrade_module_name = $item['module'] ? $item['module'] : $_coder_upgrade_module_name;

  // Loop on files.
  $filenames = scandir($dirname . '/');
  foreach ($filenames as $filename) {
    $_coder_upgrade_filename = $dirname . '/' . $filename;
    if (is_dir($dirname . '/' . $filename)) {
      if (substr(basename($filename), 0, 1) == '.' || in_array(basename($filename), $ignore)) {
        // Ignore all hidden directories and CVS directory.
        continue;
      }
      $new_filename = $filename;
      // Handle D6 conversion item #79.
      if ($filename == 'po') {
        $new_filename = 'translations';
      }
      if ($recursive) {
        // TODO Fix this!!!
        $new_item = array(
          'name' => $item['name'],
          'old_dir' => $dirname . '/' . $filename,
          'new_dir' => $new_dirname . '/' . $filename,
        );
        coder_upgrade_convert_dir($upgrades, $extensions, $new_item, $recursive);
        // Reset the module name.
        $_coder_upgrade_module_name = $item['module'];
      }
    }
    elseif (in_array($extension = pathinfo($filename, PATHINFO_EXTENSION), array_keys($extensions))) {
      copy($dirname . '/' . $filename, $new_dirname . '/' . $filename);
      if ($extension == 'php' && substr($filename, -8) == '.tpl.php') {
        // Exclude template files.
        continue;
      }
      coder_upgrade_log_print("\n*************************");
      coder_upgrade_log_print('Converting the file => ' . $filename);
      coder_upgrade_log_print("*************************");
      coder_upgrade_convert_file($dirname . '/' . $filename, $new_dirname . '/' . $filename, $_coder_upgrade_replace_files);
    }
    elseif (in_array($extension, array('inc', 'install', 'module', 'php', 'profile', 'test', 'theme', 'upgrade'))) {
      copy($dirname . '/' . $filename, $new_dirname . '/' . $filename);
      // Check for a class declaration for use in the info file.
      coder_upgrade_class_check($new_dirname . '/' . $filename);
    }
    else {
      copy($dirname . '/' . $filename, $new_dirname . '/' . $filename);
    }
  }
}

/**
 * Converts a file.
 *
 * @param string $oldname
 *   The original name of the file to convert.
 * @param string $filename
 *   The new name of the file to convert.
 * @param boolean $_coder_upgrade_replace_files
 *   Indicates whether to replace the original files.
 */
function coder_upgrade_convert_file($oldname, $filename, $_coder_upgrade_replace_files = FALSE) {
  if (!file_exists($filename)) {
    return FALSE;
  }

  // Read the file and copy the contents.
  $cur = file_get_contents($filename);
  $new = $cur;

  // Apply regular expression routines.
  coder_upgrade_apply_regex($filename, $new);
  // Apply parser routines.
  coder_upgrade_apply_parser($filename, $new);

  // Write the new file.
  if ($new != $cur) {
    $filename = $_coder_upgrade_replace_files ? $oldname : $filename;
    if (file_put_contents($filename, $new) === FALSE) {
      coder_upgrade_log_print('File could not be written');
    }
    coder_upgrade_log_print('Replaced the file');
  }
}

/**
 * Applies regular expression conversion routines to a file.
 *
 * @param string $filename
 *   The name of the file to convert.
 * @param string $new
 *   The contents of the file to convert.
 */
function coder_upgrade_apply_regex($filename, &$new) {
  // Categorize certain files.
  $is_info_file = pathinfo($filename, PATHINFO_EXTENSION) == 'info';
  $is_install_file = pathinfo($filename, PATHINFO_EXTENSION) == 'install';

  if ($is_info_file) {
    // Apply regular expression conversion routines for info file.
    coder_upgrade_log_print("Calling hook_upgrade_regex_info_alter");
    drupal_alter('upgrade_regex_info', $new);
    coder_upgrade_log_print("Completed hook_upgrade_regex_info_alter");
    return;
  }
  if ($is_install_file) {
    // Apply regular expression conversion routines for install file.
    coder_upgrade_log_print("Calling hook_upgrade_regex_install_alter");
    drupal_alter('upgrade_regex_install', $new);
    coder_upgrade_log_print("Completed hook_upgrade_regex_install_alter");
  }
  // Apply regular expression conversion routines.
  coder_upgrade_log_print("Calling hook_upgrade_regex_alter");
  drupal_alter('upgrade_regex', $new);
  coder_upgrade_log_print("Completed hook_upgrade_regex_alter");
}

/**
 * Applies grammar parser conversion routines to a file.
 *
 * @param string $filename
 *   The name of the file to convert.
 * @param string $new
 *   The contents of the file to convert.
 */
function coder_upgrade_apply_parser($filename, &$new) {
  global $_coder_upgrade_class_files;
  // Categorize certain files.
  $is_info_file = pathinfo($filename, PATHINFO_EXTENSION) == 'info';
  $is_install_file = pathinfo($filename, PATHINFO_EXTENSION) == 'install';
  if ($is_info_file) {
    // Grammar parser only parses PHP code files.
    return;
  }

  // Create reader object.
  $reader = PGPReader::getInstance();
  coder_upgrade_memory_print('create reader for file ' . $filename);
  // Set array formatting preference.
  $reader->setPreserveArrayFormat(variable_get('coder_upgrade_preserve_array_format', FALSE));
  // Set debug output preference.
  $reader->setDebug(variable_get('coder_upgrade_enable_parser_debug_output', FALSE));
  $reader->setSnippet($new);
  coder_upgrade_memory_print('set snippet');
  $reader->addTokenNames();
  coder_upgrade_memory_print('add token names');
  // Parse code file.
  $reader->buildGrammar();
  coder_upgrade_memory_print('build grammar');

  $nodes = &$reader->getClasses();
  if (!empty($nodes)) {
    $_coder_upgrade_class_files[] = $filename;
  }

  // Apply parser conversion routines for function calls.
  coder_upgrade_log_print("Calling hook_upgrade_call_alter");
  coder_upgrade_convert_function_calls($reader);
  coder_upgrade_log_print("Completed hook_upgrade_call_alter");
  coder_upgrade_memory_print('apply function call conversions');

  // Apply parser conversion routines for hook functions.
  coder_upgrade_log_print("Calling hook_upgrade_hook_alter");
  coder_upgrade_convert_functions($reader);
  coder_upgrade_log_print("Completed hook_upgrade_hook_alter");
  coder_upgrade_memory_print('apply hook function conversions');

  // Apply parser conversion routines for the file.
  coder_upgrade_log_print("Calling hook_upgrade_file_alter");
  drupal_alter('upgrade_file', $reader);
  coder_upgrade_log_print("Completed hook_upgrade_file_alter");
  coder_upgrade_memory_print('apply file conversions');

  if ($is_install_file) {
    // Apply parser conversion routines for install file.
    coder_upgrade_log_print("Calling hook_upgrade_parser_install_alter");
    drupal_alter('upgrade_parser_install', $reader);
    coder_upgrade_log_print("Completed hook_upgrade_parser_install_alter");
    coder_upgrade_memory_print('apply install file conversions');
  }

  // Use writer to redo file.
  $writer = PGPWriter::getInstance();
  coder_upgrade_memory_print('create writer');
  $new = $writer->toString($reader->getStatements());
  coder_upgrade_memory_print('writer->toString');

  // Free up memory.
  $reader->reset();
  coder_upgrade_memory_print('reset reader');
}

/**
 * Upgrades function calls using grammar parser.
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_convert_function_calls(&$reader) {
  cdp("inside " . __FUNCTION__);
  $nodes = &$reader->getFunctionCalls();
  foreach ($nodes as &$node) {
    $item = &$node->data;
    if (!isset($item) || !is_object($item) || !($item instanceof PGPFunctionCall) || $item->type != T_FUNCTION_CALL) {
      // The reference could have been changed in another routine so that it
      // no longer refers to an object.
      continue;
    }
    // If need to change other statements that we build as a function call,
    // then modify the next line. Others: eval, empty, unset, print, throw.
    $types = array(T_STRING, T_REQUIRE, T_REQUIRE_ONCE, T_INCLUDE, T_INCLUDE_ONCE);
    if (is_array($item->name) && in_array($item->name['type'], $types)) {
      // If name is an object, then it is a variable expression that is not
      // 'alterable' in the traditional sense.
      drupal_alter('upgrade_call_' . $item->name['value'], $node, $reader);
      // TODO The alter hooks can get the $reader from PGPReader::getInstance();
      // We could do the same in this function.
    }

    if (!isset($node) || !is_object($node) || !($node instanceof PGPNode)) {
      continue;
    }
    $item = &$node->data;
    if (!isset($item) || !is_object($item) || !($item instanceof PGPFunctionCall) || $item->type != T_FUNCTION_CALL) {
      continue;
    }
    if (is_array($item->name) && in_array($item->name['type'], $types)) {
      // Set name because only variables may be passed by reference.
      $name = $item->name['value'];
      drupal_alter('upgrade_call', $node, $reader, $name);
      // TODO The alter hooks can get the $reader from PGPReader::getInstance();
      // We could do the same in this function.
    }
  }
}

/**
 * Upgrades functions (or hooks) using grammar parser.
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_convert_functions(&$reader) {
  cdp("inside " . __FUNCTION__);
  global $_coder_upgrade_module_name;

  $nodes = &$reader->getFunctions();
  foreach ($nodes as &$node) {
    $item = &$node->data;
    if (!isset($item) || !is_object($item) || !($item instanceof PGPClass) || $item->type != T_FUNCTION) {
      // The reference could have been changed in another routine so that it
      // no longer refers to an object.
      continue;
    }

    $name = &$item->name;
    cdp("name = $name");

    // Convert theme_xxx function calls.
//    if (strpos($name, 'theme_') === 0) {
//      drupal_alter('upgrade_theme', $node, $reader);
//      continue;
//    }

    /*
     * If the function name does not begin with the module name, then ignore it.
     * This assumes such a function would be an instance of an API hook defined
     * by the contributed module but implemented on behalf of another module. For
     * this use case, the contributed module would define upgrade routines to
     * allow other contributed modules that implement said API to upgrade their
     * code.
     *
     * Example: the Views module defines hooks and implements them on behalf of
     * core modules.
     *
     * Strip the module name from the function name and use this as the key in
     * a switch statement. In some cases (e.g. hook_update_N), some additional
     * manipulation and checking needs to be done.
     */
    if (strpos($name, $_coder_upgrade_module_name . '_') !== 0 && strpos($name, 'theme_') !== 0) {
      clp("Ignoring function '$name' as its name does not begin with the module name or 'theme_'");
      continue;
    }

    // By convention, the module name should be followed by an underscore.
    $hook = substr($name, strlen($_coder_upgrade_module_name) + 1);
    cdp("hook = $hook");

    // Update hooks need additional manipulation.
    if (preg_match('@update_\d+$@', $hook, $matches)) {
      $hook = 'update_N';
    }

    // TODO The alter hooks can get the $reader from PGPReader::getInstance();
    // We could do the same in this function.
    drupal_alter('upgrade_hook_' . $hook, $node, $reader);

    if (!isset($item) || !is_object($item) || !($item instanceof PGPClass) || $item->type != T_FUNCTION) {
      continue;
    }
    if (strpos($name, $_coder_upgrade_module_name . '_') !== 0 && strpos($name, 'theme_') !== 0) {
      clp("Ignoring function '$name' as its name does not begin with the module name or 'theme_'");
      continue;
    }
    drupal_alter('upgrade_hook', $node, $reader, $hook);
  }
}

/**
 * Adds the module name to the item array.
 *
 * @param string $dirname
 *   A string of the directory name.
 * @param array $item
 *   Array of a directory containing the files to convert.
 */
function coder_upgrade_module_name($dirname, &$item) {
  // Extensions that indicate a module is present.
  $extensions = array('info', 'module');

  /*
   * Set the module name in case there is no module in the directory (e.g. po
   * or translations).
   *
   * This code assumes at most one module per directory. Absent this condition
   * we have no way of determining the file list for the .info file. This
   * condition does not hold for the devel project which has 4 modules in its
   * top-level directory.
   */
  $item['module'] = '';

  // Loop on files.
  $path = $dirname . '/';
  $files = scandir($path);
  foreach ($files as $file) {
    $file_path = $path . $file;
    if (!is_dir($file_path)) {
      if (in_array(pathinfo($file_path, PATHINFO_EXTENSION), $extensions)) {
        $item['module'] = pathinfo($file_path, PATHINFO_FILENAME);
        break;
      }
    }
  }
}

/**
 * Makes a patch file of the conversion routine changes.
 *
 * @param array $item
 *   Array of the directory containing the files to convert.
 * @param boolean $_coder_upgrade_replace_files
 *   Indicates whether to replace the original files.
 */
function coder_upgrade_make_patch_file($item, $_coder_upgrade_replace_files = FALSE) {
  // Patch directory.
  $patch_dir = coder_upgrade_directory_path('patch');

  // Make a patch file.
  coder_upgrade_log_print("\n*************************");
  coder_upgrade_log_print('Creating a patch file for the directory => ' . $item['old_dir']);
  coder_upgrade_log_print("*************************");
  $patch_filename = $patch_dir . $item['name'] . '.patch';
  // Swap directories if files are replaced.
  $old_dir = $_coder_upgrade_replace_files ? $item['new_dir'] : $item['old_dir'];
  $new_dir = $_coder_upgrade_replace_files ? $item['old_dir'] : $item['new_dir'];
  coder_upgrade_log_print("Making patch file: diff -up -r {$old_dir} {$new_dir} > {$patch_filename}");
  shell_exec("diff -up -r {$old_dir} {$new_dir} > {$patch_filename}");

  // Remove the path strings from the patch file (for usability purposes).
  $old1 = $old_dir . '/';
  $new1 = $new_dir . '/';
  $contents = file_get_contents($patch_filename);
  file_put_contents($patch_filename, str_replace(array($old1, $new1), '', $contents));
}

/**
 * Finds the text of a particular function.
 *
 * This is used with regular expressions, but is obsoleted by the parser.
 *
 * @param string $hook
 *   By default, the suffix of the function name to find.
 *   Example: passing $hook = 'menu' will find a function whose name ends in '_menu'.
 *   When $hook_is_suffix = FALSE, then $hook is the entire function name to find.
 * @param string $file
 *   The file to search.
 * @param boolean $match_all
 *   When TRUE, find all functions with $hook in the name.
 * @param boolean $hook_is_suffix
 *   The $hook is only the suffix of the function name.
 *
 * @return string
 *   The function text.
 */
function coder_upgrade_find_hook($hook, $file, $match_all = FALSE, $hook_is_suffix = TRUE) {
  // Construct pattern based on function parameters.
  $prefix = $hook_is_suffix ? '\w+_' : '';
  $pattern  = '/^function\s*';
//  $pattern .= $hook_is_suffix ? '\w+_' : '';
  $pattern .= $prefix . $hook . '\s*\(.*?(?=(\/\*\*|^function|\z))/ms';

  if ($match_all) {
    preg_match_all($pattern, $file, $matches, PREG_PATTERN_ORDER);
    // This block should be unnecessary with the changes to pattern above.
    if (!isset($matches[0][0])) {
      // Check to see if the function name exists.
      $pattern = '/^function\s*' . $prefix . $hook . '\s*\(/m';
      preg_match($pattern, $file, $matches);
      if (!isset($matches[0])) {
        return array();
      }
      // Find last function in file.
      $pattern = '/^function\s*' . $prefix . $hook . '.*\z/ms';
      preg_match_all($pattern, $file, $matches, PREG_PATTERN_ORDER);
      coder_upgrade_log_print('Primary search failed to find function text for _' . $hook . '. Resorting to secondary pattern to find function.');
    }
    return isset($matches[0]) ? $matches[0] : array();
  }
  else {
    preg_match($pattern, $file, $matches);
    // This block should be unnecessary with the changes to pattern above.
    if (!isset($matches[0])) {
      // Check to see if the function name exists.
      $pattern = '/^function\s*' . $prefix . $hook . '\s*\(/m';
      preg_match($pattern, $file, $matches);
      if (!isset($matches[0])) {
        return '';
      }
      // Find last function in file.
      $pattern = '/^function\s*' . $prefix . $hook . '.*\z/ms';
      preg_match($pattern, $file, $matches);
      coder_upgrade_log_print('Primary search failed to find function text for _' . $hook . '. Resorting to secondary pattern to find function.');
    }
    return isset($matches[0]) ? $matches[0] : '';
  }
}

/**
 * Loops on from and to arrays, converting the text of the subject string.
 *
 * @param string $from
 *   The pattern to search for.
 * @param string $to
 *   The string to replace the pattern with.
 * @param string $subject
 *   The string to search and replace.
 */
function coder_upgrade_do_conversions($from, $to, &$subject) {
  for ($i = 0; $i < count($from); $i++) {
    $subject = preg_replace($from[$i], $to[$i], $subject);
  }
}

/**
 * Saves the regular expression changes back to the file.
 *
 * @param string $cur
 *   The string to search for in $file.
 * @param string $new
 *   The replacement string.
 * @param string $file
 *   The text being replaced (all of or part of a file).
 * @param string $hook
 *   The hook being modified.
 */
function coder_upgrade_save_changes($cur, $new, &$file, $hook) {
  if ($new != $cur) {
    $file = str_replace($cur, $new, $file);
//    coder_upgrade_log_print('Completed conversions for ' . $hook);
  }
}

/**
 * Prints memory usage to log.
 *
 * @param string $step
 *   A string describing the code step when the memory usage is gathered.
 */
function coder_upgrade_memory_print($step) {
  static $path = '';

  if (!$path) {
    $path = coder_upgrade_path('memory');
    // Clearing here works except with run.php which runs in a separate process.
//     coder_upgrade_path_clear('memory');
  }
  coder_upgrade_path_print($path, "\n\n\n====================\n$step");
  coder_upgrade_path_print($path, 'Peak: ' . number_format(memory_get_peak_usage(TRUE), 0, '.', ',') . ' bytes');
  coder_upgrade_path_print($path, 'Curr: ' . number_format(memory_get_usage(TRUE), 0, '.', ',') . ' bytes');
}

/**
 * Prints log information if log flag is on.
 *
 * @param mixed $text
 *   A string, array, or object to print.
 */
function coder_upgrade_log_print($text) {
  global $_coder_upgrade_log;
  static $path = '';

  if (!$_coder_upgrade_log) {
    return;
  }
  if (!$path) {
    $path = coder_upgrade_path('log');
//     coder_upgrade_path_clear('log');
  }
  coder_upgrade_path_print($path, $text);
}

/**
 * Prints debug information if debug flag is on.
 *
 * @param mixed $text
 *   A string, array, or object to print.
 */
function coder_upgrade_debug_print($text) {
  global $_coder_upgrade_debug;
  static $path = '';

  if (!$_coder_upgrade_debug) {
    return;
  }
  if (!$path) {
    $path = coder_upgrade_path('debug');
//     coder_upgrade_path_clear('log');
  }
  coder_upgrade_path_print($path, $text);
}

/**
 * Clears the contents of a file.
 *
 * @param string $type
 *   File type.
 */
function coder_upgrade_path_clear($type = 'debug') {
  file_put_contents(coder_upgrade_path($type), '');
}

/**
 * Prints information to a file.
 *
 * @param string $path
 *   File path.
 * @param mixed $text
 *   A string, array, or object to print.
 */
function coder_upgrade_path_print($path, $text) {
  if ($text instanceof PGPList) {
    $result = file_put_contents($path, $text->print_r(), FILE_APPEND);
  }
  elseif ($text instanceof PGPBase) {
    $result = file_put_contents($path, $text->print_r(), FILE_APPEND);
  }
  elseif ($text instanceof stdClass) {
    $result = file_put_contents($path, print_r($text, 1), FILE_APPEND);
  }
  elseif (is_object($text)) {
    $result = file_put_contents($path, "Unknown object class\n", FILE_APPEND);
  }
  elseif (is_array($text)) {
    $result = file_put_contents($path, print_r($text, 1), FILE_APPEND);
  }
  else {
    $result = file_put_contents($path, $text . "\n", FILE_APPEND);
  }
  if ($result === FALSE) {
    echo "Unable to write to file: $path\n";
  }
}

function clp($text, $description = '') {
  if ($description) {
    $description .= ' ==>'; // Use two '=' so easier to find in file.
    coder_upgrade_log_print($description);
  }
  coder_upgrade_log_print($text);
}

function cdp($text, $description = '') {
  if ($description) {
    $description .= ' ==>'; // Use two '=' so easier to find in file.
    coder_upgrade_debug_print($description);
  }
  coder_upgrade_debug_print($text);
}

function coder_upgrade_class_check($filename) {
  global $_coder_upgrade_class_files;

  // Read the file and copy the contents.
  $snippet = file_get_contents($filename);
  $tokens = token_get_all($snippet);
//   clp($tokens, '$tokens');

  foreach ($tokens as $token) {
    if (is_array($token) && ($token[0] == T_CLASS || $token[0] == T_INTERFACE)) {
      $_coder_upgrade_class_files[] = $filename;
      return;
    }
  }
}
