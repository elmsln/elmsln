<?php
/**
 * @file
 * icor_jmol.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function icor_jmol_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_jmol:node/add/jmol
  $menu_links['menu-elmsln-add_jmol:node/add/jmol'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/jmol',
    'router_path' => 'node/add/jmol',
    'link_title' => 'JMOL',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_jmol:node/add/jmol',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('JMOL');

  return $menu_links;
}
