<?php

/**
 * @file
 * Handler for dynamic_select_plugin_row_fields.
 */
class dynamic_select_plugin_row_fields extends views_plugin_row_fields {

  function option_definition() {
    $options = parent::option_definition();

    // Set the defaults. 'inline' and 'default_field_elements' are overwritten in pre render
    $options['separator'] = array('default' => '-');
    $options['hide_empty'] = array('default' => FALSE);

    return $options;
  }

  /**
   * Adjust the form for setting options.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove form element for options which are forced
    unset($form['default_field_elements']);
    unset($form['inline']);
  }

  function pre_render($row) {

    // We have to set those options as they are expected in the rendering

    // Force all fields to be inline by default.
    $fields = $this->view->get_items('field', $this->display->id);
    $this->options['inline'] = drupal_map_assoc(array_keys($fields));

    // Force no wrapper as anyway we strip out the HTML in the output
    $this->options['default_field_elements'] = array('default' => FALSE);

    return parent::pre_render($row);
  }
}
