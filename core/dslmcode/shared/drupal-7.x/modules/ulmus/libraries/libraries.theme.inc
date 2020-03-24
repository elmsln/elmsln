<?php

/**
 * @file
 * Provides theme and preprocess functions for Libraries API.
 */

/**
 * Prepare variables for theming a table with a title.
 * 
 * @param array $variables
 *   An array of theme variables, passed by reference.
 */
function template_preprocess_libraries_table_with_title(&$variables) {
  drupal_add_css(drupal_get_path('module', 'libraries') . '/css/libraries.admin.css');

  $variables['attributes'] += array('class' => array());
  $variables['attributes']['class'][] = 'libraries-table';
}

/**
 * Returns HTML for a table with a title.
 * 
 * @param array $variables
 *   An array theme variables.
 * 
 * @return string
 *   The HTML output for this table with a title.
 */
function theme_libraries_table_with_title(array $variables) {
  $output = '';
  $output .= '<h2>' . $variables['title'] . '</h2>';
  $output .= '<div class="description">' . $variables['description'] . '</div>';
  $output .= theme_table($variables);
  return $output;
}
