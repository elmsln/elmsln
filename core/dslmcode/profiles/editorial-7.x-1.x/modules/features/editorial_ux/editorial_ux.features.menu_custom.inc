<?php
/**
 * @file
 * editorial_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function editorial_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-editorial-navigation.
  $menus['menu-editorial-navigation'] = array(
    'menu_name' => 'menu-editorial-navigation',
    'title' => 'Editorial Navigation',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Editorial Navigation');


  return $menus;
}
