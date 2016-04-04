<?php

/**
 * @file
 * Contains entity property callback functions for the 'cer' struct exposed
 * to Entity API on field collections.
 *
 * @see cer_entity_property_info_alter().
 */

/**
 * Gets a field collection's lineage as a string, e.g.
 * node:page:field_my_collection::field_collection_item:field_my_collection:%
 */
function cer_get_field_collection_lineage(array $data, array $options, $property, $data_type, array $info) {
  return implode('::', $info['raw getter callback']($data, $options, $property, $data_type, $info));
}

/**
 * Gets a field collection's lineage as an array.
 */
function cer_get_field_collection_lineage_array(array $data, array $options, $property, $data_type, array $info) {
  $collection = $data[1];

  // If this is the innermost entity, $options['lineage'] will be empty.
  if (! isset($options['lineage'])) {
    $options['lineage'][] = "field_collection_item:{$collection->field_name}:";
  }

  $data[0] = $collection->hostEntityType();
  $data[1] = $collection->hostEntity();
  list (, , $host_bundle) = entity_extract_IDs($data[0], $data[1]);
  array_unshift($options['lineage'], $data[0] . ":{$host_bundle}:{$collection->field_name}");

  // If this field collection is hosted in another field collection, recurse
  // upward. Otherwise, we're done; return the lineage array.
  if ($data[0] == 'field_collection_item') {
    return cer_get_field_collection_lineage_array($data, $options, $property, $data_type, $info);
  }
  else {
    return $options['lineage'];
  }
}

/**
 * Gets the zero-based depth of a field collection.
 */
function cer_get_field_collection_depth(array $data, array $options, $property, $data_type, array $info) {
  $lineage = cer_get_field_collection_lineage_array($data, $options, $property, $data_type, $info);
  return (sizeof($lineage) - 1);
}

/**
 * Gets the ultimate owner of a field collection -- that is, the top-level entity
 * under which it's embedded. This could be any kind of entity that's not a field
 * collection item.
 */
function cer_get_field_collection_owner(array $data, array $options, $property, $data_type, array $info) {
  // If the entity is a field collection item, recurse upward. Otherwise,
  // return the wrapped entity.
  if ($data[0] == 'field_collection_item') {
    $data[0] = $data[1]->hostEntityType();
    $data[1] = $data[1]->hostEntity();
    
    $self = __FUNCTION__;
    return $self($data, $options, $property, $data_type, $info);
  }
  else {
    return new EntityDrupalWrapper($data[0], $data[1]);
  }
}
