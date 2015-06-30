<?php
/**
 * @file
 * mooc_content_theming.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_content_theming_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'foundation_access_ux-content-theming';
  $context->description = 'This provides visualization of the uploaded image to be rendered in the header';
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
        'views-foundation_access_header-block' => array(
          'module' => 'views',
          'delta' => 'foundation_access_header-block',
          'region' => 'header',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Foundation Access');
  t('This provides visualization of the uploaded image to be rendered in the header');
  $export['foundation_access_ux-content-theming'] = $context;

  return $export;
}
