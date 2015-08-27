<?php
/**
 * @file
 * editorial_timed_activity.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function editorial_timed_activity_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'editorial_timed_activity-timer';
  $context->description = 'Add the timer to the editorial submission pages';
  $context->tag = 'Editorial';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'editorial_journal_entry' => 'editorial_journal_entry',
      ),
      'options' => array(
        'node_form' => '2',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'jquery_countdown_timer-jquery_countdown_timer' => array(
          'module' => 'jquery_countdown_timer',
          'delta' => 'jquery_countdown_timer',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Add the timer to the editorial submission pages');
  t('Editorial');
  $export['editorial_timed_activity-timer'] = $context;

  return $export;
}
