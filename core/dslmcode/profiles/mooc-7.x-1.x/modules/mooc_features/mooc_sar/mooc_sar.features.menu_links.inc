<?php
/**
 * @file
 * mooc_sar.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mooc_sar_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-course-tools-menu_search-and-replace:admin/content/book/sar
  $menu_links['menu-course-tools-menu_search-and-replace:admin/content/book/sar'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/content/book/sar',
    'router_path' => 'admin/content/book/sar',
    'link_title' => 'Search and Replace',
    'options' => array(
      'identifier' => 'menu-course-tools-menu_search-and-replace:admin/content/book/sar',
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
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_content-tools:<nolink>',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Search and Replace');

  return $menu_links;
}
