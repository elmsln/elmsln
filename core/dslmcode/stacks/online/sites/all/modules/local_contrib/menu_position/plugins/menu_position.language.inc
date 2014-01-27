<?php
/**
 * @file
 * Provides the "Language" rule plugin for the Menu Position module.
 */

/**
 * Checks if the language matches the global language.
 *
 * @param $variables
 *   An array containing each of the variables saved in the database necessary
 *   to evaluate this condition of the rule.
 * @return
 *   TRUE if condition applies successfully. Otherwise FALSE.
 */
function menu_position_menu_position_condition_language($variables) {
  // Grab the variables stored statically in the rule.
  return ($variables['language'] == $GLOBALS['language']->language) ? TRUE : FALSE;
}

/**
 * Adds form elements for the "language" plugin to the rule configuration form.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array. New form elements should be
 *   added directly to this array.
 * @param $form_state
 *   A reference to the current form state.
 */
function menu_position_menu_position_rule_language_form(&$form, &$form_state) {
  // If this is an existing rule, load the variables stored in the rule for this plugin.
  $variables = !empty($form_state['#menu-position-rule']['conditions']['language']) ? $form_state['#menu-position-rule']['conditions']['language'] : array();

  $form['conditions']['language'] = array(
    '#type' => 'fieldset',
    '#title' => t('Language'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'menu_position') . '/plugins/menu_position.language.js'),
    ),
  );
  $form['conditions']['language']['language'] = array(
    '#type' => 'select',
    '#title' => t('Language'),
    '#options' => array('' => t('Any language')) + locale_language_list(),
    '#default_value' => !empty($variables['language']) ? $variables['language'] : '',
    '#description' => t("Apply this rule only when the language matches the current page's language."),
    '#weight' => -20,
  );

  // Add a submit handler.
  $form['#submit'][] = 'menu_position_menu_position_rule_language_form_submit';
}

/**
 * Prepares the "language" variables to be stored in the rule.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function menu_position_menu_position_rule_language_form_submit(&$form, &$form_state) {
  // Check if the user has added our plugin's form elements as a condition for
  // the rule.
  if (!empty($form_state['values']['language'])) {
    // Add this plugin's variables to the rule.
    $variables = array(
      'language' => $form_state['values']['language'],
    );
    $form_state['values']['conditions']['language'] = $variables;
  }
}
