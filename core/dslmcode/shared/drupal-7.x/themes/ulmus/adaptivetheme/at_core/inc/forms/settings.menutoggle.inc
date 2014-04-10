<?php

/**
 * @file
 * Generate settings for the Menu Toggle form.
 */
function at_core_menu_toggle_form(&$form) {
  $form['at']['menu-toggle'] = array(
    '#type' => 'fieldset',
    '#title' => t('Mobile Menu Toggle'),
    '#weight' => 30,
    '#description' => t('<h2>Menu Toggle for Mobile</h2><p>The Menu Toggle will hide selected menus and a single clickable link will appear. Clicking this link toggles the menu open and closed - suitable for mobile devices. Smalltouch/smartphone breakpoints are supported by default.</p><p><strong>Superfish:</strong> if you start using the Superfish module you should re-save the theme settings. Also enable the sf-Touchscreen plugin for your Superfish menu block.</p><p><strong>Polyfills:</strong> for this to work in older browsers (such as IE8 and below) and Android 2 you need to enable the matchMedia polyfill (see the Polyfills tab).</p>'),
  );

  // Select additional breakpoints
  $form['at']['menu-toggle']['breakpoints'] = array(
    '#type' => 'fieldset',
    '#title' => t('Breakpoints'),
    '#description' => t('<h3>Select Additional Device Breakpoints</h3>'),
  );

  $form['at']['menu-toggle']['breakpoints']['menu_toggle_tablet_portrait'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apply to Tablet Portrait'),
    '#default_value' => at_get_setting('menu_toggle_tablet_portrait'),
    '#states' => array(
      'disabled' => array('input[name=menu_toggle_tablet_landscape]' => array('checked' => TRUE)),
    ),
  );
  $form['at']['menu-toggle']['breakpoints']['menu_toggle_tablet_landscape'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apply to all Tablet breakpoints'),
    '#default_value' => at_get_setting('menu_toggle_tablet_landscape'),
  );


  // Regions and Menus
  $form['at']['menu-toggle']['menus-regions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menus'),
    '#description' => t('<h3>Select Menus and/or Regions</h3>'),
  );

  // Core menus
  $form['at']['menu-toggle']['menus-regions']['core'] = array(
    '#type' => 'fieldset',
    '#title' => t('Menus'),
    '#description' => t('<strong>Drupal core standard menus (variables printed in page.tpl.php).</strong>'),
  );
  // Core main menu
  $form['at']['menu-toggle']['menus-regions']['core']['menu_toggle_main_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Main Menu'),
    '#default_value' => at_get_setting('menu_toggle_main_menu'),
  );
  // Core secondary menu
  $form['at']['menu-toggle']['menus-regions']['core']['menu_toggle_secondary_menu'] = array(
    '#type' => 'checkbox',
    '#title' => t('Secondary menu'),
    '#default_value' => at_get_setting('menu_toggle_secondary_menu'),
  );

  // Regions
  $form['at']['menu-toggle']['menus-regions']['regions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Regions'),
    '#description' => t('<strong>Regions to apply menu toggles - each menu block in these regions will get a toggle.</strong>'),
  );

  // Region - leaderboard
  $form['at']['menu-toggle']['menus-regions']['regions']['menu_toggle_leaderboard'] = array(
    '#type' => 'checkbox',
    '#title' => t('Leaderboard'),
    '#default_value' => at_get_setting('menu_toggle_leaderboard'),
  );
  // Region - header region
  $form['at']['menu-toggle']['menus-regions']['regions']['menu_toggle_header'] = array(
    '#type' => 'checkbox',
    '#title' => t('Header'),
    '#default_value' => at_get_setting('menu_toggle_header'),
  );
  // Region - menu bar
  $form['at']['menu-toggle']['menus-regions']['regions']['menu_toggle_menu_bar'] = array(
    '#type' => 'checkbox',
    '#title' => t('Menu Bar'),
    '#default_value' => at_get_setting('menu_toggle_menu_bar'),
  );

  // Customize toggle link text
  $form['at']['menu-toggle']['titles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Link Text'),
    '#description' => t('<h3>Customize Menu Titles</h3><p>These apply to the Drupal core main and secondary menus (printed in page.tpl.php). If you are using a block in a region you need to change the block title for your menu block (even if it\'s the Main menu block).</p>'),
  );
  // Main menu title
  $form['at']['menu-toggle']['titles']['menu_toggle_main_menu_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Main menu title'),
    '#default_value' => at_get_setting('menu_toggle_main_menu_title'),
  );
  // Secondary menu title
  $form['at']['menu-toggle']['titles']['menu_toggle_secondary_menu_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Secondary menu title'),
    '#default_value' => at_get_setting('menu_toggle_secondary_menu_title'),
  );
}
