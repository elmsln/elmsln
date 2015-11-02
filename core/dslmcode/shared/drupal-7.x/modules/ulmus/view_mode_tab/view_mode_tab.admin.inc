<?php
/**
 * @file
 * Administrative page callbacks for the View Mode Tab module.
 */

/**
 *  View Mode Tab admin configuration form.
 */
function view_mode_tab_admin_config_form($form, &$form_state) {
  $form['view_mode_enable_by_default'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable new view modes by default'),
    '#default_value' => variable_get('view_mode_enable_by_default', TRUE),
    '#description' => t('This will automatically enable newly created view modes to the view mode tab settings.'),
  );
  return system_settings_form($form);
}
