<?php

/**
 * @file
 * Define a new display for Views.
 */

/**
 * Implements hook_views_plugins().
 *
 * Defines some plugins used by the Views modes for
 * form dynamic element.
 * Largely inspired by references module views
 */
function dynamic_select_views_plugins() {

  $plugins = array(
    'display' => array(
      'dynamic_select' => array(
        'title' => t('Dynamic Select'),
        'admin' => t('Dynamic Select'),
        'handler' => 'dynamic_select_plugin_display',
        'uses hook menu' => FALSE,
        'use ajax' => FALSE,
        'use pager' => FALSE, // disable use of pager but still allow to limit the number of results.
        'use more' => FALSE,
        'accept attachments' => FALSE,
        // Custom property, used with views_get_applicable_views() to retrieve
        // all views with a form_search_element.
        'dynamic_select_display' => TRUE,
      ),
    ),
    'style' => array(
      'dynamic_select_style' => array(
        'title' => t('Array of results'),
        'help' => 'Returns results as a PHP array of rows stripped from HTML and special characters.',
        'handler' => 'dynamic_select_plugin_style',
        'theme' => 'views_view_unformatted',
        'uses row plugin' => TRUE,
        'uses fields' => TRUE,
        'uses options' => FALSE,
        'uses grouping' => FALSE, // Don't group the rows
        //        'type' => 'dynamic_select', 
        'even empty' => TRUE,
      ),
    ),
    'row' => array(
      'dynamic_select_fields' => array(
        'title' => t('Inline fields'),
        'help' => t('Force the inline display of fields.'),
        'handler' => 'dynamic_select_plugin_row_fields',
        'theme' => 'views_view_fields',
        'theme path' => drupal_get_path('module', 'views') . '/theme',
        'theme file' => 'theme.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE, // We us options but we will force some
        //        'type' => 'dynamic_select',
      ),
    ),
  );

  return $plugins;
}

/**
 * Implements hook_views_query_alter().
().
 *
 */
function dynamic_select_views_query_alter($view, $query) {

  $default = $view->display_handler->get_option('dynamic_select_default');

  if (!isset($default)) {

    // We are not only looking for a single default value but for the whole. So no change to the query.
    return;
  }

  // Reset the where clause.
  $query->where = array();

  $table_alias = $query->ensure_table($view->base_table);

  $operator = '=';

  // Add the clause to get only the default value 
  $query->add_where(1, $table_alias . '.' . $view->base_field, $default, $operator);
}




