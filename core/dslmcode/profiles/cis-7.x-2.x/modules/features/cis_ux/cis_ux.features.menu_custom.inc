<?php
/**
 * @file
 * cis_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cis_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-elmsln-main-navigation.
  $menus['menu-elmsln-main-navigation'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'title' => 'CIS Toolkit',
    'description' => 'Links for using CIS',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('CIS Toolkit');
  t('Links for using CIS');


  return $menus;
}
