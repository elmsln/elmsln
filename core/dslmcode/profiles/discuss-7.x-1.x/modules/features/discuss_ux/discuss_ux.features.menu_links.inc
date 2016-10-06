<?php
/**
 * @file
 * discuss_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function discuss_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_thread:thread/add.
  $menu_links['menu-elmsln-add_thread:thread/add'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'thread/add',
    'router_path' => 'thread/add',
    'link_title' => 'Thread',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_thread:thread/add',
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
  t('Thread');

  return $menu_links;
}
