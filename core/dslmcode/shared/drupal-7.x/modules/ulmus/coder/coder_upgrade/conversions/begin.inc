<?php
/**
 * @file
 * Provides conversion routines applied to the directory before routines are applied to the files.
 *
 * These routines use the grammar parser.
 *
 * The functions in this conversion routine file correspond to topics in the
 * category roadmap at http://drupal.org/node/394070 that are marked with a
 * green check mark in the Upgrade column.
 *
 * Copyright 2009-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Implements hook_upgrade_begin_alter().
 *
 * @param array $item
 *   Array of a directory containing the files to convert.
 */
function coder_upgrade_upgrade_begin_alter($item) {
//  cdp("inside " . __FUNCTION__);
  global $_coder_upgrade_menu_registry;
  if (!$_coder_upgrade_menu_registry) {
    $_coder_upgrade_menu_registry = array();
  }
  // TODO Automatically refresh the theme cache if core upgrades are being run?
  coder_upgrade_cache_theme_registry();
  coder_upgrade_cache_info_hooks($item);
}

/**
 * Caches the theme registry from core files (including disabled modules).
 */
function coder_upgrade_cache_theme_registry() {
  global $_coder_upgrade_theme_registry;

  // If this condition is not met, then the code is being run in a separate
  // process and the core theme information is read from a file.
  if (!$_coder_upgrade_theme_registry) {
    if ($cache = cache_get('upgrade_theme_registry', 'cache')) {
      // @todo Compare mtime of newest core code file to the created timestamp field in the cache.
      if (TRUE || ($cache->created > $mtime_newest_core_file)) {
        $_coder_upgrade_theme_registry = $cache->data;
      }
    }
    else {
      // Cache the theme registry (includes only enabled modules).
      $_coder_upgrade_theme_registry = theme_get_registry();
      if (!$_coder_upgrade_theme_registry) {
        drupal_theme_initialize();
        $_coder_upgrade_theme_registry = theme_get_registry();
      }
      // Build and cache the theme registry for disabled modules.
      $_coder_upgrade_theme_registry += coder_upgrade_theme_build_registry();
      // Store in persistent cache.
      cache_set('upgrade_theme_registry', $_coder_upgrade_theme_registry, 'cache');
    }
  }
}

/**
 * Builds theme registry for disabled core modules.
 *
 * Adapted from _theme_build_registry().
 *
 * @return unknown_type
 */
function coder_upgrade_theme_build_registry() {
  // Get the list of disabled core modules.
  $list = coder_upgrade_module_list(TRUE, 0);

  $cache = array();
  $hook = 'theme';
  // TODO In the D8 release of this module, will need to use the correct file.
  // $hook_info = module_hook_info();
  foreach ($list as $module => $stuff) { // foreach (module_implements('theme') as $module) {
    module_load_include('module', $module);
    if (module_hook($module, $hook)) { // || (isset($hook_info[$hook]['group']) && $include_file = module_load_include('inc', $module, $module . '.' . $hook_info[$hook]['group']) && module_hook($module, $hook))) {
      _theme_process_registry($cache, $module, 'module', $module, $path = drupal_get_path('module', $module));
    }
  }
  return $cache;
}

/**
 * Caches hook_theme() and hook_menu() entries for the modules being converted.
 *
 * @param array $item
 *   Array of a directory containing the files to convert.
 */
function coder_upgrade_cache_info_hooks($item, $recursive = TRUE) {
  global $_coder_upgrade_module_name, $_coder_upgrade_theme_registry, $_coder_upgrade_menu_registry;
  static $ignore = array('.', '..', 'CVS', '.svn');
  static $extensions = array('module', 'inc');

  $dirname = $item['old_dir'];

  // Determine module name.
  coder_upgrade_module_name($dirname, $item);
  $_coder_upgrade_module_name = $item['module'] ? $item['module'] : $_coder_upgrade_module_name;

  // Find hook_theme and hook_menu for this module and cache the results.
  $filenames = scandir($dirname . '/');
  foreach ($filenames as $filename) {
    if (!in_array($filename, $ignore)) {
      if (is_dir($dirname . '/' . $filename)) {
        if ($recursive) {
          // TODO Fix this!!!
          $new_item = array(
            'name' => $item['name'],
            'old_dir' => $dirname . '/' . $filename,
          );
          coder_upgrade_cache_info_hooks($new_item, $recursive);
          // Reset the module name.
          $_coder_upgrade_module_name = $item['module'];
        }
      }
      elseif (in_array(pathinfo($filename, PATHINFO_EXTENSION), $extensions)) {
        $values = array(
          $_coder_upgrade_module_name . '_theme',
          $_coder_upgrade_module_name . '_menu',
        );
        $cur = file_get_contents($dirname . '/' . $filename);
        // Create reader object.
        $reader = PGPReader::getInstance();
        coder_upgrade_memory_print('create reader for file ' . $filename);
        $reader->setSnippet($cur);
//         $reader->addTokenNames(); // @todo This is unnecessary.
        if (FALSE) {
          $reader->buildGrammar();
          coder_upgrade_memory_print('build grammar');
        }
        else {
          $reader->buildSpecific(T_FUNCTION, $values);
          coder_upgrade_memory_print('build specific grammar');
        }

        $functions = $reader->getFunctions();
        foreach ($functions as $function) {
//          cdp("name = {$function->data->name}");
          if ($function->data->name == $_coder_upgrade_module_name . '_theme') {
            $module_theme = @eval($function->data->body->toString());
            foreach ($module_theme as $key => &$value) {
              $value['variables'] = isset($value['arguments']) ? $value['arguments'] : array();
              unset($value['arguments']);
//              $module_theme[$key] = $value;
            }
            $_coder_upgrade_theme_registry = array_merge($_coder_upgrade_theme_registry, $module_theme);
//            break 2;
          }
          elseif ($function->data->name == $_coder_upgrade_module_name . '_menu') {
            coder_upgrade_convert_return($function->data->body, 'menu', '', 1, 1);
//            break 2;
          }
        }
        // Free up memory.
        $reader->reset();
        coder_upgrade_memory_print('reset reader');
      }
    }
  }
}

/**
 * Caches hook_menu() arrays.
 *
 * Save a list of form callback routines (including arguments to drupal_get_form()).
 *
 * @param PGPNode $node
 *   The node of the statement containing the array object.
 * @param PGPArray $array2
 *   The array object containing the array element ($current2).
 * @param PGPNode $current2
 *   The node object of the array element.
 * @param string $hook
 *   The hook name.
 * @param string $type
 *   The type (key or value) of the array element.
 * @param string $key
 *   The key of the array element (or the most recent key).
 * @param string $value
 *   The value of the array element (or NULL if element is a key).
 */
function coder_upgrade_callback_menu($node, &$array2, &$current2, $hook, $type, $key, $value) { // NOT DONE
  global $_coder_upgrade_menu_registry;

  if (!($current2 instanceof PGPNode)) {
    clp("ERROR: current2 is not a PGPNode object in hook_$hook");
    return;
  }

//   $editor = PGPEditor::getInstance(); // @todo Not used.

  /*
   * With a nice array that includes all the menu items, we can check for a
   * page callback of 'drupal_get_form'. However, this is a default and could
   * be omitted. But because there could be 'funny' code such as inside the
   * foreach loop in our example function, we do not have an easy way to
   * determine if the menu item is a callback to be changed.
   *
   * Unlike other uses for this pattern, get in on the first call, do our
   * business, and then set the array pointer to the last item to avoid
   * redundant looping.
   */

  $callback = $array2->findValue('page callback');
  $arguments = $array2->findValue('page arguments');
  if ($callback && trim($callback->toString(), "'\"") == 'drupal_get_form') {
    if ($arguments) {
      $operand = $arguments->getElement();
      if ($arguments->isType(T_ARRAY)) {
        $form = trim($operand->getValue()->toString(), "'\"");
        $_coder_upgrade_menu_registry[] = $form;
      }
      elseif ($arguments->isType(T_CONSTANT_ENCAPSED_STRING)) {
        $form = trim($arguments->toString(), "'\"");
        $_coder_upgrade_menu_registry[] = $form;
      }
    }
  }
  elseif ($callback) {
    // These callbacks are not affected by this change.
//    $form = trim($callback->toString(), "'\"");
//    $_coder_upgrade_menu_registry[] = $form;
  }
  elseif ($arguments) {
    // Depending on the code style, some of these will include callbacks.
    // But we can not be sure. Check for first parameter being $form_state.
    $operand = $arguments->getElement();
    if ($arguments->isType(T_ARRAY)) {
      $form = trim($operand->getValue()->toString(), "'\"");
      $_coder_upgrade_menu_registry[] = $form;
    }
    elseif ($arguments->isType(T_CONSTANT_ENCAPSED_STRING)) {
      $form = trim($arguments->toString(), "'\"");
      $_coder_upgrade_menu_registry[] = $form;
    }
  }
  // Set $current2 to last item in list to avoid redundant looping.
  $current2 = $array2->values->last();
}
