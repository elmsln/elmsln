<?php

/**
 * @file
 * The Node export Drupal format handler.
 *
 * Adds Drupal var export format to Node export.
 */

/**
 * Export callback.
 */
function node_export_drupal_export($nodes, $format) {
  require_once DRUPAL_ROOT . '/includes/utility.inc';
  return drupal_var_export($nodes);
}

/**
 * Import callback.
 */
function node_export_drupal_import($code_string) {
  if (substr(ltrim($code_string), 0, 6) == "array(") {
    $nodes = eval('return ' . $code_string . ';');
    if (is_array($nodes)) {
      return node_export_drupal_decode_objects($nodes);
    }
  }
}

/**
 * Recursively convert arrays back to objects.
 *
 * This is only for backwards compatibility with the deprecated node_code format.
 */
function node_export_drupal_decode_objects($array) {
  foreach ($array as $k => $v) {
    if (is_array($v)) {
      $array[$k] = node_export_drupal_decode_objects($v);
    }
  }
  if (isset($array['#_export_node_encode_object'])) {
    unset($array['#_export_node_encode_object']);
    $array = (object)$array;
  }
  return $array;
}

/**
 * Callback for actions.
 */
function node_export_drupal_action_form($context, &$form_state) {
  return node_export_action_form($context, $form_state, 'drupal');
}
