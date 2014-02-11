<?php
/**
 * @file
 * Image module integration.
 */

/**
 * Implements hook_custom_formatters_theme_alter() on behalf of image.module.
 */
function image_custom_formatters_theme_alter(&$theme) {
  $theme['custom_formatters_image_styles'] = array(
    'render element' => 'element',
    'file' => 'includes/image.inc',
  );
}

/**
 * Implements hook_custom_formatters_element_info_alter() on behalf of
 * image.module.
 */
function image_custom_formatters_element_info_alter(&$types) {
  $types['custom_formatters_image_styles'] =  array(
    '#input' => TRUE,
    '#multiple' => FALSE,
    '#process' => array('form_process_select', 'ajax_process_form'),
    '#theme' => 'custom_formatters_image_styles',
    '#theme_wrappers' => array('form_element'),
  );
}

/**
 * Implements hook_custom_formatters_form_builder_types_alter() on behalf of
 * image.module.
 */
function image_custom_formatters_form_builder_types_alter(&$fields) {
  $fields['image_styles'] = array(
    'title' => t('Image styles'),
    'properties' => array(
      'title',
      'description',
      'default_value',
      'required',
      'key',
    ),
    'default' => array(
      '#title' => t('New styles selector'),
      '#type' => 'custom_formatters_image_styles',
      '#multiple_toggle' => TRUE,
    ),
  );
}

/**
 * Theme callback for Custom Formatters Image Styles element.
 */
function theme_custom_formatters_image_styles($variables) {
  $element = $variables['element'];
  $element['#options'] = image_style_options();
  element_set_attributes($element, array('id', 'name', 'size'));
  _form_set_class($element, array('form-select'));

  return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
}
