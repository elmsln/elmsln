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
  $context->description = 'This helps display the book outline correctly at all times';
  $context->tag = 'Content';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        1 => 1,
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'system-main-menu' => array(
          'module' => 'system',
          'delta' => 'main-menu',
          'region' => 'menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('This helps display the book outline correctly at all times');
  $export['mooc_content'] = $context;

  return $export;
}
