<?php

/**
 * @file
 * Definition of views_handler_field_file_link_delete.
 */

/**
 * Field handler to present a link to delete a file.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_file_link_delete extends views_handler_field_file_link {

  /**
   * Renders the link.
   */
  function render_link($file, $values) {
    // Ensure user has access to delete this file.
    if (!file_entity_access('delete', $file)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "file/$file->fid/delete";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('Delete');
    return $text;
  }
}
