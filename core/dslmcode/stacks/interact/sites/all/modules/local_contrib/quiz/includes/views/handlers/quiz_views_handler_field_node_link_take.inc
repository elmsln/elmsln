<?php

/**
 * @file
 * Definition of quiz_views_handler_field_node_link_take.
 */

/**
 * Field handler to present a link to take a quiz node.
 *
 * @ingroup views_field_handlers
 */
class quiz_views_handler_field_node_link_take extends views_handler_field_node_link {

  /**
   * Renders the link.
   */
  function render_link($node, $values) {
    // Ensure user has access to take this quiz.
    if (!quiz_take_access($node)) {
      return;
    }

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "node/$node->nid/take";

    $text = !empty($this->options['text']) ? $this->options['text'] : t('Take quiz');
    return $text;
  }
}