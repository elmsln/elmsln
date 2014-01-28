<?php
/**
 * @file
 * chamfer_defaults.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function chamfer_defaults_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'chamfer-block-positions';
  $context->description = 'Chamfer Block default positions';
  $context->tag = 'Chamfer';
  $context->conditions = array(
    'theme' => array(
      'values' => array(
        'chamfer' => 'chamfer',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'delta_blocks-messages' => array(
          'module' => 'delta_blocks',
          'delta' => 'messages',
          'region' => 'content',
          'weight' => '-10',
        ),
        'delta_blocks-breadcrumb' => array(
          'module' => 'delta_blocks',
          'delta' => 'breadcrumb',
          'region' => 'content',
          'weight' => '-9',
        ),
        'delta_blocks-tabs' => array(
          'module' => 'delta_blocks',
          'delta' => 'tabs',
          'region' => 'content',
          'weight' => '-8',
        ),
        'delta_blocks-page-title' => array(
          'module' => 'delta_blocks',
          'delta' => 'page-title',
          'region' => 'content',
          'weight' => '-7',
        ),
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-6',
        ),
        'delta_blocks-site-name' => array(
          'module' => 'delta_blocks',
          'delta' => 'site-name',
          'region' => 'user_second',
          'weight' => '-17',
        ),
        'delta_blocks-site-slogan' => array(
          'module' => 'delta_blocks',
          'delta' => 'site-slogan',
          'region' => 'user_second',
          'weight' => '-16',
        ),
        'boxes-site_footer' => array(
          'module' => 'boxes',
          'delta' => 'site_footer',
          'region' => 'footer_first',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Chamfer');
  t('Chamfer Block default positions');
  $export['chamfer-block-positions'] = $context;

  return $export;
}
