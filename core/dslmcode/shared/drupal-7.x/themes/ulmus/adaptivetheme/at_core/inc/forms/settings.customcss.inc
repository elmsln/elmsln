<?php

/**
 * @file
 * Generate settings for the Custom CSS form.
 */
function at_core_custom_css_form(&$form) {

  $form['at']['custom-styles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Custom CSS'),
    '#weight' => 30,
  );
  $form['at']['custom-styles']['custom_css'] = array(
    '#type' => 'textarea',
    '#title' => t('Custom CSS'),
    '#rows' => 15,
    '#default_value' => at_get_setting('custom_css') ? filter_xss_admin(at_get_setting('custom_css')) : '/* Add any valid CSS declarations */',
    '#description' => t("<p>Styles entered here are saved to <code>themename.custom.css</code>, at the path configured under \"File Management\" settings.</p><p>Direct, manual changes to <code>themename.custom.css</code> will always be overwritten by submitting this form. Consider using a sub-theme for major changes or a CSS file declared in the info file.</p><p>Note that for security reasons you cannot use the greater than symbol (>) as a child combinator selector.</p>"),
  );
}