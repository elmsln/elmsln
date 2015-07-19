<?php
/**
 * @file
 * ecd_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function ecd_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'comply_ux';
  $context->description = 'Comply block UX';
  $context->tag = 'Comply';
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
        'menu-menu-comply-navigation' => array(
          'module' => 'menu',
          'delta' => 'menu-comply-navigation',
          'region' => 'left_menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Comply');
  t('Comply block UX');
  $export['comply_ux'] = $context;

  return $export;
}
