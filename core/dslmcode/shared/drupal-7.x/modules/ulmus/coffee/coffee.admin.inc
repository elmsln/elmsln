<?php

/**
 * @file
 * Admin page callbacks for the coffee module.
 */

/**
 * Form builder; Configure coffee settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function coffee_admin_settings() {
  $form = array();

  // Output the checkboxes to let admins select which menus are
  // featured in coffee.
  $menus = menu_get_menus();
  $menu_options = array();

  foreach ($menus as $name => $title) {
    $menu_options[$name] = check_plain($title);
  }

  if (!empty($menu_options)) {
    $form['coffee_settings_menus'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Menus to include in Coffee'),
      '#options' => $menu_options,
      '#default_value' => variable_get('coffee_settings_menus', array('management', 'user-menu')),
    );
  }

  $form['#submit'][0] = 'coffee_admin_settings_submit';

  return system_settings_form($form);
}

/**
 * Function coffee_admin_settings_submit().
 */
function coffee_admin_settings_submit($form, $form_state) {
  // As we're altering which menus are being included in
  // coffee, rebuild the cached commands for users so they
  // get these changes.
  cache_clear_all(NULL, 'cache_coffee');
}
