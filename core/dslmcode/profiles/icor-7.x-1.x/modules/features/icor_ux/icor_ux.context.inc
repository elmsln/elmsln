<?php
/**
 * @file
 * icor_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function icor_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'icor_ux';
  $context->description = 'ICOR block placement';
  $context->tag = 'ICOR';
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
        'menu-menu-icor-navigation' => array(
          'module' => 'menu',
          'delta' => 'menu-icor-navigation',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('ICOR');
  t('ICOR block placement');
  $export['icor_ux'] = $context;

  return $export;
}
