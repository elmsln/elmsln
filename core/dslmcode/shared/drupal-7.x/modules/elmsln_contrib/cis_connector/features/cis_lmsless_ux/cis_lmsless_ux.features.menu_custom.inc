<?php
/**
 * @file
 * cis_lmsless_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function cis_lmsless_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-cis-user-profile.
  $menus['menu-cis-user-profile'] = array(
    'menu_name' => 'menu-cis-user-profile',
    'title' => 'User Profile',
    'description' => 'CIS user profile menu items',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('CIS user profile menu items');
  t('User Profile');


  return $menus;
}
