<?php

/**
 * @file
 * Administration form functions for taxonomy display configuration.
 */

/**
 * Helper callback; perform form alterations for taxonomy display admin form.
 *
 * @param array $form
 * @param array $form_state
 *
 * @return void
 *
 * @see taxonomy_display_form_fieldset()
 */
function taxonomy_display_admin_form(&$form, &$form_state) {
  // Only proceed if we are on taxonomy_term entity type and the user has admin
  // taxonomy display.
  if ($form['#entity_type'] != 'taxonomy_term' || !user_access('administer taxonomy display')) {
    return;
  }

  // Ensure 'additional_settings' exists.
  taxonomy_display_admin_form_setup_additional_settings($form);

  // Make things easy on users getting started with the module.
  // We require the 'full' #view_mode to configure the taxonomy term page.
  if ($form['#view_mode'] == 'default') {
    $field = array(
      '#title' => t('Term page display'),
      '#type' => 'fieldset',
    );
    // Find out if full mode is enabled and change the description for term page
    // display to match.
    $entity_info = entity_get_info('taxonomy_term');
    $view_mode_settings = field_view_mode_settings('taxonomy_term', $form['#bundle']);
    if (isset($view_mode_settings['full']['custom_settings'])) {
      $field['#description'] = t('To alter the term page display you need to go to the <em>Taxonomy term page</em> view mode.');
    }
    else {
      $field['#description'] = t('Enable the <em>Taxonomy term page</em> view mode under the <em>Custom display settings</em> tab to alter the term page display.');
    }
    $form['additional_settings']['taxonomy_display'] = $field;
  }

  // Only proceed if we are on the full display mode.
  if ($form['#view_mode'] != 'full') {
    return;
  }

  // Retrieve the stored taxonomy display settings for the vocabulary.
  $stored_settings = taxonomy_display_fetch_taxonomy_display($form['#bundle']);

  $form['additional_settings']['taxonomy_display'] = array(
    '#description' => t('Configure how the taxonomy term display page should be presented when viewed for this vocabulary.'),
    '#title' => t('Term page display'),
    '#type' => 'fieldset',
  );
  $fieldset =& $form['additional_settings']['taxonomy_display'];

  // Build the plugin forms for term and associated content display.
  $plugin_types = _taxonomy_display_plugin_types();
  foreach ($plugin_types as $k => $v) {
    _taxonomy_display_admin_form_build_plugin_form($k, $fieldset, $form_state, $stored_settings);
  }

  // Add selection for adding taxonomy term core feed to page
  $fieldset['add_feed'] = array(
    '#default_value' => $stored_settings->add_feed,
    '#description' => t('Drupal, by default, includes a feed of content referencing the term, by unchecking this you can prevent the feed from being added.'),
    '#title' => t('Include feed'),
    '#type' => 'checkbox',
  );

  // Add our #validate and #submit callback which will call plugins' methods.
  $form['#validate'][] = 'taxonomy_display_admin_form_validate';
  $form['#submit'][] = 'taxonomy_display_admin_form_submit';
}

/**
 * Helper function; provide same form setup for compatibility as Display Suite.
 *
 * @param array $form
 *   The form array.
 *
 * @see http://drupal.org/node/1124168
 * @see http://drupal.org/node/1124346
 */
function taxonomy_display_admin_form_setup_additional_settings(&$form) {
  // If the additional_settings key does not exists (created by Display Suite)
  // then reproduce what Display Suite does for compatibility.
  if (!isset($form['additional_settings'])) {
    $form['additional_settings'] = array(
      '#type' => 'vertical_tabs',
      '#theme_wrappers' => array('vertical_tabs'),
      '#prefix' => '<div>',
      '#suffix' => '</div>',
      '#tree' => TRUE,
    );
    $form['#attached']['js'][] = 'misc/form.js';
    $form['#attached']['js'][] = 'misc/collapse.js';
  }

  // If the modes field exists in the base form then move it in to the fieldset.
  if (isset($form['modes'])) {
    $form['additional_settings']['modes'] = $form['modes'];
    $form['additional_settings']['modes']['#weight'] = -10;
    unset($form['modes']);
  }

  // Layout needs be first so we can reset the type key for Field API fields.
  $form['#validate'][] = 'taxonomy_display_field_ui_layouts_validate';
}

/**
 * Form submit callback; save Taxonomy Display settings for term pages.
 */
function taxonomy_display_admin_form_submit($form, &$form_state) {
  $values =& $form_state['values']['additional_settings']['taxonomy_display'];
  $td_form =& $form['additional_settings']['taxonomy_display'];

  $save_data = array();

  $plugin_types = _taxonomy_display_plugin_types();
  // Perform submit functions for our plugins.
  foreach($plugin_types as $k => $v) {
    if ($values[$k . '_display_select'] != 'missing') {
      $save_data[$k . '_display_plugin'] = $values[$k . '_display_select'];

      $class = new $values[$k . '_display_select'];
      $save_data[$k . '_display_options'] = $class->formSubmit($td_form[$k . '_display_form'], $values[$k . '_display_form']);
    }
  }

  // Save the add_feed setting.
  $save_data['add_feed'] = $values['add_feed'];

  // Save data
  taxonomy_display_save_taxonomy_display($form['#bundle'], $save_data);
}

/**
 * Form validate callback; validate Taxonomy Display settings for term pages.
 */
function taxonomy_display_admin_form_validate($form, &$form_state) {
  $values =& $form_state['values']['additional_settings']['taxonomy_display'];
  $td_form =& $form['additional_settings']['taxonomy_display'];

  $plugin_types = _taxonomy_display_plugin_types();
  // Perform submit functions for our plugins.
  foreach ($plugin_types as $k => $v) {
    if ($values[$k . '_display_select'] != 'missing') {
      $class = new $values[$k . '_display_select'];
      $class->formValidate($td_form[$k . '_display_form'], $values[$k . '_display_form']);
    }
  }
}

/**
 * Return just the term display sub-form.
 *
 * @return renderable array
 */
function taxonomy_display_ajax_associated_display_callback($form, $form_state) {
  return $form['additional_settings']['taxonomy_display']['associated_display_form'];
}

/**
 * Return just the breadcrumb display sub-form.
 */
function taxonomy_display_ajax_breadcrumb_display_callback($form, $form_state) {
  return $form['additional_settings']['taxonomy_display']['breadcrumb_display_form'];
}

/**
 * Return just the term display sub-form.
 *
 * @return renderable array
 */
function taxonomy_display_ajax_term_display_callback($form, $form_state) {
  return $form['additional_settings']['taxonomy_display']['term_display_form'];
}

/**
 * Validate handler; Move the view modes so Field UI can handle them.
 *
 * Modified from Display Suite since we are using the same form set.
 */
function taxonomy_display_field_ui_layouts_validate($form, &$form_state) {
  if (isset($form_state['values']['additional_settings']['modes']['view_modes_custom'])) {
    $form_state['values']['view_modes_custom'] = $form_state['values']['additional_settings']['modes']['view_modes_custom'];
  }
}

/**
 * Helper function; build the admin form for plugins.
 *
 * @param string $type
 *   Either 'term', 'associated', or 'breadcrumb'.
 * @param array $fieldset
 *   Form array that we will modify.
 * @param array|null $form_state
 *   The form state array.
 * @param $stored_settings
 *   Object from taxonomy_display_fetch_taxonomy_display().
 *
 * @return void
 *
 * @see taxonomy_display_admin_form()
 */
function _taxonomy_display_admin_form_build_plugin_form($type, &$fieldset, &$form_state, $stored_settings) {
  $plugin_types = _taxonomy_display_plugin_types();

  if (!isset($plugin_types[$type])) {
    return;
  }

  // Set variables needed based on type
  $select_field_title = t($plugin_types[$type]['long']);
  $select_field_description = t("Select which plugin you would like to display the term's %plugin_types_description.", array('%plugin_types_description' => $plugin_types[$type]['description']));

  $values = NULL;
  if (isset($form_state['values']['additional_settings']['taxonomy_display'])) {
    $values =& $form_state['values']['additional_settings']['taxonomy_display'];
  }

  // Populate $options with plugins that are available.
  $options = taxonomy_display_plugins($type);

  // Add support for missing plugins.
  if (isset($stored_settings->{$type . '_plugin_missing'})) {
    $options = array_merge(array('missing' => t('- Missing plugin -')), $options);
  }

  // Discover which option should be selected from the display plugins.
  if (isset($values[$type . '_display_select']) &&
      $values[$type . '_display_select'] != 'missing' &&
      array_key_exists($values[$type . '_display_select'], $options)) {
    $selected = $values[$type . '_display_select'];
  }
  elseif (isset($options['missing'])) {
    $selected = 'missing';
  }
  else {
    $selected = $stored_settings->{$type . '_display_plugin'};
  }
  $fieldset[$type . '_display_select'] = array(
    '#ajax' => array(
      'callback' => 'taxonomy_display_ajax_' . $type . '_display_callback',
      'wrapper' => 'replace-' . $type . '-display-form',
    ),
    '#default_value' => $selected,
    '#description' => $select_field_description,
    '#options' => $options,
    '#title' => $select_field_title,
    '#type' => 'select',
  );

  if (isset($form_state['taxonomy_display'][$type . '_display_handler'])) {
    $last_handler = $form_state['taxonomy_display'][$type . '_display_handler'];
  }
  $form_state['taxonomy_display'][$type . '_display_handler'] = $selected;

  if ($selected == 'missing') {
    $fieldset[$type . '_display_form'] = array(
      '#description' => t('The selected display plugin is missing. Either restore the plugin or select one that is available to configure.'),
      '#prefix' => '<div id="replace-' . $type . '-display-form">',
      '#suffix' => '</div>',
      '#type' => 'fieldset',
    );
    return;
  }

  $fieldset[$type . '_display_form'] = array(
    '#prefix' => '<div id="replace-' . $type . '-display-form">',
    '#suffix' => '</div>',
    '#title' => t('@label display options', array('@label' => $options[$selected])),
    '#type' => 'fieldset',
  );

  // Get the fieldset from the selected handler.
  $plugin_class = new $selected;
  // Set $options as null
  $display_options = NULL;
  if (!isset($stored_settings->no_record)) {
    $display_options = $stored_settings->{$type . '_display_options'};
  }
  // If the handler wasn't the one used on the last form build then reset the
  // $form_state values for it.
  if (!isset($last_handler) || $last_handler != $selected) {
    $values[$type . '_display_form'] = array();
  }
  $plugin_class->formFieldset($fieldset[$type . '_display_form'], $values[$type . '_display_form'], $display_options);
}
