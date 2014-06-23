<?php
/**
 * @file
 * cis_lmsless_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cis_lmsless_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-user-profile_logout:user/logout
  $menu_links['menu-cis-user-profile_logout:user/logout'] = array(
    'menu_name' => 'menu-cis-user-profile',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Logout',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-user-profile_logout:user/logout',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-user-profile_profile:user
  $menu_links['menu-cis-user-profile_profile:user'] = array(
    'menu_name' => 'menu-cis-user-profile',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'Profile',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-user-profile_profile:user',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Logout');
  t('Profile');


  return $menu_links;
}
