<?php

/**
 * Implements menu_tree__main_menu.
 */
function cle_foundation_access_menu_tree__menu_cle_navigation($variables) {
  return '<ul class="header-menu-options">' . $variables['tree'] . '</ul>';
}

/**
 * Implements theme_breadrumb().
 */
function cle_foundation_access_breadcrumb($variables) {
  // hide breadcrumbs
}