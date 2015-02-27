<?php

/**
 * @file
 *   Drush support for node_export.
 */

/**
 * Implements hook_drush_command().
 */
function node_export_drush_command() {
  $items = array();

  $items['node-export-export'] = array(
    'callback' => 'drupal_node_export_callback_export',
    'description' => "Export nodes using Node export.",
    'arguments' => array(
      'nids' => "A list of space-separated node IDs to export.",
    ),
    'options' => array(
      'file' => "The filename of the output file.  If supplied, the node code will be exported to that file, otherwise it will export to stdout.",
      'format' => "If supplied, node code will be output using a particular export format, if available. (e.g. serialize)",
      'status' => "Filter for 'status'; A boolean value (0 or 1) indicating whether the node is published (visible to non-administrators).",
      'promote' => "Filter for 'promote'; A boolean value (0 or 1) indicating whether the node should be displayed on the front page.",
      'sticky' => "Filter for 'sticky'; A boolean value (0 or 1) indicating whether the node should be displayed at the top of lists in which it appears.",
      'translate' => "Filter for 'translate'; A boolean value (0 or 1) indicating whether the node translation needs to be updated.",
      'language' => "Filter for 'language'; The language code (e.g. de or en-US) of this node.",
      'type' => "Filter for 'type'; The machine-readable name (e.g. story or page) of the type of this node.",
      'sql' => "Filter by SQL (EXPERIMENTAL); An SQL query string that returns nids (e.g. \"SELECT nid FROM nodes WHERE nid < 10\").",
      'code' => "Filter by PHP code (EXPERIMENTAL); PHP code that prints or returns, an array or CSV string of nids (e.g. \"custom_get_my_nids();\"). Don't include PHP tags.",
    ),
    'examples' => array(
      'drush node-export-export 45 46 47 --file=filename' =>
        "export nodes with node IDs 45, 46, and 47 to the file with the supplied filename.",
      'drush node-export-export --type=story,page --file=filename' =>
        "export nodes of type story and page to the file with the supplied filename.",
    ),
  );
  $items['node-export-import'] = array(
    'callback' => 'drush_node_export_callback_import',
    'description' => "Import nodes previously exported with Node export.",
    'options' => array(
      'uid' => "User ID of user to save nodes as. If not given will use the user with an ID of 1. You may specify 0 for the Anonymous user.",
      'file' => "The filename of the input file.  If supplied, the node code will be imported from that file, otherwise it will import to stdin.",
    ),
    'examples' => array(
      'drush node-export-import --file=filename' =>
        'Import nodes from the file with the given filename.',
      'drush node-export-import --uid=2 --file=filename' =>
        "Import nodes from the file with the given filename.  The author of the nodes will be set to the user that has the user ID of 2.",
    ),
  );

  // Add aliases for usability.
  node_export_drush_command_add_alias($items, 'node-export-export', 'node-export');
  node_export_drush_command_add_alias($items, 'node-export-export', 'ne-export');
  node_export_drush_command_add_alias($items, 'node-export-import', 'ne-import');

  return $items;
}

/**
 * A function to help alias commands as other commands.
 */
function node_export_drush_command_add_alias(&$items, $command, $alias) {
  // Create a property on the command for adding aliases, if not there.
  if (!isset($items[$command]['node_export command aliases'])) {
    $items[$command]['node_export command aliases'] = array();
  }
  // Record the alias into that property.
  $items[$command]['node_export command aliases'][] = $alias;
  // Create the alias as a new command.
  $items[$alias] = $items[$command];
  // Indicate what this new command is an alias for.
  $items[$alias]['node_export alias for'] = $command;
}

/**
 * Implements hook_drush_help().
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
function node_export_drush_help($section) {
  // This is to prevent duplication of information from hook_drush_command().
  $commands = node_export_drush_command();
  foreach ($commands as $command => $command_info) {
    if ($section == 'drush:' . $command) {
      $out = $command_info['description'];
      if (isset($command_info['node_export alias for'])) {
        $output .= "\nThis command is an alias for ";
        $output .= $command_info['node_export alias for'] . ".";
      }
      if (isset($command_info['node_export command aliases'])) {
        if (count($command_info['node_export command aliases']) == 1) {
          $output .= "\nThis command can be called by it's alias; ";
          $output .= $command_info['node_export command aliases'] . ".";
        }
        else {
          $last_alias = array_pop($command_info['node_export command aliases']);
          $output .= "\nThis command can be called by it's aliases; ";
          $output .= implode(", ", $command_info['node_export command aliases']);
          $output .= ", or " . $last_alias . ".";
        }
      }
      $out .= "\n\nArguments:";
      if (isset($command_info['arguments'])) {
        foreach ($command_info['arguments'] as $k => $v) {
          $out .= "\n  " . $k . " : " . $v;
        }
      }
      $out .= "\n\nOptions:";
      if (isset($command_info['options'])) {
        foreach ($command_info['options'] as $k => $v) {
          $out .= "\n  " . $k . " : " . $v;
        }
      }
      $out .= "\n\nExamples:";
      if (isset($command_info['examples'])) {
        foreach ($command_info['examples'] as $k => $v) {
          $out .= "\n  \'" . $k . "\' : " . $v;
        }
      }
      return dt($out);
    }
  }
}

/**
 * Drush command callback.
 *
 * export nodes.
 */
function drupal_node_export_callback_export() {

  // Set up an array of nid_filters.
  $nid_filters = array();

  // The base nids.
  $args = array_filter(func_get_args(), 'is_numeric');
  if ($args) {
    $nid_filters['base'] = $args;
  }

  // Filter for values in the node table (except for nids).
  $filters = array(
    'status',
    'promote',
    'sticky',
    'translate',
    'language',
    'type',
  );

  $query = db_select('node', 'n')->fields('n', array('nid'));
  $execute = FALSE;
  foreach ($filters as $filter) {
    $filter_option = drush_get_option($filter);
    if ($filter_option) {
      $query->condition($filter, explode(',', $filter_option), 'IN');
      // Only execute if conditions are set.
      $execute = TRUE;
    }
  }
  if ($execute) {
    $result = $query->execute();
    foreach ($result as $row) {
      $nid_filters['filters'][] = $row->nid;
    }
  }

  // Handle SQL option.
  $sql = drush_get_option('sql');
  if ($sql) {
    $result = db_query($sql);
    foreach ($result as $row) {
      $nid_filters['sql'][] = $row->nid;
    }
  }

  // Handle PHP option.
  $code = drush_get_option('code');
  if ($code) {
    ob_start();
    print eval("?><?php " . $code . " ?>");
    $result = ob_get_contents();
    ob_end_clean();
    if (is_array($result)) {
      $nid_filters['code'] = $result;
    }
    else {
      $nid_filters['code'] = explode(
        ",",
        str_replace(array("\n", "\r", "\t", " "), '', $result)
      );
    }
  }

  if (count($nid_filters) > 1) {
    // Compute the intersect of all $nid_filters if there are more than one.
    $nids = call_user_func_array('array_intersect', $nid_filters);
  }
  elseif (count($nid_filters) == 1) {
    // Use the only filter if there is only one.
    $nids = reset($nid_filters);
  }
  else {
    // Is there are no filters at all, do a query to get all nids.
    $result = db_select('node', 'n')->fields('n', array('nid'))->execute();
    $nids = array();
    foreach ($result as $row) {
      $nids[] = $row->nid;
    }
  }

  // Handle format option.
  $format = drush_get_option('format');

  if (empty($nids)) {
    drush_set_error('DRUSH_NOT_COMPLETED', "No nodes found.");
  }

  $result = node_export($nids, $format, 'dt');

  if ($result['success']) {
    $filename = drush_get_option('file');

    if ($filename) {
      // Output data to file. Note this only takes a flat filename for the current directory.
      // If file exists, ask for whether to overwrite.
      if (file_exists($filename)) {
        if (!drush_confirm(dt("File $filename exists. Do you really want to overwrite?"))) {
          return;
        }
      }
      // Write the file.
      file_put_contents($filename, $result['output']);
    }
    else {
      // stdout.
      drush_print_r($result['output']);
    }

  }
  else {
    // We have received an error message.
    drush_set_error('DRUSH_NOT_COMPLETED', strip_tags(implode("\n", $result['output'])));
  }

}

/**
 * Drush command callback.
 *
 * Import nodes from data.
 */
function drush_node_export_callback_import() {
  // Switch to site maintenance account or the specified user so imported nodes are not anonymous.
  $uid = drush_get_option('uid');
  // Test on NULL so uid may be given as 0.
  if (is_null($uid)) {
    $uid = 1;
  }
  // User 0 is already loaded.
  if ($uid != 0) {
    global $user;
    $user = user_load($uid);
  }

  $filename = drush_get_option('file');

  if ($filename) {
    $node_code = file_get_contents($filename, "r");
  }
  else {
    $node_code = file_get_contents("php://stdin", "r");
  }

  if (!empty($node_code)) {
    $result = node_export_import($node_code, 'dt');
    if (!$result['success']) {
      // We have received an error message.
      drush_set_error('DRUSH_NOT_COMPLETED', strip_tags(implode("\n", $result['output'])));
    }
    else {
      drush_print(strip_tags(implode("\n", $result['output'])));
    }
  }

}

