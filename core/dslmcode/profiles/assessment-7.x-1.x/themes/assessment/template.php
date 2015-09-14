<?php
/**
 * Implements menu_link__menu_discuss_toolkit.
 */
function assessment_foundation_access_menu_link__menu_assessment_navigation(&$variables) {
  return _foundation_access_menu_outline($variables);
}

/**
 * Implements menu_tree__menu_discuss_toolkit.
 */
function assessment_foundation_access_menu_tree__menu_assessment_navigation($variables) {
  return '<ul class="off-canvas-list has-submenu content-outline-navigation">' . $variables['tree'] . '</ul>';
}
