<?php
/**
 * @file
 * System module integration.
 */

/**
 * Implements hook_init().
 */
function custom_formatters_init() {
  module_invoke_all('custom_formatters_init');
}

/**
 * Implements hook_element_info().
 */
function custom_formatters_element_info() {
  $types = array();
  drupal_alter('custom_formatters_element_info', $types);
  return $types;
}

/**
 * Implements hook_theme().
 */
function custom_formatters_theme() {
  $theme = array();
  drupal_alter('custom_formatters_theme', $theme);
  return $theme;
}

/**
 * Implements hook_form_alter().
 */
function custom_formatters_form_alter(&$form, &$form_state, $form_id) {
  drupal_alter('custom_formatters_form_alter', $form, $form_state, $form_id);
  drupal_alter("custom_formatters_form_{$form_id}_alter", $form, $form_state);
}
