<?php
/**
 * @file
 *  Provides the views plugin information.
 */

/**
 * Implements hook_views_plugin().
 */
function views_infinite_scroll_views_plugins() {
  return array(
    'module' => 'views_infinite_scroll',
    'pager' => array(
      'infinite_scroll' => array(
        'title' => t('Infinite Scroll'),
        'help' => t('views_infinite_scroll'),
        'handler' => 'views_plugin_pager_infinite_scroll',
        'uses options' => TRUE,
        'parent' => 'full',
      ),
    ),
  );
}
