<?php

/**
 * @file
 * Drush integration for HTTPRL.
 *
 * This approach is based on drush_ecl to allow for bulk
 * loading of entities into drupal's object cache.
 * This builds on that by caching the objects, then
 * requesting the url via a httpl_ batch object loading.
 * This works best when run right after boost cache is cleared
 * so that the entire site is rebuilt in boost.
 */

/**
 * Implements hook_drush_command().
 */
function httprl_spider_drush_command() {
  $items = array();
  $items['httprl-self-request'] = array(
    'description' => dt('Perform a self request from command-line'),
    'arguments' => array(
      'path' => dt("Path to request"),
    ),
    'options' => array(
      'nonblocking' => dt('Including this option will issue the call as non-blocking.'),
      'print' => dt('Print debug statements about requests being made.'),
    ),
    'aliases' => array('hsr'),
    'examples' => array(
      'drush httprl-self-request node' => 
        'Request own node path.',
      'drush hsr --nonblocking --print' => 
        'Request front page of site in a non-blocking manner and print response',
    ),
  );
  $items['httprl-self-spider'] = array(
    'description' => dt('Load all entities with web-based urls and hit them to prime the cache. Also allows for developer alters for non entity paths.'),
    'arguments' => array(
      'type' => dt('Optional. Only prime this particular entity type'),
    ),
    'options' => array(
      'nonblocking' => dt('Including this option will issue the call as non-blocking.'),
       'print' => dt('Print debug statements about requests being made.'),
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'aliases' => array('hss'),
    'examples' => array(
      'drush httprl-self-spider' => 
        'Self request all known, web-accessible entities at their URL',
      'drush hss node --nonblocking' => 
        'Request all nodes in a nonblocking manner to prime cache',
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function httprl_spider_drush_help($section) {
  switch ($section) {
    case 'drush:httprl-self-request':
      return dt('Perform a command-lind based http self request');
    case 'drush:httprl-self-spider':
      return dt('Spider all web-accessible entity paths');
  }
}

/**
 * Drush command callback for httprl-self-request.
 */
function drush_httprl_spider_httprl_self_request($path = '', $delay_request = FALSE) {
  $batch = batch_get();
  // set default options for 
   $options = array(
    'headers' => array(
      // Set the Host header to self.
      'Host' => $_SERVER['HTTP_HOST'],
    ),
  );
  // allow for non-blocking calls in batch jobs or directly
  if (isset($batch['httprl_nonblocking'])) {
    $options['blocking'] = FALSE;
  }
  if (drush_get_option('nonblocking')) {
    $options['blocking'] = FALSE;
  }
  // build path to request
  $url = httprl_build_url_self($path);
  // Queue up the request
  httprl_request($url, $options);
  // Execute requests unless told to delay processing
  if (!$delay_request) {
    $request = httprl_send_request();
    // Print request and return code if asked
    if (isset($batch['httprl_print']) || drush_get_option('print')) {
      foreach ($request as $id => $result) {
        drush_print($id . ' -- code: ' . $result->code);
      }
    }
  }
}

/**
 * Load the cache bin with content from the various entities.
 * @param $type Optional. The specific type of entity that should
 *   get it's content cached.
 */
function drush_httprl_spider_httprl_self_spider($type = '') {
  $info = entity_get_info();
  $start = time();
  if (!empty($type)) {
    // allow for type _none_ so only pages are primed
    if ($type == '_none_') {
      $info = array();
    }
    // only allow types that have a dedicated url in menu router
    else if (!isset($info[$type]) || !isset($info[$type]['uri callback'])) {
      drush_die("Type $type must have a uri callback / be available for calling.");
    }
    else {
      // only run for this one type
      $info = array($type => $info[$type]);
    }
  }
  else {
  // scan all entities that touch the web if asked
    foreach ($info as $etype => $einfo) {
      // ween out the types we can't handle via the web
      if (!isset($einfo['uri callback'])) {
        unset($info[$etype]);
      }
    }
  }
  // Lets try things in a batch.
  _httprl_spider_batch_load_cache($info);
  $batch =& batch_get();
  $batch['progressive'] = FALSE;
  $batch['httprl_nonblocking'] = drush_get_option('nonblocking');
  $batch['httprl_print'] = drush_get_option('print');
  drush_backend_batch_process();
}

function _httprl_spider_batch_load_cache($types) {
  $batch = array(
    'operations' => array(),
    'finished' => '_httprl_spider_batches_finished',
    'title' => dt('Loading items...'),
    'init_message' => dt('Preparing to hit content...'),
    'progress_message' => dt('Submitting content...'),
    'error_message' => dt('Content could not be spidered'),
  );
  
  foreach ($types as $entity_type => $entity_info) {
    $batch['operations'][] = array(
      'httprl_spider_batch_load_cache', array($entity_type, $entity_info),
    );
  }
  // add support for non entity paths loaded in via hooks from contrib
  $batch['operations'][] = array(
    'httprl_spider_batch_load_other_paths', array(),
  );
  batch_set($batch);
}

/**
 * Batch API entity caching completion message.
 */
function _httprl_spider_batches_finished($success, $results, $operations) {
  drush_print('Succesfully cached all objects and requested front facing addresses!');
}

/**
 * Processes and loads cacheable information for entities into cache tables.
 */
function httprl_spider_batch_load_cache($entity_type, $entity_info, &$context) {
  if (!isset($context['sandbox']['progress'])) {
    // Make some assumptions like entity ids must be a positive integer.
    $context['message'] = dt("Begin requesting $entity_type");
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_id'] = -1;
    $context['sandbox']['entity_count'] = _httprl_spider_get_entity_count($entity_type);
  }
  $context['message'] = dt("Requesting {$entity_type} {$context['sandbox']['progress']} of {$context['sandbox']['entity_count']}");
  _httprl_spider_load_cache($entity_type, $entity_info, $context);
}

/**
 * Returns total number of entities given a specific entity given.
 */
function _httprl_spider_get_entity_count($entity_type) {
  $query = new EntityFieldQuery();
  return $query
    ->entityCondition('entity_type', $entity_type)
    ->count()
    ->execute();
}

/**
 * Loads content from a specific type of entity.
 */
function _httprl_spider_load_cache($entity_type, $entity_info, &$context) {
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
  _httprl_spider_load_entities($entity_type, $keys);
  // Do a final count to cache any additional entities that may have been added
  // in the interim.
  if ($context['sandbox']['progress'] >= $context['sandbox']['entity_count']) {
    $context['sandbox']['entity_count'] = _httprl_spider_get_entity_count($entity_type);
  }
  $context['finished'] = min($context['sandbox']['progress'] / $context['sandbox']['entity_count'], 1.0);
}

/**
 * Processes and loads cacheable information for entities into cache tables.
 */
function httprl_spider_batch_load_other_paths(&$context) {
  if (!isset($context['sandbox']['progress'])) {
    // Make some assumptions like entity ids must be a positive integer.
    $context['message'] = dt("Begin requesting other paths");
    $context['sandbox']['progress'] = 0;
    $context['sandbox']['current_id'] = -1;
    $context['sandbox']['entity_count'] = count(_httprl_spider_get_other_paths());
  }
  $other = count(_httprl_spider_get_other_paths());
  $context['message'] = dt("Requesting $other other paths");
  _httprl_spider_load_other_paths($context);
}

/**
 * Load other paths defined by contrib.
 */
function _httprl_spider_get_other_paths() {
  $paths = array();
  // empty container will hit the front page
  $paths[] = '';
  // allow modifications so we don't make assumptions
  drupal_alter('httprl_spider_other_paths', $paths);
  return $paths;
}

/**
 * Loads content from a specific type of entity.
 */
function _httprl_spider_load_other_paths(&$context) {
  // load paths
  $paths = _httprl_spider_get_other_paths();
  foreach ($paths as $path) {
    drush_httprl_spider_httprl_self_request($path);
  }
  $context['finished'] = TRUE;
}

/**
 * Load entities provided there are keys.
 */
function _httprl_spider_load_entities($entity_type, $keys = array()) {
  $batch = batch_get();
  if (count($keys) > 0) {
    // this will effectively seend the db cache
    $entities = entity_load($entity_type, $keys);
    foreach ($entities as $entity) {
      // this will build the path to that entity
      $path = entity_uri($entity_type, $entity);
      // build request to path, delaying actually doing it
      drush_httprl_spider_httprl_self_request($path['path'], TRUE);
    }
    // execute the request
    $request = httprl_send_request();
    // Print request and return code if asked
    if (isset($batch['httprl_print'])) {
      foreach ($request as $id => $result) {
        drush_print($id . ' -- code: ' . $result->code);
      }
    }
  }
}