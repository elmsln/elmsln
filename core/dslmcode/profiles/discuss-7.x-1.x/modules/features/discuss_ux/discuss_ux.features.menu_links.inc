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

  // Exported menu link: menu-cis-add_create-new-thread:thread/add
  $menu_links['menu-cis-add_create-new-thread:thread/add'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'thread/add',
    'router_path' => 'thread/add',
    'link_title' => 'Create new thread',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_create-new-thread:thread/add',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Create new thread');


  return $menu_links;
}
