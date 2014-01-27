<?php

class views_xml_backend_handler_argument extends views_handler_argument {
  /**
   * Set up the query for this argument. The argument sent may be found at
   * $this->argument.
   */
  function query($group_by = FALSE) {
    // @todo: Handle group_by argument.
    $this->query->add_argument($this);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['xpath_selector'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['xpath_selector'] = array(
      '#type' => 'textfield',
      '#title' => 'XPath selector',
      '#description' => t('The field name in the table that will be used as the filter.'),
      '#default_value' => $this->options['xpath_selector'],
      '#required' => TRUE,
    );
  }

  function generate() {
    $xpath = $this->options['xpath_selector'];
    $value = $this->get_value();

    // Awesome string escape.
    $value = '"' . str_replace('"', '\"', $value) . '"';
    // @todo: Maybe set an extra option so you can select the operator?
    return "$xpath = $value";
  }

  function __toString() {
    return $this->generate();
  }

  function ui_name($short = FALSE) {
    if (!empty($this->options['ui_name'])) {
      $title = check_plain($this->options['ui_name']);
      return $title;
    }
    $title = ($short && isset($this->definition['title short'])) ? $this->definition['title short'] : $this->definition['title'];
    return t('!xpath: !title', array('!xpath' => $this->options['xpath_selector'], '!title' => $title));
  }
}
