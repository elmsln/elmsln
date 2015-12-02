<?php

/**
 * @file
 * Definition of harmony_core_views_handler_post_field_link_edit.
 */

/**
 * Field handler to present a link to edit the post.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_post_field_link_edit extends harmony_core_views_handler_post_field_link {
  function render_link($post, $values) {
    if (!harmony_core_post_access_callback('update', $post)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "post/$post->post_id/edit";
    $this->options['alter']['query'] = drupal_get_destination();

    return !empty($this->options['text']) ? $this->tokenize_value(check_plain($this->options['text'])) : t('edit');
  }
}
