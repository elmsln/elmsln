<?php
/**
 * @file
 * mooc_ux_defaults.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_ux_defaults_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc_content';
  $context->description = 'Content block placement';
  $context->tag = 'Content';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'mooc_container' => 'mooc_container',
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
          'region' => 'highlighted',
          'weight' => '-10',
        ),
        'read_time-read_time' => array(
          'module' => 'read_time',
          'delta' => 'read_time',
          'region' => 'highlighted',
          'weight' => '-9',
        ),
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-25',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Content block placement');
  $export['mooc_content'] = $context;

  return $export;
}
