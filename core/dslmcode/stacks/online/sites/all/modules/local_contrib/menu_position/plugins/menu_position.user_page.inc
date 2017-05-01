<?php
/**
 * @file
 * Provides the User rule plugin for the Menu Position module.
 */

/**
 * Checks if the current pageload is a user account page.
 *
 * @param $variables
 *   An array containing each of the variables saved in the database necessary
 *   to evaluate this condition of the rule.
 * @return
 *   TRUE if condition applies successfully. Otherwise FALSE.
 */
function menu_position_menu_position_condition_user_page($variables) {
  if (empty($variables['user_page_enable'])) {
    // Short-circuit if this rule is not enabled.
    return FALSE;
  }
  // There's probably a better way to figure out the current page context.
  $args = arg();
  if ($args[0] != 'user') {
    // Short-circuit if we're not looking at a user account page.
    return FALSE;
  }

  if (!empty($args[1]) && !is_numeric($args[1])) {
    // Short circuit if arg1 is non-empty and non-numeric.
    return FALSE;
  }

  if (!empty($args[2])) {
    // Short circuit if we are on the add or edit page.
    return FALSE;
  }

  // All good!
  return TRUE;
}

/**
 * Adds form elements for the User plugin to the rule configuration form.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array. New form elements should be
 *   added directly to this array.
 * @param $form_state
 *   A reference to the current form state.
 */
function menu_position_menu_position_rule_user_page_form(&$form, &$form_state) {
  // If this is an existing rule, load the variables stored in the rule for this plugin.
  $variables = !empty($form_state['#menu-position-rule']['conditions']['user_page']) ? $form_state['#menu-position-rule']['conditions']['user_page'] : array();
  // To ensure that the plugin's form elements are placed inside vertical tabs,
  // all elements should be placed inside a collapsed fielset inside the
  // $form['conditions'] array.
  $form['conditions']['user_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('User page'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attached' => array(
      // Ensures a proper summary is added to its vertical tab.
      'js' => array(drupal_get_path('module', 'menu_position') . '/plugins/menu_position.user_page.js'),
    ),
  );
  $form['conditions']['user_page']['user_page_enable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Apply this rule on user account pages.'),
    '#default_value' => !empty($variables['user_page_enable']) ? $variables['user_page_enable'] : 0,
    '#description' => t('Check to apply this rule to user pages, e.g. user/1 or users/admin'),
    '#weight' => -20,
  );

  // Add a submit handler.
  $form['#submit'][] = 'menu_position_menu_position_rule_user_page_form_submit';
}

/**
 * Prepares the plugin's variables to be stored in the rule.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function menu_position_menu_position_rule_user_page_form_submit(&$form, &$form_state) {
  // The user has added our plugin's form elements as a condition for the rule.
  if (!empty($form_state['values']['user_page_enable'])) {
    $variables = array('user_page_enable' => $form_state['values']['user_page_enable']);
    $form_state['values']['conditions']['user_page'] = $variables;
  }
}
