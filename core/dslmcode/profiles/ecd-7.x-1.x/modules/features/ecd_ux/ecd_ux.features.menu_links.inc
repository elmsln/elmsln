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

  // Exported menu link: menu-comply-navigation_asset-compliance:asset-compliance
  $menu_links['menu-comply-navigation_asset-compliance:asset-compliance'] = array(
    'menu_name' => 'menu-comply-navigation',
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
      'identifier' => 'menu-comply-navigation_asset-compliance:asset-compliance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-comply-navigation_course-compliance:course-compliance
  $menu_links['menu-comply-navigation_course-compliance:course-compliance'] = array(
    'menu_name' => 'menu-comply-navigation',
    'link_path' => 'course-compliance',
    'router_path' => 'course-compliance',
    'link_title' => 'Course compliance',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-comply-navigation_course-compliance:course-compliance',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-comply-navigation_course-list:courses
  $menu_links['menu-comply-navigation_course-list:courses'] = array(
    'menu_name' => 'menu-comply-navigation',
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
      'identifier' => 'menu-comply-navigation_course-list:courses',
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
  t('Course compliance');
  t('Course list');


  return $menu_links;
}
