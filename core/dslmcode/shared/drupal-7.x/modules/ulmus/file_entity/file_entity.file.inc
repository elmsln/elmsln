<?php

/**
 * @file
 * File hooks implemented by the File entity module.
 */

/**
 * Implements hook_file_presave().
 */
function file_entity_file_presave($file) {
  // Always ensure the filemime property is current.
  if (!empty($file->original) || empty($file->filemime)) {
    $file->filemime = file_get_mimetype($file->uri);
  }

  // The file type is used as a bundle key, and therefore, must not be NULL.
  // It defaults to FILE_TYPE_NONE when loaded via file_load(), but in case
  // file_save() is called on a new file object, default it here too.
  if (!isset($file->type)) {
    $file->type = FILE_TYPE_NONE;
  }

  // If the file isn't already assigned a real type, determine what type should
  // be assigned to it.
  if ($file->type === FILE_TYPE_NONE) {
    $type = file_get_type($file);
    if (isset($type)) {
      $file->type = $type;
    }
  }

  field_attach_presave('file', $file);

  // Fetch image dimensions.
  file_entity_metadata_fetch_image_dimensions($file);
}

/**
 * Implements hook_file_type().
 */
function file_entity_file_type($file) {
  $types = array();
  foreach (file_type_get_enabled_types() as $type) {
    if (file_entity_match_mimetypes($type->mimetypes, $file->filemime)) {
      $types[] = $type->type;
    }
  }

  return $types;
}

/**
 * Implements hook_file_insert().
 */
function file_entity_file_insert($file) {
  // Ensure field data is saved since file_save() does not in Drupal 7.
  field_attach_insert('file', $file);

  // Save file metadata.
  if (!empty($file->metadata)) {
    $query = db_insert('file_metadata')->fields(array('fid', 'name', 'value'));
    foreach ($file->metadata as $name => $value) {
      $query->values(array(
        'fid' => $file->fid,
        'name' => $name,
        'value' => serialize($value),
      ));
    }
    $query->execute();
  }

  // Clear any related field caches.
  file_entity_invalidate_field_caches($file);
}

/**
 * Implements hook_file_update().
 */
function file_entity_file_update($file) {
  // Ensure field data is saved since file_save() does not in Drupal 7.
  field_attach_update('file', $file);

  // Save file metadata.
  db_delete('file_metadata')->condition('fid', $file->fid)->execute();
  if (!empty($file->metadata)) {
    $query = db_insert('file_metadata')->fields(array('fid', 'name', 'value'));
    foreach ($file->metadata as $name => $value) {
      $query->values(array(
        'fid' => $file->fid,
        'name' => $name,
        'value' => serialize($value),
      ));
    }
    $query->execute();
  }

  if (module_exists('image') && file_entity_file_get_mimetype_type($file) == 'image' && $file->filesize && isset($file->original)) {
    if (!isset($file->metadata)) {
      $file->metadata = array();
    }

    if (!isset($file->original->metadata)) {
      if (!is_object($file->original)) {
        $file->original = new stdClass();
      }
      $file->original->metadata = array();
    }

    // If the file has changed dimensions or a new file has been uploaded,
    // update any image field reference to this file and flush image style
    // derivatives.
    $file->metadata += array('width' => NULL, 'height' => NULL);
    $file->original->metadata += array('width' => NULL, 'height' => NULL);
    if ($file->filesize != $file->original->filesize || $file->metadata['width'] != $file->original->metadata['width'] || $file->metadata['height'] != $file->original->metadata['height']) {
      _file_entity_update_image_field_dimensions($file);
    }

    // Flush image style derivatives whenever an image is replaced.
    if (empty($file->file_entity_skip_image_flush) && file_entity_has_file_changed($file)) {
      image_path_flush($file->uri);
    }
  }

  // Clear any related field caches.
  file_entity_invalidate_field_caches($file);
}

/**
 * Returns whether the file has changed
 */
function file_entity_has_file_changed($file) {
  return empty($file->is_new) || empty($file->original) || $file->filesize != $file->original->filesize || $file->uri != $file->original->uri;
}


/**
 * Implements hook_file_delete().
 */
function file_entity_file_delete($file) {
  field_attach_delete('file', $file);

  // This is safe to call since the file's records from the usage table have
  // not yet been deleted.
  file_entity_invalidate_field_caches($file);

  // Remove file metadata.
  db_delete('file_metadata')->condition('fid', $file->fid)->execute();

  // Remove this file from the search index if needed.
  // This code is implemented in file entity module rather than in search
  // module because file entity is implementing search module's API, not the
  // other way around.
  if (module_exists('search')) {
    search_reindex($file->fid, 'file');
  }
}

/**
 * Implements hook_file_mimetype_mapping_alter().
 */
function file_entity_file_mimetype_mapping_alter(&$mapping) {
  // For info on adding new mime-types to core: http://drupal.org/node/1443070.

  // @todo. Remove after fixing this in core http://drupal.org/node/2912875.
  // Add support for autocad drawings.
  $new_mappings['dwg'] = 'application/acad';
  // For info on adding new mime-types to file_entity: drupal.org/node/2900830.

  foreach ($new_mappings as $extension => $mime_type) {
    if (!in_array($mime_type, $mapping['mimetypes'])) {
      // If the mime type does not already exist, add it.
      $mapping['mimetypes'][] = $mime_type;
    }

    // Get the index of the mime type and assign the extension to that key.
    $index = array_search($mime_type, $mapping['mimetypes']);
    $mapping['extensions'][$extension] = $index;
  }
}

/**
 * Implements hook_file_load().
 */
function file_entity_file_load($files) {
  // Add alt and title text to images.
  file_entity_set_title_alt_properties($files);

  // Add metadata to each file.
  foreach ($files as $file) {
    $file->metadata = array();
  }
  $results = db_query("SELECT * FROM {file_metadata} WHERE fid IN (:fids)", array(':fids' => array_keys($files)));

  foreach ($results as $result) {
    $name = $result->name;

    // image.module required height and width to be properties of the file.
    if ($name == 'height' || $name == 'width') {
      $files[$result->fid]->$name = unserialize($result->value);
    }

    $files[$result->fid]->metadata[$name] = unserialize($result->value);
  }
}

/**
 * Implements hook_entitycache_ENTITY_TYPE_load().
 */
function file_entity_entitycache_file_load($files) {
  // Integrates with entitycache - ensures the alt and title text on images is
  // localized.
  file_entity_set_title_alt_properties($files);
}

/**
 * Implements hook_entity_load().
 */
function file_entity_entity_load($entities, $entity_type) {
  file_entity_set_title_alt_properties_on_file_fields($entities, $entity_type);
}

/**
 * Sets the title / alt properties on file fields attached to entities.
 *
 * Files attached to a file or image field can be stored in the field cache or
 * entity cache for whichever entity that the field is attached to. Because
 * $file->alt and $file->title are set in file_entity_file_load() based on the
 * current page language, they will go into the cache with that language as
 * well. To ensure that the correct language is used when the entity is later
 * loaded and displayed in a different language, the alt and title properties
 * can be set again using this function.
 *
 * @param array $entities
 *   An array of entity objects of the same type.
 * @param string $entity_type
 *   The type of entity.
 *
 * @see file_entity_entity_load()
 * @see file_entity_entitycache_load()
 */
function file_entity_set_title_alt_properties_on_file_fields($entities, $entity_type) {
  foreach ($entities as $entity) {
    list(, , $bundle) = entity_extract_ids($entity_type, $entity);
    foreach (field_info_instances($entity_type, $bundle) as $instance) {
      if (!empty($entity->{$instance['field_name']})) {
        foreach ($entity->{$instance['field_name']} as &$items) {
          foreach ($items as &$item) {
            // We need to detect any field items that passed through
            // file_field_load(), whether they are files, images, or something
            // else. There is no direct way to do that, but checking for a few
            // expected file properties on the field item should be sufficient.
            if (is_array($item) && !empty($item['fid']) && isset($item['uri']) && isset($item['filename'])) {
              $file = (object) $item;
              file_entity_set_title_alt_properties(array($file));
              $item = (array) $file;
            }
          }
        }
      }
    }
  }
}

/**
 * Set the title / alt properties of file objects.
 *
 * @param array $files
 *   List of file entities.
 * @param stdClass $language
 *   (optional) A language object to use for translating the title and alt
 *   properties. Defaults to the language of the current request.
 */
function file_entity_set_title_alt_properties($files, $language = NULL) {
  if (!isset($language)) {
    $language = $GLOBALS['language'];
  }

  $alt = variable_get('file_entity_alt', '[file:field_file_image_alt_text]');
  $title = variable_get('file_entity_title', '[file:field_file_image_title_text]');

  $replace_options = array(
    'clear' => TRUE,
    'sanitize' => FALSE,
    'language' => $language,
  );

  foreach ($files as $file) {
    // Load alt and title text from fields.
    if (!empty($alt)) {
      $output = token_replace($alt, array('file' => $file), $replace_options);

      if (!empty($output)) {
        // @todo Remove once https://www.drupal.org/node/1713164 is fixed.
        // There is currently no way to get the raw alt text returned from the
        // token so we revert the encoding done during tokenization.
        $file->alt = decode_entities($output);
      }
    }
    if (!empty($title)) {
      $output = token_replace($title, array('file' => $file), $replace_options);

      if (!empty($output)) {
        // @todo Remove once https://www.drupal.org/node/1713164 is fixed.
        // There is currently no way to get the raw title text returned from the
        // token so we revert the encoding done during tokenization.
        $file->title = decode_entities($output);
      }
    }
  }
}

/**
 * Fetch the dimensions of an image and store them in the file metadata array.
 */
function file_entity_metadata_fetch_image_dimensions($file) {
  // Prevent PHP notices when trying to read empty files.
  // @see http://drupal.org/node/681042
  if (!$file->filesize) {
    return;
  }

  // Do not bother proceeding if this file does not have an image mime type.
  if (file_entity_file_get_mimetype_type($file) != 'image') {
    return;
  }

  // We have a non-empty image file.
  $image_info = image_get_info($file->uri);
  if ($image_info) {
    $file->metadata['width'] = $image_info['width'];
    $file->metadata['height'] = $image_info['height'];
  }
  else {
    // Fallback to NULL values.
    $file->metadata['width'] = NULL;
    $file->metadata['height'] = NULL;
  }
}

/**
 * Update the image dimensions stored in any image fields for a file.
 *
 * @param object $file
 *   A file object that is an image.
 *
 * @see http://drupal.org/node/1448124
 */
function _file_entity_update_image_field_dimensions($file) {
  // Prevent PHP notices when trying to read empty files.
  // @see http://drupal.org/node/681042
  if (!$file->filesize) {
    return;
  }

  // Do not bother proceeding if this file does not have an image mime type.
  if (file_entity_file_get_mimetype_type($file) != 'image') {
    return;
  }

  // Find all image field enabled on the site.
  $image_fields = _file_entity_get_fields_by_type('image');

  foreach ($image_fields as $image_field) {
    $query = new EntityFieldQuery();
    $query->fieldCondition($image_field, 'fid', $file->fid);
    $results = $query->execute();

    foreach ($results as $entity_type => $entities) {
      $entities = entity_load($entity_type, array_keys($entities));
      foreach ($entities as $entity) {
        foreach ($entity->{$image_field} as $langcode => $items) {
          foreach ($items as $delta => $item) {
            if ($item['fid'] == $file->fid) {
              $entity->{$image_field}[$langcode][$delta]['width'] = $file->metadata['width'];
              $entity->{$image_field}[$langcode][$delta]['height'] = $file->metadata['height'];
            }
          }
        }

        // Save the updated field column values.
        _file_entity_entity_fields_update($entity_type, $entity);
      }
    }
  }
}

/**
 * Update an entity's field values without changing anything on the entity.
 */
function _file_entity_entity_fields_update($entity_type, $entity) {
  list($id) = entity_extract_ids($entity_type, $entity);
  if (empty($id)) {
    throw new Exception(t('Cannot call _file_entity_update_entity_fields() on a new entity.'));
  }

  // Some modules use the original property.
  if (!isset($entity->original)) {
    $entity->original = $entity;
  }

  // Ensure that file_field_update() will not trigger additional usage.
  unset($entity->revision);

  // Invoke the field presave and update hooks.
  field_attach_presave($entity_type, $entity);
  field_attach_update($entity_type, $entity);

  // Clear the cache for this entity now.
  entity_get_controller($entity_type)->resetCache(array($id));
}

/**
 * Implements hook_file_metadata_info().
 */
function file_entity_file_metadata_info() {
  $info['width'] = array('label' => t('Width'), 'type' => 'integer');
  $info['height'] = array('label' => t('Height'), 'type' => 'integer');
  return $info;
}
