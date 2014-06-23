<?php
/**
 * @file
 * mooc_cis_ux.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function mooc_cis_ux_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-course-tools-menu.
  $menus['menu-course-tools-menu'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'title' => 'Course Tools Menu',
    'description' => '',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Course Tools Menu');


  return $menus;
}
