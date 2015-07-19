<?php
/**
 * @file
 * ecd_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function ecd_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-comply-navigation.
  $menus['menu-comply-navigation'] = array(
    'menu_name' => 'menu-comply-navigation',
    'title' => 'Comply Navigation',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Comply Navigation');


  return $menus;
}
