<?php
/**
 * @file
 * Provide views handlers for post revisions.
 */

/**
 * Field handler to present a link node edit.
 */
class harmony_core_views_handler_post_field_make_current extends harmony_core_views_handler_post_field_view_revision {
  /**
   * Renders the link.
   */
  function render_link($entity, $values) {
    if (harmony_core_post_revision_access_callback('update', $entity)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "post/$entity->post_id/revisions/$entity->vid/revert";
      $this->options['alter']['query'] = drupal_get_destination();
      $this->options['alter']['query']['token'] = drupal_get_token($entity->post_id . ':' . $entity->vid);

      $text = !empty($this->options['text']) ? check_plain($this->options['text']) : t('Make current');
      return $text;
    }
    else {
      $this->options['alter']['path'] = '';
    }
  }
}
