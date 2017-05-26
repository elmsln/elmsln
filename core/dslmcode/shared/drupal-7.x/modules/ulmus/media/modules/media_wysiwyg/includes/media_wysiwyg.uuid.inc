<?php

/**
 * @file
 * Functions related to adding UUID support to embedded media.
 */

/**
 * Implements hook_entity_uuid_load().
 */
function media_wysiwyg_entity_uuid_load(&$entities, $entity_type) {
  // Go through all the entity's text fields and replace file IDs in media
  // tokens with the corresponding UUID.
  foreach ($entities as $entity) {
    media_wysiwyg_filter_replace_tokens_in_all_text_fields($entity_type, $entity, 'media_wysiwyg_token_fid_to_uuid');
  }
}

/**
 * Implements hook_entity_uuid_presave().
 */
function media_wysiwyg_entity_uuid_presave(&$entity, $entity_type) {
  // Go through all the entity's text fields and replace UUIDs in media tokens
  // with the corresponding file ID.
  media_wysiwyg_filter_replace_tokens_in_all_text_fields($entity_type, $entity, 'media_wysiwyg_token_uuid_to_fid');
}

/**
 * Replaces media tokens in an entity's text fields, using the specified callback function.
 */
function media_wysiwyg_filter_replace_tokens_in_all_text_fields($entity_type, $entity, $callback) {
  $text_field_names = media_wysiwyg_filter_fields_with_text_filtering($entity_type, $entity);
  foreach ($text_field_names as $field_name) {
    if (!empty($entity->{$field_name})) {
      $field = field_info_field($field_name);
      $all_languages = field_available_languages($entity_type, $field);
      $field_languages = array_intersect($all_languages, array_keys($entity->{$field_name}));
      foreach ($field_languages as $language) {
        if (!empty($entity->{$field_name}[$language])) {
          foreach ($entity->{$field_name}[$language] as &$item) {
            $item['value'] = preg_replace_callback(MEDIA_WYSIWYG_TOKEN_REGEX, $callback, $item['value']);
          }
        }
      }
    }
  }
}

/**
 * Callback to replace file IDs with UUIDs in a media token.
 */
function media_wysiwyg_token_fid_to_uuid($matches) {
  return _media_wysiwyg_token_uuid_replace($matches, 'entity_get_uuid_by_id');
}

/**
 * Callback to replace UUIDs with file IDs in a media token.
 */
function media_wysiwyg_token_uuid_to_fid($matches) {
  return _media_wysiwyg_token_uuid_replace($matches, 'entity_get_id_by_uuid');
}

/**
 * Helper function to replace UUIDs with file IDs or vice versa.
 *
 * @param array $matches
 *   An array of matches for media tokens, from a preg_replace_callback()
 *   callback function.
 * @param string $entity_uuid_function
 *   Either 'entity_get_uuid_by_id' (to replace file IDs with UUIDs in the
 *   token) or 'entity_get_id_by_uuid' (to replace UUIDs with file IDs).
 *
 * @return string
 *   A string representing the JSON-encoded token, with the appropriate
 *   replacement between file IDs and UUIDs.
 */
function _media_wysiwyg_token_uuid_replace($matches, $entity_uuid_function) {
  $tag = $matches[0];
  $tag = str_replace(array('[[', ']]'), '', $tag);
  $tag_info = drupal_json_decode($tag);
  if (isset($tag_info['fid'])) {
    if ($new_ids = $entity_uuid_function('file', array($tag_info['fid']))) {
      $new_id = reset($new_ids);
      $tag_info['fid'] = $new_id;
    }
  }
  return '[[' . drupal_json_encode($tag_info) . ']]';
}
