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

  // Exported menu link: menu-cis-toolkit_footer-text:admin/structure/block/manage/boxes/site_footer/configure
  $menu_links['menu-cis-toolkit_footer-text:admin/structure/block/manage/boxes/site_footer/configure'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/structure/block/manage/boxes/site_footer/configure',
    'router_path' => 'admin/structure/block/manage/%/%/configure',
    'link_title' => 'Footer text',
    'options' => array(
      'attributes' => array(
        'title' => 'Edit footer text',
      ),
      'identifier' => 'menu-cis-toolkit_footer-text:admin/structure/block/manage/boxes/site_footer/configure',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-toolkit_instructional-outline:admin/content/book
  $menu_links['menu-cis-toolkit_instructional-outline:admin/content/book'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/content/book',
    'router_path' => 'admin/content/book',
    'link_title' => 'Instructional outline',
    'options' => array(
      'attributes' => array(
        'title' => 'Outline designer for establishing the instructional pacing of this course.',
      ),
      'identifier' => 'menu-cis-toolkit_instructional-outline:admin/content/book',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_search--replace:admin/content/scanner
  $menu_links['menu-cis-toolkit_search--replace:admin/content/scanner'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'admin/content/scanner',
    'router_path' => 'admin/content/scanner',
    'link_title' => 'Search / Replace',
    'options' => array(
      'attributes' => array(
        'title' => 'Search and replace text across content',
      ),
      'identifier' => 'menu-cis-toolkit_search--replace:admin/content/scanner',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 0,
  );
  // Exported menu link: menu-cis-toolkit_typo-reports:typo-reports
  $menu_links['menu-cis-toolkit_typo-reports:typo-reports'] = array(
    'menu_name' => 'menu-cis-toolkit',
    'link_path' => 'typo-reports',
    'router_path' => 'typo-reports',
    'link_title' => 'Typo Reports',
    'options' => array(
      'attributes' => array(
        'title' => 'Typographical errors as reported by other members of the content team',
      ),
      'identifier' => 'menu-cis-toolkit_typo-reports:typo-reports',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -44,
    'customized' => 0,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Footer text');
  t('Instructional outline');
  t('Search / Replace');
  t('Typo Reports');


  return $menu_links;
}
