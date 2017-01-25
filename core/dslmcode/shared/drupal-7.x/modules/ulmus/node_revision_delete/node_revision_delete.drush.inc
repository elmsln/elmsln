<?php

/**
 * @file
 * Drush integration for node_revision_delete
 */

/**
 * Implements COMMANDFILE_drush_command().
 */
function node_revision_delete_drush_command() {
  $items = array();

  $items['node-revision-delete'] = array(
    'description' => 'Deletes old node revisions for a given content type.',
    'arguments' => array(
      'type' => 'A content type\'s machine name.',
      'revisions' => 'The maximum amount of revisions to keep per node for this content type.',
    ),
    'required-arguments' => TRUE,
    'options' => array(
      'show-deleted' => 'Whether to print the list of deleted revisions or not. Defaults to FALSE',
    ),
    'examples' => array(
      'drush nrd article 50' => 'Keeps the latest 50 revisions of every article. Deletes the rest.',
    ),
    'aliases' => array('nrd'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}

/**
 * Implements drush_COMMANDFILE_COMMANDNAME().
 */
function drush_node_revision_delete($content_type, $revisions_to_keep) {
  // Set up the batch job.
  $batch = array(
    'operations' => array(
      array('node_revision_delete_batch_process', array($content_type, $revisions_to_keep))
    ),
    'title' => t('Node Revision Delete batch job'),
    'init_message' => t('Starting...'),
    'error_message' => t('An error occurred'),
    'finished' => 'node_revision_delete_batch_finish',
    'file' => drupal_get_path('module', 'node_revision_delete') . '/node_revision_delete.batch.inc',
  );

  // Start the batch job.
  batch_set($batch);
  drush_backend_batch_process();
}
