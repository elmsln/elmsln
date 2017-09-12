<?php
/**
 * @file
 * CIS Section Drush functions.
 */

/**
 * Implements hook_drush_commands().
 */
function cis_section_drush_command() {
  return array(
    'cis-process-roster' => array(
      'description' => 'Process the roster queue.',
      'aliases' => array('cis-pr'),
    ),
  );
}

/**
 * Implementation of hook_drush_help().
 */
function cis_section_drush_help($section) {
  switch ($section) {
    case 'drush:cis-process-roster':
      return dt('Process any queued roster synchronization.');
  }
}

/**
 * Drush command callback.
 */
function drush_cis_section_cis_process_roster() {
  // Check that we're not already running.
  $lock = lock_acquire('cis_section_drush_process', 300);
  if (!$lock) {
    drush_log('Already processing rosters.', 'error');
    return;
  }

  drush_log('Starting to process rosters.', 'ok');

  /* @var \DrupalQueueInterface $queue */
  $queue = \DrupalQueue::get(CisSectionRosterProcessor::QUEUE_NAME);
  while ($item = $queue->claimItem(300)) {
    try {
      $item->data->process();
      $queue->deleteItem($item);
    }
    catch (Exception $e) {
      watchdog_exception('cis_section_cron', $e);
    }
  }

  lock_release('cis_section_drush_process');
  drush_log('Finished processing rosters.', 'ok');
}