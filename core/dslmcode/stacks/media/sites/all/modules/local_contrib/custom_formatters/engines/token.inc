<?php

/**
 * @file
 * Token engine for Custom Formatters modules.
 */

/**
 * Implements custom_formatters_engine_hook_theme_alter().
 *
 * @param $theme
 */
function custom_formatters_engine_token_theme_alter(&$theme) {
  $theme['custom_formatters_token_export'] = array(
    'variables' => array(
      'item'   => NULL,
      'module' => NULL,
    ),
    'template'  => 'token.export',
    'path'      => drupal_get_path('module', 'custom_formatters') . '/engines',
  );
}

/**
 * Settings form callback for Custom Formatters Token engine.
 *
 * @param $form
 * @param $form_state
 * @param $item
 */
function custom_formatters_engine_token_settings_form(&$form, $form_state, $item) {
  $form['code']['#attributes']['class'][] = 'syntax-html';

  // Additional debugging modes.
  $form['preview']['options']['dpm']         = array(
    '#type' => 'container',
  );
  $form['preview']['options']['dpm']['html'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Output raw HTML (requires !devel module).', array('!devel' => l(t('Devel'), 'http://drupal.org/project/devel'))),
    '#default_value' => module_exists('devel'),
    '#disabled'      => !module_exists('devel'),
  );
}

/**
 * Render callback for Custom Formatters Token engine.
 *
 * @param $formatter
 * @param $obj_type
 * @param $object
 * @param $field
 * @param $instance
 * @param $langcode
 * @param $items
 * @param $display
 *
 * @return array
 */
function custom_formatters_engine_token_render($formatter, $obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {
    $text       = $formatter->code;
    $token_data = array(
      'obj_type' => $obj_type,
      $obj_type  => $object,
      'item'     => $item,
    );
    drupal_alter('custom_formatters_token_data', $token_data, $text, $field, $delta);
    $element[$delta] = array(
      '#markup' => token_replace($text, $token_data, array('clear' => TRUE))
    );
  }

  return $element;
}

/**
 * Export callback for Custom Formatters Token engine.
 *
 * @param $item
 * @param $module
 *
 * @return string
 * @throws Exception
 */
function custom_formatters_engine_token_export($item, $module) {
  return theme('custom_formatters_token_export', array(
    'item'   => $item,
    'module' => $module
  ));
}

