<?php
/**
 * @file
 * Other conversion routine file for the coder_upgrade module.
 *
 * The functions in these conversion routine files correspond to the topics in
 * the category roadmap at http://drupal.org/node/394070 that are marked with
 * a green check mark in the Upgrade column.
 *
 * Copyright 2008-9 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Upgrades function calls using grammar parser.
 *
 * System
 * http://drupal.org/node/224333#registry
 * http://drupal.org/node/224333#drupal_set_session (REVERTED)
 * http://drupal.org/node/224333#time
 * http://drupal.org/node/224333#rebuild_functions
 * http://drupal.org/node/224333#drupal_uninstall_modules
 * http://drupal.org/node/224333#module_implements_not_module_list
 * http://drupal.org/node/224333#drupal_http_request_parameters
 * http://drupal.org/node/224333#system_get_module_data
 * http://drupal.org/node/224333#static_variable_api (NOT IN THIS FUNCTION)
 * http://drupal.org/node/224333#drupal_set_html_head
 * http://drupal.org/node/224333#php_eval
 * http://drupal.org/node/224333#http_header_functions
 * http://drupal.org/node/224333#drupal_set_content
 * http://drupal.org/node/224333#time_limit
 *
 *
 * Database
 * http://drupal.org/node/224333#schema_ret
 *
 *
 * Menu
 * http://drupal.org/node/224333#comment_load (DUP Comments)
 *
 *
 * Comments
 * http://drupal.org/node/224333#comment_load
 * http://drupal.org/node/224333#comment_validate_removed
 * http://drupal.org/node/224333#comment_node_url
 *
 *
 * Input Sanitization and Input Formats
 * http://drupal.org/node/224333#check_markup_params
 * http://drupal.org/node/224333#drupal_set_title
 * http://drupal.org/node/224333#hook_filter_info (NOT IN THIS FUNCTION)
 * http://drupal.org/node/224333#filter_formats_parameters
 *
 *
 * Taxonomy
 * http://drupal.org/node/224333#taxonomy_get_tree
 * http://drupal.org/node/224333#taxonomy_crud
 *
 *
 * Javascript
 * http://drupal.org/node/224333#drupal_add_js_options
 * http://drupal.org/node/224333#drupal_add_js_weight (Included with above)
 * http://drupal.org/node/224333#rename-drupal-to-js
 *
 *
 * CSS
 * http://drupal.org/node/224333#drupal_add_js_options (DUP Javascript)
 *
 *
 * Theming
 * http://drupal.org/node/224333#rebuild_functions (DUP System)
 * http://drupal.org/node/224333#theme_changes
 *
 *
 * Form API
 * http://drupal.org/node/224333#drupal_execute_drupal_form_submit
 *
 *
 * File API
 * http://drupal.org/node/224333#file_set_status
 * http://drupal.org/node/224333#preg_match
 *
 *
 * User API
 * http://drupal.org/node/224333#user_cancel (ALSO in convert_functions)
 * http://drupal.org/node/224333#user_authenticate
 *
 *
 * Multi-lingual
 * http://drupal.org/node/224333#locale_context
 *
 *
 * Miscellaneous
 * http://drupal.org/node/224333#book_toc_parameters
 * http://drupal.org/node/224333#referer_uri
 * http://drupal.org/node/224333#drupal_clone
 * http://drupal.org/node/224333#actions_synchronize
 * http://drupal.org/node/224333#url_is_external
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_convert_function_calls(&$reader) {
  cdp("inside " . __FUNCTION__);
  $editor = new PGPEditor();
  $types = array(T_STRING);
  $editor->traverseCallback($reader->getFunctionCalls(), 'coder_upgrade_callback_function_calls', $types, $reader);
}

/**
 * Callback routine for function call changes using grammar parser.
 *
 * Programmatically changing the source code requires changing the contents of
 * the grammar object (the grammar equivalent of the code represented as a
 * PGPList of statements). A difficult way to do this would be to manually
 * create items (arrays or objects extended from the PGPBase class) and replace
 * the existing grammar items with the new items. This would essntially
 * duplicate the functionality of the PGPReader class.
 *
 * A simpler approach takes advantage of the grammar parser API which provides
 * helper functions for working with function call objects. Some examples of
 * typical tasks follow.
 *
 * Print a grammar object
 *
 * Before making a change, it is a good idea to print the contents of the
 * grammar object to become familiar with its structure and contents. PGP
 * provides a custom print_r function for this purpose. (NOTE: calls to the
 * built-in print_r, var_dump or equivalent routines for this purpose is not
 * recommended as the output may be extremely voluminous.) All of the objects
 * (as opposed to array items) can be printed using the custom print_r routine.
 * An array item can be printed using the built-in print_r routine.
 * @code
 *   // Print the grammar item (a function call object in this case).
 *   cdp($item->print_r());
 *
 *   // Print the parameters to the function call.
 *   cdp($item->parameters->print_r());
 *   // Alternatively, with a parameters object, do this.
 *   $parameters = $item->parameters;
 *   cdp($parameters->print_r());
 * @endcode
 *
 * Change the name of the function being called
 * @code
 *   // Change the name of the function being called.
 *   $name['value'] = 'new_function_name';
 * @endcode
 *
 * Get a parameter object and an expression object
 * @code
 *   // Get a parameter object (PGPExpression).
 *   $param = $item->getParameter(0);
 *
 *   // Get the first element of the parameter expression (PGPOperand or array).
 *   $element = $param->getElement(0);
 * @endcode
 *
 * Reorder the parameters
 * @code
 *  // Save the current parameters to local variables.
 *  $p0 = $item->getParameter(0);
 *  $p0 = $item->getParameter(1);
 *
 *  // Swap the parameters.
 *  $item->setParameter(0, $p1);
 *  $item->setParameter(1, $p0);
 * @endcode
 *
 * Insert or delete a parameter object
 * @code
 *   $item->insertParameter(2, $expression);
 *   $item->deleteParameter(2);
 * @endcode
 *
 * Set grammar elements from a string of code
 *
 * As mentioned above, it is not recommended to manually create items (arrays
 * or objects extended from the PGPBase class) and replace the existing grammar
 * items with the new items. A simpler approach is to create the string of code
 * to be inserted and use the PGPEditor class to convert this string to its
 * grammar representation.
 *
 * @code
 *  // Set a single parameter from a string of code.
 *  $editor->setParameter($item, 0, $code);
 *
 *  // Set all of the parameters from an array of code strings.
 *  $editor->setParameters($item, array('$form', '$form_state'));
 *
 *  // Insert a parameter from a string of code.
 *  $editor->insertParameter($item, 2, '$langcode = \'en\'');
 * @endcode
 *
 * Get grammar elements as a string of code
 *
 * @code
 *  // Print a parameter (i.e. convert it from a grammar object to a string).
 *  $parameter = $item->printParameter(1);
 *
 *  // Get the grammar equivalent of a string of code.
 *  $expression = $editor->expressionToStatement($string);
 * @endcode
 *
 * Other debug print examples.
 *
 * @code
 * cdp($list->printNode($parent));
 * cdp($list->printArray($parent));
 * cdp($list->printArray($temp->getElement(0)));
 * cdp($list->printNode($temp->get(0)));
 * @endcode
 *
 * @param PGPFunctionCall $item
 *   A function call object of the expression or statement.
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_callback_function_calls(&$item, &$reader) {
  cdp("inside " . __FUNCTION__);
//  cdp($item->print_r());

  /*
   * The $item variable passed to this function is a PGPFunctionCall object.
   * When passed here via the coder_upgrade_convert_function_calls routine, the
   * variable was an entry in the function calls array filled by the PGPReader
   * class (and accessed as $reader->getFunctionCalls()).
   *
   * The function calls array contains references to PGPFunctionCall objects.
   * As these objects are processed, they may change or eliminate other
   * references yet to be processed (i.e. if other function call references
   * are contained in the current reference). Because of this, we need to
   * test whether $item actually refers to a PGPFunctionCall object before
   * attempting to do any processing.
   */
  if (!isset($item) || !is_a($item, 'PGPFunctionCall')) {
    return;
  }

  // Create helper objects.
  $editor = new PGPEditor();
  $list = new PGPList();

  // Process function call.
  $name = &$item->name;
  switch ($name['value']) {
    case 'actions_synchronize': // DONE
      $count = $item->parameters->count();
      if ($count > 0) {
        $item->deleteParameter();
      }
      break;

    case 'book_toc': // DONE
      // Adjust parameters.
      $count = $item->parameters->count();
      if ($count > 2) {
        // Switch places.
        $p1 = $item->getParameter(1);
        $p2 = $item->getParameter(2);
        $item->setParameter(1, $p2);
        $item->setParameter(2, $p1);
      }
      // Remove default parameter.
      if ($count == 3) {
        $value = $item->printParameter(2);
        cdp("value = $value");
        if ($value == 'array()') {
          $item->deleteParameter(2);
        }
      }
      break;

    case 'check_markup': // DONE
      if ($item->parameters->count() > 2) {
        $editor->insertParameter($item, 2, '$langcode = \'\' /* TODO Set this variable. */');
      }
      break;

    case '_comment_load': // DONE
      // TODO The comment_wildcard change in hook_menu.
      $name['value'] = 'comment_load';
      break;

    case 'comment_node_url': // DONE
      $parent = $item->parent;
      $temp = $editor->statementsToText($parent);
      $from = '@comment_node_url()@';
      $to = "'comment/' . \$comment->cid";
      $temp = preg_replace($from, $to, $temp);
      $temp = $editor->textToStatements($temp);
      $parent->data = $temp->getElement(0);
      break;

    case 'comment_validate': // DONE
      $name['value'] = 'comment_form_validate';
      $editor->setParameters($item, array('$form', '$form_state /* TODO Set these variables. */'));
      break;

    case 'db_add_field':
      // includes/database.pgsql.inc Add a new field to a table.
    case 'db_add_index':
      // includes/database.pgsql.inc Add an index.
    case 'db_add_primary_key':
      // includes/database.pgsql.inc Add a primary key.
    case 'db_add_unique_key':
      // includes/database.pgsql.inc Add a unique key.
    case 'db_change_field':
      // includes/database.pgsql.inc Change a field definition.
    case 'db_create_table':
      // includes/database.inc Create a new table from a Drupal table definition.
    case 'db_create_table_sql':
      // includes/database.pgsql.inc Generate SQL to create a new table from a Drupal schema definition.
    case 'db_drop_field':
      // includes/database.pgsql.inc Drop a field.
    case 'db_drop_index':
      // includes/database.pgsql.inc Drop an index.
    case 'db_drop_primary_key':
      // includes/database.pgsql.inc Drop the primary key.
    case 'db_drop_table':
      // includes/database.pgsql.inc Drop a table.
    case 'db_drop_unique_key':
      // includes/database.pgsql.inc Drop a unique key.
    case 'db_field_names':
      // includes/database.inc Return an array of field names from an array of key/index column specifiers.
    case 'db_field_set_default':
      // includes/database.pgsql.inc Set the default value for a field.
    case 'db_field_set_no_default':
      // includes/database.pgsql.inc Set a field to have no default value.
    case 'db_rename_table':
      // includes/database.pgsql.inc Rename a table.
      $item->deleteParameter();
      break;

    case 'drupal_add_css': // DONE
      // A similar comment to that in 'drupal_add_js' below applies here.
      cdp($item->parameters->print_r());

      $count = $item->parameters->count();
      if ($count < 3) {
        $type = trim($item->printParameter(1), "'\"");
        if (in_array($type, array('module', 'theme'))) {
          $editor->setParameter($item, 1, "'file'"); // Could simply delete it.
        }
        break;
      }

      $keys = array('type', 'media', 'preprocess');
      $defaults = array("'module'", "'all'", 'TRUE');
      $string = $editor->arrayitize($item, 1, $keys, $defaults);
      $string = preg_replace('@[\'"]theme[\'"]@', "'file'", $string); // Could be deleted.

      if ($string != 'array()') {
        $temp = $editor->expressionToStatement($string);
        $temp->getElement(0)->multiline = 0;
        cdp($temp->print_r());
        $item->setParameter(1, $temp);
      }
      break;

    case 'drupal_add_js': // DONE
      /*
       * With
       * drupal_add_js('misc/collapse.js', 'core', 'header', FALSE, TRUE, TRUE);
       * we will output
       * drupal_add_js('misc/collapse.js', array(
       *   'type' => 'core',
       * ));
       * which is correct, although the function will also accept
       * drupal_add_js('misc/collapse.js', 'core');
       * The example begs the question why someone would have included all
       * the default parameters.
       *
       * A type of 'core', 'module' or 'theme' all convert to 'file' which is
       * the new default. We could add a weight item based on the type?
       */
      cdp($item->parameters->print_r());

      $count = $item->parameters->count();
      if ($count < 3) {
        $type = trim($item->printParameter(1), "'\"");
        if (in_array($type, array('core', 'module', 'theme'))) {
          $editor->setParameter($item, 1, "'file'"); // Could simply delete it.
        }
        break;
      }

      $keys = array('type', 'scope', 'defer', 'cache', 'preprocess');
      $defaults = array("'module'", "'header'", 'FALSE', 'TRUE', 'TRUE');
      $string = $editor->arrayitize($item, 1, $keys, $defaults);
      $string = preg_replace('@[\'"](core|theme)[\'"]@', "'file'", $string); // Could be deleted.

      if ($string != 'array()') {
        $temp = $editor->expressionToStatement($string);
        $temp->getElement(0)->multiline = 0;
        cdp($temp->print_r());
        $item->setParameter(1, $temp);
      }
      break;

    case 'drupal_clone': // DONE
      $name['value'] = 'clone';
      $item->noparens = 1;
      break;

    case 'drupal_eval': // DONE
      /*
       * Examine the statement containing the function call.
       * Wrap the containing statement in an "if (module_exists('php'))" block.
       * The function call may be the containing statement.
       */

      // Set the name of the function call.
      $name['value'] = 'php_eval';

      // Get the parent = statement (i.e. node) this function call is part of.
      $parent = $item->parent;
      $temp = $editor->statementsToText($parent);
      $temp = $editor->textToStatements("if (module_exists('php')) {\n\t$temp\n}");
      $parent->data = $temp->getElement(0);
      break;

    case 'drupal_execute': // DONE
      $name['value'] = 'drupal_form_submit';
      break;

    case 'drupal_get_content': // DONE
      $name['value'] = 'drupal_get_region_content';
      break;

    case 'drupal_get_headers': // DONE
      $name['value'] = 'drupal_get_header';
      break;

    case 'drupal_http_request': // DONE
      cdp($item->parameters->print_r());

      $count = $item->parameters->count();
      if ($count == 1) {
        break;
      }

      $keys = array('headers', 'method', 'data', 'max_redirects');
      $defaults = array('xxx_YYY_zzz', "'GET'", 'NULL', 3);
      $string = $editor->arrayitize($item, 1, $keys, $defaults);

      $temp = $editor->expressionToStatement($string);
      $temp->getElement(0)->multiline = 0;
      cdp($temp->print_r());
      $item->setParameter(1, $temp);
      break;

    case 'drupal_json': // DONE
      $name['value'] = 'drupal_json_output';
      break;

    case 'drupal_rebuild_code_registry': // DONE
      $name['value'] = 'registry_rebuild';
      break;

    case 'drupal_rebuild_theme_registry': // DONE
      $name['value'] = 'drupal_theme_rebuild';
      break;

    case 'drupal_set_content': // DONE
      $name['value'] = 'drupal_add_region_content';
      break;

    case 'drupal_set_header': // DONE
      // TODO the hook_file_download() changes. Use parser on the entire function.
      $temp = $item->printParameters();
      if (strpos($temp, 'Content-Type:') !== FALSE) {
        $temp = explode(':', $temp);
        foreach ($temp as $key => $string) {
          $temp[$key] = "'" . trim($string, "' ") . "'";
        }
        $editor->setParameters($item, $temp);
      }
      elseif (strpos($temp, "\$_SERVER['SERVER_PROTOCOL']") !== FALSE ||
              strpos($temp, '\$_SERVER["SERVER_PROTOCOL"]') !== FALSE) {
        $from = '@\$_SERVER\[(\'|")SERVER_PROTOCOL(\'|")\]\s*\.\s*(\'|")\s*(.*?)(\'|")@';
        $to = "$3$4$3";
        $temp = preg_replace($from, $to, $temp);
        $editor->setParameters($item, array($temp));
      }
      break;

    case 'drupal_set_html_head': // DONE
      $name['value'] = 'drupal_add_html_head';
      break;

    case 'drupal_set_title': // DONE
      $temp = $item->printParameters();
      cdp("temp = $temp");

      if (strpos($temp, 'check_plain') !== FALSE) {
        // TODO Could check for isset, count of parameters, etc.???
        // check_plain could be part of an expression (e.g. concatenation).
        $temp = $item->getParameter(0);
        $temp = $temp->getElement(0);
        cdp("Printing the first ");
        cdp($temp->print_r());
        $editor->setParameter($item, 0, $temp->printParameter(0));
        cdp($item->print_r());
        break;
      }
      $parameters = &$item->parameters;
      if ($call = &$parameters->search($parameters, 'PGPFunctionCall', 'name', 'value', 't')) {
        $temp = $call->toString();
        cdp("temp = $temp");
        if (preg_match('#(\'|")@\w+(\'|")\s*=>\s*#', $temp)) {
          $editor->setParameter($item, 1, 'PASS_THROUGH');
          cdp($item->print_r(0, $item));
        }
      }
      break;

    case 'drupal_system_listing': // DONE
      $temp = $item->printParameter(0);
      // Check for type == T_CONSTANT_ENCAPSED_STRING
      // Check for a '/' in the mask and use a different mask or delimit the '/' with '\/'.
      if ($temp[0] == "'") {
        $editor->setParameter($item, 0, "'/" . substr($temp, 1, -1) . "/'");
      }
      elseif ($temp[0] == '"') {
        $editor->setParameter($item, 0, '"/' . substr($temp, 1, -1) . '/"');
      }
      // else if type == T_VARIABLE, find the $mask used in the call and examine its value.
      break;

    case 'drupal_to_js': // DONE
      $name['value'] = 'drupal_json_encode';
      break;

    case 'drupal_uninstall_module': // DONE
      $name['value'] = 'drupal_uninstall_modules';
      $temp = $item->printParameters();
      $editor->setParameters($item, array('array(' . $temp . ')'));
      break;

    case 'file_scan_directory': // DONE
      // TODO Part of http://drupal.org/node/224333#preg_match
      // TODO Other changes apply to this function call.
      $temp = $item->printParameter(1);
      // Check for type == T_CONSTANT_ENCAPSED_STRING
      // Check for a '/' in the mask and use a different mask or delimit the '/' with '\/'.
      if ($temp[0] == "'") {
        $editor->setParameter($item, 1, "'/" . substr($temp, 1, -1) . "/'");
      }
      elseif ($temp[0] == '"') {
        $editor->setParameter($item, 1, '"/' . substr($temp, 1, -1) . '/"');
      }
      // else if type == T_VARIABLE, find the $mask used in the call and examine its value.
      break;

    case 'file_set_status': // DONE
      if ($item->parameters->count() == 2) {
        $p0 = $item->printParameter(0);
        $p1 = $item->printParameter(1);

        // Insert statement.
        $temp = $editor->textToStatements("{$p0}->status &= $p1");
        $parent = $item->parent;
        $parent->container->insertBefore($parent, $temp->getElement(0));

        // Change statement.
        $from = $temp1;
        $to = "$p0 = file_save($p0)";
        $temp = str_replace($from, $to, $temp2);
        $temp = $editor->textToStatements($temp);
        $parent->data = $temp->getElement(0);
      }
      break;

    case 'filter_formats': // DONE
      // If has a parameter, then change it to $user and add global statement.
      if ($item->parameters->count() > 0) {
        $p0 = $editor->expressionToStatement('$user');
        $item->setParameter(0, $p0);

        // Get the parent = statement (i.e. node) this function call is part of.
        $parent = &$item->parent;
        // Get the statement list the parent is part of.
        $container = &$parent->container;
        // Insert a statement.
        $statement = $editor->textToStatements("global \$user;")->getElement(0);
        $container->insertBefore($parent, $statement, 'global');
      }
      break;

    case 'format_plural': // DONE
      $count = $item->parameters->count();
      if ($count < 5) {
        break;
      }

      $keys = array('langcode');
      $defaults = array("'XXX_YYY'");
      $string = $editor->arrayitize($item, 4, $keys, $defaults);

      $temp = $editor->expressionToStatement($string);
      $temp->getElement(0)->multiline = 0;
      cdp($temp->print_r());
      $item->setParameter(4, $temp);
      break;

    case 'function_exists':
      // Change was reverted.
//      $name['value'] = 'drupal_function_exists';
      break;

    case 'menu_path_is_external': // DONE
      $name['value'] = 'url_is_external';
      break;

    case 'module_invoke': // DONE
      // http://drupal.org/node/224333#taxonomy_get_tree
      $depth = '$max_depth = NULL /* TODO Set this variable. */';
      $count = $item->parameters->count();
      // Confirm this call relates to our topic.
      if ($count > 2) {
        $p0 = $item->printParameter(0);
        $p1 = $item->printParameter(1);
        if ($p0 != "'taxonomy'" || $p1 != "'get_tree'") {
          cdp("FAILED to relate");
          break;
        }
      }

      // Adjust parameters.
      if ($count > 5) {
        // Switch places.
        $p4 = $item->getParameter(4);
        $p5 = $item->getParameter(5);
        $item->setParameter(4, $p5);
        $item->setParameter(5, $p4);
      }
      elseif ($count > 4) {
        // Insert parameter due to change in parameter order.
        $editor->insertParameter($item, 4, $depth);
        $count = $item->parameters->count();
      }

      $defaults = array(array('NULL', $depth), '-1');
      $string = $editor->removeDefaults($item, 4, $defaults);
      break;

    case 'module_list': // DONE
      $name['value'] = 'module_implements';
      $editor->setParameters($item, array('$hook /* TODO Set this variable. */'));
      break;

    case 'module_rebuild_cache': // DONE
      $name['value'] = 'system_rebuild_module_data';
      break;

    case 'referer_uri': // DONE
      $expression = $editor->expressionToStatement("\$_SERVER['HTTP_REFERER']");
      $item = $expression->getElement(0);
      break;

    case 'set_time_limit': // DONE
      $name['value'] = 'drupal_set_time_limit';
      break;

    case 'system_theme_data': // DONE
      $name['value'] = 'system_rebuild_theme_data';
      break;

    case 't': // DONE
      $count = $item->parameters->count();
      if ($count < 3) {
        break;
      }

      $keys = array('langcode');
      $defaults = array("'XXX_YYY'");
      $string = $editor->arrayitize($item, 2, $keys, $defaults);

      $temp = $editor->expressionToStatement($string);
      $temp->getElement(0)->multiline = 0;
      cdp($temp->print_r());
      $item->setParameter(2, $temp);
      break;

    case 'taxonomy_del_term': // DONE
      $name['value'] = 'taxonomy_term_delete';
      break;

    case 'taxonomy_del_vocabulary': // DONE
      $name['value'] = 'taxonomy_vocabulary_delete';
      break;

    case 'taxonomy_get_term': // DONE
      $name['value'] = 'taxonomy_term_load';
      break;

    case 'taxonomy_get_tree': // DONE
      $depth = '$max_depth = NULL /* TODO Set this variable. */';
      $count = $item->parameters->count();
      // Adjust parameters.
      if ($count > 3) {
        // Switch places.
        $p2 = $item->getParameter(2);
        $p3 = $item->getParameter(3);
        $item->setParameter(2, $p3);
        $item->setParameter(3, $p2);
      }
      elseif ($count > 2) {
        // Insert parameter due to change in parameter order.
        $editor->insertParameter($item, 2, $depth);
        $count = $item->parameters->count();
      }

      $defaults = array(array('NULL', $depth), '-1');
      $string = $editor->removeDefaults($item, 2, $defaults);
      break;

    case 'taxonomy_save_term': // DONE
      $name['value'] = 'taxonomy_term_save';
      $temp = $item->printParameters();
      $editor->setParameters($item, array('$term /* TODO Term object replaces array ' . $temp . ' */)'));
      break;

    case 'taxonomy_save_vocabulary': // DONE
      $name['value'] = 'taxonomy_vocabulary_save';
      $temp = $item->printParameters();
      $editor->setParameters($item, array('$vocabulary /* TODO Vocabulary object replaces array ' . $temp . ' */)'));
      break;

    case 'theme': // DONE
      /*
       * Create a static variable to hold the array of theme registrations.
       * Find the theme in the list so we know the names of its parameters.
       * Array-itize the parameters.
       *
       * Find the hook_theme function (using $reader passed to this function)
       * and save its contents. This assumes the hook_theme is defined in this
       * file!!!
       *
       * Add helper functions to PGPArray to get the keys and values as arrays.
       * TODO Refactor any existing code that does this.
       *
       * static $themes = array();
       *
       * $p0 = $item->getParameter(0);
       * $theme = $themes[$p0];
       * $keys = keys from $theme
       * $string = 'array(';
       * foreach ($keys as $key) {
       *   $string .= "'$key' => $p{$i},";
       * }
       * $string = ');
       */
      cdp(__FUNCTION__ . " inside theme case");
      global $_coder_upgrade_module_name;
      // Find the hook_theme function object.
      $function = $editor->findFunction($reader->getFunctions(), $_coder_upgrade_module_name . '_theme');
      if (is_null($function)) {
        return;
      }

      // Get the keys for the appropriate theme.
      $body = &$function->body;

      if (!($return = $body->find(T_RETURN, 'reverse'))) {
        clp("ERROR: return statement not found in hook_perm");
        return;
      }
      $value = &$return->value;
      $array = $value->getElement(0);
      if (get_class($array) == 'PGPArray') {
        if (!($theme = $array->findValue($item->getParameter(0)->toString()))) {
          clp("ERROR: theme entry not found in hook_theme");
          return;
        }
        $array = $theme->getElement(0);
        $arguments = $array->findValue("'arguments'");
        $keys = $arguments->getElement(0)->keysToArray();
        if (empty($keys)) {
          break;
        }
        // Remove the quotes surrounding the keys.
        foreach ($keys as $index => $key) {
          $keys[$index] = trim($key, "'\"");
        }
      }

      $count = $item->parameters->count();
      if ($count == 1) {
        break;
      }

      $defaults = array_fill(0, $count - 1, "'XXX_YYY'");
      $string = $editor->arrayitize($item, 1, $keys, $defaults);

      $temp = $editor->expressionToStatement($string);
      $temp->getElement(0)->multiline = 0;
      $item->setParameter(1, $temp);
      break;

    case 'time': // DONE
      $expression = $editor->expressionToStatement('REQUEST_TIME');
      cdp($expression->print_r());
      $item = $expression->getElement(0);
      break;

    case 'user_authenticate': // DONE
      $count = $item->parameters->count();
      if ($count == 0) {
        $editor->setParameters($item, array('$name', '$password /* TODO Set these variables */'));
        break;
      }

      /*
       * Two cases:
       * - parameter is an array expression: extract values to use as new
       *   parameters
       * - parameter is a variable expression (not an array): assume the
       *   variable has name and pass as elements
       */

      $p0 = $item->getParameter();
      $operand = $p0->getElement();
      $class = get_class($operand);
      if ($class == 'PGPOperand') {
        // Get the variable name used as the parameter.
        $parameter = $item->getParameter()->toString();
        // Make variable assignments referring to two new parameters.
        $assign1 = $editor->textToStatements('$name = ' . $parameter . "['name']; // TODO Set these variables");
        $assign2 = $editor->textToStatements('$password = ' . $parameter . "['pass'];")->getElement(0);
        cdp($assign1->print_r());
        // Insert the assignments before this statement.
        // Get the statement (i.e. node) this function call is part of.
        $parent = &$item->parent;
        // Get the statement list the parent is part of.
        $container = &$parent->container;
        // Insert statements.
        $container->insertListBefore($parent, $assign1, 'assignment');
        $container->insertBefore($parent, $assign2, 'assignment');
        // Set the parameters on this function call.
        $editor->setParameters($item, array('$name', '$password'));
      }
      elseif ($class == 'PGPArray') {
        $name = $operand->findValue("'name'")->toString();
        $password = $operand->findValue("'pass'")->toString();
        // Set the parameters on this function call.
        $editor->setParameters($item, array($name, $password));
      }
      break;

    case 'user_delete': // DONE
      $name['value'] = 'user_cancel';
      $editor->setParameter($item, 2, "\$method = 'user_cancel_block' /* TODO Set this variable */");
      break;
  }
}

/**
 * Upgrades text using simple regular expressions.
 *
 * System
 * http://drupal.org/node/224333#moved_statistics_settings
 *
 *
 * Permissions and Access
 * http://drupal.org/node/224333#moved_statistics_settings (DUP System)
 * http://drupal.org/node/224333#php_permissions
 *
 *
 * Input Sanitization and Input Formats
 * http://drupal.org/node/224333#filter_urls
 *
 * @param string $file
 *   The text of the file to convert.
 */
function coder_upgrade_convert_regex_simple_changes(&$file) {
  $hook = 'regex_simple_changes';
  $cur = $file;
  $new = $cur;

  $from = array();
  $to = array();

  // Moved admin/reports/settings to admin/config/system/statistics (replacing admin/settings/statistics).
  $from[] = "@'admin/reports/settings'@";
  $to[] = "'admin/config/system/statistics'";

  // Replace "use PHP for block visibility" with "use PHP for settings."
  $from[] = '/(\'|")use PHP for block visibility(\'|")/';
  $to[] = "$1use PHP for settings$1";

  // Moved admin/settings/filters/* to admin/settings/filter/*
  $from[] = '@admin\/settings\/filters(\/.*?)@';
  $to[] = "admin\/settings\/filter$1";

  coder_upgrade_do_conversions($from, $to, $new);
  coder_upgrade_save_changes($cur, $new, $file, $hook);
}

/**
 * Upgrades functions using grammar parser.
 *
 * Module Info / Install
 * http://drupal.org/node/224333#update_php
 *
 *
 * Permissions and Access
 * http://drupal.org/node/224333#hook_permission
 * http://drupal.org/node/224333#descriptions_permissions
 * http://drupal.org/node/224333#hook_node_access
 *
 *
 * Database
 * http://drupal.org/node/224333#schema_translation
 * http://drupal.org/node/224333#schema_html
 * http://drupal.org/node/224333#install-schema
 *
 *
 * Menus
 * http://drupal.org/node/224333#hook_menu_link_alter
 *
 *
 * Blocks
 * http://drupal.org/node/224333#remove_op (DUP Node API)
 *
 *
 * Comments
 * http://drupal.org/node/224333#remove_op (DUP Node API) (THIS IS MISSING FROM THE CHRONO PAGE!!!)
 *
 *
 * User API
 * http://drupal.org/node/224333#user_cancel (DONE with remove_op)
 * http://drupal.org/node/224333#remove_op (DUP Node API)
 *
 *
 * Node API
 * http://drupal.org/node/224333#remove_op (SPANS MULTIPLE HOOKS)
 * http://drupal.org/node/224333#node_build_rss
 * http://drupal.org/node/224333#build_mode
 * http://drupal.org/node/224333#hook_node_xxx
 *
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_convert_functions(&$reader) {
//  clp("inside " . __FUNCTION__);
  cdp("inside " . __FUNCTION__);
  $editor = new PGPEditor();
  $types = array(T_FUNCTION);
  $editor->traverseCallback($reader->getFunctions(), 'coder_upgrade_callback_functions', $types, $reader);
}

/**
 * Callback routine for function changes using grammar parser.
 *
 * The grammar parser API which provides helper functions for working with
 * function objects. Some examples of typical tasks follow.
 *
 * @code
 *   // Rename the function.
 *   $item->name = 'new_function_name';
 *
 *   // Update the document comment.
 *   $item->comment = preg_replace('@hook_perm([^i])@', "hook_permission$1", $item->comment);
 *
 *   // Get the list of body statements (note the use of the reference operator).
 *   $body = &$item->body;
 *
 *   // Find the return statement in the function.
 *   $return = $body->find(T_RETURN, 'reverse');
 * @endcode
 *
 * For other examples of using the grammar parser API
 * @see coder_upgrade_callback_function_calls
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 * @param PGPReader $reader
 *   The object containing the grammar statements of the file to convert.
 */
function coder_upgrade_callback_functions(&$node, &$reader) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;

  global $_coder_upgrade_module_name;

  $name = &$item->name;
  cdp("name = $name");

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
   * Otherwise, strip the module name from the function name and use this as
   * the key in the switch statement. In some cases (e.g. hook_update_N), some
   * additional manipulation and testing needs to be done.
   */
  if (strpos($name, $_coder_upgrade_module_name) !== 0) {
    clp("Ignoring function '$name' as its name does not begin with the module name");
    return;
  }

  // By convention, the module name should be followed by an underscore.
  $key = substr($name, strlen($_coder_upgrade_module_name) + 1);
  cdp("key = $key");

  // Update hooks need additional manipulation.
  if (preg_match('@update_\d+$@', $key, $matches)) {
    cdp(print_r($matches, 1));
    $key = 'update_N';
  }

  switch ($key) {
    case 'access':
      // Changes: hook_node_access
      coder_upgrade_convert_access($node);
      break;

    case 'block':
      // Changes: remove_op
      $callback = 'coder_upgrade_callback_block';
      $op_index = 0;
      coder_upgrade_convert_op($node, $callback, $op_index);
      break;

    case 'comment':
      // Changes: remove_op
      $callback = 'coder_upgrade_callback_comment';
      $op_index = 1;
      coder_upgrade_convert_op($node, $callback, $op_index);
      break;

    case 'install':
    case 'uninstall':
      // Changes: install-schema
      coder_upgrade_convert_install($node);
      break;

    case 'menu_link_alter':
      // Changes: hook_menu_link_alter
      coder_upgrade_convert_menu_link_alter($node);
      break;

    case 'nodeapi':
      // Changes: build_mode, remove_op and others !!!???
      $callback = 'coder_upgrade_callback_nodeapi';
      $op_index = 1;
      coder_upgrade_convert_op($node, $callback, $op_index);
      break;

    case 'node_type':
      // Changes: remove_op
      $callback = 'coder_upgrade_callback_node_type';
      $op_index = 0;
      coder_upgrade_convert_op($node, $callback, $op_index);
      break;

    case 'perm':
      // Changes: hook_permission and descriptions_permissions
      coder_upgrade_convert_perm($node);
      break;

    case 'schema':
      // Changes: schema_translation and schema_html
      coder_upgrade_convert_schema($node);
      break;

    case 'update_N':
      // Changes: update_php
      coder_upgrade_convert_update_N($node);
      break;

    case 'user':
      // Changes: remove_op, user_cancel and others !!!???
      $callback = 'coder_upgrade_callback_user';
      $op_index = 0;
      coder_upgrade_convert_op($node, $callback, $op_index);
      break;
  }
}

/**
 * Updates hook_access().
 *
 * Replace hook_access() with hook_node_access().
 * Switch places of first two parameters.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_access(&$node) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;
  cdp($item->print_r());

  global $_coder_upgrade_module_name;

  // Rename function.
  $item->name = $_coder_upgrade_module_name . '_node_access';
  // Update document comment.
  $item->comment = preg_replace('@hook_access([^i])@', "hook_node_access$1", $item->comment);

  // Switch places of the first two parameters.
//  cdp("Printing parameters");
  cdp($item->parameters->print_r());

  $count = $item->parameters->count();
  // Adjust parameters.
  if ($count > 1) {
    // Switch places.
    $p0 = $item->getParameter(0);
    $p1 = $item->getParameter(1);
    $item->setParameter(0, $p1);
    $item->setParameter(1, $p0);
  }
}

/**
 * Updates hook_install() or hook_uninstall().
 *
 * Database schema (un)installed automatically.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_install($node) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;

  // Get body statements.
  $body = &$item->body;

  /*
   * In 6.x, drupal_install_schema has a return value, but not in 7.x.
   * The code below asssumes the return value is not utilized. Otherwise,
   * set the variable to empty string.
   */

  $current = $body->first();
  while ($current->next != NULL) {
    $statement = &$current->data;
    cdp($statement->print_r());
    if (is_a($statement, 'PGPAssignment')) {
      $text = $statement->values->toString();
      cdp($text);
      if (preg_match('(drupal_install_schema|drupal_uninstall_schema)', $text)) {
        $editor = new PGPEditor();
        // Insert comment.
        $statements = $editor->textToStatements('// TODO The drupal_(un)install_schema functions are called automatically in D7.');
        $body->insertBefore($current, $statements->getElement(), 'comment');
        // Comment out the statement.
        $statements = $editor->textToStatements('// ' . $text);
        $statement = $statements->getElement();
        break;
      }
    }
    $current = &$current->next;
  }
}

/**
 * Updates hook_menu_link_alter().
 *
 * Changed hook_menu_link_alter() (removed the $menu parameter).
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_menu_link_alter(&$node) {
  $item = &$node->data;
  $count = $item->parameters->count();
  // Adjust parameters.
  if ($count > 1) {
    // Delete second parameter.
    $item->deleteParameter(1);
  }
  // TODO Do we need to check for $menu in the body of this hook?
}

/**
 * Updates hook_perm().
 *
 * Rename hook_perm() to hook_permission().
 * Permissions are required to have titles and descriptions.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_perm(&$node) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;
  cdp($item->print_r());

  // Rename function.
  $item->name .= 'ission';
  // Update document comment.
  $item->comment = preg_replace('@hook_perm([^i])@', "hook_permission$1", $item->comment);

  // Restructure the permissions array.
  $body = &$item->body;

  if (!($return = $body->find(T_RETURN, 'reverse'))) {
    clp("ERROR: return statement not found in hook_perm");
    return;
  }
//  cdp("Printing return item");
  $value = &$return->value;
  cdp($value->print_r());
  cdp($value->toString());
//  cdp("Printing return item DONE");

  $array = $value->getElement();
  if (!is_a($array, 'PGPArray')) {
    clp("ERROR: return statement does not include an array of values in hook_perm");
    return;
  }
  // Grab the PGPList of values.
  $values = $array->values;

  $string = "array(\n";
  $current = $values->first();
  while ($current->next != NULL) {
    if ($current->type == 'value') {
      // If the permission is other than a string (e.g. T_VARIABLE expression),
      // then do not enclose in quotes.
      $expression = &$current->data->first()->data;
      // TODO Fix next line when condition is TRUE
      $type = is_object($expression) ? '$expression->type' : $expression['type']; // Operand object does not have a type parameter // $type = is_object($expression) ? $expression->type : $expression['type'];
      $add_quotes = $type == T_CONSTANT_ENCAPSED_STRING;

      $permission = &$current->data->toString();
//      cdp("permission = $permission");
      $permission = trim($permission, "'\"");
      if ($add_quotes) {
        $string .= "'$permission' => array('title' => t('$permission'), 'description' => t('TODO Add a description for $permission'),),\n";
      }
      else {
        $permission2 = str_replace("'", "\'", $permission);
        $string .= "$permission => array('title' => t($permission), 'description' => t('TODO Add a description for $permission2'),),\n";
      }
    }
    $current = &$current->next;
  }
  $string .= ");\n";
//  cdp($string);
  $editor = new PGPEditor();
  $expression = $editor->expressionToStatement($string);
//  cdp("PRINT NEW expression");
//  cdp($expression->print_r(3));
//  cdp("PRINT NEW expression DONE");

  // Set the return array to the new array.
  $value->setElement(0, $expression);
}

/**
 * Updates hook_schema().
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_schema(&$node) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;
  $body = &$item->body;

  if (!($return = $body->find(T_RETURN, 'reverse'))) {
    clp("ERROR: return statement not found in hook_schema");
    return;
  }
//  cdp("Printing return item");
  cdp($item->print_r(0, $return));
//  cdp("Printing return item DONE");
  $variable = $return->value->first();

  /*
   * Traverse the body statements looking for:
   * - assignment to the return variable
   * - in the assignment
   *   - a PGPArray operand
   *   - in the operand
   *     - key of 'description'
   *     - value whose first operand is PGPArray (recurse into this)
   *       - if the value calls t() then remove t()
   */
  $body->searchCallback($body, 'coder_upgrade_convert_schema_callback', 'PGPFunctionCall', 'name', 'value', 't');
}

function coder_upgrade_convert_schema_callback(&$item /*&$node*/) {
  cdp("inside " . __FUNCTION__);
//  cdp($item->print_r());

  if (get_class($item) != 'PGPFunctionCall') {
    return;
  }

  // Fetch the first parameter of the t() call.
  $parameter = $item->getParameter();
  $operand = $parameter->getElement();
  if (is_array($operand)) {
    // schema_html: schema descriptions are now plain text instead of HTML.
    $operand['value'] = html_entity_decode($operand['value']);
  }
//  cdp("operand");
//  cdp(print_r($operand, 1));

  // Parent should be the value expression in an array (key, value) pair.
  $parent = &$item->parentExpression;
  // Set the value to the first parameter of the t() call.
  if ($parent->count() == 1) {
    // This is an example of changing a function call reference.
    $parent->setElement(0, $operand);
  }
}

/**
 * Updates hook_update_N().
 *
 * Check hook_update_N for a Doxygen style comment.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_update_N(&$node) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;
//  cdp($item->print_r());

  $comment = &$item->comment;
  if (!is_array($comment) || empty($comment)) {
    $comment = array(
      'type' => T_DOC_COMMENT,
      'value' => "/**\n * @todo Please insert a Doxygen style comment for this hook_update_N.\n *\n */",
    );
  }
  elseif ($comment['type'] != T_DOC_COMMENT) {
    $comment = array(
      'type' => T_DOC_COMMENT,
      'value' => "/**\n * @todo Please insert a Doxygen style comment for this hook_update_N.\n *\n *" . $comment['value'] . "\n */",
    );
  }
}

/**
 * Initiates the transformation of $op hook to a new hook_$op style function.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 * @param string $callback
 *   A string of the callback function for the hook.
 * @param integer $op_index
 *   An integer of the operation parameter in the function parameter list.
 */
function coder_upgrade_convert_op(&$node, $callback, $op_index) {
  cdp("inside " . __FUNCTION__);
  cdp("$callback");

  /*
   * DBTNG changes can be done in another routine
   */

  // Get the function object.
  $item = &$node->data;
  // Rename the function in case any code is left over.
  $item->name .= '_OLD';
  // Get the operation function parameter, usually called $op.
  $count = $item->parameters->count();
  // TODO This gets the entire parameter including any default value. Hook_block has $op = 'list'.
  $op = $item->printParameter($op_index);

  // Get the function body statements.
  $body = &$item->body;

  /*
   * Two likely cases: switch statement or series of if blocks.
   * Do the if blocks later.
   * Compare the second parameter to the function with the switch operand.
   */

  // Loop on the body statements looking for the $op parameter in an IF or
  // SWITCH condition.
  $current = $body->first();
  while ($current->next != NULL) {
    $statement = &$current->data;
    if (is_object($statement)) {
      cdp($statement->print_r());
    }
    if (is_a($statement, 'PGPConditional')) {
//      cdp("inside PGPConditional check");
//      cdp("statement->type = " . $statement->type);
      if ($statement->type == T_SWITCH) {
//        cdp("inside T_SWITCH check");
        // Get the list of conditions.
        $conditions = $statement->conditions;
        // Get the first condition. (With a switch there should only be one condition.)
        $condition = $conditions->getElement();
        $operand = $condition->toString();
        // If the condition variable matches the $op variable, then go to work.
        if ($op == $operand) {
          $cases = $statement->body;
          $node->traverse($cases, $callback);
        }
      }
      elseif (in_array($statement->type, array(T_IF, T_ELSEIF/*, T_ELSE*/))) {
//        cdp("inside T_IF check");
        /*
         * Extract the conditions referencing the $op variable and loop on them.
         * These are conditions of the form $op == 'operation'.
         * Replace them with condition of TRUE to not disrupt the logic.
         * Retain any other conditions as part of the body in the new hook
         * function.
         */
        $operations = coder_upgrade_extract_operations($statement->conditions, $op);
        // Loop on the extracted operations.
        foreach ($operations as $operation) {
          // Change a T_ELSEIF to a T_IF in the new hook function.
          $statement->type = T_IF; // If it isn't already.
          $block = new stdClass();
          $block->body = new PGPBody();
          $block->body->insertLast($statement);
          $case_node = new PGPNode($block, $current->container); // TODO What is the correct container???
          $callback($node, $case_node, $operation);
        }
      }
    }
    // Move to next node.
    $current = &$current->next;
    // Get the statement list the switch statement (or if block) node is part of.
    $container = &$current->container;
    $container->delete($current->previous);
  }
}

/**
 * Extracts operations from conditions and replaces the conditions with TRUE.
 *
 * @param PGPList $conditions
 *   A list of conditions to an if block.
 * @param string $op
 *   A string of the hook operation.
 * @return array
 *   Array of operations referenced in the if block.
 */
function coder_upgrade_extract_operations(&$conditions, $op) {
  cdp("inside " . __FUNCTION__);
  $operations = array();

  /*
   * A condition may consist of at most two operands separated by an operator.
   */
  if (is_a($conditions, 'PGPList')) {
    // Iterate over the conditions of the condition list.
    $current = $conditions->first();
    while ($current->next != NULL) {
      $type = $current->type;
      if ($type == 'condition') {
        // Get the condition object of the current node.
        $condition = &$current->data;
        // Iterate over elements of the condition expression.
        $found = FALSE;
        $current2 = $condition->first();
        while ($current2->next != NULL) {
          if ($current2->type == 'operand') {
            // Get the operand (object or array) of the current node.
            $element = &$current2->data;
            // Inspect the element looking for $op.
            if (is_a($element, 'PGPOperand')) {
              // Inspect the operand looking for $op.
              $text = $element->toString();
              if (strpos($text, $op) !== FALSE) {
                $found = TRUE;
              }
              else {
                $operation = $element->toString();
              }
            }
            elseif (is_array($element)) {
              // This should have type = T_CONSTANT_ENCAPSED_STRING.
              $operation = $element['value'];
            }
          }
          // An interesting effect takes place with an & on the next line.
          $current2 = /*&*/$current2->next;
        }
        if ($found) {
          // Replace condition with TRUE so the logic remains the same.
          $condition->clear();
          $data = array(
            'type' => T_STRING,
            'value' => 'TRUE',
          );
          $condition->insertLast($data, 'operand');

          // Add operation to list.
          $operations[] = trim($operation, "'\"");
        }
      }
      $current = /*&*/$current->next;
    }
  }

  return $operations;
}

/**
 * Prepares the information needed to create a new hook_$op style function.
 *
 * This is a series of functions -- one for each existing hook to be modified.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 * @param PGPNode $case_node
 *   A node object containing a PGPCase (or PGPConditional) item.
 * @param string $operation
 *   A string of the operation to create a new hook for.
 */

/**
 * Updates hook_block().
 *
 * hook_nodeapi, hook_node_type, hook_user, and hook_block removed and replaced
 * with families of related functions
 */
function coder_upgrade_callback_block($node, $case_node, $operation = '') {
  cdp("inside " . __FUNCTION__);

  if (!$operation) {
    $case = &$case_node->data;
    if (!is_a($case, 'PGPCase')) {
      cdp("Houston, we've got an unexpected statement");
      return;
    }
    $operation = $case->case->toString();
    $operation = trim($operation, "'\"");
  }

  $hook = '_block_' . str_replace(' ', '_', $operation);
  $parameters = array('$delta');

  switch ($operation) {
    case 'configure':
      // This block becomes example_block_configure
      break;
    case 'list':
      // This block becomes example_block_list
      $hook = '_block_info';
      $parameters = array();
      break;
    case 'save':
      // This block becomes example_block_save
      $parameters = array('$delta', '$edit');
      break;
    case 'view':
      // This block becomes example_block_view
      break;
    default:
      cdp("ERROR: Invalid case value");
      return;
  }

  // Create the new hook function.
  coder_upgrade_op_to_hook($node, $case_node, $hook, $parameters);
}

/**
 * Updates hook_comment().
 *
 * ADD THIS TO:
 * hook_nodeapi, hook_node_type, hook_user, and hook_block removed and replaced
 * with families of related functions
 */
function coder_upgrade_callback_comment($node, $case_node, $operation = '') {
  cdp("inside " . __FUNCTION__);

  if (!$operation) {
    $case = &$case_node->data;
    if (!is_a($case, 'PGPCase')) {
      cdp("Houston, we've got an unexpected statement");
      return;
    }
    $operation = $case->case->toString();
    $operation = trim($operation, "'\"");
  }

  $hook = '_comment_' . str_replace(' ', '_', $operation);
  $parameters = array('$comment');

  switch ($operation) {
    case 'delete':
      // This block becomes example_comment_delete
      break;
    case 'insert':
      // This block becomes example_comment_insert
      break;
    case 'publish':
      // This block becomes example_comment_publish
      break;
    case 'unpublish':
      // This block becomes example_comment_unpublish
      break;
    case 'update':
      // This block becomes example_comment_update
      break;
    case 'validate':
      // This block becomes example_comment_validate
      break;
    case 'view':
      // This block becomes example_comment_view
      break;
    default:
      cdp("ERROR: Invalid case value");
      return;
  }

  // Create the new hook function.
  coder_upgrade_op_to_hook($node, $case_node, $hook, $parameters);
}

/**
 * Updates hook_nodeapi().
 *
 * hook_nodeapi, hook_node_type, hook_user, and hook_block removed and replaced
 * with families of related functions
 */
function coder_upgrade_callback_nodeapi($node, $case_node, $operation = '') {
  cdp("inside " . __FUNCTION__);

  if (!$operation) {
    $case = &$case_node->data;
    if (!is_a($case, 'PGPCase')) {
      cdp("Houston, we've got an unexpected statement");
      return;
    }
    $operation = $case->case->toString();
    $operation = trim($operation, "'\"");
  }

  $hook = '_node_' . str_replace(' ', '_', $operation);
  $parameters = array('$node');

  switch ($operation) {
    case 'alter':
      // This block becomes example_node_build_alter
      $hook = '_node_build_alter';
      $parameters = array('$build');
      break;
    case 'delete':
      // This block becomes example_node_delete
      break;
    case 'delete revision':
      // This block becomes example_node_revision_delete
      $hook = '_node_revision_delete';
      break;
    case 'insert':
      // This block becomes example_node_insert
      break;
    case 'load':
      // This block becomes example_node_load
      $parameters = array('$node', '$types');
      break;
    case 'prepare':
      // This block becomes example_node_prepare
      break;
    case 'prepare translation':
      // This block becomes example_node_prepare_translation
      break;
    case 'print':
      // This block becomes example_node_view with $build_mode = 'print'
      $hook = '_node_view';
      $parameters = array('$node', '$build_mode = \'print\'');
      break;
    case 'rss item':
      // This block becomes example_node_view with $build_mode = 'rss'
      $hook = '_node_view';
      $parameters = array('$node', '$build_mode = \'rss\'');
      break;
    case 'search result':
      // This block becomes example_node_search_result
      break;
    case 'presave':
      // This block becomes example_node_presave
      break;
    case 'update':
      // This block becomes example_node_update
      break;
    case 'update index':
      // This block becomes example_node_update_index
      break;
    case 'validate':
      // This block becomes example_node_validate
      $parameters = array('$node', '$form');
      break;
    case 'view':
      // This block becomes example_node_view with $build_mode = 'full' by default
      $parameters = array('$node', '$build_mode = \'full\'');
      break;
    default:
      cdp("ERROR: Invalid case value");
      return;
  }

  // Create the new hook function.
  coder_upgrade_op_to_hook($node, $case_node, $hook, $parameters);
}

/**
 * Updates hook_node_type().
 *
 * hook_nodeapi, hook_node_type, hook_user, and hook_block removed and replaced
 * with families of related functions
 */
function coder_upgrade_callback_node_type($node, $case_node, $operation = '') {
  cdp("inside " . __FUNCTION__);

  if (!$operation) {
    $case = &$case_node->data;
    if (!is_a($case, 'PGPCase')) {
      cdp("Houston, we've got an unexpected statement");
      return;
    }
    $operation = $case->case->toString();
    $operation = trim($operation, "'\"");
  }

  $hook = '_node_type_' . str_replace(' ', '_', $operation);
  $parameters = array('$info');

  switch ($operation) {
    case 'delete':
      // This block becomes example_node_type_delete
      break;
    case 'insert':
      // This block becomes example_node_type_insert
      break;
    case 'update':
      // This block becomes example_node_type_update
      break;
    default:
      cdp("ERROR: Invalid case value");
      return;
  }

  // Create the new hook function.
  coder_upgrade_op_to_hook($node, $case_node, $hook, $parameters);
}

/**
 * Updates hook_user().
 *
 * hook_nodeapi, hook_node_type, hook_user, and hook_block removed and replaced
 * with families of related functions
 * Renamed user_delete() to user_cancel();
 * likewise renamed hook_user_delete() to hook_user_cancel(). (Did this exist?)
 */
function coder_upgrade_callback_user($node, $case_node, $operation = '') {
  cdp("inside " . __FUNCTION__);

  if (!$operation) {
    $case = &$case_node->data;
    if (!is_a($case, 'PGPCase')) {
      cdp("Houston, we've got an unexpected statement");
      return;
    }
    $operation = $case->case->toString();
    $operation = trim($operation, "'\"");
  }

  $hook = '_user_' . str_replace(' ', '_', $operation);
  $parameters = array('$edit', '$account');

  // TODO We can end up with multiple copies of same hook if this mapping is accurate???
  switch ($operation) {
    case 'after_update':
      // The user object has been updated and changed. Use this if (probably along with 'insert') if you want to reuse some information from the user object.
      // This block becomes example_user_update
      $hook = '_user_update';
      $parameters = array('&$edit', '$account', '$category');
      break;
    case 'categories':
      // A set of user information categories is requested.
      // This block becomes example_user_categories
      $parameters = array();
      break;
    case 'delete':
      // The user account is being deleted. The module should remove its custom additions to the user object from the database.
      // This block becomes example_user_cancel
      $hook = '_user_cancel';
      $parameters = array('$edit', '$account', '$method');
      break;
    case 'form':
      // The user account edit form is about to be displayed. The module should present the form elements it wishes to inject into the form.
      // This block becomes example_user_???
      $hook = '_user_XXX';
      break;
    case 'insert':
      // The user account is being added. The module should save its custom additions to the user object into the database and set the saved fields to NULL in $edit.
      // This block becomes example_user_insert
      $parameters = array('&$edit', '$account', '$category');
      break;
    case 'load':
      // The user account is being loaded. The module may respond to this and insert additional information into the user object.
      // This block becomes example_user_load
      $parameters = array('$users');
      break;
    case 'login':
      // The user just logged in.
      // This block becomes example_user_login
      $parameters = array('&$edit', '$account');
      break;
    case 'logout':
      // The user just logged out.
      // This block becomes example_user_logout
      $parameters = array('$account');
      break;
    case 'register':
      // The user account registration form is about to be displayed. The module should present the form elements it wishes to inject into the form.
      // This block becomes example_user_???
      $hook = '_user_XXX';
      break;
    case 'submit':
      // Modify the account before it gets saved.
      // This block becomes example_user_???
      $hook = '_user_presave';
      $parameters = array('&$edit', '$account', '$category');
      break;
    case 'update':
      // The user account is being changed. The module should save its custom additions to the user object into the database and set the saved fields to NULL in $edit.
      // This block becomes example_user_presave
      $hook = '_user_presave';
      $parameters = array('&$edit', '$account', '$category');
      break;
    case 'validate':
      // The user account is about to be modified. The module should validate its custom additions to the user object, registering errors as necessary.
      // This block becomes example_user_presave
      $hook = '_user_presave';
      $parameters = array('&$edit', '$account', '$category');
      break;
    case 'view':
      // The user's account information is being displayed. The module should format its custom additions for display, and add them to the $account->content array.
      // This block becomes example_user_view
      $parameters = array('$account', '$build_mode');
      break;
    default:
      cdp("ERROR: Invalid case value");
      return;
  }

  // Create the new hook function.
  coder_upgrade_op_to_hook($node, $case_node, $hook, $parameters);
}

/**
 * Creates hook_$op function from the case (of if) block of an $op-style hook.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 * @param PGPNode $case_node
 *   A node object containing a PGPCase item.
 * @param string $hook
 *  A string of the new function name.
 * @param array $parameters
 *  An array of function parameters.
 */
function coder_upgrade_op_to_hook($node, $case_node, $hook, $parameters) {
  /*
   * Copy the case body to the new hook function.
   * Insert before (or after) the $item function.
   *
   * When case body is empty (e.g. insert, update), then use next reference
   * until a non-empty body is found.
   *
   * TODO
   * Add the new function to the list of functions.
   * This is useful when we may need to check for the existence of a function
   * on another upgrade.
   * Example: hook_link() becomes part of hook_node_view()
   * or hook_comment_view() based on $type parameter. Also hook_link_alter()
   * code goes in hook_node_view_alter() or hook_comment_view_alter().
   * See http://drupal.org/node/224333#node_links.
   */

  global $_coder_upgrade_module_name;
  $case = &$case_node->data;

  // Set values for the new hook function.
  $comment = array(
    'type' => T_DOC_COMMENT,
    'value' => "/**\n * Implements hook$hook.\n */",
  );
  $name = $_coder_upgrade_module_name . $hook;

  // Create the new hook function.
  $function = new PGPClass($name);
  $function->comment = $comment;
  $function->type = T_FUNCTION;
  $function->parameters = new PGPList();

  // Use the editor to set the function parameters.
  $editor = new PGPEditor();
  $editor->setParameters($function, $parameters);

  // Copy the case (or if) block as the body of the function.
  $function->body = $case->body;
  if ($function->body->isEmpty()) {
    // TODO Clone the node??? Use a while loop since there could be more than two cases back to back.
    $case_node2 = &$case_node->next;
    $case2 = &$case_node2->data;
    $body2 = $case2->body;
    if (!$body2->isEmpty()) {
      $function->body = clone $case2->body;
    }
  }

  // Remove the break statement from a case block.
  if (($break = $function->body->find(T_BREAK, 'reverse', TRUE))) {
    cdp("return statement found in hook");
    $function->body->delete($break);
  }
  // Remove any trailing blank lines (after break) that are included in body.
  $last = $function->body->last();
  if (is_array($last->data) && $last->data['type'] == T_WHITESPACE) {
    cdp("YAHOO: found whitespace statement in hook_nodeapi");
    $function->body->delete($last);
  }

  // Get the statement list the function node is part of.
  $container = &$node->container;

  // Insert the new function before the old function.
  $container->insertBefore($node, $function, 'function');
  // Insert a blank line.
  $whitespace = array(
    'type' => T_WHITESPACE,
    'value' => 1,
  );
  $container->insertBefore($node, $whitespace, 'whitespace');
}
