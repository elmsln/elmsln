<?php

/**
 * @file
 * Generate configuration form and save settings.
 */

/**
 * Configuration form for Media's WYSIWYG view modes.
 */
function media_wysiwyg_view_mode_configuration_form($form, &$form_state) {
  $options = array();

  // Add the default view mode by default
  $options['default'] = t('Default');

  $entity_info = entity_get_info('file');
  foreach ($entity_info['view modes'] as $view_mode => $view_mode_info) {
    $options[$view_mode] = check_plain($view_mode_info['label']);
  }

  $form['media_wysiwyg_view_mode_wysiwyg_restricted_view_modes'] = array(
    '#type' => 'fieldset',
    '#title' => t('WYSIWYG allowed view modes'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Restrict the allowed view modes when embedding files inside of the the WYSIWYG editor.'),
  );

  foreach (file_type_get_enabled_types() as $type) {
    $form['media_wysiwyg_view_mode_wysiwyg_restricted_view_modes']["media_wysiwyg_view_mode_{$type->type}_wysiwyg_restricted_view_modes_status"] = array(
      '#type' => 'checkbox',
      '#title' => t('Restrict allowed view modes for %type', array('%type' => $type->label)),
      '#default_value' => variable_get("media_wysiwyg_view_mode_{$type->type}_wysiwyg_restricted_view_modes_status", FALSE),
    );
    $form['media_wysiwyg_view_mode_wysiwyg_restricted_view_modes']["media_wysiwyg_view_mode_{$type->type}_wysiwyg_restricted_view_modes"] = array(
      '#type' => 'checkboxes',
      '#title' => t('Restrict view modes'),
      '#options' => $options,
      '#default_value' => variable_get("media_wysiwyg_view_mode_{$type->type}_wysiwyg_restricted_view_modes", array()),
      '#states' => array(
        'visible' => array(
          ':input[name="media_wysiwyg_view_mode_' . $type->type . '_wysiwyg_restricted_view_modes_status"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  $form['media_wysiwyg_view_mode_file_wysiwyg_view_mode'] = array(
    '#type' => 'fieldset',
    '#title' => t('File WYSIWYG view mode'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#description' => t('Use a custom view mode when displaying files inside of the WYSIWYG editor.'),
  );

  foreach (file_type_get_enabled_types() as $type) {
    $form['media_wysiwyg_view_mode_file_wysiwyg_view_mode']["media_wysiwyg_view_mode_{$type->type}_file_wysiwyg_view_mode_status"] = array(
      '#type' => 'checkbox',
      '#title' => t('Use a custom view mode for %type', array('%type' => $type->label)),
      '#default_value' => variable_get("media_wysiwyg_view_mode_{$type->type}_file_wysiwyg_view_mode_status", FALSE),
    );
    $form['media_wysiwyg_view_mode_file_wysiwyg_view_mode']["media_wysiwyg_view_mode_{$type->type}_file_wysiwyg_view_mode"] = array(
      '#type' => 'select',
      '#title' => t('View mode'),
      '#options' => $options,
      '#default_value' => variable_get("media_wysiwyg_view_mode_{$type->type}_file_wysiwyg_view_mode", 'wysiwyg'),
      '#states' => array(
        'visible' => array(
          ':input[name="media_wysiwyg_view_mode_' . $type->type . '_file_wysiwyg_view_mode_status"]' => array('checked' => TRUE),
        ),
      ),
    );
  }

  return system_settings_form($form);
}
