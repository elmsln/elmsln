<?php

/**
 * @file
 * The Node export tokens file.
 *
 * Token group file.
 */

 /**
 * Implements hook_tokens().
 */
function node_export_tokens($type, $tokens, $data = array(), $options = array()) {
  $replacements = array();
  if ($type == 'node_export_filename' && !empty($data['node_export_filename'])) {
    $object = (array)$data['node_export_filename'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        // Simple key values on the node.
        case 'nid-list':
          $replacements[$original] = $object['nid-list'];
          break;

        case 'node-count':
          $replacements[$original] = $object['node-count'];
          break;

        case 'timestamp':
          $replacements[$original] = $object['timestamp'];
          break;

        case 'format':
          $replacements[$original] = $object['format'];
          break;
      }
    }
  }
  return $replacements;
}

/**
 * Implements hook_token_info().
 */
function node_export_token_info() {
  return array(
    'types' => array(
      'node_export_filename' => array(
        'name' => t('Node export filename'),
        'description' => t('Tokens related to the Node export filename.'),
        'needs-data' => 'node_export_filename',
      ),
    ),
    'tokens' => array(
      'node_export_filename' => array(
        'nid-list' => array(
          'name' => t("Node ID list"),
          'description' => t("Comma seperated list of Node IDs in square brackets (if available)."),
        ),
        'node-count' => array(
          'name' => t("Node count"),
          'description' => t("The number of nodes exported."),
        ),
        'timestamp' => array(
          'name' => t("Timestamp"),
          'description' => t("The timestamp when the file was generated."),
        ),
        'format' => array(
          'name' => t("Format"),
          'description' => t("The format used to export."),
        ),
      ),
    ),
  );
}