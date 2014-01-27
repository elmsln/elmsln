<?php
/**
 * @file
 * Devel Generate module integration.
 */

/**
 * Implements hook_custom_formatters_form_alter_alter on behalf of
 * devel_generate.module.
 */
function devel_generate_custom_formatters_form_alter_alter(&$form, &$form_state, $form_id) {
  if (in_array($form_id, array('ctools_export_ui_edit_item_form', 'ctools_export_ui_edit_item_wizard_form')) && isset($form['#formatters'])) {
    $item = !empty($form_state['values']) ? $form_state['values'] : (array) $form_state['item'];
    $entity_type = !empty($item['preview']['entity_type']) ? $item['preview']['entity_type'] : 'node';

    $info = module_invoke_all('custom_formatters_devel_generate_info');
    if (in_array($entity_type, array_keys($info)) && count($form['engine']['preview']['field']['#options']) > 0) {
      $form['engine']['preview']['entity']['#options']['devel_generate'] = 'Devel generate';
      $form['engine']['preview']['entity']['#disabled'] = FALSE;
      $form['engine']['preview']['button']['#ajax']['callback'] = 'custom_formatters_export_ui_form_js_preview_devel_generate';
      $form['engine']['preview']['button']['#disabled'] = FALSE;
    }
  }
}

/**
 * Submit callback for Custom Formatters live preview via Devel Generate.
 */
function custom_formatters_export_ui_form_js_preview_devel_generate($form, $form_state) {
  $info = module_invoke_all('custom_formatters_devel_generate_info');
  if ($form_state['values']['preview']['entity'] !== 'devel_generate' || !function_exists($function = $info[$form_state['values']['preview']['entity_type']]['process callback'])) {
    return custom_formatters_export_ui_form_js_preview($form, $form_state);
  }
  $object = $function($form_state);
  return custom_formatters_export_ui_form_js_preview($form, $form_state, $object);
}
