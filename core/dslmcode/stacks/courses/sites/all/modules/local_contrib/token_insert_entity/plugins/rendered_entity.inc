<?php
/**
 * @file
 * Wysiwyg API integration.
 */

/**
 * Implementation of hook_wysiwyg_plugin().
 */
function token_insert_entity_rendered_entity_plugin() {
  $plugins['rendered_entity'] = array(
    'title' => t('Rendered entity'),
    'vendor url' => 'http://drupal.org/project/token_insert_entity',
    'icon file' => 'insert.png',
    'icon title' => t('Insert a token'),
    'settings' => array(),
  );
  return $plugins;
}
