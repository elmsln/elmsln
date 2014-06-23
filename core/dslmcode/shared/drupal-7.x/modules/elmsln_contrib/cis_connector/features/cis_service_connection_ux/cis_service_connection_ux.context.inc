<?php
/**
 * @file
 * cis_service_connection_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function cis_service_connection_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis_service_connection_ux-blocks';
  $context->description = 'This helps display service connection blocks';
  $context->tag = 'Content';
  $context->conditions = array(
    'context_all' => array(
      'values' => array(
        '~mooc-themecompat-*' => '~mooc-themecompat-*',
      ),
    ),
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
          'weight' => '-21',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('This helps display service connection blocks');
  $export['cis_service_connection_ux-blocks'] = $context;

  return $export;
}
