<?php

/**
 * @file
 * Admin page callbacks for the imageinfo cache module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function imageinfo_cache_admin_settings_form($form, $form_state) {
  drupal_set_title(t('Imageinfo Cache Configuration'));
  module_load_include('inc', 'imageinfo_cache', 'imageinfo_cache');
  $form = array();

  $form['imageinfo_cache_use_httprl'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use HTTPRL for background image generation'),
    '#default_value' => module_exists('httprl') ? variable_get('imageinfo_cache_use_httprl', IMAGEINFO_CACHE_USE_HTTPRL) : FALSE,
    '#description' => t('If <a href="@link">HTTPRL</a> is installed, image styles will be generated in a background parallel process, thus not slowing down entity saves and image file uploads.', array('@link' => 'http://drupal.org/project/httprl')),
    '#disabled' => module_exists('httprl') ? FALSE : TRUE,
  );

  $form['pre_generation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pre Generation of Image Styles'),
    '#description' => t('Styles that end with * are enabled by default as they are being used for that field.'),
  );

  // Get image styles.
  $image_styles = array_keys(image_styles());
  $image_styles = array_combine($image_styles, $image_styles);
  ksort($image_styles);

  // Get image fields.
  $image_field_defaults = imageinfo_cache_get_image_fields(FALSE);
  $image_fields = imageinfo_cache_get_image_fields();
  $all_image_styles_used = array();
  foreach ($image_fields as $field_name => $image_styles_used) {
    if (isset($image_styles_used['#field_info'])) {
      unset($image_styles_used['#field_info']);
    }
    $image_styles_used = array_keys($image_styles_used);

    // Create the fieldset.
    $form['pre_generation']['field_' . $field_name] = array(
      '#type' => 'fieldset',
      '#title' => t('@field_name: @styles_checked', array(
        '@field_name' => strpos($field_name, 'field_') === 0 ? substr($field_name, 6) : $field_name,
        '@styles_checked' => implode(', ', $image_styles_used),
      )),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    // Add a * to the end of default styles.
    if (isset($image_field_defaults[$field_name]['#field_info'])) {
      unset($image_field_defaults[$field_name]['#field_info']);
    }
    $temp_image_styles = array();
    foreach ($image_styles as $key => $style_name) {
      if (!empty($image_field_defaults[$field_name][$style_name])) {
        $style_name .= '*';
      }
      $temp_image_styles[$key] = $style_name;
    }

    // Create the checkboxes field.
    $form['pre_generation']['field_' . $field_name]['imageinfo_cache_' . $field_name] = array(
      '#type' => 'checkboxes',
      '#options' => $temp_image_styles,
      '#default_value' => $image_styles_used,
    );
    $all_image_styles_used = array_merge($all_image_styles_used, $image_styles_used);
  }
  $all_image_styles_used = array_values(array_unique($all_image_styles_used));
  $all_image_styles_used = array_combine($all_image_styles_used, $all_image_styles_used);
  ksort($all_image_styles_used);
  $styles_not_used = array_diff($image_styles, $all_image_styles_used);

  $form['pre_generation']['styles_not_in_use'] = array(
    '#type' => 'textfield',
    '#title' => 'Image Styles Not in Use',
    '#value' => implode(', ', $styles_not_used),
  );

  $form['buttons']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset to defaults'),
  );

  // Clear the cache bins on submit.
  $form['#submit'][] = 'imageinfo_cache_admin_settings_form_submit';

  $form['actions']['#type'] = 'actions';
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );
  // By default, render the form using theme_system_settings_form().
  $form['#theme'] = 'system_settings_form';
  return $form;
}

// Submit callback.
/**
 * Only record the non-default presets.
 */
function imageinfo_cache_admin_settings_form_submit($form, &$form_state) {
  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
  if ($op == t('Reset to defaults')) {
    foreach ($form_state['values'] as $key => $value) {
      if (is_array($value)) {
        variable_del($key);
      }
    }
    drupal_set_message(t('The configuration options have been reset to their default values.'));
    return;
  }

  module_load_include('inc', 'imageinfo_cache', 'imageinfo_cache');

  // Get image styles; set value to 0.
  $image_styles = array_fill_keys(array_keys(image_styles()), 0);

  // Get the default values.
  $default_values = array();
  $image_fields = imageinfo_cache_get_image_fields(FALSE);
  foreach ($image_fields as $field_name => &$image_styles_used) {
    if (isset($image_styles_used['#field_info'])) {
      unset($image_styles_used['#field_info']);
    }
    $image_styles_used = array_keys($image_styles_used);
    if (empty($image_styles_used)) {
      $default_values['imageinfo_cache_' . $field_name] = array();
    }
    else {
      $default_values['imageinfo_cache_' . $field_name] = array_combine($image_styles_used, $image_styles_used);
    }

    // Add in not selected image styles.
    if (!is_array($default_values['imageinfo_cache_' . $field_name])) {
      $default_values['imageinfo_cache_' . $field_name] = array();
    }
    $default_values['imageinfo_cache_' . $field_name] += $image_styles;
    ksort($default_values['imageinfo_cache_' . $field_name]);
  }

  // Get the saved values.
  $values = array();
  foreach ($form_state['values'] as $field_name => $selection) {
    if (is_array($selection) && isset($default_values[$field_name])) {
      ksort($selection);
      $values[$field_name] = $selection;
    }
  }

  // Compute the array difference.
  $array_diff = array();
  foreach ($default_values as $field_name => $image_styles_used) {
    $array_diff[$field_name] = array_diff_assoc($values[$field_name], $image_styles_used);
  }

  // Save values.
  foreach ($array_diff as $key => $value) {
    if (empty($value)) {
      variable_del($key);
    }
    variable_set($key, $value);
  }
  drupal_set_message(t('The configuration options have been saved.'));
}
