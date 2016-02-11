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

  // Exported menu link: menu-elmsln-add_academic-area:node/add/academic-unit
  $menu_links['menu-elmsln-add_academic-area:node/add/academic-unit'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/academic-unit',
    'router_path' => 'node/add/academic-unit',
    'link_title' => 'Academic area',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-add_academic-area:node/add/academic-unit',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_global-resource:node/add/resource
  $menu_links['menu-elmsln-add_global-resource:node/add/resource'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/resource',
    'router_path' => 'node/add/resource',
    'link_title' => 'Global Resource',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-add_global-resource:node/add/resource',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_program:node/add/program
  $menu_links['menu-elmsln-add_program:node/add/program'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/program',
    'router_path' => 'node/add/program',
    'link_title' => 'Program',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-add_program:node/add/program',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_courses:courses/list
  $menu_links['menu-elmsln-navigation_courses:courses/list'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'courses/list',
    'router_path' => 'courses',
    'link_title' => 'Courses',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-navigation_courses:courses/list',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_resources:cis/resources
  $menu_links['menu-elmsln-navigation_resources:cis/resources'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'cis/resources',
    'router_path' => 'cis/resources',
    'link_title' => 'Resources',
    'options' => array(
      'attributes' => array(
        'title' => 'List of all resources in the system',
      ),
      'identifier' => 'menu-elmsln-navigation_resources:cis/resources',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_setup-course-access:cis-quick-setup-access-id
  $menu_links['menu-elmsln-navigation_setup-course-access:cis-quick-setup-access-id'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'cis-quick-setup-access-id',
    'router_path' => 'cis-quick-setup-access-id',
    'link_title' => 'Setup course access',
    'options' => array(
      'attributes' => array(
        'title' => 'Setup access to a space based on having the unique string.',
      ),
      'identifier' => 'menu-elmsln-navigation_setup-course-access:cis-quick-setup-access-id',
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
  t('Program');
  t('Resources');
  t('Setup course access');

  return $menu_links;
}
