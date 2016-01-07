<?php
/**
 * @file
 * mooc_random_content.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_random_content_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elmsln-random_content';
  $context->description = 'Display two random content blocks on the front page';
  $context->tag = 'ELMSLN Extra';
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
        'views-elmsln_random_content-block' => array(
          'module' => 'views',
          'delta' => 'elmsln_random_content-block',
          'region' => 'content',
          'weight' => '-23',
        ),
        'views-elmsln_random_content-block_1' => array(
          'module' => 'views',
          'delta' => 'elmsln_random_content-block_1',
          'region' => 'content',
          'weight' => '-22',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Display two random content blocks on the front page');
  t('ELMSLN Extra');
  $export['elmsln-random_content'] = $context;

  return $export;
}
