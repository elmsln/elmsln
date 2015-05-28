<?php
/**
 * @file
 * mooc_ux_defaults.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mooc_ux_defaults_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-toolkit:admin/content/scanner
  $menu_links['menu-cis-toolkit:admin/content/scanner'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/content/scanner',
    'router_path' => 'admin/content/scanner',
    'link_title' => 'Search / replace',
    'options' => array(
      'attributes' => array(
        'title' => 'Search and replace text across content',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Search / replace');


  return $menu_links;
}
