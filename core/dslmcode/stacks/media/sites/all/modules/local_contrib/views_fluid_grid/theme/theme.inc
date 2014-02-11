<?php

/**
 * @file
 * Helper functions to make theming easier.
 */

/**
 * Display the view as fluid grid using an HTML list element.
 *
 * @see template_preprocess_views_view_unformatted()
 */
function template_preprocess_views_fluid_grid_plugin_style(&$vars) {
  $view = $vars['view'];
  $rows = $vars['rows'];

  $options = $view->style_plugin->options;
  $module_path = drupal_get_path('module', 'views_fluid_grid');

  // Send base stylesheets to the page.
  drupal_add_css($module_path .'/css/views_fluid_grid.base.css');

  // Set up CSS class for the HTML list element.
  $vars['list_class'] = 'views-fluid-grid-list';

  // Items size.
  if (!empty($options['items_width']) || !empty($options['items_height'])) {
    // Send size related stylesheets to the page.
    drupal_add_css($module_path .'/css/views_fluid_grid.size.css');

    if (!empty($options['items_width'])) {
      $vars['list_class'] .= ' views-fluid-grid-items-width-'. $options['items_width'];
    }
    if (!empty($options['items_height'])) {
      $vars['list_class'] .= ' views-fluid-grid-items-height-'. $options['items_height'];
    }
  }

  if (!empty($options['advanced_layout'])) {
    // Send advanced layout stylesheets to the page.
    drupal_add_css($module_path .'/css/views_fluid_grid.advanced.css');

    // Alignment for items in the list and items' content.
    if (!empty($options['list_alignment'])) {
      $vars['list_class'] .= ' views-fluid-grid-list-'. $options['list_alignment'];
    }
    if (!empty($options['items_alignment'])) {
      $vars['list_class'] .= ' views-fluid-grid-items-'. $options['items_alignment'];
    }

    // Item margins.
    if (isset($options['items_h_margin']) && $options['items_h_margin'] != '') {
      $vars['list_class'] .= ' views-fluid-grid-items-h-margin-'. str_replace('.', '-', $options['items_h_margin']);
    }
    if (isset($options['items_v_margin']) && $options['items_v_margin'] != '') {
      $vars['list_class'] .= ' views-fluid-grid-items-v-margin-'. str_replace('.', '-', $options['items_v_margin']);
    }

    // Advanced CSS3 properties.
    if (!empty($options['box_shadow'])) {
      $vars['list_class'] .= ' views-fluid-grid-items-box-shadow';
    }
    if (!empty($options['border_radius'])) {
      $vars['list_class'] .= ' views-fluid-grid-items-border-radius';
    }
  }

  // The following snippet is 100% based on template_preprocess_views_view_unformatted().
  $vars['classes_array'] = array();
  $vars['classes'] = array();
  // Set up striping values.
  $count = 0;
  $max = count($rows);
  foreach ($rows as $id => $row) {
    $count++;
    $vars['classes'][$id][] = 'views-row';
    $vars['classes'][$id][] = 'views-row-' . $count;
    $vars['classes'][$id][] = 'views-row-' . ($count % 2 ? 'odd' : 'even');
    if ($count == 1) {
      $vars['classes'][$id][] = 'views-row-first';
    }
    if ($count == $max) {
      $vars['classes'][$id][] = 'views-row-last';
    }

    if ($row_class = $view->style_plugin->get_row_class($id)) {
      $vars['classes'][$id][] = $row_class;
    }

    // Flatten the classes to a string for each row for the template file.
    $vars['classes_array'][$id] = implode(' ', $vars['classes'][$id]);
  }
}
