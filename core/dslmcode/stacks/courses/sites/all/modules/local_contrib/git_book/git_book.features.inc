<?php
/**
 * @file
 * git_book.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function git_book_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function git_book_node_info() {
  $items = array(
    'git_book' => array(
      'name' => t('Git Book'),
      'base' => 'node_content',
      'description' => t('Use a git repo to dictate the structure of this book outline'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
