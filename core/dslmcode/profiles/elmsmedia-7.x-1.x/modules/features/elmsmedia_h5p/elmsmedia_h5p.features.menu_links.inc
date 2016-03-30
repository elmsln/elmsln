<?php
/**
 * @file
 * elmsmedia_h5p.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function elmsmedia_h5p_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_h5p:node/add/h5p-content
  $menu_links['menu-elmsln-add_h5p:node/add/h5p-content'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/h5p-content',
    'router_path' => 'node/add/h5p-content',
    'link_title' => 'H5P',
    'options' => array(
      'identifier' => 'menu-elmsln-add_h5p:node/add/h5p-content',
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
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('H5P');

  return $menu_links;
}
