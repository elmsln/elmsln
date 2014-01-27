<?php
/**
 * @file
 * Provides conversion routines applied to functions (or hooks).
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
 *
 * System
 * http://drupal.org/node/224333#search-api (TODO another hook_$op change)
 *
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
 * http://drupal.org/node/224333#block_deltas_renamed
 *
 *
 * Menus
 * http://drupal.org/node/224333#hook_menu_link_alter
 *
 *
 * Blocks
 * http://drupal.org/node/224333#remove_op (DUP Node API)
 * http://drupal.org/node/224333#block_deltas_renamed (DUP Database)
 *
 *
 * Comments
 * http://drupal.org/node/224333#remove_op (DUP Node API) (THIS IS MISSING FROM THE CHRONO PAGE!!!)
 *
 *
 * Input Sanitization and Input Formats
 * http://drupal.org/node/224333#hook_filter_info
 *
 *
 * Theming
 * http://drupal.org/node/224333#drupal_render_children
 * http://drupal.org/node/224333#theme_changes
 * http://drupal.org/node/224333#hook_theme_render_changes
 *
 *
 * Form API
 * http://drupal.org/node/224333#node_form
 * http://drupal.org/node/224333#hook_forms_signature
 * http://drupal.org/node/224333#hook_element_info
 *
 *
 * User API
 * http://drupal.org/node/224333#user_cancel (DONE with remove_op)
 * http://drupal.org/node/224333#remove_op (DUP Node API)
 * http://drupal.org/node/224333#hook-user-changes (two alter hooks in this file)
 *
 *
 * Node API
 * http://drupal.org/node/224333#node_links (NOT DONE)
 * http://drupal.org/node/224333#node_type_base
 * http://drupal.org/node/224333#remove_op (SPANS MULTIPLE HOOKS)
 * http://drupal.org/node/224333#node_build_rss
 * http://drupal.org/node/224333#build_mode
 * http://drupal.org/node/224333#hook_node_xxx
 * http://drupal.org/node/224333#hook_load_signature
 *
 *
 * Miscellaneous
 * http://drupal.org/node/224333#implementation_hook_comment
 * http://drupal.org/node/224333#trigger_overhaul
 */

/**
 * Implements hook_upgrade_hook_alter().
 */
function coder_upgrade_upgrade_hook_alter(&$node, &$reader, $hook) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;

  $editor = PGPEditor::getInstance();
  // Changes: implementation_hook_comment
  if ($item->comment) {
    // Update document comment for hook implementations.
    $item->comment = preg_replace('@\*\s+[iI]mplement.*?(hook_.*?)(\(\)|)(\.|)$@m', "* Implements $1().", $item->comment);
  }
  else {
    // Add a document comment.
    $item->comment = $editor->commentToStatement("/**\n * @todo Please document this function.\n * @see http://drupal.org/node/1354\n */");
  }

  global $_coder_upgrade_menu_registry, $_coder_upgrade_theme_registry;
  cdp($node->data->name);
  if (in_array($node->data->name, $_coder_upgrade_menu_registry)) {
    // http://drupal.org/node/224333#hook_forms_signature
    coder_upgrade_convert_form_callback($node);
  }
  elseif (strpos($node->data->name, 'theme_') === 0) {
    $theme_name = substr($node->data->name, strpos($node->data->name, "theme_") + 6);
    if (isset($_coder_upgrade_theme_registry[$theme_name])) {
      // http://drupal.org/node/224333#drupal_render_children
      // http://drupal.org/node/224333#theme_changes
      coder_upgrade_convert_theme_callback($node);
    }
    else {
      $msg = 'TODO: Should this theme ' . $theme_name . ' be declared in hook_theme()?';
      clp($msg);
      $node->data->body->insertFirst($editor->commentToStatement($msg));
    }
  }
}

function coder_upgrade_convert_form_callback(&$node) {
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;

  $editor = PGPEditor::getInstance();
  if (!$item->parameterCount()) {
    // No parameters; insert the $form and $form_state parameters.
    $item->insertParameter(0, $editor->expressionToStatement('$form'));
    $item->insertParameter(1, $editor->expressionToStatement('&$form_state'));
    return;
  }
  // Insert the $form parameter (if not already inserted).
  $p0 = $item->getParameter()->stripComments()->toString(); // TODOxxx use getParameterVariable???
  if ($p0 == '&$form_state' || $p0 == '$form_state' || $p0 != '$form') { // if ($p0 != '$form') {
    $item->insertParameter(0, $editor->expressionToStatement('$form'));
  }
}

/**
 * Updates theme_xxx() functions.
 *
 * Parameters are arrayitized.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_theme_callback(&$node) {
  global $_coder_upgrade_theme_registry;

  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Changes: drupal_render_children, theme_changes
  $item = &$node->data;
  $body = &$item->body;

  // Save the parameters for later.
  $parameters = array();
  for ($i = 0; $i < $item->parameterCount(); $i++) {
    // Allow for default values, e.g. $var = NULL.
    if ($temp = $item->getParameterVariable($i)) {
      // The parameter includes a variable; save the variable.
      $parameters[] = $temp->toString();
    }
    else {
      // The parameter has no variable.
      // Example: function foo(/*$form = NULL*/, , 'xxx') {}
      $parameters[] = '$xx_missing_xx';
    }
  }
  // Delete the current parameters.
  $item->parameters->clear();

  // Case 1: Theme function with no parameters
  // - leave the new function with no parameters
  // Case 2: Theme function whose signature omits some or all of the parameters
  // declared in the module's hook_theme()
  // - replace the function parameters with $variable
  // - insert assignment statements for each of the declared parameters
  // - log an error message about the missing signature parameters

  // Reassign function parameters to corresponding $variables array key.
  $theme_name = substr($item->name, strpos($item->name, "theme_") + 6);
  if (isset($_coder_upgrade_theme_registry[$theme_name])) {
    $hook = $_coder_upgrade_theme_registry[$theme_name];
    if (isset($hook['render element'])) {
      // In coder_upgrade_cache_info_hooks(), $hook key === 'variables'
      // for a theme defined by the module being upgraded, Thus, this
      // condition is not hit.

      // Replace the parameters by $variable, an array.
      $editor->setParameter($item, 0, '$variables');
      if (!isset($parameters[0])) {
        clp('ERROR: No parameter in signature of theme_' . $theme_name . '()');
        return;
      }
      $string = $parameters[0] . ' = $variables[\'' . $hook['render element'] . '\']';
      $body->insertFirst($editor->textToStatements($string)->getElement(0));
    }
    elseif (isset($hook['variables'])) {
      if (count($parameters) != count($hook['variables'])) {
        // The number of parameters to this theme function differs from the
        // number of variables parameters defined in hook_theme.
        clp("ERROR: Number of parameters in theme funcion '$theme_name' does not match number of parameters found in hook_theme");
        $body->insertFirst($editor->commentToStatement('// TODO Number of parameters in this theme funcion does not match number of parameters found in hook_theme.'), 'comment');
//         return;
      }
      if (empty($hook['variables'])) {
        // New function should also have no parameters.
        clp('INFO: hook_theme() for theme ' . $theme_name . ' has no parameters');
        return;
      }
      // Replace the parameters by $variable, an array.
      $editor->setParameter($item, 0, '$variables');
      $empty = FALSE;
      if (!($sentinel = $body->get(0))) {
        // Add a sentinel -- a marker for insertion.
        $sentinel = $body->insertFirst(NULL, 'sentinel');
        $empty = TRUE;
      }
      // Add an assignment statement for each of the previous function parameters.
      $i = 0;
      foreach ($hook['variables'] as $key => $value) {
        if (!isset($parameters[$i])) {
          clp('ERROR: No parameter ' . $i . ' in signature of theme_' . $theme_name . '()');
          break;
        }
        if ($parameters[$i] == '$xx_missing_xx') {
          $body->insertBefore($sentinel, $editor->commentToStatement('// TODO: Name this variable which was missing in the old function signature.'));
        }
        $string = $parameters[$i] . ' = $variables[\'' . $key . "'];\n";
        $body->insertBefore($sentinel, $editor->textToStatements($string)->getElement(0));
        $i++;
      }
      if ($empty) {
        $body->delete($sentinel);
      }
    }
  }

  // If theme function calls drupal_render, make sure last call is to drupal_render_children
  // to avoid endless loops: http://drupal.org/node/224333#drupal_render_children
  if ($statement = $body->searchBackward('PGPFunctionCall', 'name', 'value', 'drupal_render')) {
    $statement->name['value'] = 'drupal_render_children';
  }
}

/**
 * Implements hook_upgrade_hook_access_alter().
 */
function coder_upgrade_upgrade_hook_access_alter(&$node, &$reader) {
  // Changes: hook_node_access
  coder_upgrade_convert_access($node);
}

/**
 * Implements hook_upgrade_hook_action_info_alter().
 */
function coder_upgrade_upgrade_hook_action_info_alter(&$node, &$reader) {
  // Changes: trigger_overhaul
  coder_upgrade_convert_return($node->data->body, 'action_info', '', 1, 1);
}

/**
 * Implements hook_upgrade_hook_block_alter().
 */
function coder_upgrade_upgrade_hook_block_alter(&$node, &$reader) {
  // Changes: block_deltas_renamed
  // Changes: remove_op
  $callback = 'coder_upgrade_callback_block';
  $op_index = 0;
  coder_upgrade_convert_op($node, $callback, $op_index);
}

/**
 * Implements hook_upgrade_hook_comment_alter().
 */
function coder_upgrade_upgrade_hook_comment_alter(&$node, &$reader) {
  // Changes: remove_op
  $callback = 'coder_upgrade_callback_comment';
  $op_index = 1;
  coder_upgrade_convert_op($node, $callback, $op_index);
}

/**
 * Implements hook_upgrade_hook_elements_alter().
 */
function coder_upgrade_upgrade_hook_elements_alter(&$node, &$reader) {
  global $_coder_upgrade_module_name;
  $item = &$node->data;
  // Rename function.
  $item->name = $_coder_upgrade_module_name . '_element_info';
  // Update document comment.
  $item->comment = preg_replace('@hook_elements@', "hook_element_info", $item->comment);
}

/**
 * Implements hook_upgrade_hook_filter_alter().
 */
function coder_upgrade_upgrade_hook_filter_alter(&$node, &$reader) {
  // Changes: hook_filter_info
  coder_upgrade_convert_filter($node, $reader);
}

/**
 * Implements hook_upgrade_hook_form_alter().
 */
function coder_upgrade_upgrade_hook_form_alter_alter(&$node, &$reader) {
  // Changes: node_form
  $editor = PGPEditor::getInstance();

  /*
   * What if:
   * - the code uses a name other than $form?
   * - the conditions are in different order or on multiple lines?
   */

  // Conditions to test for a node edit form.
  $node_form_conditional =
    '/isset\(\$form\[\'type\'\]\)\s*&&\s*' .
    'isset\(\$form\[\'#node\'\]\)\s*&&\s*' .
    '\$form\[\'type\'\]\[\'#value\'\]\s*.\s*\'_node_form\' == \$form_id/';

  // Loop on the body statements looking for conditional statment.
  $current = &$node->data->body->first();
  while ($current->next != NULL) {
    $statement = &$current->data;
    if ($statement instanceof PGPConditional) {
      // Get the list of conditons.
      $conditions = $statement->conditions;

      // Check if conditions match node form check.
      if ($conditions instanceof PGPList) {
        $conditions = $conditions->toString();
        if (preg_match($node_form_conditional, $conditions)) {
          // Replace verbose node edit form condtional.
          $conditions = preg_replace($node_form_conditional, '!empty($form[\'#node_edit_form\'])', $conditions);
          $statement->conditions = $editor->expressionToStatement($conditions);
        }
      }
    }
    // Move to next node.
    $current = &$current->next;
  }
}

/**
 * Implements hook_upgrade_hook_hook_info_alter().
 */
function coder_upgrade_upgrade_hook_hook_info_alter(&$node, &$reader) {
  // Changes: trigger_overhaul
  $item = &$node->data;

  global $_coder_upgrade_module_name;

  // Rename function.
  $item->name = $_coder_upgrade_module_name . '_trigger_info';
  // Update document comment.
  $item->comment = preg_replace('@hook_hook_info@', "hook_trigger_info", $item->comment);

  // Restructure the triggers array.
  coder_upgrade_convert_return($node->data->body, 'hook_info', '', 1, 1);
}

/**
 * Implements hook_upgrade_hook_install_alter().
 */
function coder_upgrade_upgrade_hook_install_alter(&$node, &$reader) {
  // Changes: install-schema
  coder_upgrade_convert_install($node);
}

/**
 * Implements hook_upgrade_hook_uninstall_alter().
 */
function coder_upgrade_upgrade_hook_uninstall_alter(&$node, &$reader) {
  // Changes: install-schema
  coder_upgrade_convert_install($node);
}

/**
 * Implements hook_upgrade_hook_link_alter().
 */
function coder_upgrade_upgrade_hook_link_alter(&$node, &$reader) {
  // Changes: build_mode and others !!!???
  coder_upgrade_convert_link($node);
}

/**
 * Implements hook_upgrade_hook_load_alter().
 */
function coder_upgrade_upgrade_hook_load_alter(&$node, &$reader) {
  // Changes: hook_load_signature
  $item = &$node->data;
  $body = &$item->body;

  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Save the name of first parameter.
  if ($p0 = $item->getParameterVariable()) {
    // The parameter includes a variable; save the variable.
    $p0 = $p0->toString();
    $p0_new = $p0 . 's';
  }
  else {
    // The parameter has no variable.
    $p0 = '$xx_missing_xx';
    $p0_new = '$nodes';
    $body->insertFirst($editor->commentToStatement('// TODO: Name the variable ' . $p0 . ' which was missing in the old function signature.'));
  }
  // Add 's' to name of first parameter.
  $editor->setParameter($item, 0, $p0_new);

  // Search for a return statement.
  if (!($return = &$body->find(T_RETURN, 'reverse'))) {
    $msg = 'ERROR: return statement not found in hook_load';
    clp($msg);
    $body->insertFirst($editor->commentToStatement($msg), 'comment');
    return;
  }

  $value = &$return->getParameter();
  $return_parameter = $value->toString();
  if (!$value->isType(T_VARIABLE)) {
    // Insert an assignment statement with the value being the return operand.
    $statement = $editor->textToStatements('$node_additions = ' . $value->toString())->getElement();
    $return->insertStatementBefore($statement);
    // Replace the operand to the return statement with a variable.
    $return = $editor->textToStatements('return $node_additions')->getElement();
    $return_parameter = '$node_additions';
  }

  // Replace the return statement with a foreach loop on each node object.
  $strings[] = 'foreach (' . $return_parameter . ' as $property => &$value) {';
  $strings[] = '  ' . $p0 . '->$property = $value;';
  $strings[] = '}';
  $return = $editor->textToStatements(implode("\n", $strings))->getElement();

  // Wrap the body in a foreach loop on $nodes.
  unset($strings);
  $strings[] = 'foreach (' . $p0_new . ' as $nid => &' . $p0 . ') {';
  $strings[] = '}';
  $loop = $editor->textToStatements(implode("\n", $strings))->getElement();

  $loop->body = $item->body;
  $body = new PGPBody();
  $body->insertLast($loop);
  $item->body = $body;
}

/**
 * Implements hook_upgrade_hook_menu_link_alter_alter().
 */
function coder_upgrade_upgrade_hook_menu_link_alter_alter(&$node, &$reader) {
  // Changes: hook_menu_link_alter
  coder_upgrade_convert_menu_link_alter($node);
}

/**
 * Implements hook_upgrade_hook_nodeapi_alter().
 */
function coder_upgrade_upgrade_hook_nodeapi_alter(&$node, &$reader) {
  // Changes: build_mode, remove_op and others !!!???
  $callback = 'coder_upgrade_callback_nodeapi';
  $op_index = 1;
  coder_upgrade_convert_op($node, $callback, $op_index);
}

/**
 * Implements hook_upgrade_hook_node_info_alter().
 */
function coder_upgrade_upgrade_hook_node_info_alter(&$node, &$reader) {
  // Changes: node_type_base
  coder_upgrade_convert_return($node->data->body, 'node_info', '', 1, 1);
}

/**
 * Implements hook_upgrade_hook_node_type_alter().
 */
function coder_upgrade_upgrade_hook_node_type_alter(&$node, &$reader) {
  // Changes: remove_op
  $callback = 'coder_upgrade_callback_node_type';
  $op_index = 0;
  coder_upgrade_convert_op($node, $callback, $op_index);
}

/**
 * Implements hook_upgrade_hook_perm_alter().
 */
function coder_upgrade_upgrade_hook_perm_alter(&$node, &$reader) {
  // Changes: hook_permission and descriptions_permissions
  $item = &$node->data;

  // Rename function.
  $item->name .= 'ission';
  // Update document comment.
  $item->comment = preg_replace('@hook_perm([^i])@', "hook_permission$1", $item->comment);

  // Restructure the permissions array.
  coder_upgrade_convert_return($node->data->body, 'perm', '', 0, 0);
}

/**
 * Implements hook_upgrade_hook_profile_alter_alter().
 */
function coder_upgrade_upgrade_hook_profile_alter_alter(&$node, &$reader) {
  // Changes: hook-user-changes
  $item = &$node->data;
  $body = &$item->body;

  // Create helper objects.
  $editor = PGPEditor::getInstance();

  global $_coder_upgrade_module_name;

  // Rename function.
  $item->name = $_coder_upgrade_module_name . '_user_view';
  // Update document comment.
  $item->comment['value'] = preg_replace('@hook_profile_alter([^i])@', "hook_user_view$1", $item->comment['value']);

  // Remove '&' from first parameter.
//   $p0 = str_replace('&', '', $item->getParameter()->stripComments()->toString());

  // Save the name of first parameter.
  if ($p0 = $item->getParameterVariable()) {
    // The parameter includes a variable; save the variable.
    // Remove '&' from first parameter.
    $p0 = str_replace('&', '', $p0->toString());
  }
  else {
    // The parameter has no variable.
    $p0 = '$xx_missing_xx';
    $body->insertFirst($editor->commentToStatement('// TODO: Name the variable ' . $p0 . ' which was missing in the old function signature.'));
  }

  // Add $view_mode parameter.
  $editor->setParameters($item, array($p0, '$view_mode'));
}

/**
 * Implements hook_upgrade_hook_schema_alter().
 */
function coder_upgrade_upgrade_hook_schema_alter(&$node, &$reader) {
  // Changes: schema_translation and schema_html
  coder_upgrade_convert_schema($node);
}

/**
 * Implements hook_upgrade_hook_theme_alter().
 */
function coder_upgrade_upgrade_hook_theme_alter(&$node, &$reader) {
  // Changes: hook_theme_render_changes
  coder_upgrade_convert_return($node->data->body, 'theme', '', 1, 1);
}

/**
 * Implements hook_upgrade_hook_update_N_alter().
 */
function coder_upgrade_upgrade_hook_update_N_alter(&$node, &$reader) {
  // Changes: update_php, update_sql
  coder_upgrade_convert_update_N($node);
}

/**
 * Implements hook_upgrade_hook_user_alter().
 */
function coder_upgrade_upgrade_hook_user_alter(&$node, &$reader) {
  // Changes: remove_op, user_cancel and others !!!???
  $callback = 'coder_upgrade_callback_user';
  $op_index = 0;
  coder_upgrade_convert_op($node, $callback, $op_index);
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
  $item->comment['value'] = preg_replace('@hook_access([^i])@', "hook_node_access$1", $item->comment['value']);

  // Switch places of the first two parameters.
  //  cdp("Printing parameters");
  cdp($item->parameters->print_r());

  $count = $item->parameterCount();
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
 * Updates hook_filter().
 *
 * hook_filter() and hook_filter_tips() replaced by hook_filter_info().
 *
 * @todo Integrate hook_filter_tips() code with this function.
 * @todo Allow for other code styles, e.g. if block instead of switch.
 *   How similar is this use case to convert_return or convert_op?
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_filter(&$node, &$reader) { // DONE
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;

  global $_coder_upgrade_module_name;

  $tips = array();
  $editor = PGPEditor::getInstance();
  // Find the hook_filter_tips function object.
  $function_node = $editor->findFunction($reader->getFunctions(), $_coder_upgrade_module_name . '_filter_tips', 'node');
  if (!is_null($function_node)) {
    $tips = coder_upgrade_convert_filter_tips($function_node);
    cdp($tips, '$tips');
  }

  // Rename function.
  $item->name .= '_XXX'; // $item->name = $_coder_upgrade_module_name . '_filter_info';
  // Update document comment.
  //  $item->comment = preg_replace('@hook_filter@', "hook_filter_info", $item->comment);

  // Restructure the triggers array.
  $body = &$item->body;

  if (!($switch1 = $body->find(T_SWITCH))) {
    clp("ERROR: switch statement not found in hook_filter");
    return;
  }
  //  $value = &$switch1['value'];

  /*
   * Compare first parameter to first switch condition (s/b $op)
   * Compare second parameter to second switch condition (s/b $delta)
   *
   * Read $op case block: case operand gives the key for array
   * Read $delta case block: case operand gives the key for array
   * Return value gives the array value for above keys
   * Build array internally, then write it out.
   *
   * On the callback items, we only want the callback function name, not the
   * parameters. If there is not a function name (e.g. the filter module had
   * case 'process': case 4: return trim(check_plain($text));),
   * then make a new function with the return value as its body.
   * For this example, core created _filter_html_escape($text).
   *
   * Look for a hook_filter_tips($delta, $format, $long = false).
   * If present:
   * - if multiple $delta bodies, then create new callback functions using
   * $delta as part of the function name
   * - else if one, then create new callback function
   * - remove the $delta parameter
   * - add tips_callback parameters to filter_info array items
   */

  // Get the operation variable from the function parameter [at index $op_index].
  // This function removes any default value assignment (e.g. $op = 'list') or
  // inline comments included in the parameter expression.
  $op_index = 0;
  if (!($variable = $item->getParameterVariable($op_index))) {
    clp("ERROR: Variable not found in hook(\$op) parameter $op_index");
    return;
  }
  $op = $variable->toString();

  // Get the first condition. (With a switch there should only be one condition.)
  $condition1 = $switch1->conditions->getElement()->findNode('operand')->stripComments();
  $operand1 = $condition1->toString();
  if ($operand1 != $op) {
    clp('ERROR: switch statement operand does not match first function parameter in hook_filter');
    return;
  }

  $filters = array();
  // Get list of case statements.
  $cases1 = $switch1->body;
  $current1 = $cases1->first();
  while ($current1->next != NULL) {
    $case1 = $current1->data;
    if (!($case1 instanceof PGPCase) || $case1->type == T_DEFAULT) {
      $current1 = $current1->next;
      continue;
    }
    $key1 = trim($case1->case->stripComments()->toString(), "'\"");
    cdp("key1 = $key1");
    // TODO Convert key2 to new key: Ex. 'process' becomes 'process callback'
    $key1 = coder_upgrade_callback_filter($key1);
    cdp("new key1 = $key1");
    $body1 = $case1->body->getElement();
    if ($body1 && get_class($body1) == 'PGPFunctionCall' /*&& $body1->type == T_RETURN*/) {
      // Use case 1: returns an array.
      cdp("body1 is an array");
      if ($key1 != 'name') {
        clp("ERROR: key is not 'list' in hook_filter");
        return;
      }
      if ($body1->type != T_RETURN) {
        clp("ERROR: switch statement body for 'list' key does not return an array in hook_filter");
        return;
      }
      $value1 = $body1->getParameter()->getElement();
      if ($value1 && get_class($value1) == 'PGPArray') {
        $node_x = $value1->values->first();
        while ($node_x->next != NULL) {
          $data = $node_x->data;
          if ($node_x->type == 'key') {
            $key2 = $data->toString(); // Should be an integer = $delta
          }
          elseif ($node_x->type == 'value') {
            $filters[$key2][$key1] = $data->toString();
          }
          $node_x = $node_x->next;
        }
      }
    }
    elseif ($body1 && get_class($body1) == 'PGPConditional' && $body1->type == T_SWITCH) {
      // Use case 2: switch statement on $delta.
      $switch2 = &$body1;
      $operand2 = $switch2->conditions->toString();
      if ($operand2 != $item->getParameterVariable(1)->toString()) {
        clp("ERROR: switch statement operand does not match second function parameter in hook_filter");
        return;
      }
      // Get list of case statements.
      $cases2 = $switch2->body;
      $current2 = $cases2->first();
      while ($current2->next != NULL) {
        $case2 = $current2->data;
        if (!($case2 instanceof PGPCase) || $case2->type == T_DEFAULT) {
          $current2 = $current2->next;
          continue;
        }
        $key2 = trim($case2->case->stripComments()->toString(), "'\"");
        cdp("key2 = $key2");
        $body2 = $case2->body->getElement();
        if ($body2 && get_class($body2) == 'PGPFunctionCall') {
          // Use case 2: returns an array.
          if ($body2->type != T_RETURN) {
            clp("ERROR: switch statement operand does not match first function parameter in hook_filter");
            return;
          }
          $value2 = $body2->getParameter();
          if (get_class($value2) == 'PGPExpression') {
            // TODO On the callback items only want the callback function name, not the parameters!!!
            $filters[$key2][$key1] = $value2->toString();
            cdp($value2/*->toString()*/, '$value2');
          }
          if ($key1 == 'process callback' || $key1 == 'settings callback') {
            if ($value2->isType(T_FUNCTION_CALL)) {
              // For $value2 = trim(check_plain($text)), this will grab trim.
              // The user needs to define a callback function to do both.
              $call = &$value2->findNode('operand');
              if (is_array($call->name)) {
                // Name could be T_STRING or T_VARIABLE.
                $name = $call->name['value'];
                if ($call->name['type'] == T_STRING) {
                  $name = "'$name'";
                }
              }
              else {
                // An object expression (should be unlikely).
                $name = $call->name->toString();
              }
              $filters[$key2][$key1] = $name;
            }
          }
//           else {
//             $filters[$key2][$key1] = $value2->toString();
//           }
        }
        $current2 = $current2->next;
      }
    }
    $current1 = $current1->next;
  }
  foreach ($tips as $key2 => $callback) {
    $filters[$key2]['tips callback'] = "'$callback'";
  }

  $hook = '_filter_info';
  coder_upgrade_new_filter_hook($node, $hook, $filters);

  // Delete the function body.
  $item->body->clear();
}

// TODO Rename this function.
function coder_upgrade_callback_filter($key2) { // DONE
  switch ($key2) {
    case 'list':
      return 'name';
    case 'process':
      return 'process callback';
    case 'settings':
      return 'settings callback';
    case 'tips':
      return 'tips callback';
    default:
      return $key2;
  }
}

function coder_upgrade_new_filter_hook($node, $hook, $filters = array()) { // DONE
  global $_coder_upgrade_module_name;

  // Set values for the new hook function.
  $comment = array(
    'type' => T_DOC_COMMENT,
    'value' => "/**\n * Implements hook$hook().\n */",
  );
  $name = $_coder_upgrade_module_name . $hook; // '_filter_info';

  // Create the new hook function.
  $function = new PGPClass($name);
  $function->comment = $comment;
  $function->type = T_FUNCTION;
  $function->parameters = new PGPList();

  // Use the editor to set the function parameters.
  $editor = PGPEditor::getInstance();
  //  $editor->setParameters($function, $parameters);

  // Create body statements.
  $string = '';
  foreach ($filters as $key => $filter) {
    $string .= "\$filters[$key] = array(\n";
    foreach ($filter as $key2 => $value) {
      $string .= "  '$key2' => $value,\n";
    }
    $string .= ");\n";
  }
  $string .= "return \$filters;\n";
  cdp(print_r($string, 1));

  // Copy the case (or if) block as the body of the function.
  $function->body = $editor->textToStatements($string);
  cdp(get_class($function->body));
  cdp($editor->statementsToText($function->body));
  if ($function->body->isEmpty()) {
  }
  //  return ;

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

/**
 * Updates hook_filter_tips().
 *
 * hook_filter() and hook_filter_tips() replaced by hook_filter_info().
 *
 * @todo This should fit into the convert_op use case.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 *
 * @return array
 *   Array of tip callback functions indexed by $delta.
 */
function coder_upgrade_convert_filter_tips(&$node) { // DONE
  cdp("inside " . __FUNCTION__);
  $item = &$node->data;

  global $_coder_upgrade_module_name;

  // Rename function.
  $item->name .= '_XXX';
  // Update document comment.
  //  $item->comment .= 'This function is obsolete.'; // TODO Make a comment manipulation routine.

  // Restructure the triggers array.
  $body = &$item->body;

  if (!($switch1 = $body->find(T_SWITCH))) {
    clp("ERROR: switch statement not found in hook_filter_tips");
    return array();
  }

  /*
   * Compare first parameter to first switch condition (s/b $op)
   *
   * Read $delta case block: case operand gives the key for array
   * Return value gives the array value for above keys
   * Build array internally, then write it out.
   *
   * Look for a hook_filter_tips($delta, $format, $long = false).
   * If present:
   * - if multiple $delta bodies, then create new callback functions using
   *   $delta as part of the function name
   * - else if one, then create new callback function
   * - remove the $delta parameter
   * - add tips_callback parameters to filter_info array items
   *
   * - TODO Case 2: could be an if block
   */

  $operand1 = $switch1->conditions->toString();
  if ($operand1 != $item->printParameter()) {
    clp("ERROR: switch statement operand does not match first function parameter in hook_filter_tips");
    return array();
  }

  // Remove first parameter for new callback function.
  // TODO Do we need to clone this object for each new function???
  $parameters1 = $item->parameters;
  $parameters1->deleteElement();

  $tips = array();
  // Get list of case statements.
  $cases1 = $switch1->body;
  $current1 = $cases1->first();
  while ($current1->next != NULL) {
    $case1 = $current1->data;
    if (!($case1 instanceof PGPCase) || $case1->type == T_DEFAULT) {
      $current1 = $current1->next;
      continue;
    }
    // Get the $delta value.
    $key1 = trim($case1->case->toString(), "'\"");
    cdp("key1 = $key1");
    $body1 = $case1->body->getElement();

    // Make a new callback function.
    $hook = '_filter_tips_' . $key1;
    coder_upgrade_new_filter_tips_hook($node, $hook, $parameters1, $body1);
    // Store callback name in return array.
    $tips[$key1] = $_coder_upgrade_module_name . $hook;

    $current1 = $current1->next;
  }

  // Delete the function body.
  $item->body->clear();

  return $tips;
}

function coder_upgrade_new_filter_tips_hook($node, $hook, $parameters, $body) { // DONE
  global $_coder_upgrade_module_name;

  // Set values for the new hook function.
  $delta = substr($hook, strrpos($hook, '_') + 1);
  $comment = array(
    'type' => T_DOC_COMMENT,
    'value' => "/**\n * Filter tips callback function for \$filters[$delta] in hook_filter_info().\n */",
  );
  $name = $_coder_upgrade_module_name . $hook;

  // Create the new hook function.
  $function = new PGPClass($name);
  $function->comment = $comment;
  $function->type = T_FUNCTION;
  $function->parameters = $parameters; // new PGPList();
  $function->body = new PGPBody();
  $function->body->insertLast($body);

  //  cdp($function->print_r());

  // TODO REFACTOR: The following statements are repeated in other create_hook routines.

  // Get the statement list the function node is part of.
  $container = &$node->container;

  // Insert the new function before the old function.
  $new_node = $container->insertBefore($node, $function, 'function');
  //  $editor = PGPEditor::getInstance();
  //  cdp($editor->statementsToText($new_node));
  // Insert a blank line.
  $whitespace = array(
    'type' => T_WHITESPACE,
    'value' => 1,
  );
  $container->insertBefore($node, $whitespace, 'whitespace');
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

  $editor = PGPEditor::getInstance();

  /*
   * In 6.x, drupal_install_schema() has a return value, but not in 7.x.
   * The code below asssumes the return value is not utilized. Otherwise,
   * set the variable to array.
   *
   * @todo If there is a likelihood of multiple calls to these functions, then
   * use $body->searchCallback().
   */

  foreach (array('drupal_install_schema', 'drupal_uninstall_schema') as $function) {
    if ($call_node = $body->search('PGPFunctionCall', 'name', 'value', $function, TRUE)) {
      // Get the function call object.
      $call = $call_node->data;
      // Insert a comment before the statement containing the function call.
      $statement = $editor->commentToStatement("// TODO The drupal_(un)install_schema functions are called automatically in D7.");
      $call->insertStatementBefore($statement);
      // Get the expression containing the function call.
      $container = $call_node->container;
      if ($container->countType('operand') > 1) {
        // The function call is part of a larger expression.
        // Insert nodes to comment out the function call and replace it with default return value.
        $statement = $editor->expressionToStatement('array()/*' . $call->toString() . '*/');
        $container->insertListBefore($call_node, $statement);
        // Delete the function call node.
        $container->delete($call_node);
      }
      else {
        // The function call is the sole expression on this statement.
        // Comment out the statement.
        $call->parent->data = $editor->commentToStatement($call->toString());
      }
    }
  }
}

/**
 * Updates hook_link().
 *
 * Move node, taxonomy, and comment links into $node->content;
 * Deprecate hook_link() and hook_link_alter().
 *
 * @todo THIS IS NOT DONE.
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_link(&$node) { // NOT DONE
  return;
  cdp("inside " . __FUNCTION__);
  cdp("$callback");

  /*
   * Find code related to delete operation (in switch or if)
   * Move block to new function hook_user_cancel
   * Rename $user to $account (toString, preg_replace, convert to expression)
   * Add $method parameter
   * Add switch on $method; add core case values?
   * Place existing code under case 'user_cancel_reassign'
   * Add TODO note to check placement of code
   * DBTNG changes can be done in another routine
   */

  // Get the function object.
  $item = &$node->data;
  // Rename the function in case any code is left over.
  $item->name .= '_OLD'; // $item->name = $item->name . '_OLD'; // $item->name['value'] = $item->name['value'] . '_OLD';
  // Get the first function parameter, usually called $op.
  $count = $item->parameterCount();
  // TODO This gets the entire parameter including any default value. Hook_block has $op = 'list'.
  $op = $item->printParameter($op_index);
  //  cdp("op = '$op'");

  // Get the function body statements.
  $body = &$item->body;

  /*
   * Two likely cases: switch statement or series of if blocks.
   * Do the if blocks later.
   * Compare the second parameter to the function with the switch operand.
   */

  // TODO The following code is common to the remove_op upgrades. Refactor.

  // Loop on the body statements looking for the $op parameter in an IF or
  // SWITCH condition.
  $current = $body->first();
  while ($current->next != NULL) {
    $statement = &$current->data;
    if (is_object($statement)) {
      cdp($statement->print_r());
    }
    if ($statement instanceof PGPConditional) {
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
          $node->traverse($cases, $callback /*'coder_upgrade_callback_user'*/);
          //          // Get the statement list the switch statement node is part of.
          //          $container = &$current->container;
          //          $container->delete($current);
          //          $statement->body->clear();
        }
      }
      elseif (in_array($statement->type, array(T_IF, T_ELSEIF, T_ELSE_IF/*, T_ELSE*/))) {
        // Do something similar.
        //        cdp("inside T_IF check");
        // Get the list of conditions.
        //        $conditions = $statement->conditions;
        // Get the text of the conditions.
        //        $conditions = $statement->conditionsToArray();
        //        print_r($conditions);
        $operations = coder_upgrade_extract_operations($statement->conditions, $op); // list($operations, $others) = coder_upgrade_separate_operators($conditions, $op);
        /*
         * Extract the conditions referencing the $op variable and loop on them.
         * These are conditions of the form $op == 'operation'.
         * Replace them with condition of TRUE to not disrupt the logic.
         * Retain any other conditions as part of the body in the new hook
         * function.
         * Do we need a helper function to find the operand with $op???
         * Determine the $op comparison value (i.e. $op == 'what') so we can
         * use a case block in the upgrade routine.
         * Change a T_ELSEIF to a T_IF in the new hook function if we have
         * extra conditions.
         */
        foreach ($operations as $operand) {
 // TODO Rename $operand to $operation here and in called functions
          $statement->type = T_IF; // If it isn't already.
          $block = new stdClass();
          $block->body = new PGPBody();
          $block->body->insertLast($statement);
          $case_node = new PGPNode($block, $current->container); // TODO What is the correct container???
          $callback($node, $case_node, $operand); // coder_upgrade_callback_user($node, $case_node, $operand);
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
 * Updates hook_menu_link_alter().
 *
 * Changed hook_menu_link_alter() (removed the $menu parameter).
 *
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_menu_link_alter(&$node) {
  $item = &$node->data;
  $count = $item->parameterCount();
  // Adjust parameters.
  if ($count > 1) {
    // Delete second parameter.
    $item->deleteParameter(1);
  }
  // TODO Do we need to check for $menu in the body of this hook?
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
  $variable = &$return->getParameter()->getElement();

  // TODO This fits with the coder_upgrade_convert_return pattern.

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
  $body->searchCallback('coder_upgrade_convert_schema_callback', 'PGPFunctionCall', 'name', 'value', 't');
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
 * Update hooks now return strings or throw exceptions.
 *
 * @todo These hooks do not need to carry over from one version to the next.
 *   So we could simply delete the hook or its body. For those inclined to keep
 *   these hooks, we can modify the return statement (if any) to conform to D7.
 * @param PGPNode $node
 *   A node object containing a PGPClass (or function) item.
 */
function coder_upgrade_convert_update_N(&$node) {
  cdp("inside " . __FUNCTION__);
  // Changes: update_php, update_sql
  $item = &$node->data;

  $editor = PGPEditor::getInstance();

  // Get the function body.
  $body = &$item->body;

  // Find return statement.
  // find() only looks at statements in the list, while search() recurses through inner lists.
  if (!($return = $body->search('PGPFunctionCall', 'name', 'value', 'return', FALSE, 'backward'))) { // if (!($return = $body->find(T_RETURN, 'reverse'))) {
//    clp("ERROR: return statement not found in hook_update_N");
//    $body->insertFirst($editor->commentToStatement($msg), 'comment');
    return;
  }
  else {
    // Strip inline comment delimiter tokens from the parameter.
    $string = str_replace(array('/*', '*/'), '', $return->getParameter()->toString()); // $string = $return->getParameter()->stripComments()->toString();
    // To use PGPList->insertListBefore() need the node of $return.
//    $statement = $editor->textToStatements("// hook_update_N() no longer returns a \$ret array.\n//Instead, it should return nothing or a translated string to be displayed to the user indicating that the update ran successfully.\nSee http://drupal.org/node/224333#update_sql.");
    $statement = $editor->commentToStatement("// hook_update_N() no longer returns a \$ret array. Instead, return ");
    $return->insertStatementBefore($statement);
    $statement = $editor->commentToStatement("// nothing or a translated string indicating the update ran successfully.");
    $return->insertStatementBefore($statement);
    $statement = $editor->commentToStatement("// See http://drupal.org/node/224333#update_sql.");
    $return->insertStatementBefore($statement);
    // Replace the return() operand with t().
    $editor->setParameter($return, 0, "t('TODO Add a descriptive string here to show in the UI.') /* $string */");
  }
}

/**
 * Callback routines for coder_upgrade_convert_op().
 */

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
    if (!($case instanceof PGPCase) || $case->type == T_DEFAULT) {
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

  // http://drupal.org/node/224333#block_deltas_renamed
  // Change numeric block keys to strings
  $editor = PGPEditor::getInstance();
  $body = &$case_node->data->body;
  $text = $body->toString();
  $search = array(
    '/\$blocks\[(\d+)\]/si',
    '/\$delta ?([=!])= ?(\d+)/si',
    '/case (\'|"|)(\d+)(\'|"|)/si',
  );
  $replace = array(
    '$blocks[\'delta-\1\']',
    '$delta \1= \'delta-\2\'',
    'case \'delta-\2\'',
  );
  $count = 0;
  $text = preg_replace($search, $replace, $text, -1, $count);
  if ($count) {
    $body = $editor->textToStatements($text);
    $body->insertFirst($editor->commentToStatement('// TODO Rename block deltas (e.g. delta-0) to readable strings.'), 'comment');
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
    if (!($case instanceof PGPCase) || $case->type == T_DEFAULT) {
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
    if (!($case instanceof PGPCase) || $case->type == T_DEFAULT) {
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
      // This block becomes example_node_view with $view_mode = 'print'
      $hook = '_node_view';
      $parameters = array('$node', '$view_mode = \'print\'');
      break;
    case 'rss item':
      // This block becomes example_node_view with $view_mode = 'rss'
      $hook = '_node_view';
      $parameters = array('$node', '$view_mode = \'rss\'');
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
      // This block becomes example_node_view with $view_mode = 'full' by default
      $parameters = array('$node', '$view_mode = \'full\'');
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
    if (!($case instanceof PGPCase) || $case->type == T_DEFAULT) {
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

  // http://drupal.org/node/224333#remove_op
  // http://drupal.org/node/224333#hook-user-changes

  if (!$operation) {
    $case = &$case_node->data;
    if (!($case instanceof PGPCase) || $case->type == T_DEFAULT) {
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
      $parameters = array('$account', '$view_mode');
      break;
    default:
      cdp("ERROR: Invalid case value");
      return;
  }

  // Create the new hook function.
  coder_upgrade_op_to_hook($node, $case_node, $hook, $parameters);
}

/**
 * Callback routines for coder_upgrade_convert_return().
 */

/**
 * Updates hook_action_info() arrays.
 *
 * The arrays returned by hook_action_info(), hook_action_info_alter(),
 * actions_list(), actions_get_all_actions(), actions_actions_map() were
 * changed.
 *
 * @todo The other functions listed above.
 * @todo Database table {actions} - 'description' field is now called 'label'.
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
function coder_upgrade_callback_action_info($node, &$array2, &$current2, $hook, $type, $key, $value) { // DONE (NEEDS WORK on other functions listed above)
  cdp("inside " . __FUNCTION__);

  if (!($current2 instanceof PGPNode)) {
    clp("ERROR: current2 is not a PGPNode object in hook_$hook");
    return;
  }

  $editor = PGPEditor::getInstance();

  // The keys of this array are the action function items.
  if ($type == 'key' && $key == 'description') {
    cdp("Found the description key");
    if (!$current2->data->isType(T_CONSTANT_ENCAPSED_STRING)) {
      clp("ERROR: key expression is not a string in hook_$hook");
      return;
    }
    // Change key from 'description' to 'label.'
    $current2->data = $editor->expressionToStatement("'label'");
  }
  elseif ($type == 'key' && $key == 'hooks') {
    cdp("Found the hooks key");
    if (!$current2->data->isType(T_CONSTANT_ENCAPSED_STRING)) {
      clp("ERROR: key expression is not a string in hook_$hook");
      return;
    }
    // Change key from 'hooks' to 'triggers.'
    $current2->data = $editor->expressionToStatement("'triggers'");

    // Find the value element for this key.
    if (!$array2->findNextValue($current2)) {
      clp("ERROR: did not find a value expression for the triggers key in hook_$hook");
      return;
    }

    if (!$current2->data->isType(T_ARRAY)) {
      clp("ERROR: value expression is not a PGPArray object in hook_$hook");
      return;
    }

    /*
     * The triggers (formerly hooks) element is an associative array keyed by
     * module name with its value being an array of actions. The new format
     * combines the module name and action, eliminating one nested array.
     * Example:
     * 'hooks' => array(
     *   'comment' => array('insert', 'update'),
     *   "taxonomy" => array("insert", "update", "delete", "view"),
     * )
     *
     * 'triggers' => array(
     *   'comment_insert', 'comment_update',
     *   'taxonomy_insert', 'taxonomy_update', 'taxonomy_delete', 'taxonomy_view'
     * )
     */
    $triggers = &$current2->data->getElement();

    $ops = array();

    $trigger = $triggers->values->first();
    while ($trigger->next != NULL) {
      if ($trigger->type == 'key') {
        // This is the module (or content type) the action pertains to.
        $prefix = trim($trigger->data->toString(), "'\"");
      }
      elseif ($trigger->type == 'value') {
        if (!$trigger->data->isType(T_ARRAY)) {
          clp("ERROR: trigger value expression is not a PGPArray object in hook_$hook");
          return;
        }

        // This is the array of action operation items.
        $operation_items = $trigger->data->getElement();
        $string = $operation_items->values->toString();
        $items = explode(', ', $string);
        foreach ($items as $op) {
          $ops[] = "'{$prefix}_" . trim($op, "'\"") . "'";
        }
      }
      $trigger = &$trigger->next;
    }
    $string = 'array(' . implode(', ', $ops) . ')';
    $editor = PGPEditor::getInstance();
    $expression = $editor->expressionToStatement($string);
    // TODO Use multiline format? Depending on number of items?
    $expression->getElement()->multiline = 1;
    $expression->getElement()->preserve = 0;
    // Replace the triggers nested array with new array.
    $triggers = $expression;
  }
}

/**
 * Updates hook_hook_info() arrays.
 *
 * hook_hook_info() is now called hook_trigger_info(), and its return value has
 * been changed and simplified.
 *
 * @todo Database table {trigger_assignments} - 'op' field was removed, and the
 * 'hook' field now contains the full function name.
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
function coder_upgrade_callback_hook_info($node, &$array2, &$current2, $hook, $type, $key, $value) { // DONE
  cdp("inside " . __FUNCTION__);

  if (!($current2 instanceof PGPNode)) {
    clp("ERROR: current2 is not a PGPNode object in hook_$hook");
    return;
  }

  $editor = PGPEditor::getInstance();

  /*
   * Array levels
   * - L0 return array(
   * - L1   'node' => array(
   * - L2     'nodeapi' => array(
   * - L3       'presave' => array(
   * - L4         'runs when' => t('When either saving a new post or updating an existing post'),
   */

  // The keys of this array are the module (or content type) the hook pertains to.
  if ($type == 'key') {
    cdp("Found the module (or content type) key");
    if (!$current2->data->isType(T_CONSTANT_ENCAPSED_STRING)) {
      clp("ERROR: key expression is not a string in hook_$hook");
      return;
    }

    // This is the module (or content type) the hook pertains to.
    // TODO Other prefixes may need to be modified.
    switch ($key) {
      case 'nodeapi':
        $prefix = 'node';
        break;
      case 'taxonomy':
        $prefix = 'taxonomy_term';
        break;
      default:
        $prefix = $key;
        break;
    }

    // Find the value element for this key.
    if (!$array2->findNextValue($current2)) {
      clp("ERROR: did not find a value expression for the triggers key in hook_$hook");
      return;
    }

    if (!$current2->data->isType(T_ARRAY)) {
      clp("ERROR: value expression is not a PGPArray object in hook_$hook");
      return;
    }

    /*
     * The triggers information element is an associative array doubly keyed by
     * module name with its value being an array of action information. The new
     * format combines the module name and action, eliminating one nested array.
     * Example:
     * 'node' => array(
     *   'nodeapi' => array(
     *     'presave' => array(
     *       'runs when' => t('When either saving a new post or updating an existing post'),
     *     ),
     *   ),
     * ),
     *
     * 'node' => array(
     *   'node_presave' => array(
     *     'label' => t('When either saving a new post or updating an existing post'),
     *   ),
     * ),
     */
    $triggers = &$current2->data->getElement();

    $trigger = $triggers->values->first();
    while ($trigger->next != NULL) {
      if ($trigger->type == 'key') {
        if (!$trigger->data->isType(T_CONSTANT_ENCAPSED_STRING)) {
          clp("ERROR: trigger key expression is not a string in hook_$hook");
          return;
        }
        // This is the module (or content type) the hook pertains to.
        // Concatenate prefix with key.
        $suffix = trim($trigger->data->toString(), "'\"");
        $new_key = "'{$prefix}_$suffix'";
        $trigger->data = $editor->expressionToStatement($new_key);
      }
      elseif ($trigger->type == 'value') {
        if (!$trigger->data->isType(T_ARRAY)) {
          clp("ERROR: trigger value expression is not a PGPArray object in hook_$hook");
          return;
        }

        // This is the array of trigger information items.
        // Currently, the only key is 'label' (formerly 'runs when').
        $information_items = &$trigger->data->getElement();
        $information_items->multiline = 1;
        $information_items->preserve = 0;

        if (!$information_items->changeKey('runs when', "'label'")) {
          clp("ERROR: could not change 'runs when' key expression in hook_$hook");
          clp($information_items->toString());
          return;
        }
      }
      $trigger = &$trigger->next;
    }
    // Move up level 3 (triggers info) to level 2 (redundant module name) of the array.
    $array2->values = $triggers->values; // $array2->values = $array3->values;
    /*
     * Set array properties so the rewritten array:
     * - has a comma after all values
     * - is not indented one level too many
     */
    $array2->count = $triggers->count;
    $array2->commaCount = $triggers->count;
    $array2->multiline = 1;
    $array2->preserve = 0;
  }
}

/**
 * Updates hook_node_info() arrays.
 *
 * In hook_node_info() change 'module' back to 'base' and change 'node' to
 * 'node_content'.
 *
 * @todo A similar change applies to the array passed as the parameter to
 * node_type_set_defaults($example_node_type).
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
function coder_upgrade_callback_node_info($node, &$array2, &$current2, $hook, $type, $key, $value) { // DONE
  cdp("inside " . __FUNCTION__);

  if (!($current2 instanceof PGPNode)) {
    clp("ERROR: current2 is not a PGPNode object in hook_$hook");
    return;
  }

  $editor = PGPEditor::getInstance();

  // The keys of this array are the node type items.
  if ($type == 'key' && $key == 'module') {
    cdp("Found the module key");
    if (!$current2->data->isType(T_CONSTANT_ENCAPSED_STRING)) {
      clp("ERROR: key expression is not a string in hook_$hook");
      return;
    }
    // Change key from 'module' to 'base.'
    $current2->data = $editor->expressionToStatement("'base'");

    // Find the value element for this key.
    if (!$array2->findNextValue($current2)) {
      clp("ERROR: did not find a value expression for the base key in hook_$hook");
      return;
    }

    if (!$current2->data->isType(T_CONSTANT_ENCAPSED_STRING)) {
      clp("ERROR: value expression is not a string in hook_$hook");
      return;
    }
    if (trim($current2->data->toString(), "'\"") == 'node') {
      // Change value from 'node' to 'node_content.'
      $current2->data = $editor->expressionToStatement("'node_content'");
    }
  }
}

/**
 * Updates hook_perm() arrays.
 *
 * Permissions are required to have titles and descriptions.
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
function coder_upgrade_callback_perm($node, &$array2, &$current2, $hook, $type, $key, $value) { // DONE
  cdp("inside " . __FUNCTION__);

  if (!($current2 instanceof PGPNode)) {
    clp("ERROR: current2 is not a PGPNode object in hook_$hook");
    return;
  }

  $editor = PGPEditor::getInstance();

  // The values of this array are the permission items.
  // TODO If someone used keys with the values, this would result in consecutive
  // keys in the array and likely fail.
  if ($type == 'value' /*&& $key == ''*/) {
    $current2->type = 'key';

    $permission = $current2->data->toString();
    $permission2 = str_replace("'", "\'", $permission);
    $string = "array('title' => t($permission), 'description' => t('TODO Add a description for $permission2'),)";

    // Create new array expression.
    $editor->getReader()->setPreserveArrayFormat();
    $expression = $editor->expressionToStatement($string);
    $expression->multiline = 1;
    $expression->preserve = 0;
    $editor->getReader()->setPreserveArrayFormat(TRUE);

    // Insert new expression nodes.
    $new = /*&*/$array2->values->insertAfter($current2, $expression, 'value');
    $array2->values->insertAfter($current2, '=>', 'assign');
    // Force the settings on the original array (which is usually inline).
    $array2->multiline = 1;
    $array2->preserve = 0;
    // Set $current2 to last item inserted above to avoid redundant looping.
    $current2 = $new;
  }
}

/**
 * Updates hook_theme() arrays.
 *
 * Each theme function must register how it integrates with drupal_render().
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
function coder_upgrade_callback_theme($node, &$array2, &$current2, $hook, $type, $key, $value) { // DONE
  cdp("inside " . __FUNCTION__);

  if (!($current2 instanceof PGPNode)) {
    clp("ERROR: current2 is not a PGPNode object in hook_$hook");
    return;
  }

  $editor = PGPEditor::getInstance();

  // The keys of this array are the theme items.
  if ($type == 'key' && $key == 'arguments') {
    cdp("Found the arguments key");
    if (!$current2->data->isType(T_CONSTANT_ENCAPSED_STRING)) {
      clp("ERROR: key expression is not a string in hook_$hook");
      return;
    }
    // Save the key expression for possible modification.
    $key_expression = &$current2->data;

    // Find the value element for this key.
    if (!$array2->findNextValue($current2)) {
      clp("ERROR: did not find a value expression for the arguments key in hook_$hook");
      return;
    }

    if (!$current2->data->isType(T_ARRAY)) {
      clp("ERROR: value expression is not a PGPArray object in hook_$hook");
      return;
    }

    $array = $current2->data->getElement();
    if (!($key0 = $array->getKey())) {
      // Change key from 'arguments' to 'variables.'
      $key_expression = $editor->expressionToStatement("'variables'");
      return;
    }
    $key0 = trim($array->getKey()->toString(), "'\"");
    // At a minimum, an array with key-value pairs will have 4 keys after one
    // pair: lparens, key, assign, and value.
    // What other likely values are there for a render element?
    // Does $form ever appear with other variables? If so, how is this to be handled?
    // TODO This is not a deterministic way of setting the key.
    if ($array->count == 1 && in_array($key0, array('form', 'element', 'elements'))) { // if ($array->values->count() == 4 && in_array($key0, array('form', 'element'))) {
      // Change key from 'arguments' to 'render element.'
      $key_expression = $editor->expressionToStatement("'render element'");
      // Change value from an associative array to a string.
      $current2->data = $editor->expressionToStatement("'$key0'");
    }
    else {
      // Change key from 'arguments' to 'variables.'
      $key_expression = $editor->expressionToStatement("'variables'");
    }
  }
}
