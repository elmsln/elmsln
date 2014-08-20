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
  // Exported menu link: management_add-course:node/add/course
  $menu_links['management_add-course:node/add/course'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/course',
    'router_path' => 'node/add/course',
    'link_title' => 'Add Course',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a course to CIS',
      ),
      'identifier' => 'management_add-course:node/add/course',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 27,
    'customized' => 0,
    'parent_identifier' => 'management_courses:cis/courses',
  );
  // Exported menu link: management_add-program:node/add/program
  $menu_links['management_add-program:node/add/program'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/program',
    'router_path' => 'node/add/program',
    'link_title' => 'Add Program',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a Program of study',
      ),
      'identifier' => 'management_add-program:node/add/program',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 29,
    'customized' => 0,
    'parent_identifier' => 'management_programs:cis/programs',
  );
  // Exported menu link: management_add-resource:node/add/resource
  $menu_links['management_add-resource:node/add/resource'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/resource',
    'router_path' => 'node/add/resource',
    'link_title' => 'Add Resource',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a new resource for use in courses',
      ),
      'identifier' => 'management_add-resource:node/add/resource',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_resources:cis/resources',
  );
  // Exported menu link: management_add-service:node/add/service
  $menu_links['management_add-service:node/add/service'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/service',
    'router_path' => 'node/add/service',
    'link_title' => 'Add Service',
    'options' => array(
      'attributes' => array(
        'title' => 'Add a Service for courses to use',
      ),
      'identifier' => 'management_add-service:node/add/service',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 30,
    'customized' => 0,
    'parent_identifier' => 'management_services:cis/services',
  );
  // Exported menu link: management_add-unit:node/add/academic-unit
  $menu_links['management_add-unit:node/add/academic-unit'] = array(
    'menu_name' => 'management',
    'link_path' => 'node/add/academic-unit',
    'router_path' => 'node/add/academic-unit',
    'link_title' => 'Add Unit',
    'options' => array(
      'attributes' => array(
        'title' => 'Add an academic unit',
      ),
      'identifier' => 'management_add-unit:node/add/academic-unit',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 27,
    'customized' => 0,
    'parent_identifier' => 'management_units:cis/units',
  );
  // Exported menu link: management_admin:cis/admin
  $menu_links['management_admin:cis/admin'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/admin',
    'router_path' => 'cis',
    'link_title' => 'Admin',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'management_admin:cis/admin',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -42,
    'customized' => 1,
    'parent_identifier' => 'management_cis:cis',
  );
  // Exported menu link: management_manage-semester:cis/offerings/manage-semester
  $menu_links['management_manage-semester:cis/offerings/manage-semester'] = array(
    'menu_name' => 'management',
    'link_path' => 'cis/offerings/manage-semester',
    'router_path' => 'cis/offerings',
    'link_title' => 'Manage Semester',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'management_manage-semester:cis/offerings/manage-semester',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'management_offerings:cis/offerings',
  );
  // Exported menu link: user-menu_log-out:user/logout
  $menu_links['user-menu_log-out:user/logout'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user/logout',
    'router_path' => 'user/logout',
    'link_title' => 'Log out',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'user-menu_log-out:user/logout',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: user-menu_login:login
  $menu_links['user-menu_login:login'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'login',
    'router_path' => 'login',
    'link_title' => 'Login',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'user-menu_login:login',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: user-menu_user-account:user
  $menu_links['user-menu_user-account:user'] = array(
    'menu_name' => 'user-menu',
    'link_path' => 'user',
    'router_path' => 'user',
    'link_title' => 'User account',
    'options' => array(
      'alter' => TRUE,
      'attributes' => array(),
      'identifier' => 'user-menu_user-account:user',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Add Course');
  t('Add Program');
  t('Add Resource');
  t('Add Service');
  t('Add Unit');
  t('Admin');
  t('Log out');
  t('Login');
  t('Manage Semester');
  t('User account');

  return $menu_links;
}
