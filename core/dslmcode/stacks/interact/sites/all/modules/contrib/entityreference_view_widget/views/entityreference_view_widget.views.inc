<?php

/**
 * Implements hook_views_plugins().
 */
function entityreference_view_widget_views_plugins() {
  $entity_tables = array();
  $tables = views_fetch_data();
  foreach ($tables as $table_name => $table) {
    if (!empty($table['table']['entity type'])) {
      $entity_tables[] = $table_name;
    }
  }

  $plugins = array(
    'display' => array(
      'entityreference_view_widget' => array(
        'title' => t('Entity Reference View Widget'),
        'help' => t('Selects referenceable entities for an entity reference view widget.'),
        'handler' => 'entityreference_view_widget_plugin_display',
        'use ajax' => FALSE,
        'use pager' => TRUE,
        'use more' => FALSE,
        'accept attachments' => FALSE,
        'theme' => 'views_view',
        // Make this plugin only available to tables that map to an entity type.
        'base' => $entity_tables,
        // Custom property, used with views_get_applicable_views() to retrieve
        // all views with a 'Entity Reference View' display.
        'entityreference view display' => TRUE,
      ),
    ),
    'exposed_form' => array(
      'entityreference_view_widget' => array(
        'title' => t('Entity Reference View Widget'),
        'help' => t('Makes an exposed form work as a part of the Entityreference widget.'),
        'handler' => 'entityreference_view_widget_plugin_exposed_form',
        'uses options' => TRUE,
        // Make this plugin only available to tables that map to an entity type.
        'base' => $entity_tables,
      ),
    ),
  );
  return $plugins;
}
