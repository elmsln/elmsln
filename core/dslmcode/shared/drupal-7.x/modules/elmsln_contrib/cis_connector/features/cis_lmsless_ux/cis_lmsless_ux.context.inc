<?php
/**
 * @file
 * cis_lmsless_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function cis_lmsless_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'cis-lmsless';
  $context->description = 'LMSLess';
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
        'cis_lmsless-cis_lmsless' => array(
          'module' => 'cis_lmsless',
          'delta' => 'cis_lmsless',
          'region' => 'cis_lmsless',
          'weight' => '-10',
        ),
        'menu-menu-cis-user-profile' => array(
          'module' => 'menu',
          'delta' => 'menu-cis-user-profile',
          'region' => 'cis_user_profile',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('CIS');
  t('LMSLess');
  $export['cis-lmsless'] = $context;

  return $export;
}
