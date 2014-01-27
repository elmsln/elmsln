<?php
/**
 * @file
 * Provides the PLUGIN rule plugin for the Menu Position module.
 */

/**
 * Checks if [describe the type of functionality the plugin provides].
 *
 * This is the condition callback that will be used when a rule is evaluated. If
 * the condition was not added to the rule, this callback will not be called.
 *
 * @param $variables
 *   An array containing each of the variables saved in the database necessary
 *   to evaluate this condition of the rule.
 * @return
 *   TRUE if condition applies successfully. Otherwise FALSE.
 */
function HOOK_menu_position_condition_PLUGIN($variables) {
  // Grab the variables stored statically in the rule.
  $lolspeak = $variables['lolspeak'];

  // $node is dynamically added and may not exist.
  $node = isset($variables['context']['node']) ? $variables['context']['node'] : NULL;

  // Retrieve any extra data needed to determine the condition's result.

  // Business logic goes here.

  return ($lolspeak && $node && $node->language == 'lolspeak') ? TRUE : FALSE;
}

/**
 * Adds form elements for the PLUGIN plugin to the rule configuration form.
 *
 * If this condition was active in the current rule, the plug-in variables will
 * be available in $form_state['#menu-position-rule']['conditions']['PLUGIN'].
 *
 * It is the resposibility of this hook to add any necessary form validation and
 * submission handlers.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array. New form elements should be
 *   added directly to this array.
 * @param $form_state
 *   A reference to the current form state.
 */
function HOOK_menu_position_rule_PLUGIN_form(&$form, &$form_state) {
  // If this is an existing rule, load the variables stored in the rule for this plugin.
  $variables = !empty($form_state['#menu-position-rule']['conditions']['PLUGIN']) ? $form_state['#menu-position-rule']['conditions']['PLUGIN'] : array();

  // To ensure that the plugin's form elements are placed inside vertical tabs,
  // all elements should be placed inside a collapsed fielset inside the
  // $form['conditions'] array.
  $form['conditions']['PLUGIN'] = array(
    '#type' => 'fieldset',
    '#title' => t('Lolspeak'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attached' => array(
      // Ensures a proper summary is added to its vertical tab.
      'js' => array(drupal_get_path('module', 'menu_position') . '/plugins/menu_position.example_plugin.js'),
    ),
  );
  $form['conditions']['PLUGIN']['lolspeak'] = array(
    '#type' => 'checkbox',
    '#title' => t('Lolspeak'),
    '#default_value' => !empty($variables['lolspeak']) ? $variables['lolspeak'] : 0,
    '#description' => t('Apply this rule only on pages written in lolspeak.'),
    '#weight' => -20,
  );

  // If we have a validation handler, we can add it this way. Or we could add
  // a per-element validation handler with '#element_validate' above.
  $form['#validate'][] = 'HOOK_menu_position_rule_PLUGIN_form_validate';

  // Add a submit handler.
  $form['#submit'][] = 'HOOK_menu_position_rule_PLUGIN_form_submit';
}

/**
 * Validates the plugin's rule form elements.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function HOOK_menu_position_rule_PLUGIN_form_validate(&$form, &$form_state) {
  // Can haz valdaishun?
  if (!empty($form_state['values']['has_ponies'])) {
    form_error($form['conditions']['PLUGIN']['lolspeak'], t('No soup for you!'));
  }
}

/**
 * Prepares the plugin's variables to be stored in the rule.
 *
 * If the plugin's form elements indicate that the condition needs to be
 * included with the rule, the submit handler must, at the very least, set:
 * $form_state['conditions']['PLUGIN'] = array(). Optionally, the plugin can add
 * to this array any static variables to be stored in the database with the rule
 * configuration.
 *
 * If, after this submit handler is run, the $form_state['conditions']['PLUGIN']
 * variables array is not set, this plugin will not be added as a condition for
 * this rule.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function HOOK_menu_position_rule_PLUGIN_form_submit(&$form, &$form_state) {
  if (!empty($form_state['values']['lolspeak'])) {
    // Check if the user has added our plugin's form elements as a condition for
    // the rule.
    if ($form_state['values']['lolspeak']) {
      // Since our form elements indicate that our plugin is to be used for this
      // rule, we need to add the appropriate variables to
      // $form_state['values']['conditions']['PLUGIN'] so that they can be
      // stored statically with the rule.
      $variables = array(
        'lolspeak' => $form_state['values']['lolspeak'],
      );
      $form_state['values']['conditions']['PLUGIN'] = $variables;
    }
  }
}
