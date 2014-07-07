<?php

/**
 * @file
 * Custom Views integration join for the page counters
 *
 * @ingroup print
 */

class print_join_page_counter extends views_join {
  // PHP 4 doesn't call constructors of the base class automatically from a
  // constructor of a derived class. It is your responsibility to propagate
  // the call to constructors upstream where appropriate.
  function construct($table = NULL, $left_table = NULL, $left_field = NULL, $field = NULL, $extra = array(), $type = 'LEFT') {
    parent::construct($table, $left_table, $left_field, $field, $extra, $type);
  }

  function build_join($select_query, $table, $view_query) {
    if ($this->left_table) {
      $this->left_field = "CONCAT('node/', $this->left_table.$this->left_field)";
      $this->left_table = NULL;
    }
    parent::build_join($select_query, $table, $view_query);
  }
}
