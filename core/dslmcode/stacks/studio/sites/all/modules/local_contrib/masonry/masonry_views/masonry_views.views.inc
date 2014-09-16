<?php
/**
 * @file
 * Views-specific implementations and functions.
 */

/**
 * Implements hook_views_plugins().
 */
function masonry_views_views_plugins() {
  return array(
    'style' => array(
      'masonry_views_grid' => array(
        'title' => t('Masonry grid'),
        'handler' => 'views_plugin_style_masonry_views_grid',
        'uses options' => TRUE,
        'help' => t("Display content in a jQuery Masonry grid."),
        'theme' => 'views_view_masonry',
        'type' => 'normal',
        'uses row plugin' => TRUE,
        'uses row class' => TRUE,
        'uses grouping' => FALSE,
      ),
    ),
  );
}

