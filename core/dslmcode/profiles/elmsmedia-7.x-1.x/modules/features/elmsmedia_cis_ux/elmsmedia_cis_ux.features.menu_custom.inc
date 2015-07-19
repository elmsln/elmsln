<?php
/**
 * @file
 * elmsmedia_cis_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function elmsmedia_cis_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-elmsmedia-navigation.
  $menus['menu-elmsmedia-navigation'] = array(
    'menu_name' => 'menu-elmsmedia-navigation',
    'title' => 'ELMSMedia navigation',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('ELMSMedia navigation');


  return $menus;
}
