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
  // Translatables
  // Included for use with string extractors like potx.
  t('Content tool');
  t('Instructional Outline');
  t('Search / Replace');


  return $menu_links;
}
