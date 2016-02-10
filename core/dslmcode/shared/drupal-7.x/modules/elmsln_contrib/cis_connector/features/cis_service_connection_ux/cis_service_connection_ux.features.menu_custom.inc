<?php
/**
 * @file
 * cis_service_connection_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cis_service_connection_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-elmsln-add.
  $menus['menu-elmsln-add'] = array(
    'menu_name' => 'menu-elmsln-add',
    'title' => 'Add menu',
    'description' => 'Menu that has content users can add to the system',
  );
  // Exported menu: menu-elmsln-navigation.
  $menus['menu-elmsln-navigation'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'title' => 'Navigation menu',
    'description' => 'Navigational links for using this tool',
  );
  // Exported menu: menu-elmsln-settings.
  $menus['menu-elmsln-settings'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'title' => 'Settings menu',
    'description' => 'Modify settings with your course network or this tool',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add menu');
  t('Menu that has content users can add to the system');
  t('Modify settings with your course network or this tool');
  t('Navigation menu');
  t('Navigational links for using this tool');
  t('Settings menu');


  return $menus;
}
