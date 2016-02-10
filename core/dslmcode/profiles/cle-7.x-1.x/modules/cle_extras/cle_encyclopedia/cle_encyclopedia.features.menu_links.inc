<?php
/**
 * @file
 * cle_encyclopedia.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cle_encyclopedia_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_encyclopedia-entry:node/add/cle-encyclopedia-entry
  $menu_links['menu-elmsln-add_encyclopedia-entry:node/add/cle-encyclopedia-entry'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/cle-encyclopedia-entry',
    'router_path' => 'node/add/cle-encyclopedia-entry',
    'link_title' => 'Encyclopedia entry',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_encyclopedia-entry:node/add/cle-encyclopedia-entry',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-main-navigation_encyclopedia:cle/encyclopedia
  $menu_links['menu-elmsln-main-navigation_encyclopedia:cle/encyclopedia'] = array(
    'menu_name' => 'menu-elmsln-main-navigation',
    'link_path' => 'cle/encyclopedia',
    'router_path' => 'cle/encyclopedia',
    'link_title' => 'Encyclopedia',
    'options' => array(
      'identifier' => 'menu-elmsln-main-navigation_encyclopedia:cle/encyclopedia',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 0,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Encyclopedia');
  t('Encyclopedia entry');

  return $menu_links;
}
