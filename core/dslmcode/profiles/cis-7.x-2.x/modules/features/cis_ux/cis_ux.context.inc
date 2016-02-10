<?php
/**
 * @file
 * cis_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function cis_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-ux-toolkit';
  $context->description = 'Placement of the CIS toolkit block in Foundation Access';
  $context->tag = 'CIS';
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
        'menu-menu-elmsln-navigation' => array(
          'module' => 'menu',
          'delta' => 'menu-elmsln-navigation',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('CIS');
  t('Placement of the CIS toolkit block in Foundation Access');
  $export['cis-ux-toolkit'] = $context;

  return $export;
}
