<?php
/**
 * @file
 * Views display handler for adding a replicate link.
 */

/**
 * Field handler to present an replicate link.
 *
 * Closely modeled after:
 *   - views/modules/node/views_handler_field_node_link_edit.inc
 */
class views_handler_field_replicate_ui_link extends views_handler_field_node_link {
  /**
   * Renders the link if they have permission to view it
   */
  function render_link($entity, $values) {
    // capture the entity type in use
    $type = $this->entity_type;
    // ensure we can create this entity that is going to be replicated
    if (replicate_ui_access($type, $entity->{$this->base_field})) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = 'replicate/' . $type . '/' . $entity->{$this->base_field};
      $this->options['alter']['query'] = array('destination' => current_path());
      // output text as default or the option text
      $text = !empty($this->options['text']) ? $this->options['text'] : t('replicate');
      return $text;
    }
  }
}
