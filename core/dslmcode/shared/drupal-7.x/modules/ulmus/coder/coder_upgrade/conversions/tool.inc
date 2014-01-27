<?php
/**
 * @file
 * Provides tools to assist with conversion routines.
 *
 * These routines use the grammar parser and are version-agnostic with respect
 * to Drupal. An exception may be coder_upgrade_convert_op() which helps
 * with hook($op) style functions, many (or all?) of which were eliminated in
 * Drupal 7.x. However, this pattern may remain in contributed modules.
 *
 * Copyright 2009-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Initiates the transformation of a hook($op) to a new hook_$op style function.
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
  // Get the operation variable from the function parameter at index $op_index.
  // This function removes any default value assignment (e.g. $op = 'list') or
  // inline comments included in the parameter expression.
  if (!($variable = $item->getParameterVariable($op_index))) {
    clp("ERROR: Variable not found in hook(\$op) parameter $op_index");
    return;
  }
  $op = $variable->toString();

  // Get the function body statements.
  $body = &$item->body;

  /*
   * Two likely cases: switch statement or series of if blocks.
   * Compare the $op_index parameter to the function with the switch operand.
   */

  // Loop on the body statements looking for the $op variable in an IF or
  // SWITCH condition.
  $current = $body->first();
  while ($current->next != NULL) {
    $found = FALSE;
    $statement = &$current->data;
    if ($statement instanceof PGPConditional) {
//      cdp("inside PGPConditional check");
//      cdp("statement->type = " . $statement->type);
      if ($statement->type == T_SWITCH) {
//        cdp("inside T_SWITCH check");
        // Get the list of conditions.
        $conditions = $statement->conditions;
        // Get the first condition. (With a switch there should only be one condition.)
        $condition = $conditions->getElement()->findNode('operand')->stripComments();
        $operand = $condition->toString();
        // If the condition variable matches the $op variable, then go to work.
        if ($op == $operand) {
          $found = TRUE;
          $cases = $statement->body;
          $node->traverse($cases, $callback);
        }
      }
      elseif (in_array($statement->type, array(T_IF, T_ELSEIF, T_ELSE_IF/*, T_ELSE*/))) {
        cdp("inside T_IF check");
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
          $found = TRUE;
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
    elseif (is_array($statement) && $statement['type'] == T_WHITESPACE) {
      // Remove whitespace.
      $found = TRUE;
    }
    // Move to next node.
    $current = &$current->next;
    if ($found) {
      // Get the statement list the switch statement (or if block) node is part of.
      $container = &$current->container;
      $container->delete($current->previous);
    }
  }
  if ($body->count()) {
    $editor = PGPEditor::getInstance();
    // TODO Insert comment indicating the block was not changed.
    $body->insertFirst($editor->commentToStatement('// TODO Remaining code in this function needs to be moved to the appropriate new hook function.')/*, 'comment'*/);
  }
}

/**
 * Extracts operations from conditions and replaces the conditions with TRUE.
 *
 * @param PGPList $conditions
 *   A list of conditions to an if block.
 * @param string $op
 *   A string of the hook operation.
 *
 * @return array
 *   Array of operations referenced in the if block.
 */
function coder_upgrade_extract_operations(&$conditions, $op) {
  cdp("inside " . __FUNCTION__);
  $operations = array();

  /*
   * A condition may consist of at most two operands separated by an operator.
   */
  if ($conditions instanceof PGPList) {
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
            if ($element instanceof PGPOperand) {
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
          $current2 = /*&*/ $current2->next;
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
      $current = /*&*/ $current->next;
    }
  }

  return $operations;
}

/**
 * Creates hook_$op function from the case (or if) block of an $op-style hook.
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
    'value' => "/**\n * Implements hook$hook().\n */",
  );
  $name = $_coder_upgrade_module_name . $hook;

  // Create the new hook function.
  $function = new PGPClass($name);
  $function->comment = $comment;
  $function->type = T_FUNCTION;
  $function->parameters = new PGPList();

  // Use the editor to set the function parameters.
  $editor = PGPEditor::getInstance();
  $editor->setParameters($function, $parameters);

  // Copy the case (or if) block as the body of the function.
  $function->body = $case->body;
  if ($function->body->isEmpty()) {
    // Find the next case with a body.
    $case_node2 = $case_node->next;
    while ($case_node2->next != NULL) {
      $case2 = $case_node2->data;
      $body2 = $case2->body;
      if (!$body2->isEmpty()) {
        $function->body = $case2->body;
        break;
      }
      $case_node2 = $case_node2->next;
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

/**
 * Initiates the transformation of array assignments in a hook.
 *
 * Applies to: hook_action_info(), hook_hook_info(), hook_node_info(), hook_theme().
 *
 * NOTE
 * In general, there are 3 typical cases (or code styles):
 * - return array('key1' => array('key2' => ...);
 * - $var = array('key1' => array('key2' => ...); return $var;
 * - $var = array(); $var['key1'] = array('key2' => ...); return $var;
 *
 * The inner array to modify is 3 levels deep in the first 2 cases, but only
 * 2 levels deep in the third. In the first 2 cases, we can loop on the key1
 * arrays. In the third, the loop is on assignment statements.
 *
 * This new routine was failing on hook_hook_info() because the keys are not
 * distinguishable. Ie, we can not tell what level of the array we are on if
 * the array is inline and has 3 levels. Previously, return_case1() would strip
 * off the first layer and get to the second level. There is no guarantee of
 * nice code anyway.
 *
 * This new routine was failing on capturing drupal_get_form() callbacks
 * on case 5, like example_admin_form3() defined in
 * $items[$admin_path]['page arguments'][] = 'example_admin_form3'. This again
 * relates to a depth parameter and that we are always looking for an array.
 *
 * Should we pass a depth parameter, or figure it dynamically?
 *
 * @param PGPList $body
 *   List of statements in a block.
 * @param string $hook
 *   Name of the hook being modified.
 * @param string $callback
 *   A string of the callback function for the hook.
 * @param integer $start_depth
 *   The starting depth of nested arrays to traverse.
 * @param integer $remaining_depth
 *   The remaining depth of nested arrays to traverse. When equal to zero, stop.
 */
function coder_upgrade_convert_return(&$body, $hook, $callback = '', $start_depth = 0, $remaining_depth = -1) { // DONE
  cdp("inside " . __FUNCTION__);

  // Initialize.
  $editor = PGPEditor::getInstance();
  $callback = $callback == '' ? "coder_upgrade_callback_$hook" : $callback;
  $msg = '// TODO The array elements in this hook function need to be changed.';

  // Get a list of return statements in the body statements.
  $nodes = $body->searchAll('PGPFunctionCall', 'name', 'value', 'return', TRUE);

  // Keep track of return variables to avoid redundant searching.
  $already_searched = array();

  while (!empty($nodes)) {
    cdp('while (!empty($nodes)) ' . __FUNCTION__);
    $return_node = array_shift($nodes);
    $return = $return_node->data;

    // Evaluate the return operand.
    if (get_class($return) == 'PGPFunctionCall') {
      $value = /*&*/$return->getParameter();
      $depth = 0;
    }
    elseif (get_class($return) == 'PGPAssignment') {
      // Get the operands to the right of the assignment operator.
      $value = $return->getValue();
      cdp($return->toString(), '$return AFTER');

      // Evaluate the "depth" of the assignment based on number of indices in
      // the assignment variable.
      // Examples: the operand on the RHS is at
      //   level 1: $var = array(key => array(..), ..)
      //   level 2: $var[key1] = array(..)
      //   level 3: $var[key1][key2] = array(..)
      // This mimics what was done in return_caseN(). We went down to level 2
      // from case1 to case3.
      $assign_variable = $return->values->getElement()->getType('operand')->stripComments();
      // @todo This should handle most cases, but will fail depending on code style.
      // If depth is > start_depth (like case5), then reconstruct an array at
      // the desired depth using toString() and reparsing (see case5).
      $depth = $assign_variable->countType('index');
      if ($depth > $start_depth) {
        // @todo This works in some use cases (menu stuff in begin.inc). If we
        // need to change the original expression, this fails because $value is
        // now disjoint from the original expression.
        $value = coder_upgrade_reconstruct_array($assign_variable, $value);
        $depth = 1; // $assign_variable->countType('index');
      }
    }
    cdp($value->toString(), '$value');

    $occurrence = 1;
    // Loop on all operands in expression (e.g. $array + array(..)).
    while ($occurrence < $value->countType('operand') + 1) {
      $operand = $value->getType('operand', $occurrence);
      if ($operand) {
        cdp('inside if ($operand)');
        if (!is_object($operand)) {
          // @todo This hits stuff like $items[$admin_path]['page arguments'][] = 'example_admin_form3';
          cdp('!is_object($operand)');
          cdp($operand, '$operand');
          $occurrence++;
          continue;
        }
        cdp($operand->toString(), '$operand');
        if (get_class($operand) == 'PGPArray') {
          // Use case 1 - returns array directly.
          $operand->traverse2($return_node, $hook, $callback, $start_depth - $depth, $remaining_depth);
        }
        elseif (get_class($operand) == 'PGPOperand') {
          // Avoid redundant searching.
          if (in_array($operand->stripComments()->toString(), $already_searched)) {
            $occurrence++;
            continue;
          }

          /*
           * Search body statements for all assignments to the return variable.
           * The assignment could be to an array element like $info['node_type_name'] = array(...).
           * Or directly to the variable like $info = array('node_type_name' => array(...)).
           */

          $already_searched[] = $return_variable = $operand->stripComments()->toString();
          // @todo Limit search to nodes preceding the statement.
          $nodes = array_merge($nodes, $body->searchAll('PGPAssignment', 'values', 0, $return_variable, TRUE/*, 'backward', $parent*/));
        }
        else {
          // @todo This message is not accurate -- this error hits on the array value being a string or function call.
          clp("ERROR: operand of return statement is not an array or variable in hook_$hook");
          cdp("ERROR: operand of return statement is not an array or variable in hook_$hook");
          cdp($operand, '$operand');
          $body->insertFirst($editor->commentToStatement($msg), 'comment');
        }
      }
      $occurrence++;
    }
  }
}

/**
 * Returns array with another level whose key is from assignment variable.
 *
 * @param PGPExpression $variable
 *   The assignment variable (left of assignment operator).
 * @param PGPExpression $value
 *   The assignment value (right of assignment operator).
 *
 * @return PGPExpression
 *   The new array expression.
 */
function coder_upgrade_reconstruct_array($variable, $value) {
  cdp("inside " . __FUNCTION__);

  if ($variable->countType('index') < 2) {
    return new PGPExpression();
  }

  $editor = PGPEditor::getInstance();

  // This routine assumes the second index is the one to be reconstructed.
  $key = trim($variable->getType('index', 2)->toString(), "'\"");
  $array = $editor->expressionToStatement("array('$key' => {$value->toString()})"); //->getElement();
  cdp($array->toString(), '$array');
  return $array;

/*
  // The above works well for existing use cases, but fails for hook_perm possibly
  // because the array traverse2() routine will skip the key when $depth != $start_depth.
  $count = $variable->countType('index');
  if (!$count) {
    return new PGPExpression();
  }

  $editor = PGPEditor::getInstance();

  // Allow for a key being a string or a variable expression.
  $key = $variable->getType('index', $count)->toString(); // $key = trim($variable->getType('index', $count)->toString(), "'\"");
  if ($key) {
    $array = $editor->expressionToStatement("array($key => {$value->toString()})"); //->getElement();
  }
  else {
    $array = $editor->expressionToStatement("array({$value->toString()})"); //->getElement();
  }
  cdp($array->toString(), '$array');
  return $array;
*/
}

/**
 * Initiates the transformation of array assignments in a hook.
 *
 * Applies to: hook_action_info(), hook_hook_info(), hook_node_info(), hook_theme().
 *
 * NOTE
 * In general, there are 3 typical cases (or code styles):
 * - return array('key1' => array('key2' => ...);
 * - $var = array('key1' => array('key2' => ...); return $var;
 * - $var = array(); $var['key1'] = array('key2' => ...); return $var;
 *
 * The inner array to modify is 3 levels deep in the first 2 cases, but only
 * 2 levels deep in the third. In the first 2 cases, we can loop on the key1
 * arrays. In the third, the loop is on assignment statements.
 *
 */
function coder_upgrade_convert_return_OLD(&$node, $hook, $callback = '') { // DONE
  cdp("inside " . __FUNCTION__);
  $editor = PGPEditor::getInstance();
  $msg = '// TODO The array elements in this hook function need to be changed.';

  $item = &$node->data;

  // Get the function body.
  $body = &$item->body;

  if (!($return = $body->find(T_RETURN, 'reverse'))) {
    clp("ERROR: return statement not found in hook_$hook");
    $body->insertFirst($editor->commentToStatement($msg), 'comment');
    return;
  }

  $value = &$return->getParameter(); // @todo Strip comments.

  // Examine the type of the operand in the return statement.
  $operand = $value->getElement();
  if (get_class($operand) == 'PGPArray') {
    // Use case 1 - returns array directly.
    // The keys of this array are the node type items.
    $array1 = $value->getElement();
    coder_upgrade_callback_return_case1($array1, $hook, $callback);
  }
  elseif (get_class($operand) == 'PGPOperand') {

    /*
     * Loop on body statements until we find an assignment to the return variable.
     * The assignment could be to an array element like $info['node_type_name'] = array(...).
     * Or directly to the variable like $info = array('node_type_name' => array(...)).
     */

    $return_variable = $operand->toString();
    $count = 0;
    coder_upgrade_convert_return_loop_OLD($body->first(), $count, $return_variable, $hook, $callback);
    if (!$count) {
      clp("ERROR: assignment statement to return variable not found in hook_$hook");
      $body->insertFirst($editor->commentToStatement($msg), 'comment');
      return;
    }
  }
  else {
    clp("ERROR: operand of return statement is not an array or variable in hook_$hook");
    $body->insertFirst($editor->commentToStatement($msg), 'comment');
  }
}

function coder_upgrade_convert_return_loop_OLD(&$node, &$count, $return_variable, $hook, $callback = '') { // NOT DONE
  cdp("inside " . __FUNCTION__);
  (is_object($node->data)) ? cdp($node->data->toString(), __FUNCTION__ . ' $node') : cdp($node->data, __FUNCTION__ . ' $node');

  /*
   * Loop on body statements until we find an assignment to the return variable.
   * The assignment could be to an array element like $info['node_type_name'] = array(...).
   * Or directly to the variable like $info = array('node_type_name' => array(...)).
   */

  $current = $node;
  while ($current->next != NULL) {
    if (is_object($current->data) && $current->data->type == T_ASSIGNMENT) { // if ($current->data->isType(T_ASSIGNMENT)) {
      $assignment = $current->data;
      $assign_variable = $assignment->values->getElement()->getElement()->stripComments()->toString();
      if ($return_variable == $assign_variable) {
        // Use case 2: makes one assignment to array variable; returns variable.
        cdp("Use case 2: Assignment variable matches return variable");
        /*
         * TODO This equality check would fail if comments are embedded between
         * variable and operator.
         * Example: $theme /**\/ = $array + array(..);
         */
        $value1 = $assignment->values->getElement();
        /*
         * TODO Find the operand of class PGPArray.
         * Example: $theme /**\/ = $array + array(..);
         */
        $array1 = $value1->getElement($value1->count() - 1);
        if (!is_object($current->data) || get_class($array1) != 'PGPArray') {
          continue;
        }
        coder_upgrade_callback_return_case1($array1, $hook, $callback);
        $count++;
      }
      elseif (strpos($assign_variable, $return_variable) !== FALSE) {
        // Use case 3: makes multiple assignments to array variable; returns variable.
        cdp("Use case 3: Assignment variable includes return variable");
        /*
         * TODO This substring check would fail if comments are embedded between
         * variable and operator.
         * Example: $theme /**\/ = $array + array(..);
         */
        $assign_variable2 = $assignment->values->getElement()->getElement()->stripComments();
        $value1 = $assignment->values->getElement();
        if ($assign_variable2->countType('index') == 1) {
          cdp('variable has one index');
          $array1 = $value1->getElement($value1->count() - 1);
          coder_upgrade_callback_return_case3($array1, $hook, $callback);
          $count++;
        }
        elseif ($assign_variable2->countType('index') == 2) {
          cdp('variable has two indices');
          /*
           * TODO Use case 5
           * Assignment to array variable at an index
           * $items[$admin_path] = array_merge($default_menu_fields, $menu_item);
           * $items[$admin_path]['page callback'][] = 'example_admin_form';
           * We need to count the indices; check for last index == []
           * The second index is usually the item to be inspected
           */
          $key2 = $assign_variable2->getType('index', 2);
          coder_upgrade_callback_return_case5($assignment, /*$key2,*/ $hook, $callback);
        }
        elseif ($assign_variable2->countType('index') == 3 && $assign_variable2->getType('index', 3)->toString() == '') {
          cdp('variable has three indices');
          /*
           * TODO Use case 5
           * Assignment to array variable at an index
           * $items[$admin_path] = array_merge($default_menu_fields, $menu_item);
           * $items[$admin_path]['page callback'][] = 'example_admin_form';
           * We need to count the indices; check for last index == []
           * The second index is usually the item to be inspected
           */
          $key2 = $assign_variable2->getType('index', 2);
          coder_upgrade_callback_return_case5($assignment, /*$key2,*/ $hook, $callback);
        }
        else {
          clp("ERROR: Assignment variable has more than three index levels");
          cdp("ERROR: Assignment variable has more than three index levels");
          cdp($assign_variable2->getType('index', 3)->toString());
        }
      }
    }
    elseif (is_object($current->data) && in_array(get_class($current->data), array('PGPConditional', 'PGPFor', 'PGPForeach', 'PGPCase'))) { // elseif (is_a($current->data, 'PGPConditional')) {
      coder_upgrade_convert_return_loop($current->data->body->first(), $count, $return_variable, $hook, $callback);
    }
    else {
      cdp('fell thru conditions in ' . __FUNCTION__);
      (is_object($current->data)) ? cdp($current->data->toString(), __FUNCTION__ . ' $current') : cdp($current->data, __FUNCTION__ . ' $current');
    }
    $current = $current->next;
  }
}

/**
 * Loops on elements of first-level array.
 *
 * @todo Abstract to the PGPArray object: traverse with callback.
 * This is setting up as a nice recursive function.
 *
 * @param PGPArray $array1
 */
function coder_upgrade_callback_return_case1(&$array1, $hook, $callback = '') { // DONE
  cdp("inside " . __FUNCTION__);

  // The keys of this array are the node types.
  if (!($array1 instanceof PGPArray)) {
    clp("ERROR: array1 is not a PGPArray object in hook_$hook");
    return;
  }

  // Grab the PGPList of values.
  $values1 = $array1->values;

  $current1 = $values1->first();
  while ($current1->next != NULL) {
    if ($current1->type == 'key') {
      $key1 = $current1->data;
      // Do something if appropriate.
      // This is not the one needed; we need the next level down.
    }
    elseif ($current1->type == 'value') {
      // This is the value expression for a node type key.
      $value1 = $current1->data;
      if (get_class($value1) != 'PGPExpression') {
        clp("ERROR: value1 is not a PGPExpression object in hook_$hook");
        return;
      }
      // This is the array of node type items.
      $array2 = $value1->getElement();
      coder_upgrade_callback_return_case3($array2, $hook, $callback);
    }
    $current1 = $current1->next;
  }
}

/**
 * Loops on elements of second-level array.
 *
 * @todo Abstract to the PGPArray object: traverse with callback.
 *
 * @param PGPArray $array2
 */
function coder_upgrade_callback_return_case3(&$array2, $hook, $callback = '') { // DONE
  cdp("inside " . __FUNCTION__);
  $callback = $callback == '' ? "coder_upgrade_callback_$hook" : $callback;

  // The keys of this array are the node type items.
  if (!($array2 instanceof PGPArray)) {
    clp("ERROR: array2 is not a PGPArray object in hook_$hook");
    cdp("ERROR: array2 is not a PGPArray object in hook_$hook");
    cdp($array2);
    return;
  }

  // Grab the PGPList of values.
  $values2 = $array2->values;

  $key2 = '';
  $current2 = $values2->first();
  while ($current2->next != NULL) {
    if ($current2->type == 'key') {
      $key2 = trim($current2->data->toString(), "'\"");
      $callback($array2, $current2, $hook, $current2->type, $key2, NULL);
    }
    elseif ($current2->type == 'value') {
      $value2 = trim($current2->data->toString(), "'\"");
      $callback($array2, $current2, $hook, $current2->type, $key2, $value2);
      $key2 = ''; // Clear key in case not all elements have keys.
    }
    $current2 = $current2->next;
  }
}

function coder_upgrade_callback_return_case5(/*&*/$assignment, $hook, $callback = '') { // NOT DONE
  cdp("inside " . __FUNCTION__);
  /*
   * TODO Convert the assignment into an array expression. Then pass off the
   * array to coder_upgrade_callback_return_case3.
   *
   * Loop on assignment to remove all nodes up to and including the assignment
   * operator. Grab the second index from the first node. Then toString() and
   * build an array with the second index as the key.
   */
  $assign_variable2 = $assignment->values->getElement()->getElement()->stripComments();
  $key2 = $assign_variable2->getType('index', 2);
  if ($assignment->values->getElement()->get(1)->type != 'assign') {
    clp("ERROR: second element of assignment is not the assignment operator");
    return;
  }
  $editor = PGPEditor::getInstance();
  // Remove the assignee and the assignment operator.
  $assignment = $assignment->values->getElement();
  $assignment->deleteElement();
  $assignment->deleteElement();
  $temp = $assignment; //->values->getElement()->getElement(2); // ->stripComments();
  $key = trim($key2->toString(), "'\"");
  $array2 = $editor->expressionToStatement("array('$key' => {$temp->toString()})")->getElement();
  coder_upgrade_callback_return_case3($array2, $hook, $callback);
}
