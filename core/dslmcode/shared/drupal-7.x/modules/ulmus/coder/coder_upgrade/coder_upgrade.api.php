<?php
/**
 * @file
 * Documents hooks provided by this module.
 *
 * Copyright 2009-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Declares upgrade sets for an API (or set of APIs).
 *
 * This hook allows contributed modules to declare upgrade sets for an API
 * supplied by their module, another contributed module, or a core module. To be
 * able to apply the upgrade routines independently, the upgrade routines should
 * be contained in separate files.
 *
 * For example, if your module is called 'your_module_name' and its upgrade
 * routines are in 'your_module_name.upgrade' (the default file name), then
 * declare an upgrade set as:
 * @code
 *   function your_module_name_upgrade_info() {
 *     $upgrade = array(
 *       'title' => t('Your module API changes from 6.x to 7.x'),
 *       'link' => 'http://...',
 *     );
 *     return array('your_module_name' => $upgrade);
 *   }
 * @endcode
 *
 * @return
 *   An associative array (keyed on the upgrade name) with each element being an
 *   associative array with the following elements:
 *   - 'title': A description of the upgrade routines provided by the upgrade set.
 *   - 'link': An optional link to an issue describing the upgrade routines.
 *   - 'module': The name of the module providing the upgrade routines.
 *   - 'files': An optional array of file names containing the upgrade routines.
 *     The name includes any relative path inside the module directory. Defaults
 *     to 'your_module_name.upgrade'.
 */
function hook_upgrade_info() {
  $upgrade = array(
    'title' => t('Your module API changes from 6.x to 7.x'),
    'link' => 'http://...',
    'module' => 'your_module_name',
    'files' => array(
      'upgrades/your_module_name.upgrade',
    ),
  );
  return array('your_upgrade_name' => $upgrade);
}

/**
 * Alters a function call using the grammar parser.
 *
 * This hook allows contributed modules to alter a function call object using
 * the grammar parser. The function call may be a stand-alone statement or part
 * of an expression in another statement. For example:
 * @code
 *   foo($bar); // Stand-alone.
 *   if (foo($bar)) { // Embedded.
 *     // Do something.
 *   }
 * @endcode
 *
 * Coder Upgrade will call this alter hook for each function call in the file
 * that was parsed. However, the function name must be a string, not a variable
 * expression. To modify the latter, use hook_upgrade_file_alter(). Refer to the
 * grammar parser documentation for details of the function call object.
 *
 * @see hook_upgrade_file_alter()
 * @see PGPFunctionCall
 *
 * @param PGPFunctionCall $node
 *   A node object containing a function call object.
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function hook_upgrade_call_FUNCTION_NAME_alter(&$node, &$reader) {
  // Get the function call object.
  $item = &$node->data;

  // Change the function name.
  $item->name['value'] = 'new_name';

  if ($item->parameterCount() > 0) {
    // Delete the first parameter.
    $item->deleteParameter();
  }
}

/**
 * Alters function calls using the grammar parser.
 *
 * This hook allows contributed modules to alter any function call object using
 * the grammar parser. The function call may be a stand-alone statement or part
 * of an expression in another statement. For example:
 * @code
 *   foo($bar); // Stand-alone.
 *   if (foo($bar)) { // Embedded.
 *     // Do something.
 *   }
 * @endcode
 *
 * Coder Upgrade will call this alter hook for each function call in the file
 * that was parsed. However, the function name must be a string, not a variable
 * expression. To modify the latter, use hook_upgrade_file_alter(). Refer to the
 * grammar parser documentation for details of the function call object.
 *
 * @see hook_upgrade_file_alter()
 * @see PGPFunctionCall
 *
 * @param PGPFunctionCall $node
 *   A node object containing a function call object.
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 * @param $name
 *   The name of the function.
 */
function hook_upgrade_call_alter(&$node, &$reader, $name) {
  // Get the function call object.
  $item = &$node->data;

  // Modify the function call.
  switch ($name) {
    case 'foo':
      $item->deleteParameter();
      break;

    default:
      break;
  }
}

/**
 * Alters a hook function using the grammar parser.
 *
 * This hook allows contributed modules to alter a function object using the
 * grammar parser. The function block may be inside an interface or class, or a
 * stand-alone statement block. For example:
 * @code
 *   function foo($bar) { // Stand-alone.
 *     if ($bar) {
 *       // Do something.
 *     }
 *   }
 *   class example {
 *     function foo($bar) { // Embedded.
 *       if ($bar) {
 *         // Do something.
 *       }
 *     }
 *   }
 * @endcode
 *
 * Coder Upgrade will call this alter hook for each hook function in the file
 * that was parsed. However, the function name must follow the naming convention
 * for a hook, i.e, your_module_name_hook. If your module declares a hook for
 * another module or otherwise digresses from the standard naming convention,
 * then use hook_upgrade_file_alter() to alter this function.
 *
 * Refer to the grammar parser documentation for details of the function object
 * (i.e. PGPClass).
 *
 * @see hook_upgrade_file_alter()
 * @see PGPClass
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function hook_upgrade_hook_HOOK_NAME_alter(&$node, &$reader) {
  global $_coder_upgrade_module_name;

  // Get the function object.
  $item = &$node->data;

  // Rename the function.
  $item->name = $_coder_upgrade_module_name . '_new_hook_name';
  // Update the document comment.
  $item->comment['value'] = preg_replace('@\* Implement\s+@', "* Implements ", $item->comment['value']);

  if ($item->parameterCount() > 1) {
    // Switch the first two parameters.
    $p0 = $item->getParameter(0);
    $p1 = $item->getParameter(1);
    $item->setParameter(0, $p1);
    $item->setParameter(1, $p0);
  }
}

/**
 * Alters hook functions using the grammar parser.
 *
 * This hook allows contributed modules to alter any function object using the
 * grammar parser. The function block may be inside an interface or class, or a
 * stand-alone statement block. For example:
 * @code
 *   function foo($bar) { // Stand-alone.
 *     if ($bar) {
 *       // Do something.
 *     }
 *   }
 *   class example {
 *     function foo($bar) { // Embedded.
 *       if ($bar) {
 *         // Do something.
 *       }
 *     }
 *   }
 * @endcode
 *
 * Coder Upgrade will call this alter hook for each hook function in the file
 * that was parsed. However, the function name must follow the naming convention
 * for a hook, i.e, your_module_name_hook. If your module declares a hook for
 * another module or otherwise digresses from the standard naming convention,
 * then use hook_upgrade_file_alter() to alter this function.
 *
 * Refer to the grammar parser documentation for details of the function object
 * (i.e. PGPClass).
 *
 * @see hook_upgrade_file_alter()
 * @see PGPClass
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 * @param $hook
 *   The name of the function (excluding the module name).
 */
function hook_upgrade_hook_alter(&$node, &$reader, &$hook) {
  global $_coder_upgrade_module_name;

  // Get the function object.
  $item = &$node->data;

  // Modify hook function.
  switch ($hook) {
    case 'old_hook_name':
      // Rename the function.
      $item->name = $_coder_upgrade_module_name . '_new_hook_name';
      // Update the document comment.
      $item->comment['value'] = preg_replace('@\* Implement\s+@', "* Implements ", $item->comment['value']);

      if ($item->parameterCount() > 1) {
        // Switch the first two parameters.
        $p0 = $item->getParameter(0);
        $p1 = $item->getParameter(1);
        $item->setParameter(0, $p1);
        $item->setParameter(1, $p0);
      }
      break;

    default:
      break;
  }
}

/**
 * Alters a code file using the grammar parser.
 *
 * This hook allows contributed modules to alter a code file object using the
 * grammar parser. If a module defines a class, then the calls to its methods
 * are not included in the calls to hook_upgrade_hook_HOOK_NAME_alter or
 * hook_upgrade_hook_alter.
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function hook_upgrade_file_alter(&$reader) {
  /*
   * Task: Modify calls to class methods.
   */

  // Get list of function calls (including the calls to class methods).
  $nodes = &$reader->getFunctionCalls();
  // Loop on list.
  foreach ($nodes as &$node) {
    // Get the function call object.
    $item = &$node->data;
    if (!isset($item) || !is_object($item) || !($item instanceof PGPFunctionCall) || $item->type != T_FUNCTION_CALL) {
      /*
       * These checks are necessary as the reference (i.e. $item) could have
       * been changed in another routine so that it no longer refers to a
       * function call object.
       */
      continue;
    }

    /*
     * To be a call to a class method, the function name must be an expression
     * like $this->foo() as opposed to a string or a single variable. This code
     * checks the name is an expression (using is_a($item->name, 'PGPOperand'))
     * and the value element of the name object is '$this'.
     *
     * Review the grammar structure object using $item->print_r().
     */
    if ($item->name instanceof PGPOperand && $item->name->findNode('value') == '$this') {
      // Strip '$this->' from the name.
      $name = substr($item->name->toString(), 7);
      // Modify the function call
      my_module_convert_method($item, $reader, $name);
    }
  }
}

/**
 * Alters an install file using the grammar parser.
 *
 * This hook allows contributed modules to alter an install file object using
 * the grammar parser. This hook allows for segregation of upgrade routines that
 * only apply to an install file (e.g. the database schema API).
 *
 * @see hook_upgrade_file_alter()
 * @see hook_upgrade_hook_HOOK_NAME_alter()
 * @see hook_upgrade_hook_alter()
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function hook_upgrade_parser_install_alter(&$reader) {
  // Do something to the file.
}

/**
 * Processes the directory before upgrade routines are applied.
 *
 * This hook can be used to cache information needed by other routines. For
 * example, core changes need to know about hook_theme or hook_menu to make
 * theme changes and form API changes.
 *
 * @param array $item
 *   Array of a directory containing the files to convert.
 */
function hook_upgrade_begin_alter($item) {
  // Do something.
}

/**
 * Processes the directory after upgrade routines are applied.
 *
 * This hook can be used to apply finishing touches to the directory of
 * converted files. For example, a D7 core change is to add file entries to
 * the .info files.
 *
 * @param string $dirname
 *   The name of the directory with the converted files.
 */
function hook_upgrade_end_alter($dirname) {
  // Do something.
}

/**
 * Alters the text of a code file using regular expressions.
 *
 * @param string $file
 *   The text of the file to convert.
 */
function hook_upgrade_regex_alter(&$file) {
  $hook = 'your_changes'; // Used as the label in the log file.
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  // Do something to $file.
  $from[] = '/(your_module_name)/';
  $to[] = "$1";

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}

/**
 * Alters the text of an info file using regular expressions.
 *
 * @param string $file
 *   The text of the file to convert.
 */
function hook_upgrade_regex_info_alter(&$file) {
  $hook = 'info_file'; // Used as the label in the log file.
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  // Info file should specify core = 7.x.
  $from[] = '@^core\s+=\s+.*?$@m';
  $to[] = 'core = 7.x';

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}

/**
 * Alters the text of an install file using regular expressions.
 *
 * @param string $file
 *   The text of the file to convert.
 */
function hook_upgrade_regex_install_alter(&$file) {
  $hook = 'info_file'; // Used as the label in the log file.
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  // Do something to $file.
  $from[] = '/(your_module_name)/';
  $to[] = "$1";

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}

/**
 * @} End of "addtogroup hooks".
 */

/**
 * Sample functions.
 *
 * To use the sample functions included in this api file:
 * - Copy and paste the sample functions to a file in your module.
 * - Replace "your_module_name" with your actual module name.
 * - Replace "function_name" and "hook_name" with actual names.
 * - Complete the conversions_list() routine.
 * - Duplicate the sample conversion routine for each entry in your list,
 *   replacing "your_routine_name" with the appropriate value and changing the
 *   comment block to describe the upgrade applied by the routine.
 */

/**
 * Implements hook_upgrade_info().
 */
function your_module_name_upgrade_info() {
  $upgrade = array(
    'title' => t('Your module API changes from 6.x to 7.x'),
    'link' => 'http://...',
    'files' => array(
      'upgrades/your_module_name.upgrade',
    ),
  );
  return array('your_module_name' => $upgrade);
}

/**
 * Implements hook_upgrade_call_FUNCTION_NAME_alter().
 */
function your_module_name_upgrade_call_function_name_alter(&$node, &$reader) {
  // Get the function call object.
  $item = &$node->data;

  // Change the function name.
  $item->name['value'] = 'new_name';

  if ($item->parameterCount() > 0) {
    // Delete the first parameter.
    $item->deleteParameter();
  }
}

/**
 * Implements hook_upgrade_hook_HOOK_NAME_alter().
 */
function your_module_name_upgrade_hook_hook_name_alter(&$node, &$reader) {
  global $_coder_upgrade_module_name;

  // Get the function object.
  $item = &$node->data;

  // Rename the function.
  $item->name = $_coder_upgrade_module_name . '_new_hook_name';
  // Update the document comment.
  $item->comment['value'] = preg_replace('@\* Implement\s+@', "* Implements ", $item->comment['value']);

  if ($item->parameterCount() > 1) {
    // Switch the first two parameters.
    $p0 = $item->getParameter(0);
    $p1 = $item->getParameter(1);
    $item->setParameter(0, $p1);
    $item->setParameter(1, $p0);
  }
}

/**
 * Implements hook_upgrade_regex_alter().
 */
function your_module_name_upgrade_regex_alter(&$file) {
  $hook = 'your_changes'; // Used as the label in the log file.
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  // Do something to $file.
  $from[] = '/(your_module_name)/';
  $to[] = "$1";

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}

/**
 * Implements hook_upgrade_regex_info_alter().
 */
function your_module_name_upgrade_regex_info_alter(&$file) {
  $hook = 'info_file';
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  // Info file should specify core = 7.x.
  $from[] = '@^core\s+=\s+.*?$@m';
  $to[] = 'core = 7.x';

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}
