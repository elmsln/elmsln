<?php
/**
 * @file
 * mooc_cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mooc_cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-settings_content-tools:<nolink>
  $menu_links['menu-elmsln-settings_content-tools:<nolink>'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Content Tools',
    'options' => array(
      'identifier' => 'menu-elmsln-settings_content-tools:<nolink>',
      'fa_icon' => 'page',
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-settings_import-content-outline:import/feeds_node_helper_book_import
  $menu_links['menu-elmsln-settings_import-content-outline:import/feeds_node_helper_book_import'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => 'import/feeds_node_helper_book_import',
    'router_path' => 'import/%',
    'link_title' => 'Import content outline',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_import-content-outline:import/feeds_node_helper_book_import',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-settings_content-tools:<nolink>',
  );
  // Exported menu link: menu-elmsln-settings_outline-designer:admin/content/book
  $menu_links['menu-elmsln-settings_outline-designer:admin/content/book'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => 'admin/content/book',
    'router_path' => 'admin/content/book',
    'link_title' => 'Outline Designer',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_outline-designer:admin/content/book',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-settings_content-tools:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content Tools');
  t('Import content outline');
  t('Outline Designer');

  return $menu_links;
}
