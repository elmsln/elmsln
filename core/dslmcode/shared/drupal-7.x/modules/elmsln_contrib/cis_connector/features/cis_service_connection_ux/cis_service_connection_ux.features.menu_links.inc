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

  // Exported menu link: menu-course-tools-menu_analytics:admin/reports/course-analytics
  $menu_links['menu-course-tools-menu_analytics:admin/reports/course-analytics'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/reports/course-analytics',
    'router_path' => '',
    'link_title' => 'Analytics',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-course-tools-menu_analytics:admin/reports/course-analytics',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_course-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_course-tools:<nolink>
  $menu_links['menu-course-tools-menu_course-tools:<nolink>'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Course tools',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-course-tools-menu_course-tools:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-course-tools-menu_performance:admin/config/development/performance
  $menu_links['menu-course-tools-menu_performance:admin/config/development/performance'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/config/development/performance',
    'router_path' => 'admin/config/development/performance',
    'link_title' => 'Performance',
    'options' => array(
      'attributes' => array(
        'title' => 'Performance settings',
      ),
      'identifier' => 'menu-course-tools-menu_performance:admin/config/development/performance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_course-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_sections-list:cis/section-list
  $menu_links['menu-course-tools-menu_sections-list:cis/section-list'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'cis/section-list',
    'router_path' => '',
    'link_title' => 'Sections List',
    'options' => array(
      'attributes' => array(
        'title' => 'Listing of all sections in this area',
      ),
      'identifier' => 'menu-course-tools-menu_sections-list:cis/section-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 1,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_service-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_sections:cis/section-list
  $menu_links['menu-course-tools-menu_sections:cis/section-list'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'cis/section-list',
    'router_path' => 'cis/section-list',
    'link_title' => 'Sections',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-course-tools-menu_sections:cis/section-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_service-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_service-tools:<nolink>
  $menu_links['menu-course-tools-menu_service-tools:<nolink>'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Service Tools',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-course-tools-menu_service-tools:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-course-tools-menu_settings:admin/config/system/course-settings
  $menu_links['menu-course-tools-menu_settings:admin/config/system/course-settings'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/config/system/course-settings',
    'router_path' => 'admin/config/system/course-settings',
    'link_title' => 'Settings',
    'options' => array(
      'attributes' => array(
        'title' => 'Course display configuration',
      ),
      'identifier' => 'menu-course-tools-menu_settings:admin/config/system/course-settings',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_course-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_theme:admin/appearance
  $menu_links['menu-course-tools-menu_theme:admin/appearance'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/appearance',
    'router_path' => 'admin/appearance',
    'link_title' => 'Theme',
    'options' => array(
      'attributes' => array(
        'title' => 'Change the course theme',
      ),
      'identifier' => 'menu-course-tools-menu_theme:admin/appearance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_course-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_users:cis/user-list
  $menu_links['menu-course-tools-menu_users:cis/user-list'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'cis/user-list',
    'router_path' => 'cis/user-list',
    'link_title' => 'Users',
    'options' => array(
      'identifier' => 'menu-course-tools-menu_users:cis/user-list',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_service-tools:<nolink>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Analytics');
  t('Course tools');
  t('Performance');
  t('Sections');
  t('Sections List');
  t('Service Tools');
  t('Settings');
  t('Theme');
  t('Users');


  return $menu_links;
}
