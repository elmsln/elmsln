<?php

/**
 * @file
 * Hooks provided by the UUID module.
 */

/**
 * Ensures all records have a UUID assigned to them.
 *
 * When called this hook should ensure all records it is responsible for
 * have a UUID and if not create one.
 *
 * @see entity_uuid_sync()
 */
function hook_uuid_sync() {
  // Do what you need to do to generate missing UUIDs for you implementation.
}

/**
 * Transform entity properties from local IDs to UUIDs when they are loaded.
 */
function hook_entity_uuid_load(&$entities, $entity_type) {

}

/**
 * Transform field values from local IDs to UUIDs when an entity is loaded.
 */
function hook_field_uuid_load($entity_type, $entity, $field, $instance, $langcode, &$items) {

}

/**
 * Transform entity properties from UUIDs to local IDs before entity is saved.
 */
function hook_entity_uuid_presave(&$entity, $entity_type) {

}

/**
 * Transform field values from UUIDs to local IDs before an entity is saved.
 */
function hook_field_uuid_presave($entity_type, $entity, $field, $instance, $langcode, &$items) {

}

/**
 * Transform entity properties after an entity is saved.
 */
function hook_entity_uuid_save($entity, $entity_type) {

}

/**
 * Let modules act when an entity is deleted.
 *
 * Generally hook_entity_delete() should be used instead of this hook.
 *
 * @see hook_entity_delete()
 */
function hook_entity_uuid_delete($entity, $entity_type) {

}

/**
 * Modifies paths when they are being converted to UUID ones.
 */
function hook_uuid_menu_path_to_uri_alter($path, &$uri) {

}

/**
 * Modifies paths when they are being converted from UUID ones.
 */
function hook_uuid_menu_uri_to_path(&$path, $uri) {

}

/**
 * Allow modules to provide a list of default entities that will be imported.
 */
function hook_uuid_default_entities() {

}

/**
 * Let other modules do things before default entities are created on rebuild.
 */
function hook_uuid_entities_pre_rebuild($plan_name) {

}

/**
 * Let other modules do things after default entities are created on rebuild.
 */
function hook_uuid_entities_post_rebuild($plan_name) {

}

/**
 * Let other modules do things before default entities are created on revert.
 */
function hook_uuid_entities_pre_revert($plan_name) {

}

/**
 * Let other modules do things after default entities are created on revert.
 */
function hook_uuid_entities_post_revert($plan_name) {

}

/**
 * Let other modules alter entities that are about to be exported.
 */
function hook_uuid_entities_features_export_entity_alter(&$entity, $entity_type) {

}

/**
 * Let other modules alter fields on entities that are about to be exported.
 */
function hook_uuid_entities_features_export_field_alter($entity_type, &$entity, $field, $instance, $langcode, &$items) {

}

/**
 * Alter UUID URI data after processing.
 */
function hook_uuid_uri_data($data) {
}

/**
 * Alter entity URI before creating UUID URI.
 */
function hook_uuid_id_uri_data($data) {
}
