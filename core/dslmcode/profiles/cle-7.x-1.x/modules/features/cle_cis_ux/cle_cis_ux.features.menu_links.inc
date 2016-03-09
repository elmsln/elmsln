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

  // Exported menu link: menu-elmsln-add_create-assignment:node/add/cle-assignment
  $menu_links['menu-elmsln-add_create-assignment:node/add/cle-assignment'] = array(
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
      'identifier' => 'menu-elmsln-add_create-assignment:node/add/cle-assignment',
    ),
    'module' => 'menu',
    'hidden' => 0,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => -49,
    'customized' => 1,
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
  t('Create assignment');
  t('Create submission');
  t('Studio');

  return $menu_links;
}
