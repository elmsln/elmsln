<?php

/**
 * @file
 * Style Guide plugin file for the Filter module.
 */

/**
 * Return filter tips for display.
 *
 * @param $long
 *   Boolean indicator of long format display.
 *
 * @return
 *   Themed filter tips.
 */
function styleguide_filter_tips($long = TRUE) {
  if ($long) {
    module_load_include('module', 'filter', 'filter');
    module_load_include('inc', 'filter', 'filter.pages');
    return theme('filter_tips', array('tips' => _filter_tips(-1, TRUE), 'long' => $long));
  }
  else {
    return filter_process_format(array('#base_type' => 'textarea', '#parents' => array(), '#value' => ''));
  }
}

/**
 * Implements hook_styleguide().
 */
function filter_styleguide() {
  $items = array();

  // Show the form version.
  $items['filter_tips'] = array(
    'title' => t('Filter tips, short'),
    'content' => styleguide_filter_tips(FALSE),
    'group' => t('System')
  );
  // Show the long version.
  $items['filter_tips_long'] = array(
    'title' => t('Filter tips, long'),
    'content' => styleguide_filter_tips(TRUE),
    'group' => t('System')
  );

  return $items;
}
