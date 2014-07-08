<?php

/**
 * @file
 * Wysiwyg API integration.
 */

/**
 * Implements hook_wysiwyg_plugin().
 */
function shortcode_wysiwyg_shortcode_wysiwyg_plugin() {
  $plugins['shortcode_wysiwyg'] = array(
    'title' => t('Shortcode'),
    'vendor url' => 'http://drupal.org/project/shortcode',
    'icon file' => 'insert.png',
    'icon title' => t('Insert a Shortcode'),
    'settings' => array(),
  );
  return $plugins;
}
