<?php

/**
 * Get a list of nodes linked to the passed node via node_reference.
 *
 * @param $node
 *  node object
 *
 * @return $paths
 *   an array of node paths
 */
function expire_get_node_references($node) {
  $paths = array();
  $fields = field_info_instances('node', $node->type);
  $field_types = field_info_fields();
  // Loop over the fields of this node. If the field is a node_reference field, add any referenced nodes to $paths
  foreach ($fields as $field) {
    if ($field_types[$field['field_name']]['type'] == 'node_reference') {
      $node_field = isset($node->$field['field_name']) && !empty($node->$field['field_name']) ? $node->$field['field_name'] : array();
      if (!empty($node_field)) {
        foreach($node_field[$node->language] as $reference) {
          $paths['reference' . $reference['nid']] = 'node/'. $reference['nid'];
        }
      }
    }
  }
  return $paths;
}
