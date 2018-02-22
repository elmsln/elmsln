<?php
/**
 * @file
 * mooc_cis_ux.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_cis_ux_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc_cis_ux-blocks';
  $context->description = '';
  $context->tag = 'Content';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~mooc-themecompat-*' => '~mooc-themecompat-*',
      ),
    ),
    'user' => array(
      'values' => array(
        'administrator' => 'administrator',
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
          'region' => 'regions_admin_left',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  $export['mooc_cis_ux-blocks'] = $context;

  return $export;
}
