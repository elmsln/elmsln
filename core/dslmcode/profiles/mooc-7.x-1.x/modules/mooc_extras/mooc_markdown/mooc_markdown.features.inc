<?php
/**
 * @file
 * mooc_markdown.features.inc
 */

/**
 * Implements hook_filter_default_formats_alter().
 */
function mooc_markdown_filter_default_formats_alter(&$data) {
  if (isset($data['git_book_markdown'])) {
    $data['git_book_markdown']['filters']['cis_filter'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => 10,
    ); /* WAS: '' */
  }
}
