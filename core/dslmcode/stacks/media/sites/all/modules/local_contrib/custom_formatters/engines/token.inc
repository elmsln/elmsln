<?php
/**
 * @file
 * Token engine for Custom Formatters modules.
 */

/**
 * Implements custom_formatters_engine_hook_theme_alter().
 */
function custom_formatters_engine_token_theme_alter(&$theme) {
  $theme['custom_formatters_token_export'] = array(
    'variables' => array(
      'item' => NULL,
      'module' => NULL,
    ),
    'template' => 'token.export',
    'path' => drupal_get_path('module', 'custom_formatters') . '/engines',
  );
}

/**
 * Settings form callback for Custom Formatters Token engine.
 */
function custom_formatters_engine_token_settings_form(&$form, $form_state, $item) {
  $form['code']['#attributes']['class'][] = 'syntax-html';

  // Additional debugging modes.
  $form['preview']['options']['dpm'] = array(
    '#type' => 'container',
  );
  $form['preview']['options']['dpm']['html'] = array(
    '#type' => 'checkbox',
    '#title' => t('Output raw HTML (requires !devel module).', array('!devel' => l(t('Devel'), 'http://drupal.org/project/devel'))),
    '#default_value' => module_exists('devel'),
    '#disabled' => !module_exists('devel'),
  );

  $options = array();
  foreach (field_info_field_types() as $type => $field) {
    $options[$field['module']][$type] = $field['label'];
  }
  $form['field_types']['#type'] = 'select';
  $form['field_types']['#options'] = $options;
  unset($form['field_types']['#description']);
}

/**
 * Render callback for Custom Formatters Token engine.
 */
function custom_formatters_engine_token_render($formatter, $obj_type, $object, $field, $instance, $langcode, $items, $display) {
  $element = array();

  foreach ($items as $delta => $item) {
    $text = $formatter->code;
    $token_data = array(
      $obj_type => $object,
      'item' => $item,
    );
    drupal_alter('custom_formatters_token_data', $token_data, $text, $field);
    $element[$delta] = array(
      '#markup' => token_replace($text, $token_data, array('clear' => TRUE))
    );
  }

  return $element;
}

/**
 * Export callback for Custom Formatters Token engine.
 */
function custom_formatters_engine_token_export($item, $module) {
  return theme('custom_formatters_token_export', array('item' => $item, 'module' => $module));
}

/**
 * Help callback for Custom Formatters Token engine.
 */
function custom_formatters_engine_token_help() {
  return t('A HTML + Token Formatter utilizes Drupal Tokens and the Token module to create easy yet powerful formatters.') . "<br />\n"
       . t('All available Tokens can be navigated via the Tokens fieldset displayed below the Formatter field.');
}
