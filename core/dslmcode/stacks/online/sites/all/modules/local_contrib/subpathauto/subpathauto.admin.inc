<?php

/**
 * @file
 * Admin page callbacks for the subpathauto module.
 */

/**
 * Form builder; Configure the sub-path URL alias settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function subpathauto_settings_form($form, &$form_state) {
  $form['subpathauto_depth'] = array(
    '#type' => 'select',
    '#title' => t('Maximum depth of sub-paths to alias'),
    '#options' => array_merge(array(0 => t('Disabled')), range(1, MENU_MAX_DEPTH - 1)),
    '#default_value' => variable_get('subpathauto_depth', 1),
    '#description' => t('Increasing this value may decrease performance.'),
  );

  $form['subpathauto_ignore_admin'] = array(
    '#type' => 'checkbox',
    '#title' => t('Skip administration paths from sub-path processing.'),
    '#default_value' => variable_get('subpathauto_ignore_admin', 1),
  );

  return system_settings_form($form);
}
