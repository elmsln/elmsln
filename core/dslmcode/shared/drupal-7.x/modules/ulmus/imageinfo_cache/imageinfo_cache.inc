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
 * @param bool $use_cache
 *   (optional) Use the database cache. Default is TRUE.
 *
 * @return array
 *   An array of imagefields and styles.
 */
function imageinfo_cache_get_image_fields($run_alter = TRUE, $use_cache = TRUE) {
  $image_fields = imageinfo_cache_get_fields_with_images();
  foreach ($image_fields as $field_name => $values) {
    foreach ($values['#field_info'] as $field_values) {
      $image_fields[$field_name] += imageinfo_cache_get_styles_in_use($field_values, $run_alter, $use_cache);
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
 * @param bool $use_cache
 *   (optional) Use the database cache. Default is TRUE.
 *
 * @return array
 *   An array of what styles are used in this field.
 */
function imageinfo_cache_get_styles_in_use(array $instance_field, $run_alter = TRUE, $use_cache = TRUE) {
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
    if (!is_array($values) || empty($values['type']) || empty($values['module']) || $values['module'] !== 'lightbox2' || substr_count($values['type'], '__') != 3) {
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
  $image_styles_in_views = imageinfo_cache_get_image_styles_in_views($instance_field['field_name'], FALSE, $use_cache);
  foreach ($image_styles_in_views as $image_style_name) {
    if (is_string($image_style_name) && !empty($image_styles[$image_style_name])) {
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
function imageinfo_cache_get_image_styles_in_file_entity(array $instance_field) {
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

  $formatters = &drupal_static(__FUNCTION__ . ':formatters');
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
  $current_displays = &drupal_static(__FUNCTION__ . ':displays:' . $file_type . ':' . $view_mode);
  if (!isset($current_displays)) {
    $current_displays = file_displays_load($file_type, $view_mode, TRUE);
  }
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
 * @param bool $view_links
 *   (optional) If TRUE return links to the views that use image styles.
 *   Default is FALSE.
 * @param bool $use_cache
 *   (optional) Use the database cache. Default is TRUE.
 *
 * @return array
 *   An array image style names.
 */
function imageinfo_cache_get_image_styles_in_views($field_name, $view_links = FALSE, $use_cache = TRUE) {
  $image_styles_in_views = &drupal_static(__FUNCTION__);

  // Do nothing is the views module is missing.
  if (!module_exists('views')) {
    return array();
  }

  // Lookup info.
  if (!isset($image_styles_in_views)) {
    $cache = cache_get('__FUNCTION__');
    if (!empty($cache->data) && $use_cache) {
      $image_styles_in_views = $cache->data;
    }
    else {
      foreach (views_get_enabled_views() as $view) {
        foreach ($view->display as $display) {
          // Skip if no fields.
          if (empty($display->display_options['fields'])) {
            continue;
          }

          foreach ($display->display_options['fields'] as $view_field_name => $field_info) {
            // Skip if field is missing needed info.
            if ( empty($field_info['settings']['image_style'])
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

            $added = FALSE;
            // Core image style.
            if (!empty($field_info['settings']['image_style'])) {
              $image_styles_in_views[$view_field_name][] = $field_info['settings']['image_style'];
              $added = TRUE;
            }
            // Newer Lightbox.
            if (!empty($field_info['settings']['lightbox_style'])) {
              $image_styles_in_views[$view_field_name][] = $field_info['settings']['lightbox_style'];
              $added = TRUE;
            }
            // Older Lightbox.
            if (!empty($field_info['type']) && substr_count($field_info['type'], '__') == 3 && strpos($field_info['type'], 'lightbox2__') === 0) {
              $pieces = explode('__', $field_info['type']);

              $image_styles_in_views[$view_field_name][] = $pieces[2];
              $image_styles_in_views[$view_field_name][] = $pieces[3];
              $added = TRUE;
            }
            // File entities.
            if (!empty($field_info['settings']['file_view_mode'])) {
              $file_view_mode = imageinfo_cache_get_presets_in_file_view_mode($field_info['settings']['file_view_mode']);
              foreach ($file_view_mode as $style_in_view) {
                $image_styles_in_views[$view_field_name][] = $style_in_view;
                $added = TRUE;
              }
            }
            // File entities.
            if (!empty($field_info['view_mode'])) {
              $view_mode = imageinfo_cache_get_presets_in_file_view_mode($field_info['view_mode']);
              foreach ($view_mode as $style_in_view) {
                $image_styles_in_views[$view_field_name][] = $style_in_view;
                $added = TRUE;
              }
            }
            if ($added) {
              if (empty($image_styles_in_views[$view_field_name]['#views'])) {
                $image_styles_in_views[$view_field_name]['#views'] = l($view->human_name . ' - ' . $display->display_title, 'admin/structure/views/view/' . $view->name . '/edit/' . $display->id);
              }
              else {
                $image_styles_in_views[$view_field_name]['#views'] .= ', ' . l($view->human_name . ' - ' . $display->display_title, 'admin/structure/views/view/' . $view->name . '/edit/' . $display->id);
              }
            }
          }
        }
      }
      // Diff arrays to see if this value is different from the cached value.
      if (!empty($cache->data)) {
        $a = imageinfo_cache_array_diff_assoc_recursive($cache->data, $image_styles_in_views);
        $b = imageinfo_cache_array_diff_assoc_recursive($image_styles_in_views, $cache->data);
      }
      if (empty($cache->data) || !empty($a) || !empty($b)) {
        cache_set('__FUNCTION__', $image_styles_in_views, 'cache', CACHE_TEMPORARY);
      }
    }
  }

  // Return list.
  if ($view_links) {
    $return = '';
  }
  else {
    $return = array();
  }
  if (isset($image_styles_in_views[$field_name])) {
    if (!empty($image_styles_in_views[$field_name]['#views']) && $view_links) {
      $return = $image_styles_in_views[$field_name]['#views'];
    }
    elseif (!$view_links) {
      $copy = $image_styles_in_views[$field_name];
      unset($copy['#views']);
      $return = array_unique($copy);
    }
  }
  return $return;
}

/**
 * Generates all given presets given a file uri.
 *
 * @param mixed $uri
 *   String URI from a file object; or array of URIs.
 * @param array $instance_field
 *   Field info from field_info_instances().
 * @param array $styles
 *   (optional) Styles to use from image_styles().
 * @param bool $entity_available
 *   (optional) TRUE if coming from entity save.
 *
 * @return array
 *   An array of what was done.
 */
function imageinfo_cache_create_image_styles($uri, array $instance_field = array(), array $styles = array(), $entity_available = TRUE) {
  $return = array();

  // Use files array.
  $files = array();
  if (is_string($uri)) {
    $files[] = $uri;
  }
  else {
    $files = $uri;
  }

  if (empty($styles) && !empty($instance_field)) {
    // Get image styles used by this field.
    $styles = imageinfo_cache_get_styles_in_use($instance_field);
  }
  // Skip styles that need context.
  if (!$entity_available) {
    foreach ($styles as $style_name => $style_info) {
      if (!empty($style_info['#needs_context'])) {
        unset($styles[$style_name]);
      }
    }
  }
  // Do nothing if no styles are here for the image.
  if (empty($styles)) {
    return $return;
  }

  foreach ($files as $uri) {
    foreach ($styles as $style_name => $style_info) {
      $destination = image_style_path($style_name, $uri);

      // If the file does not exist, create it.
      if (!file_exists($destination)) {
        // Don't start generating the image if the derivative already exists or
        // if generation is in progress in another thread.
        $lock_name = 'image_style_deliver:' . $style_name . ':' . drupal_hash_base64($uri);
        $lock_acquired = lock_acquire($lock_name);
        if ($lock_acquired && image_style_create_derivative($style_info, $uri, $destination)) {
          lock_release($lock_name);
          $return[$destination] = $style_name;

          if (variable_get('imageinfo_cache_getimagesize', IMAGEINFO_CACHE_GETIMAGESIZE)) {
            // Prime get_info cache.
            image_get_info($destination);
          }
        }
      }
      else {
        $return[$destination] = FALSE;
      }
    }
    if (variable_get('imageinfo_cache_getimagesize', IMAGEINFO_CACHE_GETIMAGESIZE)) {
      // Prime get_info cache.
      image_get_info($uri);
    }
  }
  return $return;
}

/**
 * Computes the difference of arrays with additional index check recursively.
 *
 * @param array $array1
 *   The array to compare from.
 * @param array $array2
 *   An array to compare against.
 *
 * @return array
 *   Returns an array containing all the values from array1 that are not
 *   present in any of the other arrays.
 */
function imageinfo_cache_array_diff_assoc_recursive(array $array1, array $array2) {
  foreach ($array1 as $key => $value) {
    if (is_array($value)) {
      if (!isset($array2[$key])) {
        $difference[$key] = $value;
      }
      elseif (!is_array($array2[$key])) {
        $difference[$key] = $value;
      }
      else {
        $new_diff = imageinfo_cache_array_diff_assoc_recursive($value, $array2[$key]);
        if ($new_diff != FALSE) {
          $difference[$key] = $new_diff;
        }
      }
    }
    elseif (!isset($array2[$key]) || $array2[$key] != $value) {
      $difference[$key] = $value;
    }
  }
  return !isset($difference) ? 0 : $difference;
}
