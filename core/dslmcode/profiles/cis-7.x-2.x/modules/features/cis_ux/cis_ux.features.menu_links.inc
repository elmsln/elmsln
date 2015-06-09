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

  // Exported menu link: menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops
  $menu_links['menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'cis/courses/bulk_ops',
    'router_path' => 'cis/courses/bulk_ops',
    'link_title' => 'Bulk Ops',
    'options' => array(
      'attributes' => array(
        'title' => 'Course Bulk Operations',
      ),
      'identifier' => 'menu-cis-toolkit_bulk-ops:cis/courses/bulk_ops',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Bulk Ops');


  return $menu_links;
}
