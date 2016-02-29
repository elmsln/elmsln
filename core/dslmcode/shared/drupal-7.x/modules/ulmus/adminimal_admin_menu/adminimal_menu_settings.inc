<?php

/**
 * @file
 * Menu builder functions for Administration menu.
 */

/**
 * Create the settings page form.
 */
function adminimal_admin_menu_settings($form, &$form_state) {

  // Create the shortcut category.
  $form['shortcuts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Shortcuts options'),
  );

  // Create the select list.
  $form['shortcuts']['adminimal_admin_menu_render'] = array(
    '#type' => 'select',
    '#title' => t('Rendering method'),
    '#default_value' => variable_get('adminimal_admin_menu_render', 'collapsed'),
    '#options' => array(
      'hidden' => t('Hidden'),
      'inline' => t('Inline'),
      'collapsed' => t('Collapsed'),
      'newline' => t('Newline'),
      'dropdown' => t('Dropdown'),
      'exclusive' => t('Exclusive'),
    ),
    '#description' => t('Select how the shortcuts will be rendered. There are currently 6 options: <ol> <li>Hidden -> The shortcuts will not be rendered inside the admin menu</li> <li>Inline -> The shortcuts will be rendered on the same line with the root menu links</li> <li>Collapsed -> The sorctus links will be collapsed like a normal menu. <strong>(Default option)</strong></li> <li>Newline -> The shortcuts will be rendered on a new line. Below the root menu links.</li> <li>Dropdown -> The shortcuts will be rendered inside a dropdown using the select html tag.</li> <li>Exclusive -> Only the shortcuts will be rendered, and the normal menu will be hidden.</li></ol>'),
    '#required' => TRUE,
  );

  // Create the shortcut category.
  $form['advanced_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Advanced Settings'),
    '#description' => '<div class="messages warning">WARNING: Do not change any of the advanced setting unless you know what you are doing!</div>',
  );

	$form['advanced_settings']['adminimal_admin_menu_slicknav'] = array(
	  '#type' => 'checkbox',
	  '#default_value' => variable_get('adminimal_admin_menu_slicknav', 'TRUE'),
	  '#title' => t('Enable Responsive Menu.'),
	  '#description' => t('<strong>Default value => Checked</strong>. 
	  Enable this option if you want to have responsive menu and mobile device support. 
	  While disabling this option could save you few kilobytes (around 3KB), i will completely disable the responsive menu functionality.'),
	);

	$form['advanced_settings']['adminimal_admin_menu_jquery'] = array(
	  '#type' => 'checkbox',
	  '#default_value' => variable_get('adminimal_admin_menu_jquery', 'TRUE'),
	  '#title' => t('Load the requred jQuery 1.7 library automagically.'),
	  '#description' => t('<strong>Default value => Checked</strong>. This will load the newer jQuery version 1.7 using 
	  the no-conflict method so it wont interfere with any existing jQuery or other java-script libraries. 
	  The only reason to uncheck this if you are already using a newer version of jQuery site-wide and its globally accessible by the "$" variable. 
	  Unchekig this option could save you 33KB, but it may also break your javasctipt if not used correctly.'),
    '#states' => array(
      // Hide the settings when the cancel notify checkbox is disabled.
      'visible' => array(
       ':input[name="adminimal_admin_menu_slicknav"]' => array('checked' => TRUE),
      ),
      'unchecked' => array(
       variable_get('adminimal_admin_menu_jquery', 'TRUE') => FALSE,
      ),
     ),
	);

  // Create the submit button.
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;

}

/**
 * Submit handler for views_sexy_throbber_settings().
 */
function adminimal_admin_menu_settings_submit($form, &$form_state) {

  // Exclude unnecessary elements.
  form_state_values_clean($form_state);

  foreach ($form_state['values'] as $key => $value) {
    if (is_array($value) && isset($form_state['values']['array_filter'])) {
      $value = array_keys(array_filter($value));
    }
    variable_set($key, $value);
  }

  // Clear the admin menu cache.
  admin_menu_flush_caches();

  // Display a message to the user.
  drupal_set_message(t('The configuration options have been saved.'));
}
