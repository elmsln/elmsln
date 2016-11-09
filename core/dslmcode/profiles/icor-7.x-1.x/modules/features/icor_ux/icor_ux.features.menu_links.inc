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

  // Exported menu link: menu-elmsln-add_file:file/add.
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
    'weight' => -44,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_jmol:node/add/jmol.
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
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_map-point:node/add/map-point.
  $menu_links['menu-elmsln-add_map-point:node/add/map-point'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/map-point',
    'router_path' => 'node/add/map-point',
    'link_title' => 'Map point',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_map-point:node/add/map-point',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_map:node/add/map.
  $menu_links['menu-elmsln-add_map:node/add/map'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/map',
    'router_path' => 'node/add/map',
    'link_title' => 'Map',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_map:node/add/map',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_poll:node/add/poll.
  $menu_links['menu-elmsln-add_poll:node/add/poll'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/poll',
    'router_path' => 'node/add/poll',
    'link_title' => 'Poll',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_poll:node/add/poll',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_timeline-item:node/add/timeline-date.
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
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_timeline:node/add/timeline.
  $menu_links['menu-elmsln-add_timeline:node/add/timeline'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/timeline',
    'router_path' => 'node/add/timeline',
    'link_title' => 'Timeline',
    'options' => array(
      'identifier' => 'menu-elmsln-add_timeline:node/add/timeline',
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
    'weight' => -50,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_zip-file:file/add/upload/archive.
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
    'weight' => -43,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('File');
  t('JMOL');
  t('Map');
  t('Map point');
  t('Poll');
  t('Timeline');
  t('Timeline item');
  t('Zip file');

  return $menu_links;
}
