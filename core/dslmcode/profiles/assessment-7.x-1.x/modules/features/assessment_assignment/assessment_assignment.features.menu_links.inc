<?php
/**
 * @file
 * assessment_assignment.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function assessment_assignment_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_assignment:node/add/assessment-assignment
  $menu_links['menu-elmsln-add_assignment:node/add/assessment-assignment'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/assessment-assignment',
    'router_path' => 'node/add/assessment-assignment',
    'link_title' => 'Assignment',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_assignment:node/add/assessment-assignment',
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
  t('Assignment');

  return $menu_links;
}
