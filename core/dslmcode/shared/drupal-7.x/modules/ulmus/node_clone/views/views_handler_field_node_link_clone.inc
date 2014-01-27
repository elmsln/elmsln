<?php

/**
* Field handler to present a clone node link.
*
* Closely modeled after views/modules/node/views_handler_field_node_link_edit.inc
*/
class views_handler_field_node_link_clone extends views_handler_field_node_link {
  /**
   * Renders the link.
   */
  function render_link($node, $values) {

    if (!clone_access_cloning($node)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/{$node->nid}/clone";
    $this->options['alter']['query'] = drupal_get_destination();

    $text = !empty($this->options['text']) ? $this->options['text'] : t('clone');
    return $text;
  }
}
