<?php

/**
 * @file
 * Admin page callbacks for the imageinfo cache module.
 */

/**
 * Determines the administration path for a bundle.
 *
 * @param string $entity_type
 *   The type of entity; e.g. 'node' or 'user'.
 * @param string $bundle_name
 *   The bundle name.
 * @param string $field_name
 *   The field name.
 *
 * @return mixed
 *   NULL if no admin path is found; the string of the admin path.
 */
function imageinfo_cache_bundle_admin_path($entity_type, $bundle_name, $field_name) {
  $bundles = field_info_bundles($entity_type);
  if (empty($bundles) || empty($bundles[$bundle_name])) {
    return;
  }
  if (isset($bundles[$bundle_name]['admin'])) {
    $return = isset($bundles[$bundle_name]['admin']['real path'])
      ? $bundles[$bundle_name]['admin']['real path']
      : $bundles[$bundle_name]['admin']['path'];
    $return .= '/fields/' . $field_name;
    return $return;
  }
}

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 *
 * @return array
 *   Configuration form.
 */
function imageinfo_cache_admin_settings_form() {
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
  $form['imageinfo_cache_getimagesize'] = array(
    '#type' => 'checkbox',
    '#title' => t('Cache calls to getimagesize()'),
    '#default_value' => variable_get('imageinfo_cache_getimagesize', IMAGEINFO_CACHE_GETIMAGESIZE),
    '#description' => t('Useful if your filesystem is not local. Uses a wrapper around calls to the real image toolkit; putting caching in optimal places.'),
  );
  $form['imageinfo_cache_disable_on_demand_generation'] = array(
    '#type' => 'checkbox',
    '#title' => t('Disable on-demand generation'),
    '#default_value' => variable_get('imageinfo_cache_disable_on_demand_generation', IMAGEINFO_CACHE_DISABLE_ON_DEMAND_GENERATION),
    '#description' => t('Disable image style generation from the URL. Images can be generated from the URL only if you have the "administer image styles" permission.'),
  );
  if (variable_get('image_allow_insecure_derivatives', FALSE)) {
    $form['imageinfo_cache_strip_image_token'] = array(
      '#type' => 'checkbox',
      '#title' => t('Remove itok from images'),
      '#default_value' => variable_get('imageinfo_cache_strip_image_token', IMAGEINFO_CACHE_STRIP_IMAGE_TOKEN),
      '#description' => t('Sometimes the ?itok=___ query parameter can cause issues. Enabling this will remove itok from image style output.'),
    );
  }

  $form['pre_generation'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pre Generation of Image Styles'),
    '#description' => t('Styles that end with * are enabled by default as they are being used for that field.'),
  );

  $instances = field_info_instances();
  $bundles = field_info_bundles();
  $field_admin_paths = array();
  foreach ($instances as $entity_type => $type_bundles) {
    foreach ($type_bundles as $bundle => $bundle_instances) {
      foreach ($bundle_instances as $field_name => $instance) {
        $admin_path = imageinfo_cache_bundle_admin_path($entity_type, $bundle, $field_name);
        if (!empty($admin_path)) {
          if (empty($field_admin_paths[$field_name])) {
            $field_admin_paths[$field_name] = l($bundles[$entity_type][$bundle]['label'], $admin_path);
          }
          else {
            $field_admin_paths[$field_name] .= ', ' . l($bundles[$entity_type][$bundle]['label'], $admin_path);
          }
        }
      }
    }
  }

  // Get image styles.
  $image_styles = array_keys(image_styles());
  $image_styles = array_combine($image_styles, $image_styles);
  ksort($image_styles);

  // Get image fields.
  $image_field_defaults = imageinfo_cache_get_image_fields(FALSE, FALSE);
  $image_fields = imageinfo_cache_get_image_fields(TRUE, FALSE);
  $all_image_styles_used = array();
  foreach ($image_fields as $field_name => $image_styles_used) {
    if (isset($image_styles_used['#field_info'])) {
      unset($image_styles_used['#field_info']);
    }
    $image_styles_used = array_keys($image_styles_used);

    // Create the fieldset.
    $form['pre_generation']['field_' . $field_name] = array(
      '#type' => 'fieldset',
      '#title' => t('@field_name: @styles_checked_count in use', array(
        '@field_name' => strpos($field_name, 'field_') === 0 ? substr($field_name, 6) : $field_name,
        '@styles_checked_count' => format_plural(count($image_styles_used), '1 style', '@count styles'),
      )),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );
    if (!empty($field_admin_paths[$field_name])) {
      $form['pre_generation']['field_' . $field_name]['field_definition'] = array(
        '#markup' => '<div>' . t('Field defined in these entity bundles: !bundles.', array(
          '!bundles' => $field_admin_paths[$field_name],
          )) . '</div>',
      );
    }
    $views = imageinfo_cache_get_image_styles_in_views($field_name, TRUE);
    if (!empty($views)) {
      $form['pre_generation']['field_' . $field_name]['used_in_views'] = array(
        '#markup' => '<div>' . t('Views used for display: !views.', array(
          '!views' => $views,
          )) . '</div>',
      );
    }

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
    '#type' => 'markup',
    '#markup' => '<div><strong>' . t('Image styles not in use') . "</strong></br>\n" . implode("</br>\n", $styles_not_used) . '</div>',
    '#disabled' => TRUE,
  );

  // Output all imageinfo cache hooks implemented.
  $hooks_implemented = imageinfo_cache_hooks();
  foreach ($hooks_implemented as $hook => $values) {
    if (empty($values)) {
      $form['hooks_implemented'][$hook] = array(
        '#markup' => '<div><strong>' . check_plain($hook) . ':</strong> 0</div>',
      );
    }
    else {
      $form['hooks_implemented'][$hook] = array(
        '#markup' => '<div><strong>' . check_plain($hook) . ':</strong> ' . count($values) . '<br />&nbsp;&nbsp;' . filter_xss(implode('<br />&nbsp;&nbsp;', $values), array('br')) . '</div>',
      );
    }
  }
  $form['hooks_implemented'] += array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Imageinfo Cache hooks implemented by modules'),
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
 *
 * @param array $form
 *   Drupal form array.
 * @param array $form_state
 *   Drupal form state.
 */
function imageinfo_cache_admin_settings_form_submit(array $form, array &$form_state) {
  // Flush the menu cache if imageinfo_cache_disable_on_demand_generation is
  // changing state.
  $new = $form_state['values']['imageinfo_cache_disable_on_demand_generation'];
  $old = variable_get('imageinfo_cache_disable_on_demand_generation', IMAGEINFO_CACHE_DISABLE_ON_DEMAND_GENERATION);
  if ($new !== $old) {
    drupal_set_message(t('Rebuilding the menu cache.'));
    $GLOBALS['conf']['imageinfo_cache_disable_on_demand_generation'] = $new;
    drupal_register_shutdown_function('menu_rebuild');
  }

  $op = isset($form_state['values']['op']) ? $form_state['values']['op'] : '';
  if ($op === t('Reset to defaults')) {
    foreach ($form_state['values'] as $key => $value) {
      if (is_array($value)) {
        variable_del($key);
      }
      elseif (strpos($key, 'imageinfo_cache_') === 0) {
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
  $image_fields = imageinfo_cache_get_image_fields(FALSE, FALSE);
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
    elseif (strpos($field_name, 'imageinfo_cache_') === 0) {
      variable_set($field_name, $selection);
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
