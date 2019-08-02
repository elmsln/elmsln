<?php

/**
 * @file
 * Definition of views_handler_argument_node_nid.
 */

/**
 * Argument handler to accept a node id.
 */
class views_handler_argument_node_nid extends views_handler_argument_numeric {

  /**
   * Override the behavior of title(). Get the title of the node.
   */
  public function title_query() {
    $titles = array();

    $result = db_query("SELECT n.title FROM {node} n WHERE n.nid IN (:nids)", array(':nids' => $this->value));
    foreach ($result as $term) {
      $titles[] = check_plain($term->title);
    }
    return $titles;
  }

}
