<?php
/**
 * @file
 * meedjum_base.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function meedjum_base_filter_default_formats() {
  $formats = array();

  // Exported format: Markdown.
  $formats['markdown'] = array(
    'format' => 'markdown',
    'name' => 'Markdown',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_markdown' => array(
        'weight' => 0,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  // Exported format: Raw HTML.
  $formats['raw_html'] = array(
    'format' => 'raw_html',
    'name' => 'Raw HTML',
    'cache' => 1,
    'status' => 1,
    'weight' => 0,
    'filters' => array(),
  );

  return $formats;
}
