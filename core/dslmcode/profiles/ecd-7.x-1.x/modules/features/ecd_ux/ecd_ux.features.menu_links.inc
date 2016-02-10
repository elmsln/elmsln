<?php
/**
 * @file
 * ecd_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function ecd_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_course-access-request:eform/submit/course-access-request
  $menu_links['menu-elmsln-add_course-access-request:eform/submit/course-access-request'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'eform/submit/course-access-request',
    'router_path' => 'eform/submit/%',
    'link_title' => 'Course access request',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_course-access-request:eform/submit/course-access-request',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_system-access-request:eform/submit/system-access-request
  $menu_links['menu-elmsln-add_system-access-request:eform/submit/system-access-request'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'eform/submit/system-access-request',
    'router_path' => 'eform/submit/%',
    'link_title' => 'System access request',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_system-access-request:eform/submit/system-access-request',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_asset-compliance:asset-compliance
  $menu_links['menu-elmsln-navigation_asset-compliance:asset-compliance'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'asset-compliance',
    'router_path' => 'asset-compliance',
    'link_title' => 'Asset Compliance',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_asset-compliance:asset-compliance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_course-list:courses
  $menu_links['menu-elmsln-navigation_course-list:courses'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'courses',
    'router_path' => 'courses',
    'link_title' => 'Course list',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_course-list:courses',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_system-access-requests:admin/structure/entityform_types/manage/system_access_request/submissions
  $menu_links['menu-elmsln-navigation_system-access-requests:admin/structure/entityform_types/manage/system_access_request/submissions'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'admin/structure/entityform_types/manage/system_access_request/submissions',
    'router_path' => 'admin/structure/entityform_types/manage/%/submissions',
    'link_title' => 'System access requests',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_system-access-requests:admin/structure/entityform_types/manage/system_access_request/submissions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Asset Compliance');
  t('Course access request');
  t('Course list');
  t('System access request');
  t('System access requests');

  return $menu_links;
}
