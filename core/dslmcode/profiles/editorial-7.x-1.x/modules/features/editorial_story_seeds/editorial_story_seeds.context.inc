<?php
/**
 * @file
 * editorial_story_seeds.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function editorial_story_seeds_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'editorial_story_seeds-seed-block';
  $context->description = 'Story seeds block / form added to the bottom of journal entries';
  $context->tag = 'Editorial';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'editorial_journal_entry' => 'editorial_journal_entry',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'editorial_story_seeds-editorial_story_seeds_block' => array(
          'module' => 'editorial_story_seeds',
          'delta' => 'editorial_story_seeds_block',
          'region' => 'content',
          'weight' => '10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Editorial');
  t('Story seeds block / form added to the bottom of journal entries');
  $export['editorial_story_seeds-seed-block'] = $context;

  return $export;
}
