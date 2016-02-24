<?php

/**
 * Implements hook_foundation_access_ux_menu_item_icon_alter()
 *
 * This allows modules to have influence over the icon used when
 * presenting foundation access menu items in the slide out menu.
 *
 * Examples of this would be modification of the icon to match
 * with content on the page in question or when content is hidden
 * to certain roles.
 *
 * @see   hidden_nodes_foundation_access_ux_menu_item_icon_alter
 * @see   mooc_content_theming_foundation_access_ux_menu_item_icon_alter
 *
 * @param  [string] $icon     name of the icon class to apply
 * @param  [object] $node     fully loaded node that has a menu item prior to save
 */
function hook_foundation_access_ux_menu_item_icon_alter(&$icon, $node) {
  if ($node->title == 'coolstuff') {
    $icon = $node->title;
  }
}