<?php

/**
 * @file
 * Definition of views_handler_field_file_link_download.
 */

/**
 * Field handler to present a link to download a file.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_file_link_download extends views_handler_field_file_link {

  /**
   * Renders the link.
   */
  function render_link($file, $values) {
    // Ensure user has access to download this file.
    if (!file_entity_access('download', $file)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $uri = file_entity_download_uri($file);
    $this->options['alter']['path'] = $uri['path'];
    $this->options['alter'] = drupal_array_merge_deep($this->options['alter'], $uri['options']);

    $text = !empty($this->options['text']) ? $this->options['text'] : t('Download');
    return $text;
  }
}
