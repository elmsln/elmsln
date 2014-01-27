<?php
/**
 * @file
 *   Content type groups custom Views filter handler - group machine name
 */

/**
 * Filter by content type group machine name
 */
class content_type_groups_handler_filter_group extends views_handler_filter_in_operator {

  function get_value_options() {

    if (isset($this->value_options)) {
      return;
    }

    $this->value_options = array();
    $content_type_groups = ContentTypeGroup::fetch();
    foreach ($content_type_groups as $machine_name => $display_name) {
      $this->value_options[$machine_name] = $display_name;
    }

  }

}