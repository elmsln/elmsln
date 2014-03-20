<?php

/**
 * @file
 * The Node export relation node reference include.
 *
 * Helps maintain node reference relationships between nodes during node export operations.
 */

/**
 * Implements hook_form_FORM_ID_alter().
 */
function node_export_relation_settings_form_node_reference(&$form, &$form_state, $form_id) {
  $form['node_reference'] = array(
    '#type' => 'fieldset',
    '#title' => t('Node references'),
  );

  // Not supported yet.
  $form['node_reference']['node_export_node_reference_auto_inc'] = array(
    '#type' => 'checkbox',
    '#title' => t('Automatically include referenced nodes in exports'),
    '#default' => variable_get('node_export_node_reference_auto_inc', TRUE),
  );

  $form['node_reference']['node_export_node_reference_skip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip referenced nodes that cannot be exported'),
    '#default' => variable_get('node_export_node_reference_skip', TRUE),
    '#description' => t('If this is disabled, node exports will fail if a referenced node cannot be exported, for example if the user performing the export does not have access.'),
  );
}

/**
 * Update node references after import.
 */
function node_export_relation_node_reference_update($nodes) {
  foreach ($nodes as $node) {
    $uuid[$node->uuid] = $node->nid;
  }
  foreach ($nodes as $node) {
    $node_reference_fields = node_export_relation_node_reference_fields($node->type);
    if (!empty($node_reference_fields)) {
      foreach ($node_reference_fields as $node_reference_field) {
        $items = field_get_items('node', $node, $node_reference_field);
        $langcode = field_language('node', $node, $node_reference_field);
        if (!empty($items)) {
          foreach ($items as $key => &$node_reference) {
            if (!empty($node_reference['nid'])) {
              $node_uuid = node_export_relation_node_reference_map($node_reference['nid']);
              $node->{$node_reference_field}[$langcode][$key] = array('nid' => $uuid[$node_uuid]);
            }
          }
        }
      }
    }
    node_save($node);
  }
}

/**
 * Recursively load node references.
 */
function node_export_relation_node_reference_load(&$nodes, $nid) {
  // Alias for easy referencing.
  $node = &$nodes[$nid];

  // Get list of node reference fields for this node
  $node_reference_fields = node_export_relation_node_reference_fields($node->type);
  if (!empty($node_reference_fields)) {
    foreach ($node_reference_fields as $node_reference_field) {
      $items = field_get_items('node', $node, $node_reference_field);
      if (!empty($items)) {
        foreach ($items as &$node_reference) {
          if (!empty($node_reference['nid'])) {
            // Load the referenced nodes only if its not already loaded
            // This will save if from infinite loop of back references
            if (!isset($nodes[$node_reference['nid']])) {
              $new_node = node_load($node_reference['nid']);
              if (node_export_access_export($new_node)) {
                $new_node = node_export_prepare_node($new_node);
                $nodes[$new_node->nid] = $new_node;
                // Recursively load references of new nodes
                node_export_relation_node_reference_load($nodes, $new_node->nid);
              }
              elseif (!variable_get('node_export_node_reference_skip', TRUE)) {
                // Set this node to FALSE to trigger an error in node export.
                // Do not use $new_node in this code in case there is a problem with it.
                $nodes[$node_reference['nid']] = FALSE;
                // Add a warning to watchdog.
                watchdog('node_export_relation', 'No access to export node reference %nid', array('%nid' => $node_reference['nid']), WATCHDOG_WARNING);
              }
            }
          }
        }
      }
    }
  }
}

/**
 * Statically cache old node ids for mapping.
 */
function node_export_relation_node_reference_map($id, $uuid = NULL, $type = 'node') {
  static $map;
  if (isset($uuid)) {
    $map[$type][$id] = $uuid;
  }
  else {
    return $map[$type][$id];
  }
}

/**
 * Get an array listing the names of all node reference fields.
 *
 * @return
 *   Array of all created node reference fields.
 */
function node_export_relation_node_reference_fields($content_type_name) {
  // cache result
  static $node_reference_fields = array();

  if (empty($node_reference_fields[$content_type_name])) {
    $fields = field_info_instances('node', $content_type_name);
    if (!empty($fields)) {
      foreach ($fields as $field) {

        if (isset($field['widget']['module']) && $field['widget']['module'] == 'node_reference' && !empty($field['field_name'])) {
          $node_reference_fields[$content_type_name][$field['field_name']] = $field['field_name'];
        }

      }
    }
  }

  if (array_key_exists($content_type_name, $node_reference_fields)) {
    return $node_reference_fields[$content_type_name];
  }
  else {
    return NULL;
  }
}
