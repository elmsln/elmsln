<?php
/**
 * @file
 * icor_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function icor_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-icor-navigation_object-listing:icor-object-lists
  $menu_links['menu-icor-navigation_object-listing:icor-object-lists'] = array(
    'menu_name' => 'menu-icor-navigation',
    'link_path' => 'icor-object-lists',
    'router_path' => 'icor-object-lists',
    'link_title' => 'Object listing',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-icor-navigation_object-listing:icor-object-lists',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Object listing');


  return $menu_links;
}
