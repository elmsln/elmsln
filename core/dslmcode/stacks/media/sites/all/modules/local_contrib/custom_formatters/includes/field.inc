<?php
/**
 * @file
 * Field module integration.
 */

/**
 * Implements hook_field_formatter_info().
 */
function custom_formatters_field_formatter_info() {
  $formatters = array();
  $settings = variable_get('custom_formatters_settings', array('label_prefix' => TRUE, 'label_prefix_value' => t('Custom')));

  foreach (custom_formatters_crud_load_all(TRUE) as $key => $formatter) {
    $label = $settings['label_prefix'] ? "{$settings['label_prefix_value']}: {$formatter->label}" : $formatter->label;
    $formatters["custom_formatters_{$key}"] = array(
      'label' => $label,
      'field types' => drupal_explode_tags($formatter->field_types),
    );

    if (isset($formatter->fapi)) {
      ob_start();
      eval($formatter->fapi);
      ob_get_clean();

      if (isset($form)) {
        $formatters["custom_formatters_{$key}"]['settings'] = array();
        foreach ($form as $form_key => $element) {
          $formatters["custom_formatters_{$key}"]['settings'][$form_key] = isset($element['#default_value']) ? $element['#default_value'] : '';
        }
      }
    }
  }

  return $formatters;
}

/**
 * Implements hook_field_formatter_settings_summary().
 */
function custom_formatters_field_formatter_settings_summary($field, $instance, $view_mode) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $formatter = custom_formatters_crud_load(drupal_substr($display['type'], 18));

  $summary = '';

  if (isset($formatter->fapi)) {
    ob_start();
    eval($formatter->fapi);
    ob_get_clean();

    if (isset($form)) {
      foreach ($form as $key => $element) {
        if (isset($element['#type']) && !in_array($element['#type'], array('fieldset'))) {
          $value = empty($settings[$key]) ? '<em>' . t('Empty') . '</em>' : $settings[$key];
          $value = is_array($value) ? implode(', ', array_filter($value)) : $value;
          $summary .= "{$element['#title']}: {$value}<br />";
        }
      }
      $summary = !empty($summary) ? $summary : ' ';
    }
  }

  return $summary;
}

/**
 * Implements hook_field_formatter_settings_form().
 */
function custom_formatters_field_formatter_settings_form($field, $instance, $view_mode, $form, &$form_state) {
  $display = $instance['display'][$view_mode];
  $settings = $display['settings'];
  $formatter = custom_formatters_crud_load(drupal_substr($display['type'], 18));

  $element = array();

  if (isset($formatter->fapi)) {
    ob_start();
    eval($formatter->fapi);
    ob_get_clean();

    if (isset($form)) {
      $element = $form;
      foreach (array_keys($element) as $key) {
        $element[$key]['#default_value'] = $settings[$key];
      }
    }
  }

  return $element;
}

/**
 * Implements hook_field_formatter_view().
 */
function custom_formatters_field_formatter_view($obj_type, $object, $field, $instance, $langcode, $items, $display, $formatter = NULL) {
  $element = array();

  $formatter = empty($formatter) ? custom_formatters_crud_load(drupal_substr($display['type'], 18)) : $formatter;
  if (isset($formatter) && !empty($items)) {
    $engines = module_invoke_all('custom_formatters_engine_info');
    $engine = $formatter->mode;
    if (isset($engines[$engine]['file']) && file_exists($engines[$engine]['file'])) {
      require_once $engines[$engine]['file'];
    }

    if (function_exists($function = $engines[$engine]['callbacks']['render'])) {
      $element = $function($formatter, $obj_type, $object, $field, $instance, $langcode, $items, $display);
      if (is_string($element)) {
        $element = array(
          array(
            '#markup' => $element,
          ),
        );
      }
      foreach (element_children($element) as $delta) {
        $element[$delta]['#cf_options'] = isset($display['#cf_options']) ? $display['#cf_options'] : array();
      }
    }

    // Allow other modules to modify the element.
    drupal_alter('custom_formatters_field_formatter_view_element', $element, $formatter);
  }

  return $element;
}
