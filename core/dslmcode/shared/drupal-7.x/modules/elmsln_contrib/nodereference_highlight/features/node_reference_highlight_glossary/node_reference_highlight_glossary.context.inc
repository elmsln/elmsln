<?php
/**
 * @file
 * node_reference_highlight_glossary.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function node_reference_highlight_glossary_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'nrhi-glossary';
  $context->description = 'Displays a glossary block in the right slide out area if it finds any term nodes';
  $context->tag = 'Node reference highlight';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'node/*' => 'node/*',
        '~node/*/*' => '~node/*/*',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-nrhi_term_glossary-block_1' => array(
          'module' => 'views',
          'delta' => 'nrhi_term_glossary-block_1',
          'region' => 'regions_right_slideout',
          'weight' => '0',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Displays a glossary block in the right slide out area if it finds any term nodes');
  t('Node reference highlight');
  $export['nrhi-glossary'] = $context;

  return $export;
}
