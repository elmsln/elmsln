<?php
/**
 * @file
 * cis_foundation_access.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function cis_foundation_access_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis_foundation_access-admin';
  $context->description = 'Elevated permissions block positioning for sites running foundation access';
  $context->tag = 'Foundation Access';
  $context->conditions = array(
    'user' => array(
      'values' => array(
        'administrator' => 'administrator',
        'guest' => 'guest',
        'instructor' => 'instructor',
        'staff' => 'staff',
        'teaching assistant' => 'teaching assistant',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'menu-menu-course-tools-menu' => array(
          'module' => 'menu',
          'delta' => 'menu-course-tools-menu',
          'region' => 'cis_appbar_modal',
          'weight' => '-10',
        ),
        'cis_service_connection-section_context_changer' => array(
          'module' => 'cis_service_connection',
          'delta' => 'section_context_changer',
          'region' => 'cis_appbar_modal',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Elevated permissions block positioning for sites running foundation access');
  t('Foundation Access');
  $export['cis_foundation_access-admin'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis_foundation_access-global';
  $context->description = 'Global block positioning for sites running foundation access';
  $context->tag = 'Foundation Access';
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
        'masquerade-masquerade' => array(
          'module' => 'masquerade',
          'delta' => 'masquerade',
          'region' => 'cis_appbar_modal',
          'weight' => '-10',
        ),
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-10',
        ),
        'cis_service_connection-managed_footer' => array(
          'module' => 'cis_service_connection',
          'delta' => 'managed_footer',
          'region' => 'footer',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Foundation Access');
  t('Global block positioning for sites running foundation access');
  $export['cis_foundation_access-global'] = $context;

  return $export;
}
