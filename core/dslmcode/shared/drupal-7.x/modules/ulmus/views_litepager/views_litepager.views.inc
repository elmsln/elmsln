<?php
/**
 * @file
 * Views Pager plugin definition
 */

/**
 * Implements hook_views_plugins().
 */
function views_litepager_views_plugins() {
  $plugins = array(
    'pager' => array(
      'lite' => array(
        'title' => t('Paged output, lite pager'),
        'help' => t('Use the lite pager output.'),
        'handler' => 'views_litepager_plugin_pager_lite',
        'help topic' => 'pager-lite',
        'uses options' => TRUE,
        'parent' => 'full',
      ),
    ),
  );

  return $plugins;
}

