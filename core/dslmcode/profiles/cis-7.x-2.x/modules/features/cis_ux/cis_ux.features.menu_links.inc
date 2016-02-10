<?php
/**
 * @file
 * cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-add_academic-area:node/add/academic-unit
  $menu_links['menu-cis-add_academic-area:node/add/academic-unit'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/academic-unit',
    'router_path' => 'node/add/academic-unit',
    'link_title' => 'Academic area',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-add_academic-area:node/add/academic-unit',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_global-resource:node/add/resource
  $menu_links['menu-cis-add_global-resource:node/add/resource'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/resource',
    'router_path' => 'node/add/resource',
    'link_title' => 'Global Resource',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-add_global-resource:node/add/resource',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_program:node/add/program
  $menu_links['menu-cis-add_program:node/add/program'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/program',
    'router_path' => 'node/add/program',
    'link_title' => 'Program',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-add_program:node/add/program',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-main-navigation_courses:courses/list
  $menu_links['menu-elmsln-main-navigation_courses:courses/list'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'link_path' => 'courses/list',
    'router_path' => 'courses',
    'link_title' => 'Courses',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-main-navigation_courses:courses/list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-main-navigation_offerings:cis/offerings/list
  $menu_links['menu-elmsln-main-navigation_offerings:cis/offerings/list'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'link_path' => 'cis/offerings/list',
    'router_path' => 'cis/offerings/list',
    'link_title' => 'Offerings',
    'options' => array(
      'identifier' => 'menu-elmsln-main-navigation_offerings:cis/offerings/list',
    ),
    'module' => 'system',
    'hidden' => -1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -1,
    'customized' => 0,
  );
  // Exported menu link: menu-elmsln-main-navigation_people:cis/admin/people
  $menu_links['menu-elmsln-main-navigation_people:cis/admin/people'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'link_path' => 'cis/admin/people',
    'router_path' => 'cis/admin/people',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(
        'title' => 'view all people in the system',
      ),
      'identifier' => 'menu-elmsln-main-navigation_people:cis/admin/people',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-elmsln-main-navigation_resources:cis/resources
  $menu_links['menu-elmsln-main-navigation_resources:cis/resources'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'link_path' => 'cis/resources',
    'router_path' => 'cis/resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all resources in the system',
      ),
      'identifier' => 'menu-elmsln-main-navigation_resources:cis/resources',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-main-navigation_setup-course-access:cis-quick-setup-access-id
  $menu_links['menu-elmsln-main-navigation_setup-course-access:cis-quick-setup-access-id'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'link_path' => 'cis-quick-setup-access-id',
    'router_path' => 'cis-quick-setup-access-id',
    'link_title' => 'Setup course access',
    'options' => array(
      'attributes' => array(
        'title' => 'Setup access to a space based on having the unique string.',
      ),
      'identifier' => 'menu-elmsln-main-navigation_setup-course-access:cis-quick-setup-access-id',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-course-tools-menu_admin:admin
  $menu_links['menu-course-tools-menu_admin:admin'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'admin',
    'router_path' => 'admin',
    'link_title' => 'Admin',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-course-tools-menu_admin:admin',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_administration-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_administration-tools:<nolink>
  $menu_links['menu-course-tools-menu_administration-tools:<nolink>'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Administration Tools',
    'options' => array(
      'identifier' => 'menu-course-tools-menu_administration-tools:<nolink>',
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => -49,
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
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_administration-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_sections-list:cis/section-list
  $menu_links['menu-course-tools-menu_sections-list:cis/section-list'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'cis/section-list',
    'router_path' => 'cis',
    'link_title' => 'Sections List',
    'options' => array(
      'attributes' => array(
        'title' => 'Listing of all sections in this area',
      ),
      'identifier' => 'menu-course-tools-menu_sections-list:cis/section-list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
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
    'weight' => -50,
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
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-course-tools-menu_administration-tools:<nolink>',
  );
  // Exported menu link: menu-course-tools-menu_users:cis/user-list
  $menu_links['menu-course-tools-menu_users:cis/user-list'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'cis/user-list',
    'router_path' => 'cis',
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
  t('Academic area');
  t('Admin');
  t('Administration Tools');
  t('Courses');
  t('Global Resource');
  t('Offerings');
  t('People');
  t('Performance');
  t('Program');
  t('Resources');
  t('Sections List');
  t('Service Tools');
  t('Settings');
  t('Setup course access');
  t('Users');

  return $menu_links;
}
