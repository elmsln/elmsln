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

  // Exported menu: menu-cis-toolkit.
  $menus['menu-cis-toolkit'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'title' => 'Toolkit',
    'description' => 'Site toolkit',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Site toolkit');
  t('Toolkit');


  return $menus;
}
