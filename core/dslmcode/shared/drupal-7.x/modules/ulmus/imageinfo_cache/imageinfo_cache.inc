<?php

/**
 * @file
 * Imageinfo Cache module. Helper functions.
 */

/**
 * Get all fields that contain an image.
 *
 * @return array
 *   An array of imagefields.
 */
function imageinfo_cache_get_fields_with_images() {
  $image_fields = &drupal_static(__FUNCTION__);

  if (!isset($image_fields)) {
    $instances = field_info_instances();
    $image_fields = array();
    foreach ($instances as $entity_instances) {
      foreach ($entity_instances as $bundle_fields) {
        foreach ($bundle_fields as $field_values) {
          $image_type = imageinfo_cache_detect_image_widget($field_values['widget']);
          if (!empty($image_type)) {
            $image_fields[$field_values['field_name']]['#field_info'][] = $field_values;
          }
        }
      }
    }
  }
  return $image_fields;
}

/**
 * Get all fields that contain an image and what styles are used in it.
 *
 * @param bool $run_alter
 *   (optional) Run hook alter inside of imageinfo_cache_get_styles_in_use().
 *   Default is TRUE.
 *
 * @return array
 *   An array of imagefields and styles.
 */
function imageinfo_cache_get_image_fields($run_alter = TRUE) {
  $image_fields = imageinfo_cache_get_fields_with_images();
  foreach ($image_fields as $field_name => $values) {
    foreach ($values['#field_info'] as $field_values) {
      $image_fields[$field_name] += imageinfo_cache_get_styles_in_use($field_values, $run_alter);
    }
  }
  return $image_fields;
}

/**
 * Generates all in use presets given a field instance and a file uri.
 *
 * @param array $instance_field
 *   Field array from field_info_instances().
 * @param bool $run_alter
 *   (optional) Run hook alter. Default is TRUE.
 *
 * @return array
 *   An array of what styles are used in this field.
 */
function imageinfo_cache_get_styles_in_use($instance_field, $run_alter = TRUE) {
  $return = array();
  // Do nothing if the image module does not exist.
  if (!module_exists('image')) {
    return $return;
  }

  // Do nothing if no image styles are defined.
  $image_styles = image_styles();
  if (empty($image_styles) || !is_array($image_styles)) {
    return $return;
  }

  // Get the presets used in display previews.
  $styles = array();
  foreach ($instance_field as $values) {
    if (!is_array($values) || empty($values['settings'])) {
      continue;
    }
    if (!empty($values['settings']['preview_image_style']) && !empty($image_styles[$values['settings']['preview_image_style']])) {
      $styles[$values['settings']['preview_image_style']] = $image_styles[$values['settings']['preview_image_style']];
    }
  }

  // Get the presets used in displays.
  foreach ($instance_field['display'] as $values) {
    if (!is_array($values) || empty($values['settings'])) {
      continue;
    }
    // Core.
    if (!empty($values['settings']['image_style']) && !empty($image_styles[$values['settings']['image_style']])) {
      $styles[$values['settings']['image_style']] = $image_styles[$values['settings']['image_style']];
    }
    // Newer lightbox.
    if (!empty($values['settings']['lightbox_style']) && !empty($image_styles[$values['settings']['lightbox_style']])) {
      $styles[$values['settings']['lightbox_style']] = $image_styles[$values['settings']['lightbox_style']];
    }
  }

  // Get the presets used in displays by older lightbox.
  foreach ($instance_field['display'] as $values) {
    if (!is_array($values) || empty($values['type']) || empty($values['module']) || $values['module'] != 'lightbox2' || substr_count($values['type'], '__') != 3) {
      continue;
    }
    $pieces = explode('__', $values['type']);
    if (!empty($image_styles[$pieces[2]])) {
      $styles[$pieces[2]] = $image_styles[$pieces[2]];
    }
    if (!empty($image_styles[$pieces[3]])) {
      $styles[$pieces[3]] = $image_styles[$pieces[3]];
    }
  }

  // Get the presets used in views.
  $image_styles_in_views = imageinfo_cache_get_image_styles_in_views($instance_field['field_name']);
  foreach ($image_styles_in_views as $image_style_name) {
    if (!empty($image_styles[$image_style_name])) {
      $styles[$image_style_name] = $image_styles[$image_style_name];
    }
  }

  // Get the presets used in file entities.
  foreach (imageinfo_cache_get_image_styles_in_file_entity($instance_field) as $image_style_name) {
    if (!empty($image_styles[$image_style_name])) {
      $styles[$image_style_name] = $image_styles[$image_style_name];
    }
  }

  // Allow for the $styles to be altered.
  if ($run_alter) {
    // Run hook_imageinfo_cache_styles_alter().
    drupal_alter('imageinfo_cache_styles', $styles, $instance_field['field_name']);
  }

  return $styles;
}

/**
 * Given a field instance will return images styles used in file_entity.
 *
 * @param array $instance_field
 *   Field array from field_info_instances().
 *
 * @return array
 *   An array of what styles are used in this field.
 */
function imageinfo_cache_get_image_styles_in_file_entity($instance_field) {
  if (!module_exists('file_entity')) {
    return array();
  }

  $image_style_names = array();
  foreach ($instance_field['display'] as $values) {
    if (empty($values['settings']['file_view_mode'])) {
      continue;
    }
    $image_style_names = array_merge($image_style_names, imageinfo_cache_get_presets_in_file_view_mode($values['settings']['file_view_mode']));
  }
  return array_values(array_unique($image_style_names));
}

/**
 * Given a field instance will return images styles used in file_entity.
 *
 * @param string $view_mode
 *   Name of the file_entity view.
 *
 * @return array
 *   An array of what styles are used in this field.
 */
function imageinfo_cache_get_presets_in_file_view_mode($view_mode) {
  if (!module_exists('file_entity')) {
    return array();
  }

  $formatters = &drupal_static(__FUNCTION__);
  $file_type = 'image';
  if (!isset($formatters)) {
    $formatters = file_info_formatter_types();
    foreach ($formatters as $name => $formatter) {
      if (isset($formatter['file types']) && !in_array($file_type, $formatter['file types'])) {
        unset($formatters[$name]);
      }
    }
  }

  $image_style_names = array();
  $current_displays = file_displays_load($file_type, $view_mode, TRUE);
  foreach ($current_displays as $name => $display) {
    $display = (array) $display;
    if (!empty($display['status']) && !empty($display['settings'])) {
      // Core.
      if (!empty($display['settings']['image_style'])) {
        $image_style_names[] = $display['settings']['image_style'];
      }
      // Newer Lightbox.
      if (!empty($display['settings']['lightbox_style'])) {
        $image_style_names[] = $display['settings']['lightbox_style'];
      }
    }
  }
  return array_values(array_unique($image_style_names));
}

/**
 * Given a field name, will return image styles used in views for that field.
 *
 * @param string $field_name
 *   Name of a field containing images.
 *
 * @return array
 *   An array image style names.
 */
function imageinfo_cache_get_image_styles_in_views($field_name) {
  $image_styles_in_views = &drupal_static(__FUNCTION__);

  // Do nothing is the views module is missing.
  if (!module_exists('views')) {
    return array();
  }

  // Lookup info.
  if (!isset($image_styles_in_views)) {
    foreach (views_get_enabled_views() as $view) {
      foreach ($view->display as $display) {
        // Skip if no fields.
        if (empty($display->display_options['fields'])) {
          continue;
        }

        foreach ($display->display_options['fields'] as $view_field_name => $field_info) {
          // Skip if field is missing needed info.
          if (   empty($field_info['settings']['image_style'])
              && empty($field_info['settings']['file_view_mode'])
              && empty($field_info['view_mode'])
                ) {
            continue;
          }

          // Handle rendered fields by looking at relationships.
          if (strpos($view_field_name, 'rendered') === 0) {
            if (!empty($display->display_options['relationships'])) {
              $fields_with_images = imageinfo_cache_get_fields_with_images();
              $changed = FALSE;
              foreach ($display->display_options['relationships'] as $values) {
                if (!empty($values['label']) && !empty($fields_with_images[$values['label']])) {
                  $view_field_name = $values['label'];
                  $changed = TRUE;
                  break;
                }
              }
              if (empty($changed)) {
                break;
              }
            }
          }

          // Core image style.
          if (!empty($field_info['settings']['image_style'])) {
            $image_styles_in_views[$view_field_name][] = $field_info['settings']['image_style'];
          }
          // Newer Lightbox.
          if (!empty($field_info['settings']['lightbox_style'])) {
            $image_styles_in_views[$view_field_name][] = $field_info['settings']['lightbox_style'];
          }
          // Older Lightbox.
          if (!empty($field_info['type']) && substr_count($field_info['type'], '__') == 3 && strpos($field_info['type'], 'lightbox2__') === 0) {
            $pieces = explode('__', $field_info['type']);

            $image_styles_in_views[$view_field_name][] = $pieces[2];
            $image_styles_in_views[$view_field_name][] = $pieces[3];
          }
          // File entities.
          if (!empty($field_info['settings']['file_view_mode'])) {
            $file_view_mode = imageinfo_cache_get_presets_in_file_view_mode($field_info['settings']['file_view_mode']);
            foreach ($file_view_mode as $style_in_view) {
              $image_styles_in_views[$view_field_name][] = $style_in_view;
            }
          }
          // File entities.
          if (!empty($field_info['view_mode'])) {
            $view_mode = imageinfo_cache_get_presets_in_file_view_mode($field_info['view_mode']);
            foreach ($view_mode as $style_in_view) {
              $image_styles_in_views[$view_field_name][] = $style_in_view;
            }
          }
        }
      }
    }
  }

  // Return list.
  if (isset($image_styles_in_views[$field_name])) {
    return array_unique($image_styles_in_views[$field_name]);
  }
  return array();
}

/**
 * Generates all given presets given a file uri.
 *
 * This is mainly used as a wrapper for httprl.
 *
 * @param array $styles
 *   Styles to use from image_styles().
 * @param string $uri
 *   URI from a file object.
 * @param bool $use_httprl
 *   (optional) Use httprl if available. Default TRUE.
 *
 * @return array
 *   An array of what was done.
 */
function imageinfo_cache_create_image_styles($styles, $uri, $use_httprl = TRUE) {
  $return = array();
  if (   $use_httprl
      && module_exists('httprl')
      && variable_get('imageinfo_cache_use_httprl', IMAGEINFO_CACHE_USE_HTTPRL)
      && httprl_is_background_callback_capable()
        ) {
    // Setup callback options array; call function in the background.
    $callback_options = array(
      array(
        'function' => 'imageinfo_cache_create_image_styles_call',
      ),
      $styles, $uri,
    );
    // Queue up the request.
    httprl_queue_background_callback($callback_options);

    // Execute request.
    $return = httprl_send_request();
  }
  else {
    $return = imageinfo_cache_create_image_styles_call($styles, $uri);
  }
  return $return;
}
