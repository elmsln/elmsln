<?php
/**
 * Implements menu_link__menu_cis_toolkit.
 */
function cis_foundation_access_menu_link__menu_cis_toolkit(&$variables) {
  return _foundation_access_menu_outline($variables);
}

/**
 * Implements menu_tree__menu_cis_toolkit.
 */
function cis_foundation_access_menu_tree__menu_cis_toolkit($variables) {
  return '<ul class="off-canvas-list has-submenu content-outline-navigation">' . $variables['tree'] . '</ul>';
}