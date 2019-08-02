<?php

/**
 * @file
 * Definition of views_handler_filter_node_tnid_child.
 */

/**
 * Filter by whether the node is not the original translation.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_node_tnid_child extends views_handler_filter {

  /**
   * {@inheritdoc}
   */
  public function admin_summary() {
  }

  /**
   * {@inheritdoc}
   */
  public function operator_form(&$form, &$form_state) {
  }

  /**
   * {@inheritdoc}
   */
  public function can_expose() {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $table = $this->ensure_my_table();
    $this->query->add_where_expression($this->options['group'], "$table.tnid <> $table.nid AND $table.tnid > 0");
  }

}
