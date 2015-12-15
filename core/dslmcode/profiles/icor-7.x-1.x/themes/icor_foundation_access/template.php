<?php
/**
 * Implements menu_tree__main_menu.
 */
function icor_foundation_access_menu_tree__menu_icor_navigation($variables) {
  return '<ul class="header-menu-options">' . $variables['tree'] . '</ul>';
}