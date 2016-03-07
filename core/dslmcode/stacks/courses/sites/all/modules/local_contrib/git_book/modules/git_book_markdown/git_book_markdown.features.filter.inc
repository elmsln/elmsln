<?php
/**
 * @file
 * git_book_markdown.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function git_book_markdown_filter_default_formats() {
  $formats = array();

  // Exported format: Markdown.
  $formats['git_book_markdown'] = array(
    'format' => 'git_book_markdown',
    'name' => 'Markdown',
    'cache' => 0,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_markdown' => array(
        'weight' => -42,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_url' => array(
        'weight' => -32,
        'status' => 1,
        'settings' => array(
          'filter_url_length' => 72,
        ),
      ),
    ),
  );

  return $formats;
}
