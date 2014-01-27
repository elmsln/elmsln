<?php
/**
 * @file
 * Provides the "Content type" rule plugin for the Menu Position module.
 */

/**
 * Checks if the node is of a certain type.
 *
 * @param $variables
 *   An array containing each of the variables saved in the database necessary
 *   to evaluate this condition of the rule.
 * @return
 *   TRUE if condition applies successfully. Otherwise FALSE.
 */
function menu_position_menu_position_condition_content_type($variables) {
  // Check if this is a node page and then what type of node it is.
  return ($variables['context']['entity_type'] == 'node' && in_array($variables['context']['bundle_name'], $variables['content_type'])) ? TRUE : FALSE;
}

/**
 * Adds form elements for the "content type" plugin to the rule configuration form.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array. New form elements should be
 *   added directly to this array.
 * @param $form_state
 *   A reference to the current form state.
 */
function menu_position_menu_position_rule_content_type_form(&$form, &$form_state) {
  // If this is an existing rule, load the variables stored in the rule for this plugin.
  $variables = !empty($form_state['#menu-position-rule']['conditions']['content_type']) ? $form_state['#menu-position-rule']['conditions']['content_type'] : array();

  $form['conditions']['content_type'] = array(
    '#type' => 'fieldset',
    '#title' => t('Content types'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'menu_position') . '/plugins/menu_position.content_type.js'),
    ),
  );
  $form['conditions']['content_type']['content_type'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Content types'),
    '#default_value' => !empty($variables['content_type']) ? $variables['content_type'] : array(),
    '#options' => node_type_get_names(),
    '#description' => t('Apply this rule only on pages that display content of the given type(s). If you select no types, there will be no type-specific limitation.'),
    '#weight' => -20,
  );

  // Add a submit handler.
  $form['#submit'][] = 'menu_position_menu_position_rule_content_type_form_submit';
}

/**
 * Prepares the "content type" variables to be stored in the rule.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function menu_position_menu_position_rule_content_type_form_submit(&$form, &$form_state) {
  // The user has added our plugin's form elements as a condition for the rule.
  if (!empty($form_state['values']['content_type'])) {
    // Remove any 0 valued options.
    foreach ($form_state['values']['content_type'] as $key => $value) {
      if ($value === 0) {
        unset($form_state['values']['content_type'][$key]);
      }
    }
    // Determine if any checkboxes were on.
    if (!empty($form_state['values']['content_type'])) {
      // Add this plugin's variables to the rule.
      $variables = array(
        'content_type' => $form_state['values']['content_type'],
      );
      $form_state['values']['conditions']['content_type'] = $variables;
    }
  }
}
