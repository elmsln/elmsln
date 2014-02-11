<?php
/**
 * @file
 * Libraries API integration.
 */

/**
 * Implements hook_custom_formatters_form_alter_alter() on behalf of
 * libraries.module.
 */
function libraries_custom_formatters_form_alter_alter(&$form, $form_state, $form_id) {
  if (in_array($form_id, array('ctools_export_ui_edit_item_form', 'ctools_export_ui_edit_item_wizard_form')) && isset($form['#formatters'])) {
    // EditArea library support.
    if (in_array('editarea', array_keys(libraries_get_libraries()))) {
      $form['#attached']['js'][] = libraries_get_path('editarea') . '/edit_area/edit_area_full.js';

      $form['engine']['code']['#resizable'] = FALSE;
    }
  }
}
