<?php
/**
 * @file
 * Administrative form for the SVG Sanitizer module.
 */

/**
 * SVG Sanitizer admin configuration form.
 */
function svg_sanitizer_admin_config_form($form, &$form_state) {
  $form['svg_sanitizer_allowedattrs'] = array(
   '#title' => t('Allowed Attributes'),
   '#type' => 'textarea',
   '#description' => t('Comma separated list of custom attributes that should be added to the list of allowed attributes'),
   '#default_value' => implode(', ', variable_get('svg_sanitizer_allowedattrs', array())),
  );

  $form['svg_sanitizer_allowedtags'] = array(
   '#title' => t('Allowed Tags'),
   '#type' => 'textarea',
   '#description' => t('Comma separated list of custom tags that should be added to the list of allowed tags'),
   '#default_value' => implode(', ', variable_get('svg_sanitizer_allowedtags', array())),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Submit',
  );

  return $form;
}

/**
 * Submit handler for svg_sanitizer_admin_config_form()
 */
function svg_sanitizer_admin_config_form_submit($form, &$form_state) {
  $allowed_attributes = $form_state['values']['svg_sanitizer_allowedattrs'];
  $allowed_tags = $form_state['values']['svg_sanitizer_allowedtags'];
  // convert the attributes & tags into an array
  $allowed_attributes = _svg_sanitizer_variable_formatter($allowed_attributes);
  $allowed_tags = _svg_sanitizer_variable_formatter($allowed_tags);

  // Set the attributes in the svg_sanitizer_allowedattrs variable
  // as an array
  variable_set('svg_sanitizer_allowedattrs', $allowed_attributes);
  variable_set('svg_sanitizer_allowedtags', $allowed_tags);
  drupal_set_message(t('Settings have been updated.'), 'status');
}

/**
 * Helper function to format the form values to variable arrays
 * @param  [string] $variable Comma separated string that will be converted an array.
 */
function _svg_sanitizer_variable_formatter($variable) {
  $array = array();

  if (is_string($variable)) {
    // trim the whitespace from the attributes
    $variable = explode(',', $variable);
    foreach ($variable as $key => $value) {
      $array[$key] = trim($value);
    }
  }
  else {
    watchdog('_svg_sanitizer_variable_formatter', 'Argument needs to be a string.', array(), WATCHDOG_NOTICE);
  }

  return $array;
}