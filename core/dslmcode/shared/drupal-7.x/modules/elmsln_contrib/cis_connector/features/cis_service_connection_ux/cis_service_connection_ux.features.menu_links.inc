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
    'weight' => -48,
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
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-course-tools-menu_sections-list:cis/section-list
  $menu_links['menu-course-tools-menu_sections-list:cis/section-list'] = array(
    'menu_name' => 'menu-course-tools-menu',
    'link_path' => 'cis/section-list',
    'router_path' => 'cis/section-list',
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
    'weight' => 0,
    'customized' => 1,
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
  t('Admin');
  t('Administration Tools');
  t('Sections List');
  t('Service Tools');
  t('Users');

  return $menu_links;
}
