<?php
/**
 * @file
 * icor_poll.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function icor_poll_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_poll:node/add/poll
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
    'weight' => -48,
    'customized' => 1,
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Poll');

  return $menu_links;
}
