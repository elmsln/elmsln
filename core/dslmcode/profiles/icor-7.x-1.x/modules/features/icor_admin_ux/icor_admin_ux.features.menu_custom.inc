<?php
/**
 * @file
 * icor_admin_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function icor_admin_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-icor-toolkit.
  $menus['menu-icor-toolkit'] = array(
    'menu_name' => 'menu-icor-toolkit',
    'title' => 'ICOR Toolkit',
    'description' => 'Admin toolkit of links for ICOR UX',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Admin toolkit of links for ICOR UX');
  t('ICOR Toolkit');


  return $menus;
}
