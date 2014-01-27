<?php

/**
 * @file
 *   Nodequeue generate drush integration.
 */

/**
 * Implementation of hook_drush_command().
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function nodequeue_generate_drush_command() {
  $items = array();

  $items['nodequeue-generate'] = array(
    'description' => "Re-populates specified nodequeues with random nodes.",
    'drupal dependencies' => array('nodequeue_generate'),
    'arguments' => array(
      'queue' => 'Machine name of queue to be re-populated.',
    ),
    'aliases' => array('nqg'),
  );
  $items['nodequeue-generate-all'] = array(
    'description' => "Re-populates nodequeues with random nodes.",
    'drupal dependencies' => array('nodequeue_generate'),
    'aliases' => array('nqga'),
  );
  $items['nodequeue-generate-rehash'] = array(
    'description' => "Rehashes smartqueue subqueues for taxonomy smartqueue.",
    'drupal dependencies' => array('nodequeue_generate', 'smartqueue'),
    'aliases' => array('nqgr'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 */
function nodequeue_generate_drush_help($section) {
  switch ($section) {
    case 'drush:nodequeue-generate':
      return dt("Re-populates specified nodequeues with random nodes.");
    case 'drush:nodequeue-generate-all':
      return dt("Re-populates all nodequeues with random nodes.");
    case 'drush:nodequeue-generate-rehash':
      return dt("Rehashes smartqueue subqueues for taxonomy smartqueue.");
  }
}

/**
 * Re-populates specified nodequeues with random nodes.
 */
function drush_nodequeue_generate() {
  $args = func_get_args();

  // At least one queue must be specified.
  if (count($args) < 1) {
    drush_set_error('error', dt('At least one queue must be specified.'));
  }

  // Get qids from machine names.
  $qids = array();
  foreach ($args as $queue) {

    $qid = db_select('nodequeue_queue', 'nq')
      ->fields('nq', array('qid'))
      ->condition('name', $queue)
      ->execute()
      ->fetchField();

    if ($qid) {
      $qids[] = $qid;
    }
    else {
      drush_set_error('error', dt('Queue @queue was not found.', array('@queue' => $queue)));
    }

  }

  nodequeue_generate_rehash();
  nodequeue_generate_repopulate_queues($qids);
}

/**
 * Re-populates all nodequeues with random nodes.
 */
function drush_nodequeue_generate_all() {
  $qids = db_select('nodequeue_queue', 'nq')
    ->fields('nq', array('qid'))
    ->execute()
    ->fetchAll(PDO::FETCH_COLUMN, 'qid');

  nodequeue_generate_rehash();
  nodequeue_generate_repopulate_queues($qids);
}

/**
 * Rehashes smartqueue subqueues for taxonomy smartqueue.
 */
function drush_nodequeue_generate_rehash() {
  nodequeue_generate_rehash();
}
