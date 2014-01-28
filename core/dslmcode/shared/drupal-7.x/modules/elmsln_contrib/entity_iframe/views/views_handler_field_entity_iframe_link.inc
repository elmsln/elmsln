<?php

/**
* Field handler to present an iframe link.
*
* Closely modeled after views/modules/node/views_handler_field_node_link_edit.inc
*/
class views_handler_field_entity_iframe_link extends views_handler_field_node_link {
  /**
   * Renders the link if they have permission to view it
   */
  function render_link($entity, $values) {
    // capture the entity type in use
    $type = $this->entity_type;
    if (user_access('view iframe embed code') && _entity_iframe_view_iframe($type, $values->{$this->base_field})) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = 'entity_iframe/' . $type . '/' . $values->{$this->base_field};
      // output text as default or the option text
      $text = !empty($this->options['text']) ? $this->options['text'] : t('iframe version');
      return $text;
    }
  }
}
