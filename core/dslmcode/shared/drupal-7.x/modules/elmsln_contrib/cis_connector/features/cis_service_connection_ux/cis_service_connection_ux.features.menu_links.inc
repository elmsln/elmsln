<?php
/**
 * @file
 * cis_service_connection_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cis_service_connection_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-toolkit:admin/appearance
  $menu_links['menu-cis-toolkit:admin/appearance'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/appearance',
    'router_path' => 'admin/appearance',
    'link_title' => 'Theme',
    'options' => array(
      'attributes' => array(
        'title' => 'Change the course theme',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: menu-cis-toolkit:admin/config/development/performance
  $menu_links['menu-cis-toolkit:admin/config/development/performance'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/config/development/performance',
    'router_path' => 'admin/config/development/performance',
    'link_title' => 'Performance',
    'options' => array(
      'attributes' => array(
        'title' => 'Performance settings',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-45',
  );
  // Exported menu link: menu-cis-toolkit:admin/config/system/course-settings
  $menu_links['menu-cis-toolkit:admin/config/system/course-settings'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/config/system/course-settings',
    'router_path' => 'admin/config/system/course-settings',
    'link_title' => 'Course Settings',
    'options' => array(
      'attributes' => array(
        'title' => 'Settings related to the display of this course',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Course settings');
  t('Performance');
  t('Theme');


  return $menu_links;
}
