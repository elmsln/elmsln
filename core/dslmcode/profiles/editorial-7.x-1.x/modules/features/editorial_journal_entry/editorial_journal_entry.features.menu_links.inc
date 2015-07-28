<?php
/**
 * @file
 * editorial_journal_entry.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function editorial_journal_entry_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-add_private-journal-entry:node/add/editorial-journal-entry
  $menu_links['menu-cis-add_private-journal-entry:node/add/editorial-journal-entry'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/editorial-journal-entry',
    'router_path' => 'node/add/editorial-journal-entry',
    'link_title' => 'Private Journal Entry',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_private-journal-entry:node/add/editorial-journal-entry',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Private Journal Entry');


  return $menu_links;
}
