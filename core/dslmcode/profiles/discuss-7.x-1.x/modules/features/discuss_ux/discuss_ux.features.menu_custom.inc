<?php
/**
 * @file
 * discuss_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function discuss_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-elmsln-main-navigation.
  $menus['menu-elmsln-main-navigation'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'title' => 'Discuss navigation',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Discuss navigation');


  return $menus;
}
