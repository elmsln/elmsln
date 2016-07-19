<?php
/**
 * @file
 * Definition of views_handler_field_node_version_count.
 */

/**
 * A handler that loads the total count of versions/revisions of a certain node.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_node_version_count extends views_handler_field_numeric {
  function query() {
    $this->ensure_my_table();
    // Add the field.
    $params = $this->options['group_type'] != 'group' ? array('function' => $this->options['group_type']) : array();
    $this->field_alias = $this->query->add_field(NULL, '(SELECT COUNT(vid) FROM {node_revision} WHERE nid = {node}.nid)', 'node_version_count', $params);

    $this->add_additional_fields();
  }
}
