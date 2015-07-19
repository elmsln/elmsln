<?php
/**
 * @file
 * discuss_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function discuss_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'discuss_ux';
  $context->description = 'Discuss block UX';
  $context->tag = 'Discuss';
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
        'menu-menu-discuss-navigation' => array(
          'module' => 'menu',
          'delta' => 'menu-discuss-navigation',
          'region' => 'left_menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Discuss');
  t('Discuss block UX');
  $export['discuss_ux'] = $context;

  return $export;
}
