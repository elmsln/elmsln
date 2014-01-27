<?php

/**
 * @file
 * Interface between nodeaccess_userreference.module and views.module.
 */

/**
 * Implements hook_views_plugins().
 *
 * Defines some plugins used by the Views modes for
 * nodeaccess_userreference.
 */
function nodeaccess_userreference_views_plugins() {
  $plugins = array(
    'module' => 'nodeaccess_userreference', // This just tells our themes are elsewhere.
    'display' => array(
      'nodeaccess_userreference_views_plugin_display' => array(
        'path' => drupal_get_path('module', 'nodeaccess_userreference'),
        'title' => 'Node access password',
        'help' => 'Destination-agnostic display. Mostly useful for programmatic views.',
        'handler' => 'nodeaccess_userreference_views_plugin_display',
        'no ui' => TRUE, // Programmatic use only.
        'uses hook menu' => FALSE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
      ),
    ),
    'style' => array(
      'nodeaccess_userreference_views_plugin_style' => array(
        'path' => drupal_get_path('module', 'nodeaccess_userreference'),
        'title' => 'Results array of entity ids',
        'help' => 'Returns the view as a PHP array of entity ids.',
        'handler' => 'nodeaccess_userreference_views_plugin_style',
        'no ui' => TRUE, // Programmatic use only.
        'uses row plugin' => TRUE,
        'uses fields' => TRUE,
        'type' => 'normal',
        'even empty' => TRUE,
      ),
    ),
  );
  return $plugins;
}