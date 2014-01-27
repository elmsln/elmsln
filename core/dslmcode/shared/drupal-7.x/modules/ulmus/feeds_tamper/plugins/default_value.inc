<?php

/**
 * @file
 * Set field to default value.
 */

$plugin = array(
  'form'     => 'feeds_tamper_default_value_form',
  'callback' => 'feeds_tamper_default_value_callback',
  'name'     => 'Set default value',
  'multi'    => 'direct',
  'category' => 'Other',
);

function feeds_tamper_default_value_form($importer, $element_key, $settings) {
  $form = array();

  $form['default_value'] = array(
    '#type' => 'textarea',
    '#title' => t('Default value'),
    '#default_value' => isset($settings['default_value']) ? $settings['default_value'] : '',
    '#description' => t('This field will be set to the value specified.'),
  );
  return $form;
}

function feeds_tamper_default_value_callback($source, $item_key, $element_key, &$field, $settings) {
  $field = $settings['default_value'];
}
