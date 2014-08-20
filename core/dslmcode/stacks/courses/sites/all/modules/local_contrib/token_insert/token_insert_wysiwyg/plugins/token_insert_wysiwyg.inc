<?php

/**
 * @file
 * Wysiwyg API integration.
 */

/**
 * Implementats of hook_wysiwyg_plugin().
 */
function token_insert_wysiwyg_token_insert_wysiwyg_plugin() {
  $plugins['token_insert_wysiwyg'] = array(
    'title' => t('Insert token'),
    'vendor url' => 'http://drupal.org/project/token_insert',
    'icon file' => 'insert.png',
    'icon title' => t('Insert a token'),
    'settings' => array(),
  );
  return $plugins;
}

