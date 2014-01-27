<?php

/**
 * @file
 * Handler to filter for nodes that are not in a queue.
 */
class nodequeue_handler_filter_in_queue extends views_handler_filter_boolean_operator {
  function query() {
    $this->ensure_my_table();
    $this->query->add_where($this->options['group'], $this->table_alias . ".nid", $this->value, ($this->value ? '!=' : 'IS NULL'));
  }
}
