<?php

class views_autorefresh_handler_argument_date extends views_handler_argument {
  /**
   * Construct the instance
   */
  function construct() {
    parent::construct();
    $this->format = 'r';
    $this->operator = '>';
  }

  /**
   * Provide a link to the next level of the view
   */
  function summary_name($data) {
    $created = $data->{$this->name_alias};
    return empty($created) ? NULL : format_date(strtotime($created), 'custom', $this->format, NULL);
  }

  /**
   * Provide a link to the next level of the view
   */
  function title() {
    return empty($this->argument) ? NULL : format_date($this->argument, 'custom', $this->format, NULL);
  }

  /**
   * Build the query based upon the formula
   */
  function query($group_by = FALSE) {
    $this->ensure_my_table();
    $this->query->add_where_expression(0, "{$this->table_alias}.{$this->real_field} {$this->operator} :date", array(':date' => $this->argument));
  }
}

