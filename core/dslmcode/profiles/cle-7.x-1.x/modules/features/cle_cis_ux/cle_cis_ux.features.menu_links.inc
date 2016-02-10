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

  // Exported menu link: menu-elmsln-navigation_assignments-list:cle/assignments
  $menu_links['menu-elmsln-navigation_assignments-list:cle/assignments'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'cle/assignments',
    'router_path' => 'cle/assignments',
    'link_title' => 'Assignments list',
    'options' => array(
      'attributes' => array(
        'title' => 'Listing of assignments for this section',
      ),
      'identifier' => 'menu-elmsln-navigation_assignments-list:cle/assignments',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_my-draft-pages:cle/draft-pages
  $menu_links['menu-elmsln-navigation_my-draft-pages:cle/draft-pages'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'cle/draft-pages',
    'router_path' => 'cle/draft-pages',
    'link_title' => 'My Draft Pages',
    'options' => array(
      'attributes' => array(
        'title' => 'A visual showcase of all your submitted draft pages',
      ),
      'identifier' => 'menu-elmsln-navigation_my-draft-pages:cle/draft-pages',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -46,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_my-final-pages:cle/final-pages
  $menu_links['menu-elmsln-navigation_my-final-pages:cle/final-pages'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'cle/final-pages',
    'router_path' => 'cle/final-pages',
    'link_title' => 'My Final Pages',
    'options' => array(
      'identifier' => 'menu-elmsln-navigation_my-final-pages:cle/final-pages',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -45,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-navigation_my-sketch-book:cle/sketch-book
  $menu_links['menu-elmsln-navigation_my-sketch-book:cle/sketch-book'] = array(
    'menu_name' => 'menu-elmsln-navigation',
    'link_path' => 'cle/sketch-book',
    'router_path' => 'cle/sketch-book',
    'link_title' => 'My Sketch Book',
    'options' => array(
      'identifier' => 'menu-elmsln-navigation_my-sketch-book:cle/sketch-book',
    ),
    'module' => 'system',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -47,
    'customized' => 1,
  );
  // Exported menu link: menu-elmsln-settings_create-assignment:node/add/cle-assignment
  $menu_links['menu-elmsln-settings_create-assignment:node/add/cle-assignment'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => 'node/add/cle-assignment',
    'router_path' => 'node/add/cle-assignment',
    'link_title' => 'Create assignment',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_create-assignment:node/add/cle-assignment',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-settings_studio:<nolink>',
  );
  // Exported menu link: menu-elmsln-settings_create-submission:node/add/cle-submission
  $menu_links['menu-elmsln-settings_create-submission:node/add/cle-submission'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => 'node/add/cle-submission',
    'router_path' => 'node/add/cle-submission',
    'link_title' => 'Create submission',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_create-submission:node/add/cle-submission',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -50,
    'customized' => 1,
    'parent_identifier' => 'menu-elmsln-settings_studio:<nolink>',
  );
  // Exported menu link: menu-elmsln-settings_studio:<nolink>
  $menu_links['menu-elmsln-settings_studio:<nolink>'] = array(
    'menu_name' => 'menu-elmsln-settings',
    'link_path' => '<nolink>',
    'router_path' => '<nolink>',
    'link_title' => 'Studio',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-settings_studio:<nolink>',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 1,
    'expanded' => 1,
    'weight' => 0,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Assignments list');
  t('Create assignment');
  t('Create submission');
  t('My Draft Pages');
  t('My Final Pages');
  t('My Sketch Book');
  t('Studio');

  return $menu_links;
}
