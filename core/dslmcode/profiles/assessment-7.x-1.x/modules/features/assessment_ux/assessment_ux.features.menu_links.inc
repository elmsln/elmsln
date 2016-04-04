<?php
/**
 * @file
 * assessment_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function assessment_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-navigation_gradebook:gradebook/grid
  $menu_links['menu-elmsln-navigation_gradebook:gradebook/grid'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'gradebook/grid',
    'router_path' => 'gradebook/grid',
    'link_title' => 'Gradebook',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_gradebook:gradebook/grid',
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
  t('Gradebook');

  return $menu_links;
}
