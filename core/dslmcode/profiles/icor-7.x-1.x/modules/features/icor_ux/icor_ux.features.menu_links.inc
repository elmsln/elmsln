<?php
/**
 * @file
 * icor_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function icor_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-cis-add_assembled-timeline:node/add/timeline
  $menu_links['menu-cis-add_assembled-timeline:node/add/timeline'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/timeline',
    'router_path' => 'node/add/timeline',
    'link_title' => 'Assembled timeline',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_assembled-timeline:node/add/timeline',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_file:file/add
  $menu_links['menu-cis-add_file:file/add'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'file/add',
    'router_path' => 'file/add',
    'link_title' => 'File',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_file:file/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_timeline-item:node/add/timeline-date
  $menu_links['menu-cis-add_timeline-item:node/add/timeline-date'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/timeline-date',
    'router_path' => 'node/add/timeline-date',
    'link_title' => 'Timeline item',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_timeline-item:node/add/timeline-date',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_zip-file:file/add/upload/archive
  $menu_links['menu-cis-add_zip-file:file/add/upload/archive'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'file/add/upload/archive',
    'router_path' => 'file/add/upload/archive',
    'link_title' => 'Zip file',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_zip-file:file/add/upload/archive',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-icor-navigation_object-listing:icor-object-lists
  $menu_links['menu-icor-navigation_object-listing:icor-object-lists'] = array(
    'menu_name' => 'menu-icor-navigation',
    'link_path' => 'icor-object-lists',
    'router_path' => 'icor-object-lists',
    'link_title' => 'Object listing',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-icor-navigation_object-listing:icor-object-lists',
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
  t('Assembled timeline');
  t('File');
  t('Object listing');
  t('Timeline item');
  t('Zip file');


  return $menu_links;
}
