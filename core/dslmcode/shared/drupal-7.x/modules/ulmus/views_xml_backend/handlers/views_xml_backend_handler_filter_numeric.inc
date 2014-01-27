<?php
/**
 * @file
 * Numeric filter handler for views_xml_backend.
 */

class views_xml_backend_handler_filter_numeric extends views_handler_filter_numeric {
  // exposed filter options
  var $no_single = TRUE;

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

  /**
   * Add this filter to the query.
   *
   * Due to the nature of fapi, the value and the operator have an unintended
   * level of indirection. You will find them in $this->operator
   * and $this->value respectively.
   */
  function query() {
    $this->query->add_filter($this);
  }

  function generate() {
    $operator = $this->options['expose'] ? $this->operator : $this->options['operator'];
    $xpath = $this->options['xpath_selector'];

    if ($operator == 'between') {
      return $xpath . '>=' . $this->value['min'] . ' and ' . $xpath . '<=' . $this->value['max'];
    }
    if ($operator == 'not between') {
      return $xpath . '<=' . $this->value['min'] . ' or ' . $xpath . '>=' . $this->value['max'];
    }
    return $xpath . $operator . $this->value['value'];
  }

  function ui_name($short = FALSE) {
    if (!empty($this->options['ui_name'])) {
      $title = check_plain($this->options['ui_name']);
      return $title;
    }
    $title = ($short && isset($this->definition['title short'])) ? $this->definition['title short'] : $this->definition['title'];
    return t('!xpath: !title', array('!xpath' => $this->options['xpath_selector'], '!title' => $title));
  }

  function __toString() {
    return $this->generate();
  }
}
