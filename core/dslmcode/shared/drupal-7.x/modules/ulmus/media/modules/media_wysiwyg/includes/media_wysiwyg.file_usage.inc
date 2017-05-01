<?php

/**
 * @file
 * Functions related to the tracking the file usage of embedded media.
 */

/**
 * Implements hook_field_attach_insert().
 *
 * Track file usage for media files included in formatted text. Note that this
 * is heavy-handed, and should be replaced when Drupal's filter system is
 * context-aware.
 */
function media_wysiwyg_entity_insert($entity, $entity_type) {
  _media_wysiwyg_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Implements hook_field_attach_update().
 *
 * @see media_field_attach_insert().
 */
function media_wysiwyg_entity_update($entity, $entity_type) {
  _media_wysiwyg_filter_add_file_usage_from_fields($entity_type, $entity);
}

/**
 * Add file usage from file references in an entity's text fields.
 */
function _media_wysiwyg_filter_add_file_usage_from_fields($entity_type, $entity) {
  // Track the total usage for files from all fields combined.
  $entity_files = media_wysiwyg_entity_field_count_files($entity_type, $entity);

  list($entity_id, $entity_vid, $entity_bundle) = entity_extract_ids($entity_type, $entity);

  // When an entity has revisions and then is saved again NOT as new version the
  // previous revision of the entity has be loaded to get the last known good
  // count of files. The saved data is compared against the last version
  // so that a correct file count can be created for that (the current) version
  // id. This code may assume some things about entities that are only true for
  // node objects. This should be reviewed.
  // @TODO this conditional can probably be condensed
  if (empty($entity->revision) && empty($entity->old_vid) && empty($entity->is_new) && ! empty($entity->original)) {
    $old_files = media_wysiwyg_entity_field_count_files($entity_type, $entity->original);
    foreach ($old_files as $fid => $old_file_count) {
      // Were there more files on the node just prior to saving?
      if (empty($entity_files[$fid])) {
        $entity_files[$fid] = 0;
      }
      if ($old_file_count > $entity_files[$fid]) {
        $deprecate = $old_file_count - $entity_files[$fid];
        // Now deprecate this usage
        $file = file_load($fid);
        if ($file) {
          file_usage_delete($file, 'media', $entity_type, $entity_id, $deprecate);
        }
        // Usage is deleted, nothing more to do with this file
        unset($entity_files[$fid]);
      }
      // There are the same number of files, nothing to do
      elseif ($entity_files[$fid] ==  $old_file_count) {
        unset($entity_files[$fid]);
      }
      // There are more files now, adjust the difference for the greater number.
      // file_usage incrementing will happen below.
      else {
        // We just need to adjust what the file count will account for the new
        // images that have been added since the increment process below will
        // just add these additional ones in
        $entity_files[$fid] = $entity_files[$fid] - $old_file_count;
      }
    }
  }

  // Each entity revision counts for file usage. If versions are not enabled
  // the file_usage table will have no entries for this because of the delete
  // query above.
  foreach ($entity_files as $fid => $entity_count) {
    if ($file = file_load($fid)) {
      file_usage_add($file, 'media', $entity_type, $entity_id, $entity_count);
    }
  }
}

/**
 * Parse file references from an entity's text fields and return them as an array.
 */
function media_wysiwyg_filter_parse_from_fields($entity_type, $entity) {
  $file_references = array();

  foreach (media_wysiwyg_filter_fields_with_text_filtering($entity_type, $entity) as $field_name) {
    if ($field_items = field_get_items($entity_type, $entity, $field_name)) {
      foreach ($field_items as $field_item) {
        if (!empty($field_item['value'])) {
          preg_match_all(MEDIA_WYSIWYG_TOKEN_REGEX, $field_item['value'], $matches);
          foreach ($matches[0] as $tag) {
            $tag = str_replace(array('[[', ']]'), '', $tag);
            $tag_info = drupal_json_decode($tag);
            if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
              $file_references[] = $tag_info;
            }
          }

          preg_match_all(MEDIA_WYSIWYG_TOKEN_REGEX, $field_item['value'], $matches_alt);
          foreach ($matches_alt[0] as $tag) {
            $tag = urldecode($tag);
            $tag_info = drupal_json_decode($tag);
            if (isset($tag_info['fid']) && $tag_info['type'] == 'media') {
              $file_references[] = $tag_info;
            }
          }
        }
      }
    }
  }

  return $file_references;
}

/**
 * Utility function to get the file count in this entity
 *
 * @param type $entity
 * @param type $entity_type
 * @return int
 */
function media_wysiwyg_entity_field_count_files($entity_type, $entity) {
  $entity_files = array();
  foreach (media_wysiwyg_filter_parse_from_fields($entity_type, $entity) as $file_reference) {
    if (empty($entity_files[$file_reference['fid']])) {
      $entity_files[$file_reference['fid']] = 1;
    }
    else {
      $entity_files[$file_reference['fid']]++;
    }
  }
  return $entity_files;
}

/**
 * Implements hook_entity_delete().
 */
function media_wysiwyg_entity_delete($entity, $type) {
  list($entity_id) = entity_extract_ids($type, $entity);

  db_delete('file_usage')
    ->condition('module', 'media')
    ->condition('type', $type)
    ->condition('id', $entity_id)
    ->execute();
}

/**
 * Implements hook_field_attach_delete_revision().
 *
 * @param type $entity_type
 * @param type $entity
 */
function media_wysiwyg_field_attach_delete_revision($entity_type, $entity) {
  list($entity_id) = entity_extract_ids($entity_type, $entity);
  $files = media_wysiwyg_entity_field_count_files($entity_type, $entity);
  foreach ($files as $fid => $count) {
    if ($file = file_load($fid)) {
      file_usage_delete($file, 'media', $entity_type , $entity_id, $count);
    }
  }
}

/**
 * Implements hook_entity_dependencies().
 */
function media_wysiwyg_entity_dependencies($entity, $entity_type) {
  // Go through all the entity's text fields and add a dependency on any files
  // that are referenced there.
  $dependencies = array();
  foreach (media_wysiwyg_filter_parse_from_fields($entity_type, $entity) as $file_reference) {
    $dependencies[] = array('type' => 'file', 'id' => $file_reference['fid']);
  }
  return $dependencies;
}
