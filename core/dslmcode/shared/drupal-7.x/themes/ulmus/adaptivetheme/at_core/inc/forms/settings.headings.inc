<?php

/**
 * @file
 * Generate form elments for the Headings Styles settings.
 */
function at_core_headings_form(&$form) {
  // Title styles
  $form['at']['titles'] = array(
    '#type' => 'fieldset',
    '#title' => t('Title Styles'),
    '#description' => t('<h3>Title Styles</h3><p>Add extra styles to headings. Text shadows only work for CSS3 capable browsers such as Firefox, Safari, IE9 etc.</p>'),
    '#weight' => -100,
  );

  // Array of valid title types
  $headings_valid_types = array(
    'site_name',
    'site_slogan',
    'page_title',
    'node_title',
    'block_title',
    'comment_title',
  );

  // Get the fonts list
  $form_elements = font_elements();

  foreach ($form_elements as $key => $value) {

    $heading = $key;

    if (in_array($heading, $headings_valid_types)) {

      $element = $value['element'];  // e.g. "ptf" (page_title_font), this is used to set array keys and eventually body classes
      $setting = $heading; // use the key for these settings, it doesnt have "font" in it
      $container = $value['setting'];  // the theme setting used to retrieve the font values, e.g. "site_name_font"

      $setting_container = str_replace('_', '-', $container) . '-style'; // a nicer string for fielset classes
      $title = str_replace('_', ' ', drupal_ucfirst($heading)); // use the key for titles, it doesnt have "font" in it

      // Set easy reusable variables
      $setting_case       = $setting . '_case';
      $setting_weight     = $setting . '_weight';
      $setting_alignment  = $setting . '_alignment';
      $setting_shadow     = $setting . '_shadow';

      // Fieldset wrapper for each title
      $form['at']['titles']['' . $setting_container . '']  = array(
        '#type' => 'fieldset',
        '#title' => t($title),
        '#description' => t("<strong>$title</strong>"),
        '#attributes' => array('class' => array('headings-styles-wrapper')),
      );

      // Case
      $form['at']['titles']['' . $setting_container . '']['' . $setting_case . ''] = array(
        '#type' => 'select',
        '#title' => t('Case'),
        '#default_value' => at_get_setting($setting_case),
        '#options' => font_style_options('case', $element),
      );

      // Weight
      $form['at']['titles']['' . $setting_container . '']['' . $setting_weight . ''] = array(
        '#type' => 'select',
        '#title' => t('Weight'),
        '#default_value' => at_get_setting($setting_weight),
        '#options' => font_style_options('weight', $element),
      );

      // Alignment
      $form['at']['titles']['' . $setting_container . '']['' . $setting_alignment . ''] = array(
        '#type' => 'select',
        '#title' => t('Alignment'),
        '#default_value' => at_get_setting($setting_alignment),
        '#options' => font_style_options('alignment', $element),
      );

      // Text shadow
      $form['at']['titles']['' . $setting_container . '']['' . $setting_shadow . ''] = array(
        '#type' => 'select',
        '#title' => t('Shadow'),
        '#default_value' => at_get_setting($setting_shadow),
        '#options' => font_style_options('shadow', $element),
      );
    }
  }
}
