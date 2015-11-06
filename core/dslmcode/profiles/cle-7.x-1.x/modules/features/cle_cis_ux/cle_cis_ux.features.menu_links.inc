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

  // Exported menu link: menu-cis-add_create-assignment:node/add/cle-assignment
  $menu_links['menu-cis-add_create-assignment:node/add/cle-assignment'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/cle-assignment',
    'router_path' => 'node/add/cle-assignment',
    'link_title' => 'Create Assignment',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_create-assignment:node/add/cle-assignment',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cis-add_create-submission:node/add/cle-submission
  $menu_links['menu-cis-add_create-submission:node/add/cle-submission'] = array(
    'menu_name' => 'menu-cis-add',
    'link_path' => 'node/add/cle-submission',
    'router_path' => 'node/add/cle-submission',
    'link_title' => 'Create Submission',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cis-add_create-submission:node/add/cle-submission',
    ),
    'module' => 'menu',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 0,
    'weight' => 0,
    'customized' => 1,
  );
  // Exported menu link: menu-cle-navigation_my-gallery:cle/my-gallery
  $menu_links['menu-cle-navigation_my-gallery:cle/my-gallery'] = array(
    'menu_name' => 'menu-cle-navigation',
    'link_path' => 'cle/my-gallery',
    'router_path' => 'cle/my-gallery',
    'link_title' => 'My Gallery',
    'options' => array(
      'attributes' => array(
        'title' => 'All of my submissions for this course',
      ),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-cle-navigation_my-gallery:cle/my-gallery',
    ),
    'module' => 'system',
    'hidden' => 1,
    'external' => 0,
    'has_children' => 0,
    'expanded' => 1,
    'weight' => -44,
    'customized' => 1,
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Create Assignment');
  t('Create Submission');
  t('My Gallery');


  return $menu_links;
}
