<?php

/**
 * @file
 * Definition of views_handler_field_file_link_edit.
 */

/**
 * Field handler to present a link file edit.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_file_link_edit extends views_handler_field_file_link {

  /**
   * Renders the link.
   */
  function render_link($file, $values) {
    // Ensure user has access to edit this file.
    if (!file_entity_access('update', $file)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "file/$file->fid/edit";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('Edit');
    return $text;
  }
}
