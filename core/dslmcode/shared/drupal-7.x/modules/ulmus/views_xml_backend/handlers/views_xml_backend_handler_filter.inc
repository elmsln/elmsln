<?php
/**
 * @file
 * Base filter handler for views_xml_backend.
 */

class views_xml_backend_handler_filter extends views_handler_filter_string {
  // exposed filter options
  var $no_single = TRUE;

  function __toString() {
    return $this->generate();
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['case'] = array('default' => TRUE);
    $options['xpath_selector'] = array('default' => '');

    return $options;
  }

  /**
   * This kind of construct makes it relatively easy for a child class
   * to add or remove functionality by overriding this function and
   * adding/removing items from this array.
   */
  function operators() {
    $operators = array(
      '=' => array(
        'title' => t('Is equal to'),
        'short' => t('='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      '!=' => array(
        'title' => t('Is not equal to'),
        'short' => t('!='),
        'method' => 'op_equal',
        'values' => 1,
      ),
      'contains' => array(
        'title' => t('Contains'),
        'short' => t('contains'),
        'method' => 'op_contains',
        'values' => 1,
      ),
      'word' => array(
        'title' => t('Contains any word'),
        'short' => t('has word'),
        'method' => 'op_word',
        'values' => 1,
      ),
      'allwords' => array(
        'title' => t('Contains all words'),
        'short' => t('has all'),
        'method' => 'op_word',
        'values' => 1,
      ),
      'starts-with' => array(
        'title' => t('Starts with'),
        'short' => t('begins'),
        'method' => 'op_starts',
        'values' => 1,
      ),
      '!starts-with' => array(
        'title' => t('Does not start with'),
        'short' => t('not_begins'),
        'method' => 'op_not_starts',
        'values' => 1,
      ),
      'ends-with' => array(
        'title' => t('Ends with'),
        'short' => t('ends'),
        'method' => 'op_ends',
        'values' => 1,
      ),
      '!ends-with' => array(
        'title' => t('Does not end with'),
        'short' => t('not_ends'),
        'method' => 'op_not_ends',
        'values' => 1,
      ),
      '!contains' => array(
        'title' => t('Does not contain'),
        'short' => t('!has'),
        'method' => 'op_not',
        'values' => 1,
      ),
      'shorterthan' => array(
        'title' => t('Length is shorter than'),
        'short' => t('shorter than'),
        'method' => 'op_shorter',
        'values' => 1,
      ),
      'longerthan' => array(
        'title' => t('Length is longer than'),
        'short' => t('longer than'),
        'method' => 'op_longer',
        'values' => 1,
      ),
    );
    // if the definition allows for the empty operator, add it.
    if (!empty($this->definition['allow empty'])) {
      $operators += array(
        'empty' => array(
          'title' => t('Is empty (NULL)'),
          'method' => 'op_empty',
          'short' => t('empty'),
          'values' => 0,
        ),
        'not empty' => array(
          'title' => t('Is not empty (NOT NULL)'),
          'method' => 'op_empty',
          'short' => t('not empty'),
          'values' => 0,
        ),
      );
    }

    return $operators;
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
    $value = $this->value;

    // Awesome string escape.
    $value = '"' . str_replace('"', '\"', $value) . '"';
    if ($operator == '=' || $operator == '!=') {
      return "$xpath $operator $value";
    }
    if (strpos($operator, '!') === 0) {
      $operator = ltrim($operator, '!');
      return "not($operator($xpath, $value))";
    }
    return "$operator($xpath, $value)";
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
