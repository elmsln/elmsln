<?php
/**
 * @file
 * Written by Henri MEDOT <henri.medot[AT]absyx[DOT]fr>
 * http://www.absyx.fr
 */

function ckeditor_link_settings_form() {
  $form['general'] = array(
    '#type' => 'fieldset',
    '#title' => t('General settings'),
  );
  $form['general']['ckeditor_link_type_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Link type name'),
    '#description' => t('The name of the option added to the Link Type select box. Enter %site_name to use the name of this website.', array('%site_name' => '!site_name')),
    '#default_value' => variable_get('ckeditor_link_type_name', 'Internal path'),
  );
  $form['general']['ckeditor_link_type_selected'] = array(
    '#type' => 'checkbox',
    '#title' => t('Selected by default'),
    '#description' => t('Whether the %link_type link type should be selected by default instead of the URL link type.', array('%link_type' => ckeditor_link_get_link_type_name())),
    '#default_value' => variable_get('ckeditor_link_type_selected', 1),
  );
  $form['general']['ckeditor_link_limit'] = array(
    '#type' => 'select',
    '#title' => t('Number of suggestions'),
    '#description' => t('The maximum number of suggestions to display on autocomplete.'),
    '#options' => drupal_map_assoc(array(10, 15, 20, 25, 30, 40, 50, 60, 70, 80, 90, 100)),
    '#default_value' => variable_get('ckeditor_link_limit', 10),
  );

  $types = ckeditor_link_get_types();
  foreach ($types as $type) {
    $func = $type['module'] .'_ckeditor_link_'. $type['type'] .'_settings';
    if (function_exists($func)) {
      $form = array_merge($form, $func());
    }
  }

  return system_settings_form($form);
}
