<?php

/**
 * @file
 * Contains Entity API property information.
 */

/**
 * Implements hook_entity_property_info_alter().
 *
 * We add properties thus:
 *  - global flags:
 *    - entity->flag_FLAGNAME, boolean.
 *  - per-user flags:
 *    - entity->flag_FLAGNAME_users, list of users.
 *    - user->flag_FLAGNAME_flagged, list of user's flagged entities.
 */
function flag_entity_property_info_alter(&$info) {
  foreach (flag_get_flags() as $flag) {
    if ($flag->global) {
      // Global flags.
      // Boolean property on entity type.
      // This can go on either the entity as a whole, or on bundles, depending
      // on whether the flag is limited by bundle.
      $property_definition = array(
        'label' => t('Whether the entity is flagged with flag @flag', array(
          '@flag' => $flag->name,
        )),
        'description' => t('Whether the entity is flagged with flag @flag.', array(
          '@flag' => $flag->name,
        )),
        'type' => 'boolean',
        'getter callback' => 'flag_properties_get_flagging_boolean',
        'computed' => TRUE,
        'flag_name' => $flag->name,
      );
      if (count($flag->types)) {
        // Bundle specific property.
        foreach ($flag->types as $type) {
          $info[$flag->entity_type]['bundles'][$type]['properties']['flag_' . $flag->name] = $property_definition;
        }
      }
      else {
        // Generic property, applies for all bundles.
        $info[$flag->entity_type]['properties']['flag_' . $flag->name] = $property_definition;
      }
    }
    else {
      // Per-user flags.
      // User property: list of flagged entities by the user.
      $info['user']['properties']['flag_' . $flag->name . '_flagged'] = array(
        'label' => t('Flagged @entity-type with flag @flag', array(
          '@entity-type' => $flag->entity_type,
          '@flag' => $flag->name,
        )),
        'description' => t('Returns a list of entities a user flagged with flag @flag.', array(
          '@flag' => $flag->name,
        )),
        'type' => 'list<' . $flag->entity_type . '>',
        'getter callback' => 'flag_properties_get_flagged_entities',
        'computed' => TRUE,
        'flag_name' => $flag->name,
        'flag_entity_type' => $flag->entity_type,
      );
      $info['user']['properties']['flag_sid'] = array(
        'label' => t('Flag user session identifier'),
        'description' => t('Returns the sessions id used to distinguish anonymous users from each other.'),
        'type' => 'text',
        'getter callback' => 'flag_properties_get_user_sid',
        'computed' => TRUE,
      );
      // Entity property: list of users who have flagged this entity.
      // This can go on either the entity as a whole, or on bundles, depending
      // on whether the flag is limited by bundle.
      $property_definition = array(
        'label' => t('Users who flagged the entity with flag @flag', array(
          '@flag' => $flag->name,
        )),
        'description' => t('Returns a list of users who flagged an entity with flag @flag.', array(
          '@flag' => $flag->name,
        )),
        'type' => 'list<user>',
        'getter callback' => 'flag_properties_get_flagging_users',
        'computed' => TRUE,
        'flag_name' => $flag->name,
      );
      if (count($flag->types)) {
        // Bundle specific property.
        foreach ($flag->types as $type) {
          $info[$flag->entity_type]['bundles'][$type]['properties']['flag_' . $flag->name . '_user'] = $property_definition;
        }
      }
      else {
        // Generic property, applies for all bundles.
        $info[$flag->entity_type]['properties']['flag_' . $flag->name . '_user'] = $property_definition;
      }
    }
  }
}
