<?php
/**
 * @file
 * inbox_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function inbox_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'inbox-home';
  $context->description = 'Blocks for the homepage of inbox';
  $context->tag = 'Inbox';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-inbox_calendar-block_2' => array(
          'module' => 'views',
          'delta' => 'inbox_calendar-block_2',
          'region' => 'content',
          'weight' => '-16',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blocks for the homepage of inbox');
  t('Inbox');
  $export['inbox-home'] = $context;

  return $export;
}
