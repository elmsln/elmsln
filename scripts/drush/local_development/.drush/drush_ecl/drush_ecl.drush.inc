<?php

/**
 * @file drush_ecl.drush.inc
 *   drush integration for caching entity content.
 *   Simple idea - load each of the entities.
 */

/**
 * Implementation of hook_drush_help().
 */
function drush_ecl_drush_help($section) {
  switch ($section) {
    case 'drush:entitycache-load':
      return dt('Used without parameters, this command loads all the various content in the entities into cache using entity_load()');
  }
}

/**
 * Implementation of hook_drush_command().
 */
function drush_ecl_drush_command() {
  $items = array();
  $items['entitycache-load'] = array(
    'callback' => 'drush_ecl_load_cache',
    'description' => dt('Load the cache with the various entities configured to use the cache'),
    'arguments' => array(
      'type' => dt('Optional. Only load the particular entity type objects into cache'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('ecl'),
  );
  
  return $items;
}

/**
 * Load the cache bin with content from the various entities.
 * @param $type Optional. The specific type of entity that should
 *   get it's content cached.
 */
function drush_ecl_load_cache($type = '') {
  $types = entity_get_info();
  $start = time();
  if (!empty($type)) {
    if (!isset($types[$type])) {
      drush_die("Type $type is not supported");
    }
    else {
      $types = array($type => $types[$type]);
    }
  }
  
  // Lets try things in a batch.
  _drush_ecl_batch_load_cache($types);
  $batch =& batch_get();
  $batch['progressive'] = FALSE;
  drush_backend_batch_process();
}

function _drush_ecl_batch_load_cache($types) {
  if (count($types) == 0) {
    return;
  }

  $batch = array(
    'operations' => array(),
    'finished' => '_drush_ecl_batches_finished',
    'title' => dt('Loading cache...'),
    'init_message' => dt('Preparing to cache content...'),
    'progress_message' => dt('Submitting content...'),
    'error_message' => dt('Content could not get cached'),
  );
  
  foreach ($types as $entity_type => $entity_info) {
    $batch['operations'][] = array(
      'drush_ecl_batch_load_cache', array($entity_type, $entity_info),
    );
  }
  batch_set($batch);
}

/**
 * Batch API entity caching completion message.
 */
function _drush_ecl_batches_finished($success, $results, $operations) {
  drush_print('Succesfully cached all content!');
}

/**
 * Processes and loads cacheable information for entities into cache tables.
 */
function drush_ecl_batch_load_cache($entity_type, $entity_info, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    // Make some assumptions like entity ids must be a positive integer.
    $context['message'] = dt("Begin caching $entity_type");
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_id'] = -1;
    $context['sandbox']['entity_count'] = _drush_ecl_get_entity_count($entity_type);
  }
  $context['message'] = dt("Caching {$entity_type} {$context['sandbox']['progress']} of {$context['sandbox']['entity_count']}");
  _drush_ecl_load_cache($entity_type, $entity_info, $context);
}

/**
 * Returns total number of entities given a specific entity given.
 */
function _drush_ecl_get_entity_count($entity_type) {
  $query = new EntityFieldQuery();
  return $query
    ->entityCondition('entity_type', $entity_type)
    ->count()
    ->execute();
}

/**
 * Loads cache bin with content from a specific type of entity.
 */
function _drush_ecl_load_cache($entity_type, $entity_info, &$context) {
  $max_limit = 50;
  $query = new EntityFieldQuery;
  $result = $query
    ->entityCondition('entity_type', $entity_type)
    ->entityCondition('entity_id', $context['sandbox']['current_id'], '>')
    ->entityOrderBy('entity_id', 'ASC')
    ->range(0, $max_limit)
    ->execute();
    
  $keys = array();
  $limit = 0;
  if (count($result) <= 0) {
    $context['finished'] = TRUE;
    return;
  }
  foreach ($result[$entity_type] as $entity_key => $entity_info) {
    $keys[] = $entity_key;
    $context['sandbox']['progress']++;
    $context['sandbox']['current_id'] = $entity_key;
  }
  _drush_ecl_load_entities($entity_type, $keys);
  // Do a final count to cache any additional entities that may have been added
  // in the interim.
  if ($context['sandbox']['progress'] >= $context['sandbox']['entity_count']) {
    $context['sandbox']['entity_count'] = _drush_ecl_get_entity_count($entity_type);
  }
  $context['finished'] = min($context['sandbox']['progress'] / $context['sandbox']['entity_count'], 1.0);
}

/**
 * Load entities provided there are keys.
 */
function _drush_ecl_load_entities($entity_type, $keys = array()) {
  if (count($keys) > 0) {
    entity_load($entity_type, $keys);
  }
}
