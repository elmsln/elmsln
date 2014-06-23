<?php
/**
 * @file
 * mooc_theme_foundation.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_theme_foundation_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc-themecompat-foundation-blocks';
  $context->description = 'Compatibility with foundation';
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
        'menu-menu-course-tools-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-course-tools-menu',
          'region' => 'admin_first',
          'weight' => '-10',
        ),
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-9',
        ),
        'cis_service_connection-active_outline' => array(
          'module' => 'cis_service_connection',
          'delta' => 'active_outline',
          'region' => 'sidebar_first',
          'weight' => '-10',
        ),
        'cis_service_connection-instructor_contact' => array(
          'module' => 'cis_service_connection',
          'delta' => 'instructor_contact',
          'region' => 'sidebar_first',
          'weight' => '-9',
        ),
        'boxes-site_footer' => array(
          'module' => 'boxes',
          'delta' => 'site_footer',
          'region' => 'footer',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Compatibility with foundation');
  t('MOOC theme compat');
  $export['mooc-themecompat-foundation-blocks'] = $context;

  return $export;
}
