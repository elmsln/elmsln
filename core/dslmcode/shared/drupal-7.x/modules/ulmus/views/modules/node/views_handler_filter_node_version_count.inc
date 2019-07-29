<?php

/**
 * @file
 * Definition of views_handler_filter_node_version_count.
 */

/**
 * Filter to handle dates stored as a timestamp.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_node_version_count extends views_handler_filter_numeric {

  /**
   * {@inheritdoc}
   */
  public function op_between($field) {
    if ($this->operator == 'between') {
      $this->query->add_where_expression($this->options['group'], '(SELECT COUNT(vid) FROM {node_revision} WHERE nid = {' . $this->table_alias . '}.nid) BETWEEN :min AND :max', array(':min' => $this->value['min'], ':max' => $this->value['max']));
    }
    else {
      $this->query->add_where_expression($this->options['group'], '((SELECT COUNT(vid) FROM {node_revision} WHERE nid = {' . $this->table_alias . '}.nid) <= :min OR (SELECT COUNT(vid) FROM {node_revision} WHERE nid = {' . $this->table_alias . '}.nid) >= :max)', array(':min' => $this->value['min'], ':max' => $this->value['max']));
    }
  }

  /**
   * {@inheritdoc}
   */
  public function op_simple($field) {
    $this->query->add_where_expression($this->options['group'], '(SELECT COUNT(vid) FROM {node_revision} WHERE nid = {' . $this->table_alias . '}.nid)' . $this->operator . ' :value', array(':value' => $this->value['value']));
  }

  /**
   * {@inheritdoc}
   */
  public function op_empty($field) {
    if ($this->operator == 'empty') {
      $operator = "IS NULL";
    }
    else {
      $operator = "IS NOT NULL";
    }

    $this->query->add_where_expression($this->options['group'], '(SELECT COUNT(vid) FROM {node_revision} WHERE nid = {' . $this->table_alias . '}.nid) ' . $this->operator);
  }

  /**
   * {@inheritdoc}
   */
  public function op_regex($field) {
    $this->query->add_where_expression($this->options['group'], '(SELECT COUNT(vid) FROM {node_revision} WHERE nid = {' . $this->table_alias . '}.nid) RLIKE :value', array(':value' => $this->value['value']));
  }

}
