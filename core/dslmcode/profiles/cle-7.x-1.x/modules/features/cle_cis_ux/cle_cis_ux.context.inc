<?php
/**
 * @file
 * cle_cis_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function cle_cis_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cle_cis_ux';
  $context->description = 'CLE user experience when integrated with CIS';
  $context->tag = 'CLE';
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
        'menu-menu-elmsln-main-navigation' => array(
          'module' => 'menu',
          'delta' => 'menu-elmsln-main-navigation',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('CLE');
  t('CLE user experience when integrated with CIS');
  $export['cle_cis_ux'] = $context;

  return $export;
}
