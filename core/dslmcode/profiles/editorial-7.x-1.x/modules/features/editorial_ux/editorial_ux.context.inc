<?php
/**
 * @file
 * editorial_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function editorial_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'editorial_ux';
  $context->description = 'Editorial block UX';
  $context->tag = 'Editorial';
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
        'menu-menu-editorial-navigation' => array(
          'module' => 'menu',
          'delta' => 'menu-editorial-navigation',
          'region' => 'left_menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Editorial');
  t('Editorial block UX');
  $export['editorial_ux'] = $context;

  return $export;
}
