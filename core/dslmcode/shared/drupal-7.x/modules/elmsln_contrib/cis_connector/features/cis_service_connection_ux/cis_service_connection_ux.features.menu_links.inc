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

  // Exported menu link: menu-cis-toolkit_analytics:admin/reports/course-analytics
  $menu_links['menu-cis-toolkit_analytics:admin/reports/course-analytics'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/reports/course-analytics',
    'router_path' => 'admin/reports/course-analytics',
    'link_title' => 'Analytics',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-toolkit_analytics:admin/reports/course-analytics',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_course-tools:<nolink>',
  );
  // Exported menu link: menu-cis-toolkit_course-tools:<nolink>
  $menu_links['menu-cis-toolkit_course-tools:<nolink>'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Course tools',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-toolkit_course-tools:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_footer:admin/structure/block/manage/boxes/site_footer/configure
  $menu_links['menu-cis-toolkit_footer:admin/structure/block/manage/boxes/site_footer/configure'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/structure/block/manage/boxes/site_footer/configure',
    'router_path' => 'admin/structure/block/manage/%/%/configure',
    'link_title' => 'Footer',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-toolkit_footer:admin/structure/block/manage/boxes/site_footer/configure',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_course-tools:<nolink>',
  );
  // Exported menu link: menu-cis-toolkit_performance:admin/config/development/performance
  $menu_links['menu-cis-toolkit_performance:admin/config/development/performance'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/config/development/performance',
    'router_path' => 'admin/config/development/performance',
    'link_title' => 'Performance',
    'options' => array(
      'attributes' => array(
        'title' => 'Performance settings',
      ),
      'identifier' => 'menu-cis-toolkit_performance:admin/config/development/performance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_course-tools:<nolink>',
  );
  // Exported menu link: menu-cis-toolkit_sections-list:cis/section-list
  $menu_links['menu-cis-toolkit_sections-list:cis/section-list'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/section-list',
    'router_path' => 'cis/section-list',
    'link_title' => 'Sections list',
    'options' => array(
      'attributes' => array(
        'title' => 'Listing of all sections in this area',
      ),
      'identifier' => 'menu-cis-toolkit_sections-list:cis/section-list',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_service-tools:<nolink>',
  );
  // Exported menu link: menu-cis-toolkit_service-tools:<nolink>
  $menu_links['menu-cis-toolkit_service-tools:<nolink>'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Service Tools',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-toolkit_service-tools:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -43,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_settings:admin/config/system/course-settings
  $menu_links['menu-cis-toolkit_settings:admin/config/system/course-settings'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/config/system/course-settings',
    'router_path' => 'admin/config/system/course-settings',
    'link_title' => 'Settings',
    'options' => array(
      'attributes' => array(
        'title' => 'Settings related to the display of this course',
      ),
      'identifier' => 'menu-cis-toolkit_settings:admin/config/system/course-settings',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_course-tools:<nolink>',
  );
  // Exported menu link: menu-cis-toolkit_theme:admin/appearance
  $menu_links['menu-cis-toolkit_theme:admin/appearance'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/appearance',
    'router_path' => 'admin/appearance',
    'link_title' => 'Theme',
    'options' => array(
      'attributes' => array(
        'title' => 'Change the course theme',
      ),
      'identifier' => 'menu-cis-toolkit_theme:admin/appearance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-cis-toolkit_course-tools:<nolink>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Analytics');
  t('Course tools');
  t('Footer');
  t('Performance');
  t('Sections list');
  t('Service Tools');
  t('Settings');
  t('Theme');


  return $menu_links;
}
