<?php
/**
 * @file
 * editorial_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function editorial_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-settings_blog-settings:<nolink>
  $menu_links['menu-elmsln-settings_blog-settings:<nolink>'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Blog settings',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_blog-settings:<nolink>',
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
  t('Blog settings');

  return $menu_links;
}
