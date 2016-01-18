<?php
/**
 * @file
 * mooc_theme_aurora.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function mooc_theme_aurora_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'mooc-themecompat-aurora-blocks';
  $context->description = 'Compatibility with aurora';
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
        'delta_blocks-site-name' => array(
          'module' => 'delta_blocks',
          'delta' => 'site-name',
          'region' => 'header',
          'weight' => '-10',
        ),
        'delta_blocks-site-slogan' => array(
          'module' => 'delta_blocks',
          'delta' => 'site-slogan',
          'region' => 'header',
          'weight' => '-9',
        ),
        'system-main-menu' => array(
          'module' => 'system',
          'delta' => 'main-menu',
          'region' => 'banner',
          'weight' => '-10',
        ),
        'mooc_helper-active_outline' => array(
          'module' => 'mooc_helper',
          'delta' => 'active_outline',
          'region' => 'main_prefix',
          'weight' => '-10',
        ),
        'delta_blocks-tabs' => array(
          'module' => 'delta_blocks',
          'delta' => 'tabs',
          'region' => 'content',
          'weight' => '-10',
        ),
        'system-main' => array(
          'module' => 'system',
          'delta' => 'main',
          'region' => 'content',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 1;

  // Translatables
  // Included for use with string extractors like potx.
  t('Compatibility with aurora');
  t('MOOC theme compat');
  $export['mooc-themecompat-aurora-blocks'] = $context;

  return $export;
}
