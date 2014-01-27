<?php
/**
 * @file
 * Provides conversion routines applied to function calls.
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
 * The upgrades to these functions are documented at the following urls.
 *
 * Module Info / Install
 * http://drupal.org/node/224333#update_sql (OMITS the update hooks part)
 *
 *
 * System
 * http://drupal.org/node/224333#absolute_includes
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
 * http://drupal.org/node/224333#drupal_set_header_renamed
 * http://drupal.org/node/224333#remove-drupal-urlencode
 *
 *
 * Database
 * http://drupal.org/node/224333#schema_ret
 * #db_result (not documented)
 * http://drupal.org/node/224333#db_is_active
 *
 *
 * Menu
 * http://drupal.org/node/224333#comment_load (DUP Comments)
 * http://drupal.org/node/224333#admin_path_changes
 * http://drupal.org/node/224333#menu_tree_data
 *
 *
 * Blocks
 * http://drupal.org/node/224333#custom_block
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
 * http://drupal.org/node/224333#taxonomy_form_all
 * http://drupal.org/node/224333#no-synonyms-taxonomy
 *
 *
 * Javascript
 * http://drupal.org/node/224333#drupal_add_js_options
 * http://drupal.org/node/224333#drupal_add_js_weight (Included with above)
 * http://drupal.org/node/224333#drupal_add_js_external
 * http://drupal.org/node/224333#jquery_ui
 * http://drupal.org/node/224333#rename-drupal-to-js
 *
 *
 * CSS
 * http://drupal.org/node/224333#drupal_add_js_options (DUP Javascript)
 * http://drupal.org/node/224333#drupal_add_css_inline
 * http://drupal.org/node/224333#drupal_add_css_weight (Should have a DUP in Javascript)
 * http://drupal.org/node/224333#form_clean_id
 *
 *
 * Theming
 * http://drupal.org/node/224333#rebuild_functions (DUP System)
 * http://drupal.org/node/224333#theme_page
 * http://drupal.org/node/224333#theme_changes
 * http://drupal.org/node/224333#placeholder
 * http://drupal.org/node/224333#theme_pager
 * http://drupal.org/node/224333#theme_username
 *
 *
 * Form API
 * http://drupal.org/node/224333#drupal_execute_drupal_form_submit
 * http://drupal.org/node/224333#hook_forms_signature
 *
 *
 * File API
 * http://drupal.org/node/224333#file_scan_directory_array_itize
 * http://drupal.org/node/224333#file_scan_directory_nomask
 * http://drupal.org/node/224333#file_set_status
 * http://drupal.org/node/224333#preg_match
 * http://drupal.org/node/224333#file_scan_directory_property_names
 * http://drupal.org/node/224333#file_prepare_directory
 *
 *
 * User API
 * http://drupal.org/node/224333#user_cancel (ALSO in convert_functions)
 * http://drupal.org/node/224333#user_load_multiple
 * http://drupal.org/node/224333#user_authenticate
 *
 *
 * Node API
 * http://drupal.org/node/224333#node_load_multiple
 * http://drupal.org/node/224333#node_type_base (ALSO in convert_functions)
 * http://drupal.org/node/224333#node_invoke_nodeapi
 * http://drupal.org/node/224333#node_type_get_functions
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
 * http://drupal.org/node/224333#drupal_valid_path
 * http://drupal.org/node/224333#drupal_goto_params
 * http://drupal.org/node/224333#format_date
 * http://drupal.org/node/224333#url_query_parameter
 */

/**
 * Implements hook_upgrade_call_alter().
 */
function coder_upgrade_upgrade_call_alter(&$node, &$reader, $name) { // NEEDS WORK
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
//  $name = &$item->name;

  switch ($name) {
    // http://drupal.org/node/224333#custom_block
    // All 'box' functions renamed to 'custom_block'.
    case 'block_box_delete':
    case 'block_box_delete_submit':
    case 'block_box_form':
    case 'block_box_get':
    case 'block_box_save':
      $item->name['value'] = str_replace('box', 'custom_block', $item->name['value']);
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

      /*
       * TODO
       * See http://drupal.org/node/224333#update_sql
       * Search for assignments to and return statements with the $ret parameter
       * used in these db_operation function calls.
       *
       * These could be moved to the install file although it may be possible to
       * call them in other files.
       */
      break;

    // http://drupal.org/node/224333#admin_path_changes
    // logout path changed to user/logout.
    case 'drupal_goto':
    case 'url':
    case 'drupal_get_path_alias':
    case 'drupal_get_normal_path':
      if (trim($item->printParameter(), "'\"") == 'logout') {
        $editor->setParameter($item, 0, "'user/logout'");
      }
      break;

    case 'drupal_lookup_path':
    case 'l':
      if (trim($item->printParameter(1), "'\"") == 'logout') {
        $editor->setParameter($item, 1, "'user/logout'");
      }
      break;

    case 'drupal_urlencode':
      // http://drupal.org/node/224333#remove-drupal-urlencode
      $item->name['value'] = 'drupal_encode_path';
      break;

    case 'require':
    case 'require_once':
    case 'include':
    case 'include_once':
      // These are included by $reader in function call list.
      // Use with http://drupal.org/node/224333#absolute_includes
      coder_upgrade_convert_require($item, $reader);
      break;

    // http://drupal.org/node/224333#no-synonyms-taxonomy
    // Taxonomy synonyms have been removed.
    case 'taxonomy_get_synonyms':
    case 'taxonomy_get_synonym_root':
      coder_upgrade_convert_taxonomy_synonyms($item);
      break;

    default:
      break;
  }
}

/**
 * Implements hook_upgrade_call_actions_synchronize_alter().
 */
function coder_upgrade_upgrade_call_actions_synchronize_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $count = $item->parameters->count();
  if ($count > 0) {
    $item->deleteParameter();
  }
}

/**
 * Implements hook_upgrade_call_book_toc_alter().
 */
function coder_upgrade_upgrade_call_book_toc_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
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
}

/**
 * Implements hook_upgrade_call_check_markup_alter().
 */
function coder_upgrade_upgrade_call_check_markup_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  if ($item->parameters->count() > 2) {
    $editor->insertParameter($item, 2, '$langcode = \'\' /* TODO Set this variable. */');
  }
}

/**
 * Implements hook_upgrade_call__comment_load_alter().
 */
function coder_upgrade_upgrade_call__comment_load_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'comment_load';
  // TODO The %_comment wildcard change to %comment in hook_menu. (See coder_upgrade.other_regex.inc.)
}

/**
 * Implements hook_upgrade_call_comment_node_url_alter().
 */
function coder_upgrade_upgrade_call_comment_node_url_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $item->insertStatementBefore($editor->commentToStatement('// TODO Please make sure $comment is a valid comment object.'));
  $temp = $editor->expressionToStatement("'comment/' . \$comment->cid");
  $node->container->insertListBefore($node, $temp);
  $node->container->delete($node);
}

/**
 * Implements hook_upgrade_call_comment_validate_alter().
 */
function coder_upgrade_upgrade_call_comment_validate_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'comment_form_validate';
  $editor->setParameters($item, array('$form', '$form_state /* TODO Set these variables. */'));
}

/**
 * Implements hook_upgrade_call_db_add_field_alter().
 *//*
function coder_upgrade_upgrade_call_db_add_field_alter(&$item, &$reader) { // NEEDS WORK
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Add a new field to a table.
  $item->deleteParameter();

  /*
   * TODO
   * See http://drupal.org/node/224333#update_sql
   * Search for assignments to and return statements with the $ret parameter
   * used in these db_operation function calls.
   *
   * These could be moved to the install file although it may be possible to
   * call them in other files.
   *//*
}*/

/**
 * Implements hook_upgrade_call_db_add_index_alter().
 *//*
function coder_upgrade_upgrade_call_db_add_index_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Add an index.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_add_primary_key_alter().
 *//*
function coder_upgrade_upgrade_call_db_add_primary_key_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Add a primary key.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_add_unique_key_alter().
 *//*
function coder_upgrade_upgrade_call_db_add_unique_key_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Add a unique key.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_change_field_alter().
 *//*
function coder_upgrade_upgrade_call_db_change_field_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Change a field definition.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_create_table_alter().
 *//*
function coder_upgrade_upgrade_call_db_create_table_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.inc Create a new table from a Drupal table definition.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_create_table_sql_alter().
 *//*
function coder_upgrade_upgrade_call_db_create_table_sql_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Generate SQL to create a new table from a Drupal schema definition.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_drop_field_alter().
 *//*
function coder_upgrade_upgrade_call_db_drop_field_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Drop a field.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_drop_index_alter().
 *//*
function coder_upgrade_upgrade_call_db_drop_index_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Drop an index.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_drop_primary_key_alter().
 *//*
function coder_upgrade_upgrade_call_db_drop_primary_key_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Drop the primary key.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_drop_table_alter().
 *//*
function coder_upgrade_upgrade_call_db_drop_table_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Drop a table.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_drop_unique_key_alter().
 *//*
function coder_upgrade_upgrade_call_db_drop_unique_key_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Drop a unique key.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_field_names_alter().
 *//*
function coder_upgrade_upgrade_call_db_field_names_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.inc Return an array of field names from an array of key/index column specifiers.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_field_set_default_alter().
 *//*
function coder_upgrade_upgrade_call_db_field_set_default_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Set the default value for a field.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_field_set_no_default_alter().
 *//*
function coder_upgrade_upgrade_call_db_field_set_no_default_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Set a field to have no default value.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_rename_table_alter().
 *//*
function coder_upgrade_upgrade_call_db_rename_table_alter(&$item, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Process function call.
  $name = &$item->name;
  // includes/database.pgsql.inc Rename a table.
  $item->deleteParameter();
}*/

/**
 * Implements hook_upgrade_call_db_column_exists_alter().
 */
function coder_upgrade_upgrade_call_db_column_exists_alter(&$node, &$reader) {
  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $item->name['value'] = 'db_field_exists';
}

/**
 * Implements hook_upgrade_call_db_is_active_alter().
 */
function coder_upgrade_upgrade_call_db_is_active_alter(&$node, &$reader) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // db_is_active() has been been replaced by proper exception catching.
  $container = &$item->parent->container;
  $parent = &$item->parent->data;
  if (get_class($parent) == 'PGPConditional' && $parent->type == T_IF) {
    // Build try/catch block.
    $try = new PGPTryCatch();
    $try->type = T_TRY;
    $try->body = $parent->body;

    $catch = new PGPTryCatch();
    $catch->type = T_CATCH;
    $catch->exception = $editor->expressionToStatement('Exception $e');
    $catch->body = new PGPBody();
    $catch->body->insertFirst($editor->commentToStatement('// Database is unavailable.'), 'comment');

    // Replace the if block with a try block.
    $parent = $try;
    // Insert catch block following the recast try block.
    $container->insertAfter($item->parent, $catch);
  }
}

/**
 * Implements hook_upgrade_call_db_result_alter().
 */
function coder_upgrade_upgrade_call_db_result_alter(&$node, &$reader) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $p0 = $item->printParameter();
  $temp = $editor->textToStatements(trim($p0) . '->fetchField();');
  $item = $temp->getElement(0);
}

/**
 * Implements hook_upgrade_call_drupal_add_css_alter().
 */
function coder_upgrade_upgrade_call_drupal_add_css_alter(&$node, &$reader) { // DONE (UPDATED)
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  // A similar comment to that in 'drupal_add_js' below applies here.
  cdp($item->parameters->print_r());

  $count = $item->parameters->count();
  if ($count == 1) {
    return;
  }
  if ($count == 2) {
    $type = trim($item->printParameter(1), "'\"");
    if ($type == 'module') {
      $item->deleteParameter(1);
      return;
    }
  }

  // Insert a new weight parameter.
  $type = trim($item->printParameter(1), "'\"");
  $weight = coder_upgrade_css_weight($type);
  $editor->insertParameter($item, 2, "$weight");

  // Arrayitize the parameters.
  $keys = array('type', 'weight', 'media', 'preprocess');
  $defaults = array("'module'", 'CSS_DEFAULT', "'all'", 'TRUE');
  $string = $editor->arrayitize($item, 1, $keys, $defaults);
  $string = preg_replace('@[\'"]theme[\'"]@', "'file'", $string); // Could be deleted.

  if ($string != 'array()') {
    $temp = $editor->expressionToStatement($string);
    $temp->getElement(0)->multiline = 0;
    cdp($temp->print_r());
    $item->setParameter(1, $temp);
  }
}

/**
 * Returns the new css weight parameter.
 *
 * @param string $type
 *
 * @return string
 */
function coder_upgrade_css_weight($type) {
  switch ($type) {
    case 'module':
      return 'CSS_DEFAULT';

    case 'theme':
      return 'CSS_THEME';

    default:
      return 'CSS_DEFAULT';
  }
}

/**
 * Implements hook_upgrade_call_drupal_add_js_alter().
 */
function coder_upgrade_upgrade_call_drupal_add_js_alter(&$node, &$reader) { // DONE (UPDATED)
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  /*
   * With
   * drupal_add_js('misc/collapse.js', 'core', 'header', FALSE, TRUE, TRUE);
   * we will output
   * drupal_add_js('misc/collapse.js', array('type' => 'file', 'weight' => JS_LIBRARY));
   * which is correct, although the function will also accept
   * drupal_add_js('misc/collapse.js', array('weight' => JS_LIBRARY));
   * The example begs the question why someone would have included all
   * the default parameters.
   *
   * A type of 'core', 'module' or 'theme' all convert to 'file' which is
   * the new default. The weight parameter then corresponds to the old type.
   */
  cdp($item->parameters->print_r());

  $count = $item->parameters->count();
  if ($count == 1) {
    return;
  }
  if ($count == 2) {
    $type = trim($item->printParameter(1), "'\"");
    if ($type == 'module') { // if (in_array($type, array('module', ''))) {
      $item->deleteParameter(1);
      return;
    }
    elseif (in_array($type, array('core', 'theme'))) {
      // Add a default value for the scope parameter (removed below).
      $editor->insertParameter($item, 2, "'header'");
    }
  }

  // Insert a new weight parameter.
  $type = trim($item->printParameter(1), "'\"");
  $weight = coder_upgrade_js_weight($type);
  $editor->insertParameter($item, 3, "$weight");

  // Arrayitize the parameters.
  $keys = array('type', 'scope', 'weight', 'defer', 'cache', 'preprocess');
  $defaults = array("'module'", "'header'", 'JS_DEFAULT', 'FALSE', 'TRUE', 'TRUE');
  $string = $editor->arrayitize($item, 1, $keys, $defaults);
  $string = preg_replace('@[\'"](core|theme)[\'"]@', "'file'", $string); // Could be deleted.

  if ($string != 'array()') {
    $temp = $editor->expressionToStatement($string);
    $temp->getElement(0)->multiline = 0;
    cdp($temp->print_r());
    $item->setParameter(1, $temp);
  }
}

/**
 * Returns the new js weight parameter.
 *
 * @param string $type
 *
 * @return string
 */
function coder_upgrade_js_weight($type) {
  switch ($type) {
    case 'core':
      return 'JS_LIBRARY';

    case 'module':
      return 'JS_DEFAULT';

    case 'theme':
      return 'JS_THEME';

    default:
      return 'JS_DEFAULT';
  }
}

/**
 * Implements hook_upgrade_call_drupal_clone_alter().
 */
function coder_upgrade_upgrade_call_drupal_clone_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'clone';
  $item->noparens = 1;
}

/**
 * Implements hook_upgrade_call_drupal_eval_alter().
 */
function coder_upgrade_upgrade_call_drupal_eval_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
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
}

/**
 * Implements hook_upgrade_call_drupal_execute_alter().
 */
function coder_upgrade_upgrade_call_drupal_execute_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_form_submit';
}

/**
 * Implements hook_upgrade_call_drupal_get_content_alter().
 */
function coder_upgrade_upgrade_call_drupal_get_content_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_get_region_content';
}

/**
 * Implements hook_upgrade_call_drupal_get_form_alter().
 */
function coder_upgrade_upgrade_call_drupal_get_form_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  // http://drupal.org/node/224333#hook_forms_signature
  /*
   * This needs to be approached from multiple angles.
   *
   * Up-front processing: read hook_menu and hook_theme
   * (the latter for the theme change).
   * Look for calls to drupal_get_form or system_settings_form.
   * The latter already passes the $form array.
   * Find the function whose name is the first parameter name.
   * Add $form as a parameter.
   * The first parameter may be a variable, in which case we could try to
   * find it and get the string value.
   *
   * Recurse over menu items with page callback = drupal_get_form
   * and look for functions with name = first parameter of page arguments.
   * Add $form as a parameter.
   * This could be done from the convert_functions routine for hook_menu.
   */

  $count = $item->parameters->count();
  if ($count == 0) {
    return;
  }

  $form = $item->getParameter();
  $operand = $form->getElement();
  $value = $form->toString();
  if ($form->isType(T_CONSTANT_ENCAPSED_STRING)) {
    // Parameter is a string.
    // Get the function name.
    $value = trim($operand['value'], "'\"");
    // Find the function object with this name.
    $function = $editor->findFunction($reader->getFunctions(), $value);
    if (!is_null($function)) {
      $p0 = $function->parameterCount() ? $function->getParameter()->stripComments()->toString() : '';
      if ($p0 != '$form') {
        // Insert the $form parameter (if not already inserted).
        $function->insertParameter(0, $editor->expressionToStatement('$form'));
      }
    }
  }
  elseif ($form->isType(T_VARIABLE)) {
    // Parameter is a variable.
    $variable = $operand->findNode('value');
    // Get the parent = statement (i.e. node) this function call is part of.
    $parent = $item->parent; // $parent = &$item->parent;
    // Find the assignment in the statement list the parent is part of.
    $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
    if ($statement) {
      $operand2 = &$statement->values->getElement()->findNode('operand', 'backward');
      // TODO A pattern here - this is the same code as above but executed on a different object.
      if (is_array($operand2) && $operand2['type'] == T_CONSTANT_ENCAPSED_STRING) {
        $value = trim($operand2['value'], "'\"");
        $function = $editor->findFunction($reader->getFunctions(), $value);
        if (!is_null($function)) {
          $p0 = $function->parameterCount() ? $function->getParameter()->stripComments()->toString() : '';
          if ($p0 != '$form') {
            // Insert the $form parameter (if not already inserted).
            $function->insertParameter(0, $editor->expressionToStatement('$form'));
          }
        }
      }
      else {
        clp("ERROR: Could not find a string to change in " . __FUNCTION__);
        $item->insertStatementBefore($editor->commentToStatement('// TODO ' . $item->printParameter(1) . ' needs to have $form as its first parameter.'));
      }
    }
    else {
      clp("ERROR: Could not find a string to change in " . __FUNCTION__);
      $item->insertStatementBefore($editor->commentToStatement('// TODO ' . $item->printParameter(1) . ' needs to have $form as its first parameter.'));
    }
  }
  else {
    clp("ERROR: Form callback is not a string or variable" . __FUNCTION__);
    $item->insertStatementBefore($editor->commentToStatement('// TODO ' . $item->printParameter(1) . ' needs to have $form as its first parameter.'));
  }
  // TODO Comment out an assignment of $form = array();
}

/**
 * Implements hook_upgrade_call_drupal_get_headers_alter().
 */
function coder_upgrade_upgrade_call_drupal_get_headers_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
//  $name['value'] = 'drupal_get_header'; // Overwritten by following change.
  // http://drupal.org/node/224333#drupal_set_header_renamed
  $name['value'] = 'drupal_get_http_header';
}

/**
 * Implements hook_upgrade_call_drupal_goto_alter().
 */
function coder_upgrade_upgrade_call_drupal_goto_alter(&$node, &$reader) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  if ($item->parameterCount() < 2) {
    // Nothing to do.
    return;
  }

  // Convert query and fragment parameters into an array.

  // Save the http_response_code parameter.
  $http_code = $item->getParameter(3);
  $item->deleteParameter(3);

  if ($item->parameterCount() > 1) {
    // Convert query string into an array
    $query = $item->getParameter(1);
    $operand = $query->getElement();
    $value = $query->toString();
    if ($query->isType(T_CONSTANT_ENCAPSED_STRING)) {
      // Parameter is a string.
      $query = coder_upgrade_query_to_array($item->printParameter(1));
      $item->setParameter(1, $query);
    }
    elseif ($query->isType(T_VARIABLE)) {
      // Parameter is a variable.
      $variable = $operand->findNode('value');
      // Get the parent = statement (i.e. node) this function call is part of.
      $parent = $item->parent; // $parent = &$item->parent;
      // Get the statement list the parent is part of.
      $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
      if ($statement) {
        $operand2 = &$statement->values->getElement()->findNode('operand', 'backward');
        // TODO A pattern here - this is the same code as above but executed on a different object.
        if (is_array($operand2) && $operand2['type'] == T_CONSTANT_ENCAPSED_STRING) {
          $operand2 = coder_upgrade_query_to_array($operand2['value']);
        }
        else {
          clp("ERROR: Could not find a string to change in " . __FUNCTION__);
          $item->insertStatementBefore($editor->commentToStatement('// TODO ' . $item->printParameter(1) . ' needs to be an array of keys and values instead of a string.'));
        }
      }
      else {
        clp("ERROR: Could not find a string to change in " . __FUNCTION__);
        $item->insertStatementBefore($editor->commentToStatement('// TODO ' . $item->printParameter(1) . ' needs to be an array of keys and values instead of a string.'));
      }
    }
    elseif ($query->isType(T_STRING)) {
      // Parameter is a constant.
      if ($value != 'NULL') {
        $item->insertStatementBefore($editor->commentToStatement('// TODO ' . $item->printParameter(1) . ' needs to be an array of keys and values instead of a string.'));
      }
      // TODO Handle constants - add todo comment - try to find the define?
    }
    else {
//      clp("ERROR: Could not find a string to change in " . __FUNCTION__);
      $item->insertStatementBefore($editor->commentToStatement('// TODO ' . $item->printParameter(1) . ' needs to be an array of keys and values instead of a string.'));
    }
  }

  // Arrayitize the parameters.
  $keys = array('query', 'fragment');
  $defaults = array('NULL', 'NULL');
  $string = $editor->arrayitize($item, 1, $keys, $defaults);

  if (is_object($http_code) || $string != 'array()') {
    $temp = $editor->expressionToStatement($string);
    $temp->getElement(0)->multiline = 0;
    $item->setParameter(1, $temp);
  }
  if (is_object($http_code)) {
    $item->setParameter(2, $http_code);
  }
}

/**
 * Converts a url query string to an associative array.
 *
 * @param string $string
 *
 * @return PGPExpression
 *   The associative array.
 */
function coder_upgrade_query_to_array($string) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  $string = trim($string, "'\"");
  if ($string == '') {
    // Empty string is equivalent to NULL in this case.
    return $editor->expressionToStatement('NULL');
  }
  parse_str($string, $query_str);
  // This removes a trailing comma from an inline array expression.
  $editor->getReader()->setPreserveArrayFormat(FALSE);
  $query = $editor->expressionToStatement(str_replace(array("\n", "  "), '', var_export($query_str, TRUE)));
  $query->getElement()->multiline = 0;
  $editor->getReader()->setPreserveArrayFormat(TRUE);
  return $query;
}

/**
 * Implements hook_upgrade_call_drupal_http_request_alter().
 */
function coder_upgrade_upgrade_call_drupal_http_request_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  cdp($item->parameters->print_r());

  $count = $item->parameters->count();
  if ($count == 1) {
    return;
  }

  $keys = array('headers', 'method', 'data', 'max_redirects');
  $defaults = array('xxx_YYY_zzz', "'GET'", 'NULL', 3);
  $string = $editor->arrayitize($item, 1, $keys, $defaults);

  $temp = $editor->expressionToStatement($string);
  $temp->getElement(0)->multiline = 0;
  cdp($temp->print_r());
  $item->setParameter(1, $temp);
}

/**
 * Implements hook_upgrade_call_drupal_json_alter().
 */
function coder_upgrade_upgrade_call_drupal_json_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_json_output';
}

/**
 * Implements hook_upgrade_call_drupal_rebuild_code_registry_alter().
 */
function coder_upgrade_upgrade_call_drupal_rebuild_code_registry_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'registry_rebuild';
}

/**
 * Implements hook_upgrade_call_drupal_rebuild_theme_registry_alter().
 */
function coder_upgrade_upgrade_call_drupal_rebuild_theme_registry_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_theme_rebuild';
}

/**
 * Implements hook_upgrade_call_drupal_set_content_alter().
 */
function coder_upgrade_upgrade_call_drupal_set_content_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_add_region_content';
}

/**
 * Implements hook_upgrade_call_drupal_set_header_alter().
 */
function coder_upgrade_upgrade_call_drupal_set_header_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  // http://drupal.org/node/224333#drupal_set_header_renamed
  $name['value'] = 'drupal_add_http_header';

  if (!$item->parameterCount()) {
    // Nothing else to do.
    return;
  }

  $temp = $item->printParameter();
  $p0 = $item->getParameter();
  if ($p0->count() > 1) {
    // This is a complex expression.
    if ($p0->isType(T_CONSTANT_ENCAPSED_STRING)) {
      $operand = &$p0->getElement();
      if (($pos = strpos($operand['value'], ':')) !== FALSE) {
        $type = trim(substr($operand['value'], 0, $pos), "'\" ");
        /*
         * Retain the existing quote type in case of any embedded quotes and
         * other quoted items in the rest of the expression.
         * Ex: 'Content-Disposition: attachment; filename="'
         */
        $operand['value'] = str_replace(array($type, ': ', ':'), '', $operand['value']);
        // Append the charset onto the parameter string.
//        if ($type == 'Content-Type' && strpos($value, 'charset') === FALSE) {
//          $value .= '; charset=utf-8';
//        }
        $type = "'$type'";
        // if value == '', then remove operator == '.' from expression
        if ($operand['value'] == "''" || $operand['value'] == '""') {
          $p0->deleteElement();
          $p0->deleteElement(); // Delete the first operator.
        }
        $editor->insertParameter($item, 0, $type);
      }
    }
    elseif ($p0->isType(T_VARIABLE)) {
      $temp = $p0->getElement()->toString();
      if (strpos($temp, "\$_SERVER['SERVER_PROTOCOL']") !== FALSE ||
          strpos($temp, '$_SERVER["SERVER_PROTOCOL"]') !== FALSE) {
        $p0->deleteElement();
        $p0->deleteElement(); // Delete the first operator.
        if ($p0->isType(T_CONSTANT_ENCAPSED_STRING)) {
          // Remove a leading space, e.g. ' 500 Internal server error'.
          $operand = &$p0->getElement();
          $operand['value'] = str_replace(array('" ', "' "), array('"', "'"), $operand['value']);
        }
        $editor->insertParameter($item, 0, "'Status'");
      }
    }
  }
  else {
    if ($p0->isType(T_CONSTANT_ENCAPSED_STRING)) {
      if (strpos($temp, 'HTTP/') !== FALSE) {
        $temp = trim(substr($temp, 9), "'\" "); // Assumes protocol = HTTP/n.n where n is a digit.
        $editor->setParameters($item, array("'Status'", "'$temp'"));
      }
      elseif (strpos($temp, ':') !== FALSE) {
        list($type, $value) = explode(':', $temp);
        $type = trim($type, "'\" ");
        $value = trim($value, "'\" ");
        if ($type == 'Content-Type' && strpos($value, 'charset') === FALSE) {
          $value .= '; charset=utf-8';
        }
        $type = "'$type'";
        $value = "'$value'";
        $editor->setParameters($item, array($type, $value));
      }
    }
    else {
      // Could be a variable that we could search for and change?
    }
  }

  // TODO the hook_file_download() changes. Use parser on the entire function.
}

/**
 * Implements hook_upgrade_call_drupal_set_html_head_alter().
 */
function coder_upgrade_upgrade_call_drupal_set_html_head_alter(&$node, &$reader) { // DONE (UPDATED)
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_add_html_head';

  $count = $item->parameters->count();
  if ($count == 1) {
    // http://drupal.org/node/224333#drupal_add_css_inline
    // Inline css can be now added via drupal_add_css
    $p0 = $item->printParameter();
    if (preg_match('#^([\'"])\s*<style type=[\'"]text/css[\'"]>(.*)</style>#si', $p0, $matches)) {
      $name['value'] = 'drupal_add_css';
      $editor->setParameters($item, array($matches[1] . $matches[2] . $matches[1], "array('type' => 'inline')"));
      return;
    }
    // http://drupal.org/node/224333#drupal_add_js_external
    // External JavaScript files can be now added via drupal_add_js
    if (preg_match('#^[\'"]<script.*src=[\'"](.*?)[\'"]#i', $p0, $matches)) {
      $name['value'] = 'drupal_add_js';
      $editor->setParameter($item, 0, "'" . $matches[1] . "'");
      $editor->setParameter($item, 1, "array('type' => 'external')");
      return;
    }

    $key = '$key = NULL /* TODO Set this variable. */';
    // Insert new required parameter when first parameter is set.
    $editor->insertParameter($item, 1, $key);
  }
}

/**
 * Implements hook_upgrade_call_drupal_set_title_alter().
 */
function coder_upgrade_upgrade_call_drupal_set_title_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $parameters = &$item->parameters;
  // Find all calls to check_plain() in the parameter expression.
  while ($node2 = &$parameters->search('PGPFunctionCall', 'name', 'value', 'check_plain', TRUE)) {
    // Insert the nodes in the parameter expression to check_plain()
    // into the parameter expression to drupal_set_title() right before the call
    // to check_plain().
    $parameters->insertListBefore($node2, $node2->data->getParameter());
    // Remove the check_plain() call as drupal_set_title() now does this.
    $parameters->delete($node2);
  }
  // TODO Should check the argument keys not the text to the t().
  if ($item->parameterCount() == 1 && $call = &$parameters->search('PGPFunctionCall', 'name', 'value', 't')) {
    $temp = $call->toString();
    cdp("temp = $temp");
    if (preg_match('#(\'|")[@|%]\w+(\'|")\s*=>\s*#', $temp) && preg_match('#(\'|")!\w+(\'|")\s*=>\s*#', $temp) === 0) {
      // This is a likely condition for setting 'PASS_THROUGH' but not an absolute.
      $editor->setParameter($item, 1, 'PASS_THROUGH');
      cdp($item->print_r(0, $item));
    }
  }
}

/**
 * Implements hook_upgrade_call_drupal_system_listing_alter().
 */
function coder_upgrade_upgrade_call_drupal_system_listing_alter(&$node, &$reader) { // DONE (Revise like file_scan_directory)
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
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
}

/**
 * Implements hook_upgrade_call_drupal_to_js_alter().
 */
function coder_upgrade_upgrade_call_drupal_to_js_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_json_encode';
}

/**
 * Implements hook_upgrade_call_drupal_uninstall_module_alter().
 */
function coder_upgrade_upgrade_call_drupal_uninstall_module_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_uninstall_modules';
  $temp = $item->printParameters();
  $editor->setParameters($item, array('array(' . $temp . ')'));
}

/**
 * Implements hook_upgrade_call_file_check_directory_alter().
 */
function coder_upgrade_upgrade_call_file_check_directory_alter(&$node, &$reader) {
  // Get the function call object.
  $item = &$node->data;

  // http://drupal.org/node/224333#file_prepare_directory
  $name = &$item->name;
  $name['value'] = 'file_prepare_directory';
}

/**
 * Implements hook_upgrade_call_file_scan_directory_alter().
 */
function coder_upgrade_upgrade_call_file_scan_directory_alter(&$node, &$reader) { // DONE (IN PROGRESS)
  cdp(__FUNCTION__);
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;

  /*
   * TODO Default values will not harm anything if they are in the $options
   * array. However, if the mask and nomask parameters are variables, then they
   * need to be changed to preg format. Also, the key values need to change in
   * the function call and the variables that reference the file objects.
   */

  // Save the depth parameter.
  $depth = $item->getParameter(7);
  $item->deleteParameter(7);

  if ($item->parameters->count() > 1) {
    // Change mask from ereg to preg style.
    // Part of http://drupal.org/node/224333#preg_match
    $mask = $item->getParameter(1);
    $operand = $mask->getElement();
    if (is_array($operand) && $operand['type'] == T_CONSTANT_ENCAPSED_STRING) {
      // Parameter is a string.
      $mask = coder_upgrade_ereg_to_preg($item->printParameter(1));
      $editor->setParameter($item, 1, $mask);
    }
    elseif ($operand instanceof PGPOperand && $operand->findNode('type') == T_VARIABLE) {
      // Parameter is a variable.
      $variable = $operand->findNode('value');
      // Get the parent = statement (i.e. node) this function call is part of.
      $parent = $item->parent; // $parent = &$item->parent;
      // Get the statement list the parent is part of.
      $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
      if ($statement) {
        $operand2 = &$statement->values->getElement()->findNode('operand', 'backward');
        // TODO A pattern here - this is the same code as above but executed on a different object.
        if (is_array($operand2) && $operand2['type'] == T_CONSTANT_ENCAPSED_STRING) {
          $operand2['value'] = coder_upgrade_ereg_to_preg($operand2['value']);
          $mask = $operand2['value'];
        }
        else {
          clp("ERROR: Could not find a string to change in " . __FUNCTION__);
        }
      }
    }
    else {
      clp("ERROR: Could not find a string to change in " . __FUNCTION__);
    }
  }

  if ($item->parameters->count() > 2) {
    // Change nomask from array to preg style.
    // http://drupal.org/node/224333#file_scan_directory_nomask
    $nomask = $item->getParameter(2);
    $operand = $nomask->getElement();
    if ($operand instanceof PGPArray) {
      // Parameter is an array.
      $nomask = coder_upgrade_array_to_preg($operand);
      $editor->setParameter($item, 2, $nomask);
    }
    elseif ($operand instanceof PGPOperand && $operand->findNode('type') == T_VARIABLE) {
      // Parameter is a variable.
      $variable = $operand->findNode('value');
      // Get the parent = statement (i.e. node) this function call is part of.
      $parent = $item->parent; // $parent = &$item->parent;
      // Get the statement list the parent is part of.
      $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
      if ($statement) {
        $operand2 = &$statement->values->getElement()->findNode('operand', 'backward');
        // TODO A pattern here - this is the same code as above but executed on a different object.
        if ($operand2 instanceof PGPArray) {
          $nomask = coder_upgrade_array_to_preg($operand2);
          $operand2 = array('type' => T_CONSTANT_ENCAPSED_STRING, 'value' => $nomask);
        }
        else {
          clp("ERROR: Could not find a string to change in " . __FUNCTION__);
        }
      }
    }
    else {
      clp("ERROR: Could not find a string to change in " . __FUNCTION__);
    }
  }

  if ($item->parameters->count() > 5) {
    // Change key values.
    // http://drupal.org/node/224333#file_scan_directory_property_names
    $operand = $item->getParameter(5)->getElement();
    if (is_array($operand) && $operand['type'] == T_CONSTANT_ENCAPSED_STRING) {
      // Parameter is a string.
      $key = coder_upgrade_file_key($item->printParameter(5));
      $editor->setParameter($item, 5, $key);
    }
    elseif ($operand instanceof PGPOperand && $operand->findNode('type') == T_VARIABLE) {
      // Parameter is a variable.
      $variable = $operand->findNode('value');
      $parent = $item->parent;
      $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
    }
    // Edge case: the parameter could have a comment.
    // Make a general function to clean the parameter of comments and whitespace so we can truly evaluate it.
    // TODO Add a comment if unable to make the change. This applies to all routines!!!
  }

  // http://drupal.org/node/224333#file_scan_directory_array_itize
  // Arrayitize the parameters.
  $keys = array('nomask', 'callback', 'recurse', 'key', 'min_depth');
  $defaults = array(/*"array('.', '..', 'CVS')"*/ "'/(\.\.?|CVS)$/'", '0', 'TRUE', /*"'filename'"*/ "'uri'", 0);
  $string = $editor->arrayitize($item, 2, $keys, $defaults);

  if (is_object($depth) || $string != 'array()') {
    $temp = $editor->expressionToStatement($string);
    $temp->getElement(0)->multiline = 0;
    $item->setParameter(2, $temp);
  }
  if (is_object($depth)) {
    $item->setParameter(3, $depth);
  }

  // TODO Could regex for '->filename' and change to '->filepath'???
  // See http://drupal.org/files/issues/file_scan_directory-1.patch
}

/**
 * Returns the new file key parameter.
 *
 * @param string $key
 *
 * @return string
 */
function coder_upgrade_file_key($key) {
  switch ($key) {
    case "'filename'":
      return "'uri'";

    case "'basename'":
      return "'filename'";

    case "'name'":
      return "'name'";

    default:
      return "'uri'";
  }
}

/**
 * Converts an ereg string to a preg string.
 *
 * @param string $string
 *
 * @return string
 */
function coder_upgrade_ereg_to_preg($string) {
  cdp(__FUNCTION__);
  // Check for type == T_CONSTANT_ENCAPSED_STRING
  // Check for a '/' in the mask and use a different mask or delimit the '/' with '\/'.
  $delimiters = array('/', '@', '#', '%', '~', ''); // TODO Are these all legal?
  foreach ($delimiters as $delimiter) {
    if (strpos($string, $delimiter) === FALSE) {
      break;
    }
  }

  if (!$delimiter) {
    clp('ERROR: Could not find a suitable delimiter for the regular expression');
    $delimiter = '/';
    $string = str_replace('/', '\/', $string);
  }

  $quote = $string[0];
  return $quote . $delimiter . substr($string, 1, -1) . $delimiter . $quote;
}

/**
 * Returns a preg string for the nomask parameter.
 *
 * @param PGPOperand $nomask
 *
 * @return string
 */
function coder_upgrade_array_to_preg($operand) {
  cdp(__FUNCTION__);
  $defaults = array('.', '..', 'CVS');
  $current = $operand->values->first();
  while ($current->next != NULL) {
    if ($current->type == 'value') {
      $values[] = trim($current->data->toString(), "'\"");
    }
    $current = $current->next;
  }
  $defaults = array_diff($defaults, $values);
  if (empty($defaults)) {
    return "'/(\.\.?|CVS)$/'";
  }
  $strings = array();
  foreach ($values as $value) {
    $strings[] .= str_replace('.', '\.', $value);
  }
  return "'/(" . implode('|', $strings) . ")/'";
}

/**
 * Implements hook_upgrade_call_file_set_status_alter().
 */
function coder_upgrade_upgrade_call_file_set_status_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Get the text of the function call and its parent statement.
  $temp1 = $item->toString();
  $temp2 = $editor->statementsToText($item->parent); // This includes a ';' at end.

  if ($item->parameters->count() == 2) {
    $p0 = $item->printParameter(0);
    $p1 = $item->printParameter(1);

    // Insert statement.
    $statement = $editor->textToStatements("{$p0}->status &= $p1")->getElement(0);
    $item->insertStatementBefore($statement);

    // Change statement.
    $from = $temp1;
    $to = "$p0 = file_save($p0)";
    $temp = str_replace($from, $to, $temp2);
    $temp = $editor->textToStatements($temp);
    $parent = $item->parent;
    $parent->data = $temp->getElement(0);
  }
}

/**
 * Implements hook_upgrade_call_filter_formats_alter().
 */
function coder_upgrade_upgrade_call_filter_formats_alter(&$node, &$reader) { // DONE (UPDATED)
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  cdp('filter_formats');
  /*
   * If call has a parameter, then change it to $user and add global statement.
   * If no parameter, then this still implies current user in D6.
   * Set the existing assignment variable to itself at $index.
   * Ex: $formats = filter_formats($index);
   * becomes
   * global $user;
   * $formats = filter_formats($user);
   * $formats = $formats[$index];
   */
  $index = $item->printParameter(0);
  cdp("index = '$index'");
  $p0 = $editor->expressionToStatement('$user');
  $item->setParameter(0, $p0);

  // Get the parent = statement (i.e. node) this function call is part of.
  $parent = &$item->parent;
  // Get the statement list the parent is part of.
  $container = &$parent->container;
  // Insert a statement.
  $statement = $editor->textToStatements("global \$user;")->getElement(0);
  $container->insertBefore($parent, $statement, 'global');
  if ($index) {
    // Insert a statement.
    $assignment = $parent->data;
    $assign_variable = $assignment->values->getElement()->getElement()->toString();
    cdp($parent->data->print_r());
    $statement = $editor->textToStatements("$assign_variable = $assign_variable\[$index\];")->getElement(0);
    $container->insertAfter($parent, $statement, 'assignment');
  }
}

/**
 * Implements hook_upgrade_call_format_date_alter().
 */
function coder_upgrade_upgrade_call_format_date_alter(&$node, &$reader) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Change date types
  $date_type = $item->printParameter(1);
  $date_type = trim($date_type, "'\"");
  switch ($date_type) {
    case 'small':
      $editor->setParameter($item, 1, "'short'");
      break;
    case 'large':
      $editor->setParameter($item, 1, "'long'");
      break;
  }
}

/**
 * Implements hook_upgrade_call_format_plural_alter().
 */
function coder_upgrade_upgrade_call_format_plural_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $count = $item->parameters->count();
  if ($count < 5) {
    return;
  }

  $keys = array('langcode');
  $defaults = array("'XXX_YYY'");
  $string = $editor->arrayitize($item, 4, $keys, $defaults);

  $temp = $editor->expressionToStatement($string);
  $temp->getElement(0)->multiline = 0;
  cdp($temp->print_r());
  $item->setParameter(4, $temp);
}

/**
 * Implements hook_upgrade_call_form_clean_id_alter().
 */
function coder_upgrade_upgrade_call_form_clean_id_alter(&$node, &$reader) {
  // Get the function call object.
  $item = &$node->data;

  // http://drupal.org/node/224333#form_clean_id
  $name = &$item->name;
  $name['value'] = 'drupal_clean_css_identifier';
}

/**
 * Implements hook_upgrade_call_function_exists_alter().
 */
function coder_upgrade_upgrade_call_function_exists_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  // Change was reverted.
  //      $name['value'] = 'drupal_function_exists';

  // Change: db_is_active
  $p0 = trim($item->getParameter()->stripComments()->toString(), "'\"");
  if ($p0 == 'db_is_active') {
    // Replace with "class_exists('Database', FALSE)".
    $item->name['value'] = 'class_exists';
    $editor->setParameters($item, array("'Database'", 'FALSE'));
  }
}

/**
 * Implements hook_upgrade_call_jquery_ui_add_alter().
 */
function coder_upgrade_upgrade_call_jquery_ui_add_alter(&$node, &$reader) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // http://drupal.org/node/224333#jquery_ui
  // jquery_ui_add is now drupal_add_library which loads a single library.
  $name = &$item->name;
  $name['value'] = 'drupal_add_library';

  /*
   * Note: This is an interesting pattern that can be applied elsewhere.
   * If the parameter is a variable, then find the variable assignment and
   * replace the operand accordingly. Then go through the rest of the code.
   */
  $operand = $item->getParameter()->getElement();
  if ($item->getParameter()->isType(T_VARIABLE)) {
    // Parameter is a variable.
    $variable = $item->getParameter()->getElement()->findNode('value');
    $parent = $item->parent;
    // TODO This single search won't find multiple assignments to array variable.
    $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
    if ($statement) {
      $operand = &$statement->values->getElement()->findNode('operand', 'backward');
      cdp($operand);
    }
  }

  // Examine the type of the operand in the parameter.
  if (is_array($operand)) {
    // This is a simple string.
    $value = trim($operand['value'], "'\"");
    $editor->setParameter($item, 0, "'$value'");
  }
  elseif (get_class($operand) == 'PGPArray') {
    $current = $operand->values->first();
    while ($current->next != NULL) {
      if ($current->type == 'value') {
        $values[] = $current->data->toString();
      }
      $current = $current->next;
    }
    $editor->setParameter($item, 0, array_pop($values));
    if ($values) {
      $parent = &$item->parent;
      $container = &$parent->container;
      foreach ($values as $value) {
        $temp = $editor->textToStatements("drupal_add_library('system', {$value})")->getElement();
        $container->insertBefore($parent, $temp);
      }
    }
  }
  else { // elseif (get_class($operand) == 'PGPOperand') {
    // This would be a variable and should not occur.
    $statement = $editor->commentToStatement("// TODO {$operand->toString()} needs to be a string or multiple calls to drupal_add_library need to be made.");
    $item->insertStatementBefore($statement);
  }

  // Insert a new first parameter.
  $editor->insertParameter($item, 0, "'system'");
}

/**
 * Implements hook_upgrade_call_menu_path_is_external_alter().
 */
function coder_upgrade_upgrade_call_menu_path_is_external_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'url_is_external';
}

/**
 * Implements hook_upgrade_call_menu_tree_data().
 */
function coder_upgrade_upgrade_call_menu_tree_data_alter(&$node, &$reader) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Function now expects an array of links, rather than a query resource.
  $p1 = $item->getParameter()->getElement();
  if (!is_object($p1)) {
    // TODO
    return;
  }
  elseif (get_class($p1) == 'PGPOperand') {
    $resource = $p1->toString();
  }
  elseif (get_class($p1) == 'PGPFunctionCall') {
    $resource = '$result';
    $statement = $editor->textToStatements('$result = ' . $p1->toString())->getElement(0);
    $item->insertStatementBefore($statement);
  }
  // Insert statements.
  $statement = $editor->textToStatements('$list = array()')->getElement(0);
  $item->insertStatementBefore($statement);
  $statement = $editor->textToStatements("foreach ({$resource} as \$item) {\n\t\$list[] = \$item;\n}")->getElement(0);
  $item->insertStatementBefore($statement);
  $editor->setParameter($item, 0, '$list');
}

/**
 * Implements hook_upgrade_call_menu_valid_path_alter().
 */
function coder_upgrade_upgrade_call_menu_valid_path_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name; // NOT DONE
  $name['value'] = 'drupal_valid_path';
  //      cdp($item->parameters->print_r());
  $count = $item->parameters->count();
  if (!$count) {
    $editor->setParameter($item, 0, "'' /* TODO Please pass a menu path */");
    return;
  }
  coder_upgrade_convert_menu_valid_path($item, $reader, $editor);
}

/**
 * Implements hook_upgrade_call_module_invoke_alter().
 */
function coder_upgrade_upgrade_call_module_invoke_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  // http://drupal.org/node/224333#taxonomy_get_tree
  $depth = '$max_depth = NULL /* TODO Set this variable. */';
  $count = $item->parameters->count();
  // Confirm this call relates to our topic.
  if ($count > 2) {
    $p0 = $item->printParameter(0);
    $p1 = $item->printParameter(1);
    if ($p0 != "'taxonomy'" || $p1 != "'get_tree'") {
      cdp("FAILED to relate");
      return;
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
}

/**
 * Implements hook_upgrade_call_module_list_alter().
 */
function coder_upgrade_upgrade_call_module_list_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'module_implements';
  $editor->setParameters($item, array('$hook /* TODO Set this variable. */'));
}

/**
 * Implements hook_upgrade_call_module_rebuild_cache_alter().
 */
function coder_upgrade_upgrade_call_module_rebuild_cache_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'system_rebuild_module_data';
}

/**
 * Implements hook_upgrade_call_node_get_types_alter().
 */
function coder_upgrade_upgrade_call_node_get_types_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  if ($item->parameterCount() && !$item->getParameter()->isType(T_CONSTANT_ENCAPSED_STRING)) {
    // Add TODO comment.
    $item->insertStatementBefore($editor->commentToStatement('// TODO Please change this function call to node_type_get_$op based on the value of the $op variable.'));
    return;
  }

  $op = $item->printParameter(0);
  $node2 = $item->printParameter(1);
  $reset = $item->printParameter(2);

  // node_get_types($op) is now node_type_get_$op.
  $op = trim($op, "'\"");
  $op = $op ? $op : 'types';

  $item->parameters->clear();
  switch ($op) {
    case 'module':
      $op = 'base';
    case 'name':
    case 'type':
      $todo = '';
      if (strtoupper($node2) == 'NULL' || $node2 == '') {
        $node2 = $node2 == '' ? '$node' : $node2;
        $todo = ' /* TODO The $node parameter should not be null. Please declare and initialize a $node parameter. */';
      }
      $editor->setParameter($item, 0, $node2 . $todo);
      break;
  }

  $name = &$item->name;
  $name['value'] = 'node_type_get_' . $op;

  // node_type_clear() (to clear the static cache) is now a separate function.
  if ($reset && $reset != 'FALSE') {
    $statement = $editor->textToStatements("node_types_clear();")->getElement(0);
    $item->insertStatementBefore($statement);
  }
}
/**
 * Implements hook_upgrade_call_node_invoke_nodeapi_alter().
 */
function coder_upgrade_upgrade_call_node_invoke_nodeapi_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'module_invoke_all';

  if ($item->parameterCount() < 2) {
    $item->insertStatementBefore($editor->commentToStatement('// TODO The $hook parameter should not be null. Please declare and initialize a $hook parameter.'));
    $editor->insertParameter($item, 0, 'node_ . $hook /* TODO Set this variable. */');
    return;
  }

  $op = $item->getParameter(1);
  $p2 = $item->printParameter(2);
  $p3 = $item->printParameter(3);

  $item->deleteParameter(3);
  $item->deleteParameter(2);
  $item->deleteParameter(1);

  if ($op->isType(T_CONSTANT_ENCAPSED_STRING)) {
    $operation = trim($op->toString(), "'\"");
    switch ($operation) {
      case 'delete':
      case 'insert':
      case 'load':
      case 'prepare':
      case 'presave':
      case 'update':
      case 'validate':
        // This operation hook becomes node_x
        break;

      case 'prepare translation':
      case 'search result':
      case 'update index':
        // This operation hook becomes node_x_x
        $operation = str_replace(" ", "_", $operation);
        break;

      case 'alter':
        // This operation hook becomes node_build_alter
        $operation = 'build_alter';
        break;

      case 'delete revision':
        // This operation hook becomes node_revision_delete
        $operation = 'revision_delete';
        break;

      case 'print':
        // This operation hook becomes node_view with $view_mode = 'print'
        $operation = 'view';
        $p2 = "'print'";
        break;

      case 'rss item':
        // This operation hook becomes node_view with $view_mode = 'rss'
        $operation = 'view';
        $p2 = "'rss'";
        break;

      case 'view':
        // This operation hook becomes node_view with $view_mode = 'full' by default
        if ($p2 && !in_array(strtolower($p2), array('null', 'false'))) {
          $p2 = "'teaser'";
        }
        elseif ($p3 && !in_array(strtolower($p3), array('null', 'false'))) {
          $p2 = "'full'";
        }
        break;

      default:
        cdp("ERROR: Invalid case value");
        return;
    }
    $p0 = "'node_" . $operation . "'";
  }
  else {
    $p0 = "'node_' . " . $op->toString();
    // Let's assume $p2 is valid.
//    $p2 .= $p2 ? " /* TODO: Set this parameter based on the " . $op->toString() . " hook */" : '';
  }

  $editor->insertParameter($item, 0, $p0);
  if ($p2) {
    $editor->setParameter($item, 2, $p2);
  }
}

/**
 * Implements hook_upgrade_call_node_load_alter().
 */
function coder_upgrade_upgrade_call_node_load_alter(&$node, &$reader) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // First parameter no longer an array, so we need to use node_load_multiple().
  $p0 = $item->getParameter()->getElement();
  if (is_object($p0) && get_class($p0) == 'PGPArray') {
    if ($nid = $p0->findValue('nid')) {
      $item->setParameter(0, $nid);
    }
    else {
      $name = &$item->name;
      $name = 'node_load_multiple';

      if ($item->parameterCount() > 1) {
        // Add vid to conditions array if present
        // TODO Would it work to have passed nid and vid as params in D6?
        // If so, then we should allow for this.
        $key = $editor->expressionToStatement("'vid'");
        // TODO Add an API function to insert array item with or w/o key.
        $p0->values->insertLast($key, 'key');
        $assign = '=>';
        $p0->values->insertLast($assign, 'assign');
//      $value = $editor->expressionToStatement($item->printParameter(1));
        $p0->values->insertLast($item->getParameter(1), 'value');
        $p0->count++;
        cdp($p0);
//      $p1 = $item->printParameter(1); // TODO What if this has an assignment?
        $item->deleteParameter(1);

        $editor->insertParameter($item, 0, 'array()');
      }
      // TODO Maybe use array_shift to get the first node?
      $item->insertStatementBefore($editor->commentToStatement('// TODO node_load_multiple returns an array of nodes, rather than a single node'));
    }
  }
}

/**
 * Implements hook_upgrade_call__node_type_set_defaults_alter().
 */
function coder_upgrade_upgrade_call__node_type_set_defaults_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  // http://drupal.org/node/224333#node_type_base
  $name['value'] = 'node_type_set_defaults';
}

/**
 * Implements hook_upgrade_call_referer_uri_alter().
 */
function coder_upgrade_upgrade_call_referer_uri_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $expression = $editor->expressionToStatement("\$_SERVER['HTTP_REFERER']");
  $item = $expression->getElement(0);
}

/**
 * Updates require() and its siblings.
 */
function coder_upgrade_convert_require(&$item, &$reader) { // DONE
  cdp(__FUNCTION__);
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // These language elements are included by $reader in function call list.
  // Use with http://drupal.org/node/224333#absolute_includes

  // Eliminate parentheses (if any).
  $item->noparens = 1;

  // Get first parameter.
  $p0 = $item->getParameter();
  $operand = $p0->getElement();
  if ($operand instanceof PGPOperand && $operand->findNode('type') == T_STRING && $operand->findNode('value') == 'DRUPAL_ROOT') {
    // Nothing to change.
    cdp('leaving the routine');
    return;
  }
  if (is_array($operand) && $operand['type'] == T_CONSTANT_ENCAPSED_STRING) {
    if (strpos($operand['value'], "'./'") === 0) { // if ($operand['value'][0] == '.') {
      cdp('found ./');
      // Remove './' from the beginning of the string.
      $operand['value'] = str_replace('./', '', $operand['value']);
      cdp('value = ' . $operand['value']);
      if ($operand['value'] == "''" || $operand['value'] == '""') {
        cdp('deleteElement');
        $p0->deleteElement();
        $p0->deleteElement(); // This should be a concatenation operator.
      }
    }
  }
  // Prepend DRUPAL_ROOT before existing expression.
  $editor->setParameter($item, 0, "DRUPAL_ROOT . '/' . " . $p0->toString());
}

/**
 * Implements hook_upgrade_call_set_time_limit_alter().
 */
function coder_upgrade_upgrade_call_set_time_limit_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'drupal_set_time_limit';
}

/**
 * Implements hook_upgrade_call_system_theme_data_alter().
 */
function coder_upgrade_upgrade_call_system_theme_data_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'system_rebuild_theme_data';
}

/**
 * Implements hook_upgrade_call_t_alter().
 */
function coder_upgrade_upgrade_call_t_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $count = $item->parameters->count();
  if ($count < 3) {
    return;
  }

  $keys = array('langcode');
  $defaults = array("'XXX_YYY'");
  $string = $editor->arrayitize($item, 2, $keys, $defaults);

  $temp = $editor->expressionToStatement($string);
  $temp->getElement(0)->multiline = 0;
  cdp($temp->print_r());
  $item->setParameter(2, $temp);
}

/**
 * Implements hook_upgrade_call_taxonomy_del_term_alter().
 */
function coder_upgrade_upgrade_call_taxonomy_del_term_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'taxonomy_term_delete';
}

/**
 * Implements hook_upgrade_call_taxonomy_del_vocabulary_alter().
 */
function coder_upgrade_upgrade_call_taxonomy_del_vocabulary_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'taxonomy_vocabulary_delete';
}

/**
 * Implements hook_upgrade_call_taxonomy_form_all_alter().
 */
function coder_upgrade_upgrade_call_taxonomy_form_all_alter(&$node, &$reader) {
  cdp(__FUNCTION__);
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  $item->insertStatementBefore($editor->commentToStatement('// TODO taxonomy_form_all has been removed, use an autocomplete field instead.'));

  // Replace function call with array().
  // This is an example of deleting a function call reference.
  $string = str_replace(array('/*', '*/'), '', $item->toString());
  $temp = $editor->expressionToStatement("array() /* $string */");
  $node->container->insertListBefore($node, $temp);
  $node->container->delete($node);
}

/**
 * Implements hook_upgrade_call_taxonomy_get_term_alter().
 */
function coder_upgrade_upgrade_call_taxonomy_get_term_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'taxonomy_term_load';
}

/**
 * Implements hook_upgrade_call_taxonomy_get_tree_alter().
 */
function coder_upgrade_upgrade_call_taxonomy_get_tree_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
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
}

/**
 * Implements hook_upgrade_call_taxonomy_save_term_alter().
 */
function coder_upgrade_upgrade_call_taxonomy_save_term_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'taxonomy_term_save';
  $temp = $item->printParameters();
  $editor->setParameters($item, array('$term /* TODO Term object replaces array ' . $temp . ' */)'));
}

/**
 * Implements hook_upgrade_call_taxonomy_save_vocabulary_alter().
 */
function coder_upgrade_upgrade_call_taxonomy_save_vocabulary_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'taxonomy_vocabulary_save';
  $temp = $item->printParameters();
  $editor->setParameters($item, array('$vocabulary /* TODO Vocabulary object replaces array ' . $temp . ' */)'));
}

/**
 * Implements hook_upgrade_call_theme_alter().
 */
function coder_upgrade_upgrade_call_theme_alter(&$node, &$reader) { // DONE
  global $_coder_upgrade_theme_registry;

  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;

  $p0 = $item->getParameter();
  if (!$p0->isType(T_CONSTANT_ENCAPSED_STRING)) {
    // TODO Look for the assignment to the theme hook (a variable or expression).
    $item->insertStatementBefore($editor->commentToStatement('// TODO Please change this theme call to use an associative array for the $variables parameter.'));
    return;
  }

  // Process changes to specific themes.
  $theme = trim($item->printParameter(), "'\"");
  // This change is not documented.
  // Width and height parameters have been added after path.
  if ($theme == 'image' || $theme == 'image_style') { // DONE
    $index = $theme == 'image' ? 2 : 3;
    if ($item->parameterCount() > $index) {
      // Delete $getsize parameter.
      $item->deleteParameter($index + 3);
      // Insert placeholders for width and height parameters.
      $editor->insertParameter($item, $index, "''");
      $editor->insertParameter($item, $index + 1, "''");
    }
  }
  // http://drupal.org/node/224333#theme_page
  if ($theme == 'page') { // DONE
    $item->insertStatementBefore($editor->commentToStatement('// TODO Please change this theme call as discussed at http://drupal.org/node/224333#theme_page.'));
    // Get the statement (i.e. node) this function call is part of.
    $parent = &$item->parent;
    // Comment out the statement.
    $text = $parent->data->toString();
    $parent->data = $editor->textToStatements('// ' . $text)->getElement();
    return;
  }
  // http://drupal.org/node/224333##theme_pager
  // Limit parameter has been removed.
  if ($theme == 'pager') { // DONE
    $item->deleteParameter(2); // Does nothing if no third parameter.
  }
  // http://drupal.org/node/224333#placeholder
  // theme('placeholder') has been replaced by drupal_placeholder().
  if ($theme == 'placeholder') { // DONE
    $item->deleteParameter();
    $name['value'] = 'drupal_placeholder';
    return;
  }
  // http://drupal.org/node/224333#theme_username
  // theme('username') parameters have changed.
  // Note: this is automatically handled below.
//  if ($theme == 'username') { // DONE
//    $p1 = $item->printParameter(1);
//    $p1 = "array('account' => $p1)";
//    $editor->setParameter($item, 1, $p1);
//    return;
//  }

  /*
   * http://drupal.org/node/224333#theme_changes
   *
   * In module pre-processing, create a global variable to hold the array of
   * theme registrations for all core files (including disabled modules). Add
   * to this array the theme entries for the current module. Find the current
   * theme call in the global list to get the names of its parameters.
   * Array-itize the parameters.
   *
   * See drupal_common_theme() in common.inc and hook_theme in the core modules.
   *
   * See http://drupal.org/files/issues/theme-wip-572618-83.patch
   */

  $theme = trim($item->printParameter(0), "'\"");
  if (!isset($_coder_upgrade_theme_registry[$theme])) {
    clp("ERROR: Theme entry for '$theme' not found in theme registry or hook_theme");
    $item->insertStatementBefore($editor->commentToStatement('// TODO Please change this theme call to use an associative array for the $variables parameter.'));
    return;
  }
  $hook = $_coder_upgrade_theme_registry[$theme];

  if (isset($hook['variables']) && $hook['variables']) {
    $count = $item->parameterCount();
    // TODO Incorporate default value elimination into this.
    if ($count == 1 /*|| $count - 1 != count($hook['variables'])*/) {
      // This theme call is missing some or all of the variables parameters.
      $item->insertStatementBefore($editor->commentToStatement('// TODO Please change this theme call to use an associative array for the $variables parameter.'));
      return;
    }
    elseif ($count - 1 > count($hook['variables'])) {
      // The number of parameters to this theme call exceeds the number of
      // variables parameters defined in hook_theme.
      clp("ERROR: Number of parameters in call to theme '$theme' exceeds the number of parameters found in theme registry or hook_theme");
      $item->insertStatementBefore($editor->commentToStatement('// TODO Please change this theme call to use an associative array for the $variables parameter.'));
      return;
    }

    $defaults = array_fill(0, $count - 1, "'XXX_YYY'");
    $string = $editor->arrayitize($item, 1, array_keys($hook['variables']), $defaults);
    $temp = $editor->expressionToStatement($string);
    $temp->getElement(0)->multiline = 0;
    $item->setParameter(1, $temp);
  }
}

/**
 * Implements hook_upgrade_call_time_alter().
 */
function coder_upgrade_upgrade_call_time_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $expression = $editor->expressionToStatement('REQUEST_TIME');
  cdp($expression->print_r());
  $item = $expression->getElement(0);
}

/**
 * Implements hook_upgrade_call_update_sql_alter().
 *
 * @todo Move this routine to db.inc.
 */
function coder_upgrade_upgrade_call_update_sql_alter(&$node, &$reader) {
  cdp(__FUNCTION__);
  // Change: update_sql
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  $item->insertStatementBefore($editor->commentToStatement('// TODO update_sql has been removed. Use the database API for any schema or data changes.'));

  // Replace function call with array().
  // This is an example of deleting a function call reference.
  $string = str_replace(array('/*', '*/'), '', $item->toString());
  $temp = $editor->expressionToStatement("array() /* $string */");
  $node->container->insertListBefore($node, $temp);
  $node->container->delete($node);
}

/**
 * Implements hook_upgrade_call_url_alter().
 */
function coder_upgrade_upgrade_call_url_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  if ($item->parameterCount() < 2) {
    // Nothing to do.
    return;
  }

  // Convert query string into an array
  $p1 = $item->getParameter(1)->getElement();
  if (!is_object($p1) || !$p1->isType(/*'PGPArray'*/ T_ARRAY)) {
    // Add TODO comment.
    $item->insertStatementBefore($editor->commentToStatement('// TODO The second parameter to this function call should be an array.'));
    return;
  }

  if ($query = &$p1->findValue('query')) {
    if ($query->isType(T_CONSTANT_ENCAPSED_STRING)) {
      $query = coder_upgrade_query_to_array($query->first()->data['value']);
    }
  }
}

/**
 * Implements hook_upgrade_call_user_authenticate_alter().
 */
function coder_upgrade_upgrade_call_user_authenticate_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $count = $item->parameters->count();
  if ($count == 0) {
    $editor->setParameters($item, array('$name', '$password /* TODO Set these variables */'));
    return;
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
    $parameter = $item->printParameter();
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
    $name = $operand->findValue('name')->toString();
    $password = $operand->findValue('pass')->toString();
    // Set the parameters on this function call.
    $editor->setParameters($item, array($name, $password));
  }
}

/**
 * Implements hook_upgrade_call_user_delete_alter().
 */
function coder_upgrade_upgrade_call_user_delete_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
  $name['value'] = 'user_cancel';
  $editor->setParameter($item, 2, "\$method = 'user_cancel_block' /* TODO Set this variable */");
}

/**
 * Implements hook_upgrade_call_user_load_alter().
 */
function coder_upgrade_upgrade_call_user_load_alter(&$node, &$reader) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  if (!$item->parameterCount()) {
    // No parameters is an acceptable default in D7, but should cause an
    // uncaught error in D6. In D7, this will cause all users to be loaded.
    $item->name['value'] = 'user_load_multiple';
    return;
  }

  /*
   * Steps
   * - parameter may be a value, array, or variable (with a preceding assignment)
   * - value:
   *   - leave as is
   * - array
   *   - extract 'uid' element
   *   - leave remaining items as $conditions in new function
   *   - change function to user_load_multiple
   *   - wrap in array_shift to return first item
   * - variable:
   *   - if variable is an array item, eg. $var['uid']
   *     - then handle like value above (NOT DONE -- could also be an array)
   *   - if variable has an assignment statement in scope
   *     - then handle like array above
   *       (attempt to extract uid from other conditions)
   */

  $p0 = FALSE;
  if ($item->getParameter()->isType(T_VARIABLE)) {
    // Parameter is a variable.
    $variable = $item->getParameter()->findNode('operand')->findNode('value');
    $parent = $item->parent;
    // TODO This single search won't find multiple assignments to array variable.
    $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
    if ($statement) {
      $operand = &$statement->values->getElement()->findNode('operand', 'backward');
      $p0 = coder_upgrade_convert_user_load($item, $operand, FALSE);
      if (is_object($operand) && $operand->isType(T_ARRAY) && !$operand->count) {
        // Assignment variable has no more value in its array.
        // So delete this parameter from the function call.
        $item->deleteParameter();
      }
    }
    else {
      // Assume the variable is the uid?
      $text = $item->getParameter()->stripComments()->toString();
      $item->insertStatementBefore($editor->commentToStatement('// TODO Convert "user_load" to "user_load_multiple" if "' . $text . '" is other than a uid.'));
      $item->insertStatementBefore($editor->commentToStatement('// To return a single user object, wrap "user_load_multiple" with "array_shift" or equivalent.'));
      $item->insertStatementBefore($editor->commentToStatement('// Example: array_shift(user_load_multiple(array(), ' . $text . '))'));
    }
  }
  else {
    $operand = &$item->getParameter()->findNode('operand');
    $p0 = coder_upgrade_convert_user_load($item, $operand);
    if ($item->getParameter()->isType(T_ARRAY)) {
      // Parameter is an array.
      $array = $item->getParameter()->getElement();
      if (!$array->count) {
        $item->deleteParameter();
      }
    }
  }
  if ($p0) {
    $item->insertParameter(0, $p0);
  }
  if ($item->name['value'] == 'user_load_multiple') {
    // Wrap current call with array_shift to return first object from array.
    $call = $item->toString();
    $item = $editor->expressionToStatement("array_shift($call)");
  }
}

function coder_upgrade_convert_user_load(&$item, &$operand, $is_parameter = TRUE) { // DONE
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // TODO We need an isType() that is not a class method.
  if (is_array($operand) && $operand['type'] == T_CONSTANT_ENCAPSED_STRING) {
    // Value is a string. (Assume it is an integer.)
//    $uid = trim($operand['value'], "'\"");
//    $operand = $editor->expressionToStatement("array($uid)");
    return FALSE; // return $is_parameter ? $operand : FALSE;
  }
  elseif (is_array($operand)) {
    // Unexpected.
  }
  elseif (is_object($operand) && $operand->isType(T_ARRAY)) {
    $array = &$operand;
    if ($uid = $array->findValue('uid')) {
      // Array contains a value for key = 'uid'
      $array->deleteKey('uid');
      if ($array->count) {
        // If other conditions, then need to use user_load_multiple.
        $p0 = $editor->expressionToStatement("array(" . $uid->toString() . ")");
        $item->name['value'] = 'user_load_multiple';
      }
      else {
        // Stay with user_load.
        $p0 = $editor->expressionToStatement($uid->toString());
      }
    }
    else {
      // Create empty array for $uids parameter.
      $p0 = $editor->expressionToStatement('array()');
      $item->name['value'] = 'user_load_multiple';
    }
    return $p0;
  }
  elseif (is_object($operand)) {
    // Unexpected.
  }
  else {
    // Value is a number.
//    $uid = trim($operand, "'\"");
//    $operand = $editor->expressionToStatement("array($uid)");
    return FALSE; // return $is_parameter ? $operand : FALSE;
  }

  return FALSE;
}

/**
 * Implements hook_upgrade_call_variable_get_alter().
 */
function coder_upgrade_upgrade_call_variable_get_alter(&$node, &$reader) { // (OMIT)
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
}

/**
 * Implements hook_upgrade_call_variable_set_alter().
 */
function coder_upgrade_upgrade_call_variable_set_alter(&$node, &$reader) { // (OMIT)
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Process function call.
  $name = &$item->name;
}

/**
 * Updates menu_valid_path().
 *
 * Copied from hook_node_info() change.
 *
 * NOTE
 * In general, there are 3 typical cases (or code styles):
 * Case 1: passes variable directly.
 * if (!menu_valid_path(array('link_path' => $expression))) { ... }
 *
 * Case 2: makes one assignment to array variable; passes variable.
 * $item = array('link_path' => $expression);
 * if (!menu_valid_path($item)) { ... }
 *
 * Case 3: makes multiple assignments to array variable; passes variable.
 * $item['link_path'] = $expression1;
 * $item['link_title'] = $expression2;
 * if (!menu_valid_path($item)) { ... }
 *
 * [The inner array to modify is 3 levels deep in the first 2 cases, but only
 * 2 levels deep in the third. In the first 2 cases, we can loop on the key1
 * arrays. In the third, the loop is on assignment statements.]
 */
function coder_upgrade_convert_menu_valid_path(&$item, &$reader, &$editor) { // DONE
  cdp("inside " . __FUNCTION__);

  $operand = $item->getParameter()->getElement();
  cdp($operand->print_r());

  // Examine the type of the operand in the parameter.
  if (get_class($operand) == 'PGPArray') {
    // Use case 1 - passes variable directly.
    cdp("Case 1: passes variable directly");
    coder_upgrade_callback_menu_valid_path($item, $operand);
  }
  elseif (get_class($operand) == 'PGPOperand') {
    $p0 = $operand->toString();
    if ($operand->count() > 2) {
      // Use case 4 - passes more complex variable directly. (NOT HANDLED)
      // The operand passed is more complex than a variable name. It might
      // be an expression like $item['xx'] or $item->xx.
      clp("ERROR: Variable expression $p0 passed as parameter in menu_valid_path");
      $editor->setParameter($item, 0, "$p0 /* TODO Please pass a menu path directly */");
      return;
    }
    if ($operand->getElement(0) != T_VARIABLE) {
      clp("ERROR: Parameter $p0 is not a variable in menu_valid_path");
      return;
    }

    $variable = $operand->getElement(1);
    cdp("variable = $variable");

    // Get the statement (i.e. node) this function call is part of.
    $parent = &$item->parent;
    // Get the statement list the parent is part of.
    $container = &$parent->container;
    // Search the container for assignment to the variable.

    /*
     * Loop on body statements until we find an assignment to the parameter
     * variable. Loop in reverse from the parent statement to find the last
     * setting of the variable.
     */

    $parameter_variable = $operand->toString();
    $count = 0;

    $current = $parent->previous;
    while ($current->previous != NULL) {
      if (is_object($current->data) && $current->data->type == T_ASSIGNMENT) {
        $assignment = $current->data;
        $assign_variable = $assignment->values->getElement()->getElement()->toString();
        if ($parameter_variable == $assign_variable) {
          // Use case 2: makes one assignment to array variable; pass variable.
          cdp("Case 2: Assignment variable matches parameter variable");
          $value1 = $assignment->values->getElement();
          $array1 = $value1->getElement($value1->count() - 1);
          coder_upgrade_callback_menu_valid_path($item, $array1);
          //          $count++;
          return;
        }
        elseif (strpos($assign_variable, $parameter_variable) !== FALSE && strpos($assign_variable, 'link_path') !== FALSE) {
          // Use case 3: makes multiple assignments to array variable; pass variable.
          cdp("Case 3: Assignment variable includes parameter variable");
          $value1 = $assignment->values->getElement();
          $value2 = $value1->getElement($value1->count() - 1);
          // Make an expression object to use as function call parameter.
          $expression = new PGPExpression();
          $expression->insertLast($value2, 'operand');
          $item->setParameter(0, $value2);
          cdp($item->toString());
          //          $count++;
          return;
        }
      }
      $current = $current->previous;
    }
    if (!$count) {
      clp("ERROR: Assignment statement to parameter variable not found in menu_valid_path");
      return;
    }
  }
}

/**
 * Changes function call parameter.
 *
 * @param PGPFunctionCall $item
 * @param PGPArray $operand
 */
function coder_upgrade_callback_menu_valid_path(&$item, &$operand) { // DONE
  cdp("inside " . __FUNCTION__);
  // TODO This key value could also be in double quotes.
  $value = $operand->findValue('link_path');
  cdp($value->print_r());
  $item->setParameter(0, $value);
  cdp($item->toString());
}

/**
 * Comments out taxonomy synonym functions.
 */
function coder_upgrade_convert_taxonomy_synonyms(&$item) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Comment out function.
  // Replace function call with default return value (so code will theoretically still run).
  $item->insertStatementBefore($editor->commentToStatement('// TODO The taxonomy synonym functionality has been removed.'));
  $item->insertStatementBefore($editor->commentToStatement('// To replace this functionality, you can add a synonym field to your vocabulary.'));
  $temp = $item->toString();
  $item = $editor->expressionToStatement('array() /*' . $temp . '*/');
}
