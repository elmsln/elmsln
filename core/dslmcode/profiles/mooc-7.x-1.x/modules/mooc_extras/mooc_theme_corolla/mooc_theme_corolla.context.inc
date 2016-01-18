<?php
/**
 * @file
 * mooc_theme_corolla.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_theme_corolla_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc-themecompat-corolla-blocks';
  $context->description = 'MOOC block positioning for adaptive theme';
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
        'mooc_helper-active_outline' => array(
          'module' => 'mooc_helper',
          'delta' => 'active_outline',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'cis_service_connection-section_context_changer' => array(
          'module' => 'cis_service_connection',
          'delta' => 'section_context_changer',
          'region' => 'regions_admin_left',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('MOOC block positioning for adaptive theme');
  t('MOOC theme compat');
  $export['mooc-themecompat-corolla-blocks'] = $context;

  return $export;
}
