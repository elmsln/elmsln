<?php

/**
 * @file
 * Contains CER hook implementations.
 */

/**
 * Implements hook_cer_fields().
 */
function cer_cer_fields() {
  $fields = array();

  if (module_exists('taxonomy')) {
    $fields = array_merge($fields, _cer_collect_fields_of_type('taxonomy_term_reference', 'CerTaxonomyTermReferenceField'));
  }
  if (module_exists('entityreference')) {
    $fields = array_merge($fields, _cer_collect_fields_of_type('entityreference', 'CerEntityReferenceField'));
  }
  if (module_exists('node_reference')) {
    $fields = array_merge($fields, _cer_collect_fields_of_type('node_reference', 'CerNodeReferenceField'));
  }
  if (module_exists('user_reference')) {
    $fields = array_merge($fields, _cer_collect_fields_of_type('user_reference', 'CerUserReferenceField'));
  }
  if (module_exists('field_collection')) {
    $fields = array_merge($fields, _cer_collect_fields_of_type('field_collection', 'CerFieldCollectionField'));
  }

  return $fields;
}

/**
 * Implmements hook_cer_fields_alter().
 */
function cer_cer_fields_alter(array &$fields) {
  foreach (array_keys($fields) as $identifier) {
    list ($entity_type, $bundle, $field) = explode(':', $identifier);

    if ($entity_type == 'field_collection_item') {
      $result = db_query("SELECT entity_type, bundle, field_name FROM {field_config_instance} WHERE field_name = :field_collection", array(':field_collection' => $bundle));

      foreach ($result as $r) {
        $fields[$identifier]['parents'][] = "{$r->entity_type}:{$r->bundle}:{$r->field_name}";
      }

      $fields[$identifier]['require parent'] = TRUE;
    }
  }
}

function _cer_collect_fields_of_type($field_type, $class) {
  $fields = array();

  $result = db_query("SELECT fci.entity_type, fci.bundle, fci.field_name FROM {field_config_instance} fci INNER JOIN {field_config} fc ON fc.id = fci.field_id WHERE fc.type = :type AND fc.deleted = 0 AND fci.deleted = 0", array(':type' => $field_type));
  foreach ($result as $r) {
    $fields["{$r->entity_type}:{$r->bundle}:{$r->field_name}"]['class'] = $class;
  }

  return $fields;
}
