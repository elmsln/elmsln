<?php

/**
 * @file
 * API documentation for the At.js module.
 */

/**
 * Alter the Entity Field Query used in the AJAX callback.
 *
 * @param object $query
 *   An EntityFieldQuery object.
 * @param array $context
 *   An array containing the listener object.
 *
 * @see atjs_ajax_callback()
 */
function hook_atjs_ajax_query_alter($query, $context) {
}

/**
 * Alter the results returned by the Entity Field query that
 * will be passed back to the autocomplete. Use this hook to
 * alter and provide extra variables to the template.
 *
 * @param array $results
 *   Results that will be pass
 * @param array $context
 *   An array containing the listener object.
 *
 * @see atjs_ajax_callback()
 */
function hook_atjs_ajax_results_alter($results, $context) {
}

/**
 * Alter the load function and or arguments to pass to the load
 * function when loading an entity after the filter has matched
 * some text. This hook is useful to allow entities to be loaded
 * by something other than the entity id, e.g. load user by mail
 * or username.
 *
 * @param array $context
 *   An array containing the listener object.
 *
 * @see _atjs_filter_match_load_entity()
 */
function hook_atjs_filter_match_load_entity_alter($load_function, $load_arguments, $context) {
}

/**
 * Text has been found, and an entity loaded, this hook occurs
 * before being passed to theme_atjs_link().
 *
 * @param object $listener
 *   The listener object involved with the replacement, this will
 *   tell you useful things like the type of entity that's been
 *   loaded. $listener->entity_type (target entity type).
 * @param object $entity
 *   The loaded entity.
 */
function hook_atjs_entity_replaced($listener, $entity) {
}

/**
 * New mentions have been detected, respond to them!
 *
 * @param object $listener
 * @param string $entity_type
 *   The source entity type.
 * @param object $entity
 *   The source entity, as in the entity from where the mention
 *   is coming from.
 * @param string $mentioned_entity_type
 *   The type of entities being mentioned from the source entity.
 * @param array $new_mentions
 *   An array of entity id's that are new mentions.
 *
 * @see atjs_field_attach_check_usage()
 */
function hook_atjs_new_entity_mentions($listener, $entity_type, $entity, $mentioned_entity_type, $new_mentions) {
}

/**
 * Mentions have been removed.
 *
 * @param object $listener
 * @param string $entity_type
 *   The source entity type.
 * @param object $entity
 *   The source entity, as in the entity from where the mention
 *   is coming from.
 * @param string $removed_entity_type
 *   The type of entities being removed from the source entity.
 * @param array $removed_mentions
 *   An array of entity id's that are have been removed.
 *
 * @see atjs_field_attach_check_usage()
 */
function hook_atjs_new_entity_mentions_removed($listener, $entity_type, $entity, $removed_entity_type, $removed_mentions) {
}
