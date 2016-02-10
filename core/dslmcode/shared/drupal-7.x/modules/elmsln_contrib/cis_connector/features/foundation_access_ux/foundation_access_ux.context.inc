<?php
/**
 * @file
 * foundation_access_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function foundation_access_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'foundation_access_ux-add';
  $context->description = 'Menu that controls the adding of content to the system in question';
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
        'menu-menu-elmsln-add' => array(
          'module' => 'menu',
          'delta' => 'menu-elmsln-add',
          'region' => 'local_header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Foundation Access');
  t('Menu that controls the adding of content to the system in question');
  $export['foundation_access_ux-add'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'foundation_access_ux-admin';
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
        'menu-menu-elmsln-settings' => array(
          'module' => 'menu',
          'delta' => 'menu-elmsln-settings',
          'region' => 'cis_lmsless_modal',
          'weight' => '-10',
        ),
        'cis_service_connection-section_context_changer' => array(
          'module' => 'cis_service_connection',
          'delta' => 'section_context_changer',
          'region' => 'cis_lmsless_modal',
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
  $export['foundation_access_ux-admin'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'foundation_access_ux-global';
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
          'region' => 'cis_lmsless_modal',
          'weight' => '-10',
        ),
        'cis_lmsless-cis_lmsless_user' => array(
          'module' => 'cis_lmsless',
          'delta' => 'cis_lmsless_user',
          'region' => 'cis_lmsless_modal',
          'weight' => '-9',
        ),
        'cis_lmsless-cis_lmsless_network' => array(
          'module' => 'cis_lmsless',
          'delta' => 'cis_lmsless_network',
          'region' => 'cis_lmsless_modal',
          'weight' => '-8',
        ),
        'cis_shortcodes-cis_shortcodes_block' => array(
          'module' => 'cis_shortcodes',
          'delta' => 'cis_shortcodes_block',
          'region' => 'cis_lmsless_modal',
          'weight' => '-7',
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
  $export['foundation_access_ux-global'] = $context;

  return $export;
}
