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
  // Exported menu link: menu-cis-toolkit_courses:courses/list
  $menu_links['menu-cis-toolkit_courses:courses/list'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'courses/list',
    'router_path' => 'courses',
    'link_title' => 'Courses',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-toolkit_courses:courses/list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_look-up-instructor-sections:psu_get_course_list
  $menu_links['menu-cis-toolkit_look-up-instructor-sections:psu_get_course_list'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'psu_get_course_list',
    'router_path' => 'psu_get_course_list',
    'link_title' => 'Look up instructor sections',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-cis-toolkit_look-up-instructor-sections:psu_get_course_list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_people:cis/admin/people
  $menu_links['menu-cis-toolkit_people:cis/admin/people'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/admin/people',
    'router_path' => 'cis/admin/people',
    'link_title' => 'People',
    'options' => array(
      'attributes' => array(
        'title' => 'view all people in the system',
      ),
      'identifier' => 'menu-cis-toolkit_people:cis/admin/people',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_resources:cis/resources
  $menu_links['menu-cis-toolkit_resources:cis/resources'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/resources',
    'router_path' => 'cis/resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all resources in the system',
      ),
      'identifier' => 'menu-cis-toolkit_resources:cis/resources',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_setup-course-access:cis-quick-setup-access-id
  $menu_links['menu-cis-toolkit_setup-course-access:cis-quick-setup-access-id'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis-quick-setup-access-id',
    'router_path' => 'cis-quick-setup-access-id',
    'link_title' => 'Setup course access',
    'options' => array(
      'attributes' => array(
        'title' => 'Setup access to a space based on having the unique string.',
      ),
      'identifier' => 'menu-cis-toolkit_setup-course-access:cis-quick-setup-access-id',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Academic area');
  t('Courses');
  t('Global Resource');
  t('Look up instructor sections');
  t('People');
  t('Program');
  t('Resources');
  t('Setup course access');

  return $menu_links;
}
