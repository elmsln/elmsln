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

  // Exported menu link: menu-elmsln-add_assembled-timeline:node/add/timeline
  $menu_links['menu-elmsln-add_assembled-timeline:node/add/timeline'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_assembled-timeline:node/add/timeline',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_file:file/add
  $menu_links['menu-elmsln-add_file:file/add'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_file:file/add',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_timeline-item:node/add/timeline-date
  $menu_links['menu-elmsln-add_timeline-item:node/add/timeline-date'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_timeline-item:node/add/timeline-date',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_zip-file:file/add/upload/archive
  $menu_links['menu-elmsln-add_zip-file:file/add/upload/archive'] = array(
    'menu_name' => 'menu-elmsln-add',
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
      'identifier' => 'menu-elmsln-add_zip-file:file/add/upload/archive',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assembled timeline');
  t('File');
  t('Timeline item');
  t('Zip file');

  return $menu_links;
}
