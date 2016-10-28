<?php
/**
 * @file
 * cle_cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cle_cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_assignment:node/add/cle-assignment.
  $menu_links['menu-elmsln-add_assignment:node/add/cle-assignment'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/cle-assignment',
    'router_path' => 'node/add/cle-assignment',
    'link_title' => 'Assignment',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_assignment:node/add/cle-assignment',
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
  t('Assignment');

  return $menu_links;
}
