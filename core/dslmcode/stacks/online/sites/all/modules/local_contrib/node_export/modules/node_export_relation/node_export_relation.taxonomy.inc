<?php

/**
 * @file
 * The Node export relation OG include.
 *
 * Helps maintain organic groups relationships between nodes during node export operations.
 */

/**
 * Add taxonomy term reference UUID.
 */
function node_export_relation_taxonomy_build_term_reference($node) {
  $reference_fields = node_export_relation_taxonomy_term_reference_fields($node);
  // Iterate through the class properties
  foreach ($reference_fields as $field => $val) {
    // There may be multiple languages
    foreach ($val as $lang => $values) {
      // Multi-value fields
      foreach ($values as $pos => $value) {
        $term = taxonomy_term_load($value['tid']);
        $new_field = $node->$field;
        $new_field[$lang][$pos]['uuid'] = $term->uuid;
        $node->$field = $new_field;
      }
    }
  }
}

/**
 * Restore the tid based on the term UUID.
 */
function node_export_relation_taxonomy_restore_term_reference($node) {
  $reference_fields = node_export_relation_taxonomy_term_reference_fields($node);
  // Iterate through the class properties
  foreach ($reference_fields as $field => $val) {
    // There may be multiple languages
    foreach ($val as $lang => $values) {
      // Multi-value fields
      foreach ($values as $pos => $value) {
        if (isset($value['uuid'])) {
          // @TODO load_by_uuid
          $tid = db_select('taxonomy_term_data', 'ttd')
            ->fields('ttd', array('tid'))
            ->condition('ttd.uuid', $value['uuid'])
            ->execute()
            ->fetchField();
          if ($tid) {
            $new_field[$lang][$pos]['tid'] = $tid;
            $node->$field = $new_field;
          }
        }
      }
    }
  }
}

/**
 * Get the term reference fields for a node.
 */
function node_export_relation_taxonomy_term_reference_fields($node) {
  $reference_fields = array();
  $instances = field_info_instances('node', $node->type);
  if (!empty($instances)) {
    foreach ($instances as $instance) {
      $field = field_info_field($instance['field_name']);
      if (isset($field['type']) && $field['type'] == 'taxonomy_term_reference') {
        $field_name = $instance['field_name'];
        $reference_fields[$field_name] = $node->$field_name;
      }
    }
  }
  return $reference_fields;
}