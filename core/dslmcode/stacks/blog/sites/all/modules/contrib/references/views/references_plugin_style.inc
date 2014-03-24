<?php

/**
 * @file
 * Handler for references_plugin_style.
 */
class references_plugin_style extends views_plugin_style {
  function render() {
    $options = $this->display->handler->get_option('references_options');

    // Play nice with View UI 'preview' : if the view is not executed through
    // _*_reference_potential_references_views(), just display the HTML.
    if (empty($options)) {
      return parent::render();
    }

    $title_field = $options['title_field'];

    // Group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);

    // Grab the alias of the 'id' field added by references_plugin_display.
    $id_field_alias = $this->display->handler->id_field_alias;

    $results = array();
    $this->view->row_index = 0;
    foreach ($sets as $title => $records) {
      foreach ($records as $label => $values) {
        // Render the row.
        $rendered = $this->row_plugin->render($values);
        // Remove linebreaks and extra spaces introduced by templates.
        $rendered = preg_replace('/\s+/', ' ', trim($rendered));

        // Collect the rendered row, and the raw title value.
        $results[$values->{$id_field_alias}] = array(
          'rendered' => $rendered,
          'group' => $title,
          'title' => $this->view->field[$title_field]->get_value($values),
        );

        $this->view->row_index++;
      }
    }
    unset($this->view->row_index);

    return $results;
  }
}
