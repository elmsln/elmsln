<?php
/**
 * @file
 * editorial_journal_entry.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function editorial_journal_entry_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function editorial_journal_entry_node_info() {
  $items = array(
    'editorial_journal_entry' => array(
      'name' => t('Journal entry'),
      'base' => 'node_content',
      'description' => t('An entry for your private journal.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
