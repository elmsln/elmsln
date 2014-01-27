<?php
/**
 * @file
 * Provides the "User roles" rule plugin for the Menu Position module.
 */

/**
 * Checks if the currently logged in user has a certain role.
 *
 * @param $variables
 *   An array containing each of the variables saved in the database necessary
 *   to evaluate this condition of the rule.
 * @return
 *   TRUE if condition applies successfully. Otherwise FALSE.
 */
function menu_position_menu_position_condition_user_role($variables) {
  // Check for the roles the currently logged in user has.
  foreach (array_keys($GLOBALS['user']->roles) as $role_id) {
    if (array_key_exists($role_id, $variables['user_role'])) {
      return TRUE;
    }
  }
  return FALSE;
}

/**
 * Adds form elements for the "user role" plugin to the rule configuration form.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array. New form elements should be
 *   added directly to this array.
 * @param $form_state
 *   A reference to the current form state.
 */
function menu_position_menu_position_rule_user_role_form(&$form, &$form_state) {
  // If this is an existing rule, load the variables stored in the rule for this plugin.
  $variables = !empty($form_state['#menu-position-rule']['conditions']['user_role']) ? $form_state['#menu-position-rule']['conditions']['user_role'] : array();

  $form['conditions']['user_role'] = array(
    '#type' => 'fieldset',
    '#title' => t('User roles'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'menu_position') . '/plugins/menu_position.user_roles.js'),
    ),
  );
  $form['conditions']['user_role']['user_role'] = array(
    '#type' => 'checkboxes',
    '#title' => t('User roles'),
    '#default_value' => !empty($variables['user_role']) ? $variables['user_role'] : array(),
    '#options' => user_roles(TRUE),
    '#description' => t('Apply this rule on pages when the currently logged in user has this role(s).'),
    '#weight' => -20,
  );

  // Add a submit handler.
  $form['#submit'][] = 'menu_position_menu_position_rule_user_role_form_submit';
}

/**
 * Prepares the "user role" variables to be stored in the rule.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function menu_position_menu_position_rule_user_role_form_submit(&$form, &$form_state) {
  // The user has added our plugin's form elements as a condition for the rule.
  if (!empty($form_state['values']['user_role'])) {
    // Remove any 0 valued options.
    foreach ($form_state['values']['user_role'] as $key => $value) {
      if ($value === 0) {
        unset($form_state['values']['user_role'][$key]);
      }
    }
    // Determine if any checkboxes were on.
    if (!empty($form_state['values']['user_role'])) {
      // Add this plugin's variables to the rule.
      $variables = array(
        'user_role' => $form_state['values']['user_role'],
      );
      $form_state['values']['conditions']['user_role'] = $variables;
    }
  }
}
