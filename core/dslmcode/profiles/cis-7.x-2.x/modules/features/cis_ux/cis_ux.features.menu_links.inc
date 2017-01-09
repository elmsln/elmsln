<?php
/**
 * @file
 * cis_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function cis_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_academic-area:node/add/academic-unit.
  $menu_links['menu-elmsln-add_academic-area:node/add/academic-unit'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/academic-unit',
    'router_path' => 'node/add/academic-unit',
    'link_title' => 'Academic area',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-add_academic-area:node/add/academic-unit',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_global-resource:node/add/resource.
  $menu_links['menu-elmsln-add_global-resource:node/add/resource'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/resource',
    'router_path' => 'node/add/resource',
    'link_title' => 'Global Resource',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-add_global-resource:node/add/resource',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -48,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-add_program:node/add/program.
  $menu_links['menu-elmsln-add_program:node/add/program'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/program',
    'router_path' => 'node/add/program',
    'link_title' => 'Program',
    'options' => array(
      'attributes' => array(),
      'identifier' => 'menu-elmsln-add_program:node/add/program',
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
  t('Academic area');
  t('Global Resource');
  t('Program');

  return $menu_links;
}
