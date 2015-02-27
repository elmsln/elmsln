<?php

/**
 * @file
 * The Node export DSV format handler.
 *
 * Adds configurable DSV format to Node export.
 */

/**
 * Settings callback.
 */
function node_export_dsv_settings($form, $form_state) {
  $settings['dsv'] = array(
    '#type' => 'fieldset',
    '#title' => t('DSV format settings'),
    '#description' => t(
     'Select how your DSV output will be formatted - this must be configured the
     same on both sites.  By default this is configured to RFC4180 CSV format
     where the delimiter is a comma (,), the enclosure is a double-quote ("),
     and the seperator is CRLF (\r\n).  Not all configurations may be possible,
     use wisely.  Enclosure will only be used to escape values that contain any
     of the configured strings.  Additionally single-quotes will be used to
     escape values that are equivalent to reserved words (NULL, TRUE, FALSE).'
    ),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $settings['dsv']['node_export_dsv_delimiter'] = array(
    '#type' => 'textfield',
    '#title' => t('Value delimiter'),
    '#size' => 5,
    '#maxlength' => 255,
    '#default_value' => variable_get('node_export_dsv_delimiter', ','),
    '#required' => TRUE,
  );

  $settings['dsv']['node_export_dsv_enclosure'] = array(
    '#type' => 'textfield',
    '#title' => t('Escape enclosure'),
    '#size' => 5,
    '#maxlength' => 255,
    '#default_value' => variable_get('node_export_dsv_enclosure', '"'),
    '#required' => TRUE,
  );

  $settings['dsv']['node_export_dsv_seperator'] = array(
    '#type' => 'textfield',
    '#title' => t('Record seperator'),
    '#size' => 5,
    '#maxlength' => 255,
    '#default_value' => variable_get('node_export_dsv_seperator', '\r\n'),
    '#required' => TRUE,
  );

  $settings['dsv']['node_export_dsv_escape_eol'] = array(
    '#type' => 'checkbox',
    '#title' => t('Always escape values containing line breaks'),
    '#default_value' => variable_get('node_export_dsv_escape_eol', 1),
    '#description' => t('This is to overcome problems where Windows injects CRLF line breaks.'),
  );

  return $settings;
}

function node_export_dsv_string($string) {
  $replace = array(
   '\n' => "\n",
   '\r' => "\r",
   '\t' => "\t",
   '\v' => "\v",
   '\e' => "\e",
   '\f' => "\f",
  );
  return str_replace(array_keys($replace), array_values($replace), $string);
}

/**
 * Export callback.
 */
function node_export_dsv_export($nodes, $format) {
  $delimiter = node_export_dsv_string(variable_get('node_export_dsv_delimiter', ','));
  $enclosure = node_export_dsv_string(variable_get('node_export_dsv_enclosure', '"'));
  $seperator = node_export_dsv_string(variable_get('node_export_dsv_seperator', '\r\n'));
  $escape_eol = variable_get('node_export_dsv_escape_eol', 1);
  return node_export_dsv_encode($nodes, $delimiter, $enclosure, $seperator, $escape_eol);
}

/**
 * Build DSV string.
 */
function node_export_dsv_encode($nodes, $delimiter, $enclosure, $seperator, $escape_eol) {
  $encoded_nodes = array();
  $dsv_lines = array();

  $node_keys = array();
  foreach (array_keys($nodes) as $node_key) {
    $new_node_key = 'node_' . $node_key;
    $node_keys[] = $new_node_key;
    node_export_dsv_encode_node($encoded_nodes, $new_node_key, $nodes[$node_key]);
  }

  $dsv_lines['node_export_dsv_header'] = array_keys($encoded_nodes);

  foreach (array_keys($encoded_nodes) as $header_value) {
    $encoded_nodes[$header_value] = array_merge(array_fill_keys($node_keys, NULL), $encoded_nodes[$header_value]);
    foreach (array_keys($encoded_nodes[$header_value]) as $encoded_node_key) {
      $dsv_lines[$encoded_node_key][$header_value] = $encoded_nodes[$header_value][$encoded_node_key];
    }
  }

  return node_export_dsv_array_to_dsv($dsv_lines, $delimiter, $enclosure, $seperator, $escape_eol);
}

/**
 * Process a node and update $header and $encoded_nodes accordingly.
 */
function node_export_dsv_encode_node(&$encoded_nodes, $node_key, $var, $parent = NULL) {

  foreach ($var as $k => &$v) {

    // Get the new header value.
    $header_value = node_export_dsv_encode_header_value($parent, $var, $k);

    if (is_object($v) || is_array($v)) {
      // Recurse through the structure.
      node_export_dsv_encode_node($encoded_nodes, $node_key, $v, $header_value);
    }
    else {
      // Create a safe text version of this value and store it against the header using a safe key.
      $encoded_nodes[$header_value][$node_key] = node_export_dsv_encode_sanitize_value($v);
    }
  }
}

/**
 * Encode a value.
 */
function node_export_dsv_encode_sanitize_value($var) {
    if (is_numeric($var)) {
      return $var;
    }
    elseif (is_bool($var)) {
      return ($var ? 'TRUE' : 'FALSE');
    }
    elseif (is_null($var)) {
      return 'NULL';
    }
    elseif (is_string($var) && !empty($var)) {
      // Single-quote strings that could be confused for null or boolean.
      if (in_array(strtoupper($var), array('TRUE', 'FALSE', 'NULL'))) {
        $var = "'" . $var . "'";
      }

      return $var;
    }
    else {
      return '';
    }
}

/**
 * Decode a value.
 */
function node_export_dsv_decode_sanitize_value($var) {
  // Allow numeric, bool, and null values to pass right back as is.
  if (is_numeric($var) || is_bool($var) || is_null($var)) {
    return $var;
  }
  // Allow the special case strings back as is.
  elseif (in_array(strtoupper($var), array("'TRUE'", "'FALSE'", "'NULL'"))) {
    return $var;
  }
  // Assume this is a string.
  return "'" . str_replace("'", "\'", $var) . "'";
}

/**
 * Create header value from $parents, $var, and $k.
 */
function node_export_dsv_encode_header_value($parents, $var, $k) {
  if (is_null($parents)) {
    // Special case; on the first level do not prefix the key.
    $header_value = $k;
  }
  elseif (is_object($var)) {
    $header_value = $parents . "->" . $k;
  }
  elseif (is_array($var)) {
    $header_value = $parents . "['" . $k . "']";
  }
  return $header_value;
}

/**
 * Import callback.
 */
function node_export_dsv_import($code_string) {
  $delimiter = node_export_dsv_string(variable_get('node_export_dsv_delimiter', ','));
  $enclosure = node_export_dsv_string(variable_get('node_export_dsv_enclosure', '"'));
  $seperator = node_export_dsv_string(variable_get('node_export_dsv_seperator', '\r\n'));
  return node_export_dsv_decode($code_string, $delimiter, $enclosure, $seperator);
}

/**
 *  Interpret a DSV string.
 */
function node_export_dsv_decode($code_string, $delimiter, $enclosure, $seperator) {
  // Get array data from DSV.
  $array = @node_export_dsv_dsv_to_array($code_string, $delimiter, $enclosure, $seperator);

  // If the first two rows are of equal length, we can assume this is a DSV.
  // Also checks there are a decent number of fields.
  if (!empty($array[0]) && !empty($array[1]) && count($array[0]) > 10 && count($array[0]) == count($array[1])) {
    $nodes = array();

    // Assume row 0 is the header, and the rest of the rows are the nodes.
    $header = array_shift($array);

    // Build the nodes.
    foreach ($array as &$row) {
      $node = (object)array();
      foreach ($row as $key => $item) {
        $item = node_export_dsv_decode_sanitize_value($item);
        eval('$node->' . $header[$key] . ' = ' . $item . ';');
      }
      $nodes[] = $node;
    }

    return $nodes;
  }
}

/**
 *  Encode DSV.
 */
function node_export_dsv_array_to_dsv($array, $delimiter, $enclosure, $seperator, $escape_eol) {
  $lines = array();
  foreach ($array as $line) {
    $out_item = array();
    foreach ($line as $item) {
      if (stripos($item, $enclosure) !== FALSE) {
        $item = str_replace($enclosure, $enclosure . $enclosure, $item);
      }
      if (
        (stripos($item, $delimiter) !== FALSE)
        || (stripos($item, $enclosure) !== FALSE)
        || (stripos($item, $seperator) !== FALSE)
        || ($escape_eol && stripos($item, "\n") !== FALSE)
      ) {
        $item = $enclosure . $item . $enclosure;
      }
      $out_item[] = $item;
    }
    $lines[] = implode($delimiter, $out_item);
  }
  return implode($seperator, $lines);
}

/**
 *  Decode DSV.
 */
function node_export_dsv_dsv_to_array($string, $delimiter, $enclosure, $seperator) {
  $lines = array();
  $out_item = array();
  $count = strlen($string);
  $escape = FALSE;
  $double_escape = FALSE;
  $position = 0;
  $i = 0;
  $seperators = str_split($seperator);

  while ($i < $count) {
    $c = $string[$i];

    // Determine whether this is an EOL.
    $is_eol = TRUE;
    for ($j = 0; $j < count($seperators); $j++) {
      if (!isset($string[$i + $j]) || $string[$i + $j] != $seperators[$j]) {
        $is_eol = FALSE;
        break;
      }
    }

    if ($is_eol) {
      if ($escape) {
        $out_item[$position] .= $c;
      }
      else {
        $i += count($seperators);
        $lines[] = $out_item;
        $out_item = array();
        $position = 0;
        continue;
      }
    }
    elseif ($c == $delimiter) {
      if ($escape) {
        $out_item[$position] .= $c;
      }
      else {
        if ($string[$i - 1] == $delimiter) {
          $out_item[$position] .= '';
        }
        $position++;
        $escape = FALSE;
        $double_escape = FALSE;
      }
    }
    elseif ($c == $enclosure) {
      if ($double_escape) {
        $out_item[$position] .= $enclosure;
        $double_escape = FALSE;
      }
      if ($escape) {
        $escape = FALSE;
        $double_escape = TRUE;
      }
      else {
        $escape = TRUE;
        $double_escape = FALSE;
      }
    }
    else {
      if ($double_escape) {
        $out_item[$position] .= $enclosure;
        $double_escape = FALSE;
      }
      $out_item[$position] .= $c;
    }
    $i++;
  }
  if (!empty($out_item)) {
    $lines[] = $out_item;
  }
  return $lines;
}

/**
 * Callback for actions.
 */
function node_export_dsv_action_form($context, &$form_state) {
  return node_export_action_form($context, $form_state, 'dsv');
}