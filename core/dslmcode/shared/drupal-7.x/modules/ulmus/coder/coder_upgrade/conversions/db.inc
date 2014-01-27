<?php
/**
 * @file
 * Provides conversion routines applied to database API function calls and hooks.
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
 * Database
 * http://drupal.org/node/224333#dbtng (NOT FINISHED)
 * http://drupal.org/node/224333#db_rewrite_sql (NOT FINISHED)
 */

/**
 * Implements hook_upgrade_call_db_query_alter().
 */
function coder_upgrade_upgrade_call_db_query_alter(&$node, &$reader) { // NEEDS WORK
  // Disable this routine until it is improved.
//  return;

  /*
   * Use cases
   * - query is a string: parse directly
   * - query is a variable; find the variable and see if it is a string (assigned only once or always from strings, no expressions)
   * - query is an expression (leave this alone)
   */

  if ($sql = coder_upgrade_locate_query_string($node)) {
    // Parse the string.
    coder_upgrade_parse_query_string($node, $sql);
  }
}

/**
 * Implements hook_upgrade_call_db_query_range_alter().
 */
function coder_upgrade_upgrade_call_db_query_range_alter(&$node, &$reader) { // NEEDS WORK
  // Disable this routine until it is improved.
//  return;

  // Get the function call object.
  $item = &$node->data;

  $from = $count = 0;
  if ($item->parameterCount() < 3) {
    clp("ERROR: db_query_range() has less than three parameters.");
    // Nothing to do.
//    return;
  }
  else {
    // Save the values from and delete the last two parameters.
    $i = $item->parameterCount() - 1;
    $from = $item->getParameter($i)->stripComments()->toString();
    $item->deleteParameter($i);
    $i--;
    $count = $item->getParameter($i)->stripComments()->toString();
    $item->deleteParameter($i);
  }

//  coder_upgrade_upgrade_call_db_query_alter($node, $reader);
  if ($sql = coder_upgrade_locate_query_string($node)) {
    // Parse the string.
    coder_upgrade_parse_query_string($node, $sql, $from, $count);
  }

  // Add finishing touches to new query syntax for a range query.
  // See http://drupal.org/node/310075.
  // ->range($from, $count)
}

/**
 * Implements hook_upgrade_call_db_rewrite_sql_alter().
 *
 * @todo db_rewrite_sql() replaced with hook_query_alter()
 * @see http://drupal.org/node/224333#db_rewrite_sql
 */
function coder_upgrade_upgrade_call_db_rewrite_sql_alter(&$node, &$reader) {
  // TODO This is not ready as the call to arrayitize() on a SELECT will
  // look at the count of parameters to db_rewrite_sql() which are not the
  // same as count of parameters to db_query().
  return;
  // Create helper objects.
//  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  /*
   * Use cases
   * - query is a string: parse directly
   * - query is a variable; find the variable and see if it is a string
   * - query is an expression
   */

  // Process function call.
  $name = &$item->name; // NOT DONE - Copied from db_query above
  $p0 = $item->getParameter(0)->stripComments();
  if ($p0->count() == 1) {
    $operand0 = $p0->getElement();
    if (is_array($operand0) && $operand0['type'] == T_CONSTANT_ENCAPSED_STRING) {
      // Convert values to strings.
      // Parse the string.
      coder_upgrade_parse_query_string($node, $operand0);
      // Add $query->addTag('node_access' /* TODO Please indicate the appropriate tag */);
    }
  }
}

/**
 * Returns the query string if found.
 *
 * @param PGPNode $node
 *   The node containing the function call object to be replaced.
 * @param PGPOperand $operand
 *   The query string to be parsed (first parameter to $item).
 *
 * @return string
 *   The query string or FALSE.
 */
function coder_upgrade_locate_query_string(&$node) { // NEEDS WORK
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  /*
   * Use cases
   * - query is a string: parse directly
   * - query is a variable: find the variable and see if it is a string (assigned only once or always from strings, no expressions)
   * - query is an expression (leave this alone)
   */

  // Find the query string. (TODO Are there any API functions in which the query parameter is not in slot zero?)
  $found = FALSE;
  $p0 = $item->getParameter(0)->stripComments();
  if ($p0->count() == 1) {
    // The parameter is a single item expression.
//    $operand0 = $p0->getElement();
    if ($p0->isType(T_CONSTANT_ENCAPSED_STRING)) {
      // The parameter is a string containing the query expression.
      $found = TRUE;
      return $p0->toString();
    }
    elseif ($p0->isType(T_VARIABLE)) {
      // The parameter is a variable containing the query expression.
      cdp('inside T_VARIABLE');
//      $operand0 = $p0->getElement();
      // Parameter is a variable.
      $variable = $p0->getElement()->findNode('value'); // $variable = $operand0->findNode('value');
      cdp($variable, '$variable');
      // Get the parent = statement (i.e. node) this function call is part of.
//      $parent = $item->parent; // $parent = &$item->parent;
      // Find the assignment in the statement list the parent is part of.
      $statement = $item->searchBackward('PGPAssignment', 'values', 0, $variable); // $statement = $parent->container->searchBackward('PGPAssignment', 'values', 0, $variable, $parent);
      cdp($statement, '$statement');
      if ($statement && $statement->values->getElement()->countType('operand') == 2) {
        cdp('inside $statement->values->countType == 2');
        // This assignment could look like $foo = 'bar'.
        $operand2 = &$statement->values->getElement()->findNode('operand', 'backward');
        // TODO A pattern here - this is the same code as above but executed on a different object.
        if (is_array($operand2) && $operand2['type'] == T_CONSTANT_ENCAPSED_STRING) {
          // The parameter variable is assigned a string containing the query expression.
          $found = TRUE;
          return $operand2['value'];
        }
      }
    }
  }
  clp("ERROR: Could not find a SQL string to parse in " . __FUNCTION__);
  $item->insertStatementBefore($editor->commentToStatement('// TODO Please convert this statement to the D7 database API syntax.'));
  return FALSE;
}

/**
 * Replaces D6 database API call with D7 equivalent.
 *
 * @todo Fill in this with unhandled items.
 *
 * @param PGPNode $node
 *   The node containing the function call object to be replaced.
 * [@param PGPOperand $operand
 *   The query string to be parsed (first parameter to $item).]
 * @param string $sql
 *   The query string to be parsed
 * @param integer $from
 *   The first record from the result set to return.
 * @param integer $count
 *   The number of records to return from the result set.
 */
function coder_upgrade_parse_query_string(&$node, /*&$operand*/ $sql, $from = 0, $count = 0) {
  global $_coder_upgrade_replacement_values_is_array, $_coder_upgrade_replacement_index;
  $_coder_upgrade_replacement_index = 0;

  // Create helper objects.
//  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // TODO Parse the values - the other parameters
  // TODO The parameter could be an array variable or expression like array_merge($a, $b)
  // With the latter, add an assignment variable equal to the expression. Then
  // set replacement variables equal to variable[$index].
  // See http://drupalcode.org/viewvc/drupal/drupal/modules/simpletest/tests/database_test.test?revision=1.80&view=markup
  $values = array();
  for ($i = 1; $i < $item->parameterCount(); $i++) {
    $item->setParameter($i, $item->getParameter($i)->stripComments());
    $values[] = $item->printParameter($i);
  }
  cdp($values, '$values');

  /*
   * TODO Run the table names through a conversion routine.
   * Ex: taxonomy, block, etc.
   */
  $new = array();

  $delimiter = $sql[0]; // Save this for SELECT queries.
  // Alter the string for these SQL types as we are making entirely new syntax.
  // Trim won't work here, since it'll trim off the last ' if the string ends in '%s'
  $sql = substr($sql, 1, -1); // $sql = substr($operand['value'], 1, -1);
  // Assume there is no literal string containing any new lines or commas.
//  $sql = preg_replace("@\n@", ' ', $sql);

  if (strpos($sql, 'SELECT') === 0) {
    // @todo If $sql is defined outside of db_query(), then this approach will
    // replace the variable with the new string and leave the assignment alone.
    $new = coder_upgrade_parse_select_query_string($node, $sql, $values, $delimiter);
//    coder_upgrade_insert_dbtng_statement($node, $new); // ???
  }

  // Assume there is no literal string containing any new lines or commas.
  $sql = preg_replace("@\n@", ' ', $sql);

  if (strpos($sql, 'INSERT') === 0) {
    $new = coder_upgrade_parse_insert_query_string($sql, $values);
    coder_upgrade_insert_dbtng_statement($node, $new);
  }
  elseif (strpos($sql, 'UPDATE') === 0) {
    $new = coder_upgrade_parse_update_query_string($sql, $values);
    coder_upgrade_insert_dbtng_statement($node, $new);
  }
  elseif (strpos($sql, 'DELETE') === 0) {
    $new = coder_upgrade_parse_delete_query_string($sql, $values);
    coder_upgrade_insert_dbtng_statement($node, $new);
  }
}

/**
 * Replaces D6 database API call with D7 equivalent.
 *
 * @todo Fill in this with unhandled items.
 *
 * @param PGPNode $node
 *   The node containing the function call object to be replaced.
 * @param string $sql
 *   The SQL query string to parse.
 * @param array $values
 *   List of replacement values passed to db_query().
 */
function coder_upgrade_parse_select_query_string($node, $sql, $values, $delimiter) {
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  $find = '@^(SELECT.*?WHERE\s+)(.*?)$@s';
  preg_match($find, $sql, $matches);
  cdp($matches, '$matches');
  if (empty($matches) /*|| !isset($matches[2])*/) {
    cdp($sql, '$sql');
    clp('ERROR: could not parse sql SELECT statement.');
    return array('NULL'); // $new;
  }
  // Convert conditions to use named placeholders (i.e., from field = '%s' to
  // field = :field).
  // TODO handle more complex conditions
//  if (isset($matches[2]) && $matches[2]) {
    preg_match_all('/
      (\S*)\s*([!=<>]+)\s*[\'"]?%[sdfb][\'"]? # Match field = %d
      |
      (\S*)\s*([!=<>]+)\s*([\'"].*?[\'"]|\S*) # Match field literals
      |
      (\S*)\s+IN\s?\([\'"]%s[\'"]?\) # Match field IN(%s)
    /x', $matches[2], $conditions);
    cdp($conditions, '$conditions');
    $condition_keys = array();
    foreach ($conditions[0] as $key => $condition) {
      if ($conditions[1][$key]) {
        // field = %d condition
        $condition_keys[] = ':' . $conditions[1][$key];
        $sql /*$operand['value']*/ = str_replace($condition, $conditions[1][$key] . ' ' . $conditions[2][$key] . ' :' . $conditions[1][$key], $sql /*$operand['value']*/);
      }
      elseif ($conditions[3][$key]) {
        // field = literal condition
        $condition_keys[] = ':' . $conditions[3][$key];
        $sql /*$operand['value']*/ = str_replace($condition, $conditions[3][$key] . ' ' . $conditions[4][$key] . ' :' . $conditions[3][$key], $sql /*$operand['value']*/);
        $item->insertParameter($key + 1, $editor->expressionToStatement($conditions[5][$key]));
      }
      elseif ($conditions[6][$key]) {
        // field IN (%s) condition
        $condition_keys[] = ':' . $conditions[6][$key];
        $sql /*$operand['value']*/ = str_replace($condition, $conditions[6][$key] . ' IN (:' . $conditions[6][$key] . ')', $sql /*$operand['value']*/);
        // D6 convention was to use implode(",", $array).  Now we can just pass in the array.
        $param = $item->getParameter($key + 1)->getElement()->getParameter(1);
        $item->setParameter($key + 1, $param);
      }
    }
    // Replace the $sql parameter.
    $editor->setParameter($item, 0, $delimiter . $sql . $delimiter /*$operand['value']*/);

    if (empty($condition_keys)) {
      // Parsing of conditions failed.
      clp("ERROR: Could not parse the conditions to select query '$sql' in " . __FUNCTION__);
      $item->insertStatementBefore($editor->commentToStatement('// TODO Please convert this statement to the D7 database API syntax.'));
      return;
    }

    // Arrayitize the values array.
    $string = $editor->arrayitize($item, 1, $condition_keys, array_fill(0, count($condition_keys), "'XXX_YYY'"));
    cdp($string, '$string');
    $temp = $editor->expressionToStatement($string);
    $temp->getElement(0)->multiline = 0;
    $item->setParameter(1, $temp);
//  }
}

/**
 * Replaces D6 database API call with D7 equivalent.
 *
 * @todo Fill in this with unhandled items.
 *
 * @param string $sql
 *   The SQL query string to parse.
 * @param array $values
 *   List of replacement values passed to db_query().
 */
function coder_upgrade_parse_insert_query_string($sql, $values) {
  global $_coder_upgrade_replacement_values_is_array;

  $new = array();
  // Look for query with a WHERE clause.
  // INSERT INTO {mytable_longer_name} (intvar, stringvar, floatvar) VALUES (%d, '%s', %f)
  // TODO How does DBTNG handle multiple rows to insert?
  $find = '@INSERT INTO\s+{(\w+)}\s+\((.*?)\)\s+VALUES\s+\((.*?)\)@s';
  preg_match($find, $sql, $matches);
  cdp($matches);
  if (empty($matches) /*|| !isset($matches[2])*/) {
    cdp($sql, '$sql');
    clp('ERROR: could not parse sql INSERT statement.');
    return array('NULL'); // $new;
  }

  // Parse fields to be updated.
  if (count($matches[2]) != count($matches[3])) {
    clp('ERROR: could not parse field names and replacements on sql INSERT statement.');
    return array('NULL'); // $new;
  }
  $fields = preg_split("@,\s*@", $matches[2]);
  $holders = preg_split("@,\s*@", $matches[3]);
  $fields = array_combine($fields, $holders);
  cdp($fields);
  $replacement_count = coder_upgrade_count_sql_values($holders);
  $_coder_upgrade_replacement_values_is_array = count($values) == 1 && ($replacement_count > 1 /*|| count($values) != $replacement_count*/);

  // Build DBTNG syntax string.
  // TODO Values could be literals not placeholders.
  $new[] = "\$id = db_insert('{$matches[1]}')";
  $new[] = "\t->fields(array(";
  foreach ($fields as $field => $value) {
    if (preg_match('/%[sdbf]/', $value)) {
      // Value is a placeholder.
      $value = coder_upgrade_next_replacement_value($values);
    }
    else {
      // Value is a literal (assume so).
    }
    $new[] = "\t\t'$field' => $value,";
  }
  $new[] = "\t))";
  $new[] = "\t->execute();";

  return $new;
}

/**
 * Replaces D6 database API call with D7 equivalent.
 *
 * @todo Fill in this with unhandled items.
 *
 * @param string $sql
 *   The SQL query string to parse.
 * @param array $values
 *   List of replacement values passed to db_query().
 */
function coder_upgrade_parse_update_query_string($sql, $values) {
  cdp(__FUNCTION__);
  global $_coder_upgrade_replacement_values_is_array;

  // Regex needs to handle multi-line strings. The parsing and exploding of
  // fields and conditions fails on this.
  // Also, if there are multiple values to be replaced and only a single value
  // as parameter to drupal_query, then assume it is an array and apply it in
  // order by index to the substitutions.
  // db_update('quotes_blocks')->fields(array('name' => $vals[0], 'block_type' => $vals[1], ...)

  $new = array();
  // Look for query with both SET and WHERE clauses.
  // UPDATE {node} SET title='%s', status=%d WHERE uid=%d
  $find = '@^UPDATE\s+{(\w+)}\s+SET\s+(.*?)\s+WHERE\s+(.*?)$@s';
  // TODO Check for WHERE and use a different regex.
  preg_match($find, $sql, $matches);
  cdp($matches, '$matches');
  if (empty($matches)) {
    // Look for query with only a SET clause.
    $find = '@^UPDATE\s+{(\w+)}\s+SET\s+(.*?)$@s';
    preg_match($find, $sql, $matches);
    cdp($matches, '$matches');
    if (empty($matches) /*|| !isset($matches[2])*/) {
      cdp($sql, '$sql');
      clp('ERROR: could not parse sql UPDATE statement.');
      return array('NULL'); // $new;
    }
  }

  // Parse fields to be updated.
  // TODO This will fail on a literal string with a comma.
  $fields = preg_split("@,\s*@", $matches[2]); // $fields = explode(', ', $matches[2]);
  cdp($fields, '$fields');
  $condition_count = isset($matches[3]) && $matches[3] ? coder_upgrade_count_sql_conditions($matches[3]) : 0;
  $replacement_count = coder_upgrade_count_sql_fields($fields) + $condition_count;
  cdp($replacement_count, '$replacement_count');
  if (/*count($values) > 1 &&*/ count($values) != $replacement_count) {
    clp('ERROR: number of replacement values to db_query does not equal number of items needing replacement.');
    clp($sql);
  }
  $_coder_upgrade_replacement_values_is_array = count($values) == 1 && ($replacement_count > 1 /*|| count($values) != $replacement_count*/);

  // Build DBTNG syntax string.
  $new[] = "db_update('{$matches[1]}')";
  $new[] = "\t->fields(array(";
  foreach ($fields as $field) {
    list($field, $value) = explode("=", $field);
    // Value is a placeholder
    if (preg_match('/%[sdbf]/', $value)) {
      $value = coder_upgrade_next_replacement_value($values);
    }
    // Trim the field for whitespace.
    $field = trim($field);
    $new[] = "\t\t'$field' => $value,";
  }
  $new[] = "\t))";
  if (isset($matches[3]) && $matches[3]) {
    $new[] = coder_upgrade_parse_sql_conditions($matches[3], $values);
  }
  $new[] = "\t->execute();";
  cdp($new, '$new');

  return $new;
}

/**
 * Replaces D6 database API call with D7 equivalent.
 *
 * @todo Fill in this with unhandled items.
 *
 * @param string $sql
 *   The SQL query string to parse.
 * @param array $values
 *   List of replacement values passed to db_query().
 */
function coder_upgrade_parse_delete_query_string($sql, $values) {
  global $_coder_upgrade_replacement_values_is_array;

  $new = array();
  // Look for query with a WHERE clause.
  // DELETE FROM {node} WHERE uid=%d AND created < %d
  $find = '@^DELETE\s+FROM\s+{(\w+)}\s+WHERE\s+(.*?)$@s';
  preg_match($find, $sql, $matches);
  cdp($matches);
  if (empty($matches)) {
    // Look for query without a WHERE clause.
    $find = '@^DELETE\s+FROM\s+{(\w+)}$@s';
    preg_match($find, $sql, $matches);
    cdp($matches, '$matches');
    if (empty($matches)) {
      cdp($sql, '$sql');
      clp('ERROR: could not parse sql DELETE statement.');
      return array('NULL'); // $new;
    }
  }

  // Parse condition for rows to be deleted.
  $condition_count = isset($matches[2]) && $matches[2] ? coder_upgrade_count_sql_conditions($matches[2]) : 0;
  $replacement_count = $condition_count;
  cdp($replacement_count, '$replacement_count');
  if (/*count($values) > 1 &&*/ count($values) != $replacement_count) {
    clp('ERROR: number of replacement values to db_query does not equal number of items needing replacement.');
    clp($sql);
  }
  $_coder_upgrade_replacement_values_is_array = count($values) == 1 && ($replacement_count > 1 /*|| count($values) != $replacement_count*/);

  // Build DBTNG syntax string.
  $new[] = "db_delete('{$matches[1]}')";
  if (isset($matches[2]) && $matches[2]) {
    $new[] = coder_upgrade_parse_sql_conditions($matches[2], $values);
  }
  $new[] = "\t->execute();";
  cdp($new, '$new');

  return $new;
}

/**
 * Inserts (or replaces) D6 database API call with D7 call.
 *
 * @param PGPNode $node
 *   The node containing the function call object to be replaced.
 * @param array $new
 *   The array of strings of the new database API call.
 *
 * @return unknown_type
 */
function coder_upgrade_insert_dbtng_statement(&$node, $new) {
  cdp(__FUNCTION__);
  // Create helper objects.
  $editor = PGPEditor::getInstance();

  // Get the function call object.
  $item = &$node->data;

  // Create the expression text to be inserted.
  // TODO Handle the indentation of the output string in the toString() routine.
  $new = implode("\n", $new);
  $new = str_replace("\t", '  ', $new);

  if ($new == 'NULL') {
    clp("ERROR: Could not parse the SQL string");
    $comment = '// TODO Please convert this statement to the D7 database API syntax.';
  }
  else {
    $comment = '// TODO Please review the conversion of this statement to the D7 database API syntax.';
  }
  // Insert a comment before the statement containing the function call.
  $item->insertStatementBefore($editor->commentToStatement($comment));

  // Insert a multiline-safe comment with the original function call.
  $string = str_replace(array('/*', '*/'), '', $item->toString());
  $item->insertStatementBefore($editor->commentToStatement("/* $string */"));

  // Create a new DBTNG expression (of chained operations).
  $temp = $editor->expressionToStatement($new);
  // Insert the expression in the containing statement before the function call.
  $node->container->insertListBefore($node, $temp);
  // Delete the function call.
  // NOTE: This is an example of deleting a function call reference.
  $node->container->delete($node);
  // NOTE: If the replacement was another function call, then we could write:
  //   $temp->parent = $item->parent;
  //   $item = $temp;
}

/**
 * Replaces values with array of indexed items.
 *
 * @param array $values
 *   The replacement values.
 */
function coder_upgrade_next_replacement_value(&$values) {
  global $_coder_upgrade_replacement_values_is_array, $_coder_upgrade_replacement_index;

  if ($_coder_upgrade_replacement_values_is_array) {
    $value = $values[0] . "['$_coder_upgrade_replacement_index']";
    $_coder_upgrade_replacement_index++;
  }
  else {
    $value = array_shift($values);
  }
  return $value;
}

/**
 * Returns count of sql fields that need a replacement value.
 *
 * @param array fields
 *   Array of sql fields.
 *
 * @return integer
 *   Count of fields.
 */
function coder_upgrade_count_sql_fields($fields) {
  $count = 0;
  foreach ($fields as $field) {
    list($field, $value) = explode("=", $field);
    if (is_null($value)) {
      cdp($field, '$field');
    }
    if (preg_match('/%[sdbf]/', $value)) {
      // Value is a placeholder.
      $count++;
    }
  }
  return $count;
}

/**
 * Returns count of sql values that need a replacement value.
 *
 * @param array values
 *   Array of sql values.
 *
 * @return integer
 *   Count of values.
 */
function coder_upgrade_count_sql_values($values) {
  $count = 0;
  foreach ($values as $value) {
    if (preg_match('/%[sdbf]/', $value)) {
      // Value is a placeholder.
      $count++;
    }
  }
  return $count;
}

/**
 * Returns count of sql conditions that need a replacement value.
 *
 * @param string $string
 *   String of sql conditions.
 *
 * @return integer
 *   Count of conditions.
 */
function coder_upgrade_count_sql_conditions($string) {
  // Check for inner conditionals or function calls.  For now, we'll just use
  // where() instead of conditionals, given the complexity of inner conditionals.
  if (preg_match("/\((.*)\)/", $string, $matches)) {
    return 1; // return "\t\t->where('$string', " . var_dump($values) . ")";
  }

  $count = 0;
  // TODO Handle other conjunctions besides AND.
  $conditions = preg_split('/AND|OR|XOR|&&|\|\|/', $string);
  if (!is_array($conditions)) {
    $conditions = array($string);
  }
  foreach ($conditions as $condition) {
    // TODO Handle other functions like IN, BETWEEN
    list($condition, $operator, $value) = preg_split('/([!=><]+|LIKE|IN|BETWEEN)/', $condition, -1, PREG_SPLIT_DELIM_CAPTURE);
    if (preg_match('/%[sbdf]/', trim($value))) {
      $count++;
    }
  }
  return $count;
}

/**
 * Parses sql conditions into conditional object strings.
 *
 * @param string $string
 *   String of sql conditions.
 * @param array $values
 *
 * @return string
 *   String of conditions in DBTNG syntax.
 */
function coder_upgrade_parse_sql_conditions($string, $values) {
  // Check for inner conditionals or function calls.  For now, we'll just use
  // where() instead of conditionals, given the complexity of inner conditionals.
  if (preg_match("/\((.*)\)/", $string, $matches)) {
    return "\t\t->where('$string', " . var_dump($values) . ")";
  }
  // TODO Handle other conjunctions besides AND.
  $conditions = preg_split('/AND|OR|XOR|&&|\|\|/', $string);
  if (!is_array($conditions)) {
    $conditions = array($string);
  }

  foreach ($conditions as $condition) {
    list($condition, $operator, $value) = preg_split('/([!=><]+|LIKE)/', $condition, -1, PREG_SPLIT_DELIM_CAPTURE);
    if (preg_match('/%[sbdf]/', trim($value))) {
      $value = coder_upgrade_next_replacement_value($values);
    }
    // Trim the condition for whitespace.
    $condition = trim($condition);
    $value = trim($value);
    // TODO handle IN and BETWEEN conditions
    // TODO Handle function conditions such as LIKE, MIN, SUM
    switch ($operator) {
      case '=':
        $parsed_conditions[] = "\t->condition('$condition', $value)";
        break;
      default:
        $parsed_conditions[] = "\t->condition('$condition', $value, '$operator')";
        break;
    }
  }
  return implode("\n", $parsed_conditions);
}
