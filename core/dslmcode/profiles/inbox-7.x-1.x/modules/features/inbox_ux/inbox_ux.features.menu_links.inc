<?php
/**
 * @file
 * inbox_ux.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function inbox_ux_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-elmsln-add_calendar-event:node/add/inbox-event
  $menu_links['menu-elmsln-add_calendar-event:node/add/inbox-event'] = array(
    'menu_name' => 'menu-elmsln-add',
    'link_path' => 'node/add/inbox-event',
    'router_path' => 'node/add/inbox-event',
    'link_title' => 'Calendar event',
    'options' => array(
      'attributes' => array(),
      'item_attributes' => array(
        'id' => '',
        'class' => '',
        'style' => '',
      ),
      'identifier' => 'menu-elmsln-add_calendar-event:node/add/inbox-event',
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
  t('Calendar event');

  return $menu_links;
}
