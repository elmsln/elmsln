<?php

/**
 * @file
 * This is the drush integration for the expire module.
 */

/**
 * Implements hook_drush_command().
 */
function expire_drush_command() {

  // Expire absolute URLs.
  $items['expire-url'] = array(
    'description' => 'Expire fully qualified URLs.',
    'arguments' => array(
      'urls' => 'URLs to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-url http://example.com/testpage.html' => 'Expire a single URL.',
      'drush xp-url http://example.com/ http://test.com/logo.jpg' => 'Expire multiple URLs.',
    ),
    'aliases' => array('xp-url'),
    'drupal dependencies' => array('expire'),
    'callback' => 'drush_expire_absolute_url',
  );

  // Expire internal paths.
  $items['expire-path'] = array(
    'description' => 'Expire a drupal path.',
    'arguments' => array(
      'paths' => 'A list drupal paths to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-path node/123' => 'Expire a single drupal path.',
      'drush expire-path FRONT' => 'Expire the front page.',
      'drush xp-path FRONT node/234 contact' => 'Expire multiple drupal paths.',
    ),
    'aliases' => array('xp-path'),
    'drupal dependencies' => array('expire'),
    'callback' => 'drush_expire_internal_path',
  );

  // Expire node objects.
  $items['expire-node'] = array(
    'description' => 'Expire a node by node ID.',
    'arguments' => array(
      'nids' => 'Numeric node-ids to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-node 2' => 'Expire single node by node ID.',
      'drush xp-node 2 24 612' => 'Expire multiple nodes by node IDs.',
    ),
    'aliases' => array('xp-node'),
    'drupal dependencies' => array('expire'),
    'callback' => 'drush_expire_node'
  );

  // Expire user objects.
  $items['expire-user'] = array(
    'description' => 'Expire a user by user ID.',
    'arguments' => array(
      'uids' => 'Numeric user IDs to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-user 2' => 'Expire single user by his ID.',
      'drush xp-user 2 24 612' => 'Expire multiple users by their IDs.',
    ),
    'aliases' => array('xp-user'),
    'drupal dependencies' => array('expire'),
    'callback' => 'drush_expire_user'
  );

  // Expire comment objects.
  $items['expire-comment'] = array(
    'description' => 'Expire a comment by comment ID.',
    'arguments' => array(
      'cids' => 'Numeric comment IDs to expire separated by spaces.',
    ),
    'examples' => array(
      'drush expire-comment 2' => 'Expire single comment by its ID.',
      'drush xp-comment 2 24 612' => 'Expire multiple comments by their IDs.',
    ),
    'aliases' => array('xp-comment'),
    'drupal dependencies' => array('expire', 'comment'),
    'callback' => 'drush_expire_comment'
  );

  return $items;
}

/**
 * Callback for expire-url drush command.
 */
function drush_expire_absolute_url() {

  // Get drush params.
  $absolute_urls = drush_get_arguments();
  unset($absolute_urls[0]);

  // Expire urls.
  ExpireAPI::executeExpiration($absolute_urls, '', NULL, TRUE);
}

/**
 * Callback for expire-path drush command.
 */
function drush_expire_internal_path() {

  // Get drush params.
  $paths = drush_get_arguments();
  unset($paths[0]);

  $internal_paths = array();
  foreach ($paths as &$path) {
    if ($path === 'FRONT') {
      $internal_paths += ExpireAPI::getFrontPageUrls();
    }
    else {
      $internal_paths[] = $path;
    }
  }
 
  // Expire internal paths.
  ExpireAPI::executeExpiration($internal_paths);
}

/**
 * Callback for expire-node drush command.
 */
function drush_expire_node() {
  _drush_expire_entity('node');
}

/**
 * Callback for expire-user drush command.
 */
function drush_expire_user() {
  _drush_expire_entity('user');
}

/**
 * Callback for expire-comment drush command.
 */
function drush_expire_comment() {
  _drush_expire_entity('comment');
}

/**
 * Internal function for expiration of all entities.
 */
function _drush_expire_entity($entity_type) {

  // Get drush params.
  $ids = drush_get_arguments();
  unset($ids[0]);

  $handler = _expire_get_expiration_handler($entity_type);
  $entities = entity_load($entity_type, $ids);
  if (is_object($handler) && !empty($entities)) {
    foreach ($entities as $entity) {
      $handler->expire($entity, 0, $skip_action_check = TRUE);
    }
  }
}
