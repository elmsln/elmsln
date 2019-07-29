<?php

/**
 * @file
 * Definition of views_handler_filter_field_list.
 */

/**
 * Filter handler which uses list-fields as options.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_field_list extends views_handler_filter_many_to_one {

  /**
   * {@inheritdoc}
   */
  public function init(&$view, &$options) {
    parent::init($view, $options);
    // Migrate the settings from the old filter_in_operator values to
    // filter_many_to_one.
    if ($this->options['operator'] == 'in') {
      $this->options['operator'] = 'or';
    }
    if ($this->options['operator'] == 'not in') {
      $this->options['operator'] = 'not';
    }
    $this->operator = $this->options['operator'];
  }

  /**
   * {@inheritdoc}
   */
  public function get_value_options() {
    $field = field_info_field($this->definition['field_name']);
    $this->value_options = list_allowed_values($field);
  }

}
