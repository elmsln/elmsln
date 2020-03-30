<?php

/**
 * @file
 * Token integration for the file_entity module.
 */

/**
 * Implements hook_token_info().
 */
function file_entity_token_info() {
  // File type tokens.
  $info['types']['file-type'] = array(
    'name' => t('File type'),
    'description' => t('Tokens associated with file types.'),
    'needs-data' => 'file_type',
  );
  $info['tokens']['file-type']['name'] = array(
    'name' => t('Name'),
    'description' => t('The name of the file type.'),
  );
  $info['tokens']['file-type']['machine-name'] = array(
    'name' => t('Machine-readable name'),
    'description' => t('The unique machine-readable name of the file type.'),
  );
  $info['tokens']['file-type']['count'] = array(
    'name' => t('File count'),
    'description' => t('The number of files belonging to the file type.'),
  );
  $info['tokens']['file-type']['edit-url'] = array(
    'name' => t('Edit URL'),
    'description' => t("The URL of the file type's edit page."),
  );

  // File tokens.
  $info['tokens']['file']['type'] = array(
    'name' => t('File type'),
    'description' => t('The file type of the file.'),
    'type' => 'file-type',
  );
  $info['tokens']['file']['download-url'] = array(
    'name' => t('Download URL'),
    'description' => t('The URL to download the file directly.'),
    'type' => 'url',
  );

  if (module_exists('token')) {
    $info['types']['file_field'] = array(
      'name' => t('Media'),
      'description' => t('Tokens related to a file_entity field.'),
      'hidden' => TRUE,
    );

    $default_text = ' ' . t('Defaults to first value.');

    $info['tokens']['file_field'] = array(
      'field' => array(
        'name' => t('Field token value'),
        'description' => t('Default: The value returned by the token field formatter.') . $default_text,
      ),
      'url' => array(
        'name' => t('URL'),
        'description' => t('URL of the file_entity resource.') . $default_text,
        'type' => 'array',
      ),
      'filename' => array(
        'name' => t('Filename'),
        'description' => t('Filename the file_entity resource.') . $default_text,
        'type' => 'array',
      ),
      'filemime' => array(
        'name' => t('MIME type'),
        'description' => t('MIME type of the file_entity resource.') . $default_text,
        'type' => 'array',
      ),
      'type' => array(
        'name' => t('File type'),
        'description' => t('File type of the file_entity resource.') . $default_text,
        'type' => 'array',
      ),
      'image' => array(
        'name' => t('Image'),
        'description' => t('URL of a representative image for the file_entity resource, e.g. a video thumbnail.') . $default_text,
        'type' => 'array',
      ),
      'height' => array(
        'name' => t('Height'),
        'description' => t('Height of the file_entity resource, for videos or images.') . $default_text,
        'type' => 'array',
      ),
      'width' => array(
        'name' => t('Width'),
        'description' => t('Width of the file_entity resource, for videos or images.') . $default_text,
        'type' => 'array',
      ),
      'https-url' => array(
        'name' => t('Secure URL'),
        'description' => t('URL of the file_entity resource using HTTPS.') . $default_text,
        'type' => 'array',
      ),
      'https-image' => array(
        'name' => t('Secure image'),
        'description' => t('URL of a representative image for the file_entity resource using HTTPS, usually for videos.') . $default_text,
        'type' => 'array',
      ),
    );

    $all_fields = field_info_field_map();
    foreach ($all_fields as $field_name => $field) {
      if ($field['type'] == 'file') {
        $field_info = _token_field_info($field_name);
        foreach (array_keys($field['bundles']) as $entity_type) {
          if ($entity_type == 'taxonomy_term') {
            $entity_type = 'term';
          }
          $info['tokens'][$entity_type][$field_name] = array(
            'name' => $field_info['label'],
            'description' => $field_info['description'],
            'type' => 'file_field',
            'module' => 'file_entity',
          );
        }
      }
    }
  }

  return $info;
}

/**
 * Implements hook_token_info_alter().
 */
function file_entity_token_info_alter(&$info) {
  $info['tokens']['file']['name']['description'] = t('The name of the file.');
}

/**
 * Provide replacement values for placeholder tokens.
 */
function file_entity_tokens($type, $tokens, array $data = array(), array $options = array()) {
  $replacements = array();

  // Check that this token call contains the data we need
  if ($type == 'entity' && !empty($data['entity_type']) && !empty($data['entity']) &&
    !empty($data['token_type']) && module_exists('token')) {

    foreach ($tokens as $name => $original) {

      // Split out the token into its parts
      $parts = explode(':', $name, 3);

      $field_name    = $parts[0];
      $property      = (isset($parts[1])) ? $parts[1] : '';
      $array_handler = (isset($parts[2])) ? $parts[2] : '';

      // Check that the field has content and that we should handle it
      if (!empty($data['entity']->$field_name) && _token_module($data['token_type'], $field_name) == 'file_entity') {

        // Get basic information
        $entity_type = $data['entity_type'];
        if ($entity_type == 'taxonomy_term') {
          $entity_type = 'term';
        }
        $langcode = isset($options['language']) ? $options['language']->language : NULL;
        $entity = clone $data['entity'];

        // If we are looking for the field output, let field module handle it
        if (empty($property) || $property == 'field') {
          unset($entity->_field_view_prepared);
          $field_output = field_view_field($entity_type, $entity, $field_name, 'token', $langcode);
          $field_output['#token_options'] = $options;
          $field_output['#prerender'][] = 'token_pre_render_field_token';
          $replacements[$original] = drupal_render($field_output);
        }
        else {
          $items = field_get_items($entity_type, $entity, $field_name);
          $return = _file_entity_tokens_get_property($items, $property, $array_handler);

          // We may get a single value or an array.
          // Handle array with the array function from token module.
          if (is_array($return)) {
            $search_tokens = token_find_with_prefix($tokens, $field_name);
            if ($array_tokens = token_find_with_prefix($search_tokens, $property)) {
              $replacements += token_generate('array', $array_tokens, array('array' => $return), $options);
            }
          }
          else {
            if (!is_null($return)) {
              $replacements[$original] = $return;
            }
          }
        }

        // Unset clone of entity
        unset($entity);
      }
    }
  }

  $url_options = array('absolute' => TRUE);
  if (isset($options['language'])) {
    $url_options['language'] = $options['language'];
    $language_code = $options['language']->language;
  }
  else {
    $language_code = NULL;
  }

  $sanitize = !empty($options['sanitize']);

  // File tokens.
  if ($type == 'file' && !empty($data['file'])) {
    $file = $data['file'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'type':
          if ($file_type = file_type_load($file->type)) {
            $replacements[$original] = $sanitize ? check_plain($file_type->label) : $file_type->label;
          }
          break;

        case 'download-url':
          $uri = file_entity_download_uri($file);
          $replacements[$original] = url($uri['path'], $uri['options'] + $url_options);
          break;
      }
    }

    // Chained token relationships.
    if (($file_type_tokens = token_find_with_prefix($tokens, 'type')) && $file_type = file_type_load($file->type)) {
      $replacements += token_generate('file-type', $file_type_tokens, array('file_type' => $file_type), $options);
    }
    if ($download_url_tokens = token_find_with_prefix($tokens, 'download-url')) {
      $replacements += token_generate('url', $download_url_tokens, file_entity_download_uri($file), $options);
    }
  }

  // File type tokens.
  if ($type == 'file-type' && !empty($data['file_type'])) {
    $file_type = $data['file_type'];

    foreach ($tokens as $name => $original) {
      switch ($name) {
        case 'name':
          $replacements[$original] = $sanitize ? check_plain($file_type->label) : $file_type->label;
          break;

        case 'machine-name':
          // This is a machine name so does not ever need to be sanitized.
          $replacements[$original] = $file_type->type;
          break;

        case 'count':
          $query = db_select('file_managed');
          $query->condition('type', $file_type->type);
          $query->addTag('file_type_file_count');
          $count = $query->countQuery()->execute()->fetchField();
          $replacements[$original] = (int) $count;
          break;

        case 'edit-url':
          $replacements[$original] = url('admin/structure/file-types/manage/' . $file_type->type . '/fields', $url_options);
          break;
      }
    }
  }

  return $replacements;
}

/**
 * This helper function gets file properties for token replacement.
 *
 * @param array $files
 * An array of files that are values for the field.
 *
 * @param string $property
 * The property to retrieve from the file info. See file_entity_token_info() for
 * a list of properties.
 *
 * @param string $array_handler
 * The optional array modifier, e.g. "count" or "join:,".
 *
 * @return mixed
 * Either a single value, the first of the array, or an array of values.
 */
function _file_entity_tokens_get_property($files, $property, $array_handler = 'first') {
  $value = NULL;
  // If we only need the first variable
  $return_first = ($array_handler == 'first' || empty($array_handler) || $array_handler == 'value:0');

  // This static variable stores image info
  $info = &drupal_static(__FUNCTION__);

  foreach ($files as $file) {
    $file['url'] = file_create_url($file['uri']);
    $file['https-url'] = str_replace('http://', 'https://', $file['url']);

    // If values are: filename, filemime, type, url, https-url
    if (isset($file[$property])) {
      $value = $file[$property];
    }

    // If values are: image, height, width, https-image
    elseif (!empty($info[$file['fid']])) {
      if (isset($info[$file['fid']][$property])) {
        $value = $info[$file['fid']][$property];
      } else {
        $value = NULL;
      }
    }
    // If values are files types
    else {

      // If file type is image
      if ($file['type'] == 'image') {
        $imageuri = $file['uri'];
      }

      // If file type is video
      elseif ($file['type'] == 'video' && strpos($file['uri'], '://v')) {
        list($provider, $filename) = preg_split('!://v.*/!', $file['uri']);
        $imageuri = "public://file_entity-$provider/$filename.jpg";
      }

      // Do nothing for other file types
      // @todo: Other file types may need handling
      else {
        $imageuri = FALSE;
      }

      if ($info[$file['fid']] = image_get_info($imageuri)) {
        $info[$file['fid']]['image'] = file_create_url($imageuri);
        $info[$file['fid']]['https-image'] = str_replace('http://', 'https://', $info[$file['fid']]['image']);
      }

      if (isset($info[$file['fid']][$property])) {
        $value = $info[$file['fid']][$property];
      } else {
        $value = NULL;
      }
    }

    if ($return_first) {
      return $value;
    }
    $values[] = $value;
  }

  return $values;
}
