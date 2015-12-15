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
        'speedreader-speedreader-block' => array(
          'module' => 'speedreader',
          'delta' => 'speedreader-block',
          'region' => 'cis_lmsless_modal',
          'weight' => '-9',
        ),
        'mooc_helper-mooc_helper_toc' => array(
          'module' => 'mooc_helper',
          'delta' => 'mooc_helper_toc',
          'region' => 'cis_lmsless_modal',
          'weight' => '-8',
        ),
        'mooc_helper_book_nav-book_sibling_nav' => array(
          'module' => 'mooc_helper_book_nav',
          'delta' => 'book_sibling_nav',
          'region' => 'header',
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
