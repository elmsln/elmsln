<?php

/**
 * @file
 * The Node export XML format handler.
 *
 * Adds XML format to Node export.
 */

/**
 * Export callback.
 */
function node_export_xml_export($nodes, $format) {
  $xml_code = "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\n";
  $xml_code .= "<node_export created=\"" . date('r') . "\">\n";
  $xml_code .= node_export_xml_encode($nodes);
  $xml_code .= "</node_export>";
  return $xml_code;
}

/**
 * Import callback.
 */
function node_export_xml_import($code_string) {
  // Check for "<?xml" at the start.
  if (substr(ltrim($code_string), 0, 5) == "<?xml") {

    // Decode the XML.
    $xml_class = new NodeExportXmlDecoder();
    $result = $xml_class->decode($code_string);

    // Convert the nodes into objects.
    if (!isset($result['success'])) {
      foreach($result as $k => $v) {
        $result[$k] = (object)$v;
      }
    }

    return $result;
  }
}

/**
 * Build XML string recursively.
 */
function node_export_xml_encode($var, $iteration = 0) {
  $xml_code = "";
  $tab = '';
  for ($i = 0; $i <= $iteration; $i++) {
    $tab = $tab . "  ";
  }
  $iteration++;
  foreach ($var as $key => $value) {
    $attributes = array();
    if (is_bool($value)) {
      $attributes['type'] = 'boolean';
    }
    elseif (is_null($value)) {
      $attributes['type'] = 'NULL';
    }
    elseif (is_object($value)) {
      if ($iteration == 1 && isset($value->nid) && isset($value->type)) {
        // Assume first-level object with a nid and type is a stdClass node.
        $key = "node";
      }
      else {
        $attributes['class'] = get_class($value);
      }
      $value = (array)$value;
    }
    if (is_array($value) && array_values($value) === $value) {
      $attributes['_numeric_keys'] = "1";
    }
    $attr_string = "";
    foreach ($attributes as $attr_name => $attr_value) {
      $attr_string .= ' ' . $attr_name . '="' . $attr_value . '"';
    }

    if (is_numeric($key)) {
      $key = "n" . $key;
    }
    $xml_code .= $tab . "<" . $key . $attr_string . ">";

    if (is_array($value)) {
      if (!empty($value)) {
        $xml_code .= "\n";
        $xml_code .= node_export_xml_encode($value, $iteration);
        if (!is_numeric($key)) {
          $xml_code .= $tab;
        }
      }
    }
    elseif (is_numeric($value)) {
      $xml_code .= $value;
    }
    elseif (is_bool($value)) {
      $xml_code .= ($value ? 'TRUE' : 'FALSE');
    }
    elseif (is_string($value)) {
      $xml_code .= htmlspecialchars($value);
    }
    $xml_code .= "</" . $key . ">\n";
  }
  return $xml_code;
}

/**
 * Class for parsing Node export XML.
 */
class NodeExportXmlDecoder {
  var $stack;
  var $output;

  function decode($code_string) {
    $parser = xml_parser_create();
    xml_set_element_handler($parser, array(&$this, 'start_handler'), array(&$this, 'end_handler'));
    xml_set_character_data_handler($parser, array(&$this, 'data_handler'));
    $this->stack = array(
      array(
        'name' => 'node_export',
        'attributes' => array(),
        'children' => array(),
        'data' => '',
      )
    );
    if (!xml_parse($parser, $code_string)) {
      $errors[] = "Node export XML import was unsuccessful, error details follow.  No nodes imported.";
      $line = xml_get_current_line_number($parser);
      $column = xml_get_current_column_number($parser);
      $error = xml_error_string(xml_get_error_code($parser));
      $errors[] = "Line " . $line . ", Column " . $column .": ". $error;
      $lines = explode("\n", $code_string, $line + 1);
      $errors[] = "<pre>". htmlspecialchars($lines[$line - 1]) ."</pre>";
      xml_parser_free($parser);
      return array(
        'success' => FALSE,
        'output' => $errors,
      );
    }
    xml_parser_free($parser);

    $tmp = $this->build($this->stack[0]);
    if (count($tmp) == 1) {
      $this->output = array_pop($tmp);
    }
    else {
      $this->output = array();
    }
    unset($this->stack);
    return $this->output;
  }

  function build($stack) {
    $result = array();

    if (count($stack['children']) > 0) {
      $keycount = array();
      foreach ($stack['children'] as $child) {
        $keycount[] = $child['name'];
      }
      if (count(array_unique($keycount)) != count($keycount)) {
        // Enumerated array.
        $children = array();
        foreach ($stack['children'] as $child) {
          $children[] = $this->build($child);
        }
      }
      else {
        // Associative array.
        $children = array();
        foreach ($stack['children'] as $child) {
          if (!empty($stack['attributes']['_NUMERIC_KEYS'])) {
            $child['name'] = intval(substr($child['name'], 1));
          }
          $children[$child['name']] = $this->build($child);
        }
      }
      $result = array_merge($result, $children);
    }

    if (count($result) == 0) {
      // An atomic value.
      $return = trim($stack['data']);
      if (isset($stack['attributes']['TYPE'])) {
        if ($stack['attributes']['TYPE'] == 'boolean') {
          return (trim($stack['data']) == 'TRUE' ? TRUE : FALSE);
        }
        elseif ($stack['attributes']['TYPE'] == 'NULL') {
          return NULL;
        }
      }
      return htmlspecialchars_decode(trim($stack['data']));
    }
    else {
      // An array or object.
      if (isset($stack['attributes']['CLASS'])) {
        $object = new $stack['attributes']['CLASS']();
        foreach ($result as $k => $v) {
          $object->$k = $v;
        }
        $result = $object;
      }
      return $result;
    }
  }

  function start_handler($parser, $name, $attributes = array()) {
    $token = array();
    $token['name'] = strtolower($name);
    $token['attributes'] = $attributes;
    $token['data'] = '';
    $token['children'] = array();
    $this->stack[] = $token;
  }

  function end_handler($parser, $name, $attributes = array()) {
    $token = array_pop($this->stack);
    $this->stack[count($this->stack) - 1]['children'][] = $token;
  }

  function data_handler($parser, $data) {
    $this->stack[count($this->stack) - 1]['data'] .= $data;
  }

}

/**
 * Callback for actions.
 */
function node_export_xml_action_form($context, &$form_state) {
  return node_export_action_form($context, $form_state, 'xml');
}