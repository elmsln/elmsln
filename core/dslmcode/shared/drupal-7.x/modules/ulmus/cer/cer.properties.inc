<?php

/**
 * @file
 * Contains entity property callback functions for the 'cer' struct exposed
 * to Entity API.
 */

/**
 * Unpacks the cer_left and cer_right values into a CerFieldChain object.
 */
function cer_unpack_field_chain($data, array $options, $property, $entity_type, array $info) {
  return CerFieldChain::unpack($data);
}

/**
 * Creates a parent struct for the lineage, depth, owner, and original properties.
 * All that these other callbacks really need is the entity type and object, so
 * that's what this returns.
 */ 
function cer_get_cer_struct($entity, array $options, $property, $entity_type, array $info) {
  return array( $entity_type, $entity );
}

/**
 * Gets the lineage of the entity as a string, in the format entity_type:bundle:%
 */
function cer_get_entity_lineage(array $data, array $options, $property, $data_type, array $info) {
  list (, , $bundle) = entity_extract_IDs($data[0], $data[1]);
  return $data[0] . ":{$bundle}:";
}

/**
 * Gets the entity depth as an integer. cer_entity_property_info_alter() overrides this
 * callback for field collections, and for all other entity types it's 0 (top level).
 */
function cer_get_entity_depth(array $data, array $options, $property, $data_type, array $info) {
  return 0;
}

/**
 * Gets the ultimate owner of the entity as an EntityDrupalWrapper. cer_entity_property_info_alter()
 * overrides this callback for field collections, and for all other entity types the entity
 * owns itself.
 */
function cer_get_entity_owner(array $data, array $options, $property, $data_type, array $info) {
  return new EntityDrupalWrapper($data[0], $data[1]);
}

/**
 * Gets the original entity, before update. If no update has taken place, the current
 * entity is returned.
 */
function cer_get_entity_original(array $data, array $options, $property, $data_type, array $info) {
  return new EntityDrupalWrapper($data[0], (isset($data[1]->original) ? $data[1]->original : $data[1]));
}
