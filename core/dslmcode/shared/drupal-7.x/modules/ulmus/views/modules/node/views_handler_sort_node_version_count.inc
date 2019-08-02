<?php

/**
 * @file
 * Definition of views_handler_sort_node_version_count.
 */

/**
 * A handler that sorts on the total count of versions/revisions of a node.
 *
 * @ingroup views_sort_handlers
 */
class views_handler_sort_node_version_count extends views_handler_sort {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();

    $this->query->add_orderby(NULL, '(SELECT COUNT(vid) FROM {node_revision} WHERE nid = {' . $this->table_alias . '}.nid)', $this->options['order'], 'sort_node_version_count');
  }

}
