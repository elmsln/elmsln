<?php

/**
 * @file
 * Definition of views_handler_field_file_link_usage.
 */

/**
 * Field handler to present a link to view the usage of a file.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_file_link_usage extends views_handler_field_file_link {

  /**
   * Renders the link.
   */
  function render_link($file, $values) {
    // Ensure user has access to update this file.
    if (!file_entity_access('update', $file)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "file/$file->fid/usage";
    $this->options['alter']['query'] = drupal_get_destination();

    // Get total count for each file.
    $total_count = 0;
    foreach (file_usage_list($file) as $module => $usage) {
      foreach ($usage as $entity_type => $entity_ids) {
        foreach ($entity_ids as $id => $count) {
          $total_count += $count;
        }
      }
    }

    $text = !empty($this->options['text']) ? $this->options['text'] : format_plural((int) $total_count, '1 place', '@count places');
    return $text;
  }
}
