<?php
/**
 * @file
 * elmsmedia_cis_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function elmsmedia_cis_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'elmsmedia_ux';
  $context->description = 'ELMSMedia block positioning';
  $context->tag = 'ELMSMedia';
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
        'menu-menu-elmsmedia-navigation' => array(
          'module' => 'menu',
          'delta' => 'menu-elmsmedia-navigation',
          'region' => 'left_menu',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('ELMSMedia');
  t('ELMSMedia block positioning');
  $export['elmsmedia_ux'] = $context;

  return $export;
}
