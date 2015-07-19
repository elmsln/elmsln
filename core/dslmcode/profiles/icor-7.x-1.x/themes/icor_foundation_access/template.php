<?php
/**
 * Implements menu_link__main_menu.
 */
function icor_foundation_access_menu_link__menu_icor_navigation(&$variables) {
  return _foundation_access_menu_outline($variables);
}

/**
 * Implements menu_tree__main_menu.
 */
function icor_foundation_access_menu_tree__menu_icor_navigation($variables) {
  return '<ul class="off-canvas-list has-submenu content-outline-navigation">' . $variables['tree'] . '</ul>';
}