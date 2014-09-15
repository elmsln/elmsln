<?php
/**
 * @file
 * icor_cis_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function icor_cis_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'icor_cis_ux-blocks';
  $context->description = 'Blocks for ICOR UX for admin users';
  $context->tag = 'icor';
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
        'menu-menu-cis-toolkit' => array(
          'module' => 'menu',
          'delta' => 'menu-cis-toolkit',
          'region' => 'regions_admin_left',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Blocks for ICOR UX for admin users');
  t('icor');
  $export['icor_cis_ux-blocks'] = $context;

  return $export;
}
