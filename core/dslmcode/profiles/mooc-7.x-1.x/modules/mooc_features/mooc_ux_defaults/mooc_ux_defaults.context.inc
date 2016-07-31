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
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-9',
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
