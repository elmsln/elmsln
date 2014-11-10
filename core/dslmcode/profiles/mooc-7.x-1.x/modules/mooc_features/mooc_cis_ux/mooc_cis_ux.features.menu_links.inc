<?php
/**
 * @file
 * mooc_cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mooc_cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-course-tools-menu_content-tool:<nolink>
  $menu_links['menu-course-tools-menu_content-tool:<nolink>'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Content tool',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
    'customized' => 1,
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
  // Exported menu link: menu-course-tools-menu_footer:admin/structure/block/manage/boxes/site_footer/configure
  $menu_links['menu-course-tools-menu_footer:admin/structure/block/manage/boxes/site_footer/configure'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/structure/block/manage/boxes/site_footer/configure',
    'router_path' => 'admin/structure/block/manage/%/%/configure',
    'link_title' => 'Footer',
    'options' => array(
      'attributes' => array(
        'title' => 'Edit the site footer block',
      ),
      'identifier' => 'menu-course-tools-menu_footer:admin/structure/block/manage/boxes/site_footer/configure',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_course-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_instructional-outline:admin/content/book
  $menu_links['menu-course-tools-menu_instructional-outline:admin/content/book'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/content/book',
    'router_path' => 'admin/content/book',
    'link_title' => 'Instructional Outline',
    'options' => array(
      'attributes' => array(
        'title' => 'Outline designer for establishing the instructional pacing of this course.',
      ),
      'identifier' => 'menu-course-tools-menu_instructional-outline:admin/content/book',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
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
  // Exported menu link: menu-course-tools-menu_search--replace:admin/content/scanner
  $menu_links['menu-course-tools-menu_search--replace:admin/content/scanner'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin/content/scanner',
    'router_path' => 'admin/content/scanner',
    'link_title' => 'Search / Replace',
    'options' => array(
      'attributes' => array(
        'title' => 'Search and replace text within content',
      ),
      'identifier' => 'menu-course-tools-menu_search--replace:admin/content/scanner',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
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
    'weight' => 0,
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
  // Exported menu link: menu-course-tools-menu_typo-reports:typo-reports
  $menu_links['menu-course-tools-menu_typo-reports:typo-reports'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'typo-reports',
    'router_path' => 'typo-reports',
    'link_title' => 'Typo Reports',
    'options' => array(
      'attributes' => array(
        'title' => 'Reported typographical errors in content',
      ),
      'identifier' => 'menu-course-tools-menu_typo-reports:typo-reports',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_content-tool:<nolink>',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Content tool');
  t('Course tools');
  t('Footer');
  t('Instructional Outline');
  t('Performance');
  t('Search / Replace');
  t('Sections');
  t('Service Tools');
  t('Settings');
  t('Theme');
  t('Typo Reports');


  return $menu_links;
}
