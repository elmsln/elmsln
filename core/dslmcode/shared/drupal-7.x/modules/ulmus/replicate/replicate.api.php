<?php

/**
 * @file
 * API documentation for the Replicate module.
 */

/**
 * Alter the replica of type ENTITY_TYPE.
 *
 * Use this function to make specific changes to an entity of a given type.
 *
 * @param object $replica
 *   Reference to the fully loaded entity object being saved (the clone) that
 *   can be altered as needed.
 *
 * @see replicate_clone_entity()
 */
function hook_replicate_entity_ENTITY_TYPE(&$replica) {
  // Do something specific to this type of entity.
  $wrapper = entity_metadata_wrapper('ENTITY_TYPE', $replica);
  $wrapper->field_my_field->set('This is a replica of a ENTITY_TYPE');
}

/**
 * Alter the replica before returning it (and before entity is saved).
 *
 * This hook is called at the end of the operations
 * of replicate_clone_entity() function, allowing to alter the replicate
 * before it is returned to the caller. This function will apply to all
 * replicated entities.
 *
 * @param object $replica
 *   Reference to the fully loaded entity object being saved (the clone) that
 *   can be altered as needed.
 * @param string $entity_type
 *   Type of the entity containing the field.
 * @param object $original
 *   The fully loaded original entity object.
 *
 * @see replicate_clone_entity()
 * @see drupal_alter()
 */
function hook_replicate_entity_alter(&$replica, $entity_type, $original) {
  // Do something common to all entities that are replicated.
  $wrapper = entity_metadata_wrapper($entity_type, $replica);
  $wrapper->field_is_replica->set(TRUE);

}

/**
 * Alter the replica right after it has been saved.
 *
 * This hook is called at the end of the operations
 * of replicate_entity() (and so replicate_entity_by_id) function, allowing to
 * alter the replicate before it is returned to the caller. This function will
 * not apply to replication directly using replicate_clone_entity and
 * replicate_clone_entity_by_id as these functions don't save entities.
 *
 * This hook is meant to be used to trigger other actions, not modifying the
 * replicated entity. For that use hook_replicate_entity_alter().
 *
 * @param object $replica
 *   Reference to the fully loaded entity object being saved (the clone) that
 *   can be altered as needed.
 * @param string $entity_type
 *   Type of the entity containing the field.
 * @param object $original
 *   The fully loaded original entity object.
 *
 * @see replicate_clone_entity()
 * @see drupal_alter()
 */
function hook_replicate_entity_after_save($replica, $entity_type, $original) {
  // Do something common to all entities that are replicated.
  $wrapper = entity_metadata_wrapper($entity_type, $replica);
  $wrapper->field_is_replica->set(TRUE);
}

/**
 * Manage the replication of a specific field type.
 *
 * May be used to manage the replication of custom field type,
 * for example node references.
 *
 * @param object $replica
 *   Reference to the fully loaded entity object being saved (the clone) that
 *   can be altered as needed.
 * @param string $entity_type
 *   Type of the entity containing the field.
 * @param string $field_name
 *   Name of the field that is going to be processed.
 *
 * @see replicate_clone_entity()
 */
function hook_replicate_field_FIELD_TYPE(&$replica, $entity_type, $field_name) {
  // Simplified example from Replicate Field Collection module.
  // Manage the replication of a Field Collection field with a custom function.
  foreach ($replica->$field_name as $language => $values) {
    my_custom_function_to_clone_field_collections($replica, $entity_type, $field_name, $language);
  }
}
