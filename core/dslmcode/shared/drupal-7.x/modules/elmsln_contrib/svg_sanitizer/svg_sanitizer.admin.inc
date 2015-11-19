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
  // convert the attributes into an array
  $allowed_attributes = explode(',', $allowed_attributes);
  // trim the whitespace from the attributes
  foreach ($allowed_attributes as $key => $attribute) {
    $allowed_attributes[$key] = trim($attribute);
  }

  // Set the attributes in the svg_sanitizer_allowedattrs variable
  // as an array
  variable_set('svg_sanitizer_allowedattrs', $allowed_attributes);
  drupal_set_message(t('Settings have been updated.'), 'status');
}
