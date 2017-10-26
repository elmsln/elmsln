<?php
/**
 * @file
 * webcomponents_app_context.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function webcomponents_app_context_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'webcomponents-app';
  $context->description = 'A context that\'s true when the apps path is loaded';
  $context->tag = 'webcomponents';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'apps' => 'apps',
        'apps/*' => 'apps/*',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('A context that\'s true when the apps path is loaded');
  t('webcomponents');
  $export['webcomponents-app'] = $context;

  return $export;
}
