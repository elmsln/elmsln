<?php
/**
 * @file
 * mooc_nav_block.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_nav_block_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc_nav_block';
  $context->description = 'Navigation block placement';
  $context->tag = 'Content';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'page' => 'page',
      ),
      'options' => array(
        'node_form' => '1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'mooc_nav_block-mooc_nav' => array(
          'module' => 'mooc_nav_block',
          'delta' => 'mooc_nav',
          'region' => 'content',
          'weight' => '0',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Navigation block placement');
  $export['mooc_nav_block'] = $context;

  return $export;
}
