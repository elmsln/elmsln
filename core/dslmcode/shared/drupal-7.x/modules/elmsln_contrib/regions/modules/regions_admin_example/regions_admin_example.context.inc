<?php
/**
 * @file
 * regions_admin_example.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function regions_admin_example_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'regions_admin';
  $context->description = 'Admin options in the left admin region';
  $context->tag = 'Regions Admin Example';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '~admin*' => '~admin*',
        '~ajax*' => '~ajax*',
        '~node/*/*' => '~node/*/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'masquerade-masquerade' => array(
          'module' => 'masquerade',
          'delta' => 'masquerade',
          'region' => 'regions_admin_left',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Admin options in the left admin region');
  t('Regions Admin Example');
  $export['regions_admin'] = $context;

  return $export;
}
