<?php

/**
 * @file
 * Replicate entities via drush framework.
 */

/**
 * Implements hook_drush_command().
 */
function replicate_drush_command() {
  $items = array();

  $items['replicate-drush-entity-by-ids'] = array(
    'description' => 'Replicate an entity',
    'arguments' => array(
      'entity-type' => dt('Type of entity (eg. Node, Comment, ...) that you wish to replicate.'),
      'entity-ids' => dt('A comma delimited list of entity IDs which should be replicated (eg. NodeID, TermID, ...).'),
    ),
    'required-arguments' => 1,
    'aliases' => array('rep', 'replicate'),
    'examples' => array(
      'drush replicate-drush-entity-by-ids node 1' =>
        'Replicate node 1 using full command.',
      'drush replicate node 1,2,3' =>
        'Replicate nodes 1,2 and 3 using aliased command.',
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function replicate_drush_help($command) {
  switch ($command) {
    case 'drush:replicate-drush-entity-by-id':
      return dt('Replicate an entity by providing an entity type and id.');
  }
}

/**
 * Command callback to replicate entities.
 */
function drush_replicate_drush_entity_by_ids($entity_type = NULL, $ids = NULL) {
  $original_ids = explode(',', $ids);

  foreach ($original_ids as $original_id) {
    $entity_id = replicate_entity_by_id($entity_type, $original_id);
    if (!empty($entity_id)) {
      drush_log(dt('@entity_type @entity_id is clone of @entity_type @original_id', array('@entity_type' => $entity_type, '@entity_id' => $entity_id, '@original_id' => (int)$original_id)), 'success');
    }
    else {
      drush_log(dt('Impossible to replicate @entity_type @original_id', array('@entity_type' => $entity_type, '@original_id' => check_plain($original_id))), 'error');
    }
  }
}
