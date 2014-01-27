<?php

/**
 * @file
 * Views field handler for the nodequeue queue links
 */
class nodequeue_handler_field_queue_tab extends views_handler_field_node_link {
  function render($values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');
    $nid = $values->{$this->aliases['nid']};
    return l($text, "node/$nid/nodequeue");
  }
}
