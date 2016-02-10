<?php
/**
 * @file
 * icor_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function icor_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-elmsln-main-navigation.
  $menus['menu-elmsln-main-navigation'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'title' => 'ICOR navigation',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('ICOR navigation');


  return $menus;
}
