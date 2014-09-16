<?php

/**
 * @file
 * Handler for dynamic_select_plugin_style.
 */
class dynamic_select_plugin_style extends views_plugin_style {

  /** Note: we ignore grouping.
   Views is very naive about grouping, and it can only group on one field.
   It doesn't understand anything about which object (node, comment, etc.) the field belongs to,
   and doesn't make any smart grouping choices based on the parent object of the grouping field.
   The grouping field does not modify the views SQL query - grouping is handed after records are retrieved from the database.
   */

  function render() {

    $array = $this->display->handler->get_option('dynamic_select_array');

    // Play nice with View UI 'preview' : if the view is not called to get an array, just display the HTML.
    if (!isset($array)) {
      return parent::render();
    }

    $results = array();

    $id_field = $this->view->base_field;

    // Make sure fields are rendered otherwise you get an error later on when you call render($row)...
    $this->render_fields($this->view->result);

    foreach ($this->view->result as $row_index => $row) {

      $id = $row->{$id_field};

      $this->view->row_index = $row_index; // Required as the theme function called by render needs it

      $rendered = strip_tags($this->row_plugin->render($row));

      // Remove linebreaks and extra spaces introduced by templates.
      $rendered = preg_replace('/\s+/', ' ', trim($rendered));

      $results[$id] = $rendered;
    }

    unset($this->view->row_index);

    return $results;
  }
}
