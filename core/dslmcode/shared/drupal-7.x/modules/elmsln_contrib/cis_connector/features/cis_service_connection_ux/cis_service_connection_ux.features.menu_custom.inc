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

  // Exported menu: menu-cis-add.
  $menus['menu-cis-add'] = array(
    'menu_name' => 'menu-cis-add',
    'title' => 'Add menu',
    'description' => 'Menu that has content users can add to the system',
  );
  // Exported menu: menu-course-tools-menu.
  $menus['menu-course-tools-menu'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'title' => 'Course Tools Menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add menu');
  t('Course Tools Menu');
  t('Menu that has content users can add to the system');


  return $menus;
}
