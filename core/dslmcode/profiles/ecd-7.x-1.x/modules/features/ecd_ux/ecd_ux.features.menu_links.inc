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
    'link_title' => 'Course access',
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
    'link_title' => 'System access',
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
  // Exported menu link: menu-elmsln-navigation_access-requests:admin/structure/entityform_types/manage/course_access_request/submissions
  $menu_links['menu-elmsln-navigation_access-requests:admin/structure/entityform_types/manage/course_access_request/submissions'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'admin/structure/entityform_types/manage/course_access_request/submissions',
    'router_path' => 'admin/structure/entityform_types/manage/%/submissions',
    'link_title' => 'Access requests',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_access-requests:admin/structure/entityform_types/manage/course_access_request/submissions',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-navigation_courses:courses',
  );
  // Exported menu link: menu-elmsln-navigation_bulk-update:courses/bulk-update
  $menu_links['menu-elmsln-navigation_bulk-update:courses/bulk-update'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'courses/bulk-update',
    'router_path' => 'courses/bulk-update',
    'link_title' => 'Bulk update',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_bulk-update:courses/bulk-update',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-navigation_courses:courses',
  );
  // Exported menu link: menu-elmsln-navigation_compliance:courses/compliance
  $menu_links['menu-elmsln-navigation_compliance:courses/compliance'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'courses/compliance',
    'router_path' => 'courses/compliance',
    'link_title' => 'Compliance',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_compliance:courses/compliance',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-navigation_courses:courses',
  );
  // Exported menu link: menu-elmsln-navigation_courses:courses
  $menu_links['menu-elmsln-navigation_courses:courses'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'courses',
    'router_path' => 'courses',
    'link_title' => 'Courses',
    'options' => array(
      'identifier' => 'menu-elmsln-navigation_courses:courses',
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
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Access requests');
  t('Bulk update');
  t('Compliance');
  t('Course access');
  t('Courses');
  t('System access');

  return $menu_links;
}
