<?php

/**
 * @file
 * Definition of harmony_core_views_handler_thread_field_link_delete.
 */

/**
 * Field handler to present a link to delete a thread.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_thread_field_link_delete extends harmony_core_views_handler_thread_field_link {
  /**
   * Renders the link.
   */
  function render_link($thread, $values) {
    // Ensure user has access to delete this node.
    if (!harmony_core_thread_access_callback('delete', $thread)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "thread/$thread->thread_id/delete";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->tokenize_value(check_plain($this->options['text'])) : t('delete');
    return $text;
  }
}
