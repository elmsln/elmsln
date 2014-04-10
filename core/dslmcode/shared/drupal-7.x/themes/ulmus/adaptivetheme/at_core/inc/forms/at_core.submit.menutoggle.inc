<?php

/**
 * @file
 * Save the Menu Toggle CSS to file
 */
function at_core_submit_menu_toggle($values, $theme_name, $path) {
  $smalltouch_portrait_media_query  = $values['smalltouch_portrait_media_query'];
  $smalltouch_landscape_media_query = $values['smalltouch_landscape_media_query'];
  $tablet_portrait_media_query      = $values['tablet_portrait_media_query'];
  $tablet_landscape_media_query     = $values['tablet_landscape_media_query'];
  $bigscreen_media_query            = $values['bigscreen_media_query'];

  // if landscape is seleted force portrait to be true, because form states are display only!
  if (isset($values['menu_toggle_tablet_landscape']) && $values['menu_toggle_tablet_landscape'] == 1) {
    if ($values['menu_toggle_tablet_portrait'] == 0) {
      $values['menu_toggle_tablet_portrait'] = 1;
    }
  }

  $menu_toggle_css = array();
  $menu_toggle_css_active = '
  .at-mt .at-menu-toggle-button {
    position: static;
    top: 0;
  }
  .at-mt .menu-toggle {
    display: none;
  }
  .at-mt .menu-toggle ul li,
  .at-mt .menu-toggle ul li a {
    display: block;
    float:none;
  }';

  $menu_toggle_css_inactive = '
  .at-mt .at-menu-toggle-button {
    position: absolute;
    top: -99999em;
  }
  .at-mt .menu-toggle {
    display:block !important;
  }';

  // We need extra overrides for superfish if the module is active, pre Superfish module 1.9
  if (module_exists('superfish')) {
  $menu_toggle_superfish_css = '
  .at-mt .menu-toggle .sf-menu {
    float: none;
    margin: 0;
    height: auto;
  }
  .at-mt .menu-toggle .sf-menu ul,
  .at-mt .menu-toggle .sf-menu li {
    margin: 0;
    position: relative;
    top: 0;
    display: block;
    float: none;
    clear: both;
    width: 100% !important;
    left: 0 !important;
  }
  .at-mt .menu-toggle .sf-menu ul {
    left: 0;
    position: static;
  }
  .at-mt .menu-toggle .sf-hidden {
    display: none !important;
  }';
  }
  else {
    $menu_toggle_superfish_css = '';
  }

  $comment = "/* Menu toggle is using the media queries from the standard, tablet and smalltouch layout settings */\n";

  // Smalltouch portrait
  $smalltouch_portrait_css = $menu_toggle_css_active . $menu_toggle_superfish_css;
  $menu_toggle_css[] = $comment . '@media ' . $smalltouch_portrait_media_query . ' {' . "\n" . $smalltouch_portrait_css . "\n" . '}';

  // Smalltouch landscape
  $smalltouch_landscape_css = $menu_toggle_css_active . $menu_toggle_superfish_css;
  $menu_toggle_css[] = '@media ' . $smalltouch_landscape_media_query . ' {' . "\n" . $smalltouch_landscape_css . "\n" . '}';

  // Tablet portrait
  if (isset($values['menu_toggle_tablet_portrait']) && $values['menu_toggle_tablet_portrait'] == 1) {
    $tablet_portrait_css = $menu_toggle_css_active . $menu_toggle_superfish_css;
  }
  else {
    $tablet_portrait_css = $menu_toggle_css_inactive;
  }
  $menu_toggle_css[] = '@media ' . $tablet_portrait_media_query . ' {' . "\n" . $tablet_portrait_css . "\n" . '}';

  // Tablet landscape
  if (isset($values['menu_toggle_tablet_landscape']) && $values['menu_toggle_tablet_landscape'] == 1) {
    $tablet_landscape_css = $menu_toggle_css_active . $menu_toggle_superfish_css;
  }
  else {
    $tablet_landscape_css = $menu_toggle_css_inactive;
  }
  $menu_toggle_css[] = '@media ' . $tablet_landscape_media_query . ' {' . "\n" . $tablet_landscape_css . "\n" . '}';

  // Bigscreen is always inactive
  $menu_toggle_css[] = '@media ' . $bigscreen_media_query . ' {' . "\n" . $menu_toggle_css_inactive . "\n" . '}';

  // Contextual links can get messed up, add a brutal override to make sure that does not happen
  $menu_toggle_css[] = '.at-mt .at-menu-toggle div.contextual-links-wrapper ul.contextual-links{display:none}';

  $menu_toggle_css_processed = implode("\n", $menu_toggle_css);
  $file_name = $theme_name . '.menutoggle.css';
  $filepath = $path . '/' . $file_name;
  file_unmanaged_save_data($menu_toggle_css_processed, $filepath, FILE_EXISTS_REPLACE);
}
