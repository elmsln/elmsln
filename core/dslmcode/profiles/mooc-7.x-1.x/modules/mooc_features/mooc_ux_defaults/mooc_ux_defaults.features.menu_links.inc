<?php
/**
 * @file
 * mooc_ux_defaults.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function mooc_ux_defaults_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: management_simplify:admin/config/user-interface/simplify
  $menu_links['management_simplify:admin/config/user-interface/simplify'] = array(
    'menu_name' => 'management',
    'link_path' => 'admin/config/user-interface/simplify',
    'router_path' => 'admin/config/user-interface/simplify',
    'link_title' => 'Simplify',
    'options' => array(
      'attributes' => array(
        'title' => 'Configure hidden fields globally.',
      ),
      'identifier' => 'management_simplify:admin/config/user-interface/simplify',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
    'parent_identifier' => 'management_user-interface:admin/config/user-interface',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Simplify');

  return $menu_links;
}
