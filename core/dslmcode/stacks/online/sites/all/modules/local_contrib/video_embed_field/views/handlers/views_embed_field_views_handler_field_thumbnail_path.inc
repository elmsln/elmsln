<?php

/**
 * @file
 * Video embed field thumbnail_path column implementation.
 */

/**
 * Defines a field handler that can display the thumbnail_path url instead of
 * the drupal internal uri.
 */
class views_embed_field_views_handler_field_thumbnail_path extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  function get_value($values, $field = NULL) {
    $value = parent::get_value($values, $field);

    return file_create_url($value);
  }
}
