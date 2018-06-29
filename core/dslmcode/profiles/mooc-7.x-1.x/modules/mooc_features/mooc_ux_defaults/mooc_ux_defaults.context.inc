<?php
/**
 * @file
 * mooc_ux_defaults.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_ux_defaults_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc_content';
  $context->description = 'Content block placement';
  $context->tag = 'Content';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'git_book' => 'git_book',
        'mooc_container' => 'mooc_container',
        'page' => 'page',
        'section' => 'section',
      ),
      'options' => array(
        'node_form' => '2',
      ),
    ),
    'path' => array(
      'values' => array(
        '*' => '*',
        '~node/*' => '~node/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'mooc_helper_book_nav-book_sibling_nav' => array(
          'module' => 'mooc_helper_book_nav',
          'delta' => 'book_sibling_nav',
          'region' => 'header',
          'weight' => '-10',
        ),
        'mooc_nav_block-mooc_nav' => array(
          'module' => 'mooc_nav_block',
          'delta' => 'mooc_nav',
          'region' => 'highlighted',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Content');
  t('Content block placement');
  $export['mooc_content'] = $context;

  return $export;
}
