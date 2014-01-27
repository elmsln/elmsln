<?php

/**
 * @file
 * Handler for nodeaccess_userreference_views_plugin_style.
 */
class nodeaccess_userreference_views_plugin_style extends views_plugin_style {
  function render() {
    $results = array();
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);
    $base_field = $this->view->base_field;
    $this->view->row_index = 0;
    foreach ($sets as $title => $records) {
      foreach ($records as $label => $row) {
        $results[] = $row->{$base_field};
        $this->view->row_index++;
      }
    }
    unset($this->view->row_index);
    return $results;
  }
}