<?php
/**
 * @file
 * Contains core functions for the Views module support.
 */

/*
 * Implements hook_views_plugins().
 *
 * This function annnounces the style plugin for flexslider views.
 */
function flexslider_views_views_plugins() {
  return array(
    'style' => array(
      // Style plugin for the navigation.
      'flexslider' => array(
        'title' => t('Flex Slider'),
        'help' => t('Display the results in a Flex Slider widget.'),
        'handler' => 'flexslider_views_plugin_style_flexslider',
        'theme' => 'views_view_flexslider',
        'theme file' => 'flexslider_views.theme.inc',
        'theme path' => drupal_get_path('module', 'flexslider_views') . '/theme',
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => FALSE,
      ),
    ),
  );
}
