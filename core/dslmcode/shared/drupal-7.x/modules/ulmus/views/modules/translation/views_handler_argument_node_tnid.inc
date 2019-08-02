<?php

/**
 * @file
 * Definition of views_handler_argument_node_tnid.
 */

/**
 * Argument handler to accept a node translation id.
 *
 * @ingroup views_argument_handlers
 */
class views_handler_argument_node_tnid extends views_handler_argument_numeric {

  /**
   * {@inheritdoc}
   */
  public function title_query() {
    $titles = array();

    $result = db_query("SELECT n.title FROM {node} n WHERE n.tnid IN (:tnids)", array(':tnids' => $this->value));
    foreach ($result as $term) {
      $titles[] = check_plain($term->title);
    }
    return $titles;
  }

}
