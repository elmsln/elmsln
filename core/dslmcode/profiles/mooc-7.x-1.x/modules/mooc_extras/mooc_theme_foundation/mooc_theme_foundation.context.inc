<?php
/**
 * @file
 * mooc_theme_foundation.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_theme_foundation_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc-themecompat-foundation-blocks';
  $context->description = 'Compatibility with foundation';
  $context->tag = 'MOOC theme compat';
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
        'speedreader-speedreader-block' => array(
          'module' => 'speedreader',
          'delta' => 'speedreader-block',
          'region' => 'cis_appbar_modal',
          'weight' => '-9',
        ),
        'cis_service_connection-active_outline' => array(
          'module' => 'cis_service_connection',
          'delta' => 'active_outline',
          'region' => 'left_menu',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Compatibility with foundation');
  t('MOOC theme compat');
  $export['mooc-themecompat-foundation-blocks'] = $context;

  return $export;
}
