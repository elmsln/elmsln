<?php

/**
 * @file
 * Definition of harmony_core_views_handler_post_field_link_delete.
 */

/**
 * Field handler to present a link to delete a post.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_post_field_link_delete extends harmony_core_views_handler_post_field_link {
  /**
   * Renders the link.
   */
  function render_link($post, $values) {
    // Ensure user has access to delete this node.
    if (!harmony_core_post_access_callback('delete', $post)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "post/$post->post_id/delete";
    $this->options['alter']['query'] = drupal_get_destination();

    return !empty($this->options['text']) ? $this->tokenize_value(check_plain($this->options['text'])) : t('delete');
  }
}
