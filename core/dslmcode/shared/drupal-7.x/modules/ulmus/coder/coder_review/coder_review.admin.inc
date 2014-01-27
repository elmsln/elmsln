<?php

/**
 * @file
 * Administrative forms and functions for the Coder module.
 */

/**
 * Page callback: Configures administrative settings via system_settings_form().
 *
 * @see coder_review_menu()
 * @see coder_review_settings_form_submit()
 */
function coder_review_admin_settings($form, &$form_state) {
  // Bootstrap enough to run.
  require_once realpath(dirname(__FILE__)) . '/coder_review.common.inc';

  $settings = _coder_review_get_default_settings();
  $form = _coder_review_settings_form($settings, $system, $files);
  $form['help'] = array(
    '#type' => 'markup',
    '#markup' => t('After setting these defaults, use <a href="@url">coder review</a> to perform code reviews.', array('@url' => url('admin/config/development/coder/review'))),
    '#weight' => -1,
  );
  $form['#submit'][] = 'coder_review_settings_form_submit';
  return system_settings_form($form);
}

/**
 * Form submission handler for coder_review_admin_settings().
 */
function coder_review_settings_form_submit($form, &$form_state) {
  $form_state['storage'] = $form_state['values'];
  variable_set('coder_modules', _coder_review_settings_array($form_state, 'module'));
  variable_set('coder_themes', _coder_review_settings_array($form_state, 'theme'));
}

/**
 * Returns HTML for the modules form.
 *
 * This was copied from theme_system_modules_fieldset() and modified to handle
 * additional links.
 *
 * @param array $variables
 *   An associative array containing the key:
 *   - form: A render element representing the form.
 *
 * @ingroup themeable
 *
 * @todo Create an issue for this and get this function into D8.
 */
function theme_coder_review_modules_fieldset($variables) {
  $form = $variables['form'];

  // Individual table headers.
  $rows = array();
  // Iterate through all of the modules to Determine the available operations.
  $children = element_children($form);
  $operations = drupal_map_assoc(array('help', 'permissions', 'configure'));
  foreach ($children as $key) {
    $links = array_filter(array_keys($form[$key]['links']), function ($var) {
      return $var && $var[0] != '#';
    });
    if ($links) {
      $operations += drupal_map_assoc($links);
    }
  }
  // Iterate through all the modules.
  foreach ($children as $key) {
    // Stick it into $module for easier accessing.
    $module = $form[$key];
    $row = array();
    unset($module['enable']['#title']);
    $row[] = array('class' => array('checkbox'), 'data' => drupal_render($module['enable']));
    $label = '<label';
    if (isset($module['enable']['#id'])) {
      $label .= ' for="' . $module['enable']['#id'] . '"';
    }
    $row[] = $label . '><strong>' . drupal_render($module['name']) . '</strong></label>';
    $row[] = drupal_render($module['version']);
    // Add the description, along with any modules it requires.
    $description = drupal_render($module['description']);
    if ($module['#requires']) {
      $description .= '<div class="admin-requirements">' . t('Requires: !module-list', array('!module-list' => implode(', ', $module['#requires']))) . '</div>';
    }
    if ($module['#required_by']) {
      $description .= '<div class="admin-requirements">' . t('Required by: !module-list', array('!module-list' => implode(', ', $module['#required_by']))) . '</div>';
    }
    $row[] = array('data' => $description, 'class' => array('description'));
    // Display links (such as help or permissions) in their own columns.
    foreach ($operations as $key) {
      $row[] = array('data' => drupal_render($module['links'][$key]), 'class' => array($key));
    }
    $form['#header'][4]['colspan'] = count($operations);
    $rows[] = $row;
  }

  return theme('table', array('header' => $form['#header'], 'rows' => $rows));
}
