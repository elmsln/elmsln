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

  // Exported menu link: menu-elmsln-add_private-journal-entry:node/add/editorial-journal-entry
  $menu_links['menu-elmsln-add_private-journal-entry:node/add/editorial-journal-entry'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_private-journal-entry:node/add/editorial-journal-entry',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-settings_configure-journal-exercises:admin/structure/taxonomy/editorial_exercise
  $menu_links['menu-elmsln-settings_configure-journal-exercises:admin/structure/taxonomy/editorial_exercise'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => 'admin/structure/taxonomy/editorial_exercise',
    'router_path' => 'admin/structure/taxonomy/%',
    'link_title' => 'Configure journal exercises',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_configure-journal-exercises:admin/structure/taxonomy/editorial_exercise',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-settings_blog-settings:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Configure journal exercises');
  t('Private Journal Entry');

  return $menu_links;
}
