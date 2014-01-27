<?php

/**
 * @file
 * Plugin to provide a site context. A site context is a site wrapped in a
 * context object that can be utilized by anything that accepts contexts.
 */

$plugin = array(
  'title' => t('Site'),
  'description' => t('A site object.'),
  'context' => 'path_breadcrumbs_ctools_context_create_context',
  'keyword' => 'site',
  'context name' => 'site',
  'convert' => 'path_breadcrumbs_ctools_context_site_convert',

  // This context is deprecated and should not be usable in the UI.
  'no ui' => TRUE,
  'no required context ui' => TRUE,
);

/**
 * Create a context from manual configuration.
 */
function path_breadcrumbs_ctools_context_create_context($empty, $data = NULL, $conf = FALSE) {
  $context = new ctools_context('path_breadcrumbs_site');
  $context->plugin = 'path_breadcrumbs_site';
  $context->keyword = 'site';

  return $context;
}

/**
 * Convert a context into a string.
 */
function path_breadcrumbs_ctools_context_site_convert($context, $type) {
  $values = token_generate('site', array($type => $type));
  if (isset($values[$type])) {
    return $values[$type];
  }
  return '';
}
