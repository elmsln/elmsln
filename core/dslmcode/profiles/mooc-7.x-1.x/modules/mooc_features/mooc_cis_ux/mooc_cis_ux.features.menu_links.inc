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

  // Exported menu link: menu-course-tools-menu_content-tool:<nolink>
  $menu_links['menu-course-tools-menu_content-tool:<nolink>'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Content tool',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-course-tools-menu_import-content-outline:import/feeds_node_helper_book_import
  $menu_links['menu-course-tools-menu_import-content-outline:import/feeds_node_helper_book_import'] = array(
    'menu_name' => 'menu-course-tools-menu',
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
      'identifier' => 'menu-course-tools-menu_import-content-outline:import/feeds_node_helper_book_import',
      'fa_icon' => 'page',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_outline-designer:admin/content/book
  $menu_links['menu-course-tools-menu_outline-designer:admin/content/book'] = array(
    'menu_name' => 'menu-course-tools-menu',
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
      'identifier' => 'menu-course-tools-menu_outline-designer:admin/content/book',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_search-and-replace:admin/content/scanner
  $menu_links['menu-course-tools-menu_search-and-replace:admin/content/scanner'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/content/scanner',
    'router_path' => 'admin/content/scanner',
    'link_title' => 'Search and Replace',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-course-tools-menu_search-and-replace:admin/content/scanner',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Content tool');
  t('Import content outline');
  t('Outline Designer');
  t('Search and Replace');

  return $menu_links;
}
