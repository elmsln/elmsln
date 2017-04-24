<?php
/**
 * @file
 * Filter by the file schema type.
 */

class views_handler_filter_schema_type extends views_handler_filter_in_operator {
  function get_value_options() {
    if (!isset($this->value_options)) {
      $this->value_title = t('File Schema types');
      $types = file_get_stream_wrappers(STREAM_WRAPPERS_VISIBLE);
      $options = array();
      foreach ($types as $type => $info) {
        $options[$type] = t($info['name']);
      }
      asort($options);
      $this->value_options = $options;
    }
  }

  function op_simple() {
    if (empty($this->value)) {
      return;
    }
    $this->ensure_my_table();

    // We use array_values() because the checkboxes keep keys and that can cause
    // array addition problems.
    $statements = array();

    $not_in = $this->operator == 'not in' ? TRUE : FALSE;
    $schema_operator = $not_in ? 'NOT LIKE' : 'LIKE';
    $composite = $not_in ? ' AND ' : ' OR ';

    foreach ($this->value as $schema) {
      $statements[] = 'uri ' . $schema_operator . ' \'' . db_like($schema) . '://%\'';
    }

    $this->query->add_where_expression($this->options['group'], implode($composite, $statements));
  }
}
