<?php

/**
 * Implements menu_tree__main_menu.
 */
function elmsmedia_foundation_access_menu_tree__menu_elmsmedia_navigation($variables) {
  return '<ul class="header-menu-options">' . $variables['tree'] . '</ul>';
}