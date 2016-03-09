<?php
/**
 * @file
 * cle_critique.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cle_critique_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-navigation_give-feedback:cle/critique/critique-peer
  $menu_links['menu-elmsln-navigation_give-feedback:cle/critique/critique-peer'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'cle/critique/critique-peer',
    'router_path' => 'cle/critique/critique-peer',
    'link_title' => 'Give feedback',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-navigation_give-feedback:cle/critique/critique-peer',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-navigation_critique:cle/critique',
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Give feedback');

  return $menu_links;
}
