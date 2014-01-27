<?php
/**
 * @file
 * Provides the "Pages" rule plugin for the Menu Position module.
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
function menu_position_menu_position_condition_pages($variables) {
  // Grab the variables stored statically in the rule.
  $pages = $variables['pages'];

  // Convert the Drupal path to lowercase.
  $path = drupal_strtolower(drupal_get_path_alias($_GET['q']));
  // Compare the lowercase internal and lowercase path alias (if any).
  $page_match = drupal_match_path($path, $pages);
  if (!$page_match && $path != $_GET['q']) {
    $page_match = drupal_match_path($_GET['q'], $pages);
  }

  return $page_match;
}

/**
 * Adds form elements for the "node type" plugin to the rule configuration form.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array. New form elements should be
 *   added directly to this array.
 * @param $form_state
 *   A reference to the current form state.
 */
function menu_position_menu_position_rule_pages_form(&$form, &$form_state) {
  // If this is an existing rule, load the variables stored in the rule for this plugin.
  $variables = !empty($form_state['#menu-position-rule']['conditions']['pages']) ? $form_state['#menu-position-rule']['conditions']['pages'] : array();

  $form['conditions']['pages'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#attached' => array(
      'js' => array(drupal_get_path('module', 'menu_position') . '/plugins/menu_position.pages.js'),
    ),
  );
  $form['conditions']['pages']['pages'] = array(
    '#type' => 'textarea',
    '#title' => t('Pages'),
    '#default_value' => !empty($variables['pages']) ? $variables['pages'] : '',
    '#description' => t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>')),
    '#weight' => -20,
  );

  // Add a submit handler.
  $form['#submit'][] = 'menu_position_menu_position_rule_pages_form_submit';
}

/**
 * Prepares the "node type" variables to be stored in the rule.
 *
 * @param $form
 *   A reference to the "add/edit rule" form array.
 * @param $form_state
 *   A reference to the current form state, including submitted values.
 */
function menu_position_menu_position_rule_pages_form_submit(&$form, &$form_state) {
  // The user has added our plugin's form elements as a condition for the rule.
  if (!empty($form_state['values']['pages'])) {
    // Add this plugin's variables to the rule.
    $variables = array(
      'pages' => drupal_strtolower(trim($form_state['values']['pages'])),
    );
    $form_state['values']['conditions']['pages'] = $variables;
  }
}
