<?php

/**
 * @file
 * Definition of harmony_core_views_handler_thread_field_link_edit.
 */

/**
 * Field handler to present a link to edit the thread.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_thread_field_link_edit extends harmony_core_views_handler_thread_field_link {
  function render_link($thread, $values) {
    if (!harmony_core_thread_access_callback('update', $thread)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "thread/$thread->thread_id/edit";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->tokenize_value(check_plain($this->options['text'])) : t('edit');
    return $text;
  }
}
