<?php

/**
 * @file
 * Custom Views integration join for the page counters.
 *
 * @ingroup print
 */

/**
 * Class print_join_page_counter.
 */
class print_join_page_counter extends views_join {

  /**
   * @inheritdoc
   */
  public function construct($table = NULL, $left_table = NULL, $left_field = NULL, $field = NULL, $extra = array(), $type = 'LEFT') {
    // PHP 4 doesn't call constructors of the base class automatically from a
    // constructor of a derived class. It is your responsibility to propagate
    // the call to constructors upstream where appropriate.
    parent::construct($table, $left_table, $left_field, $field, $extra, $type);
  }

  /**
   * @inheritdoc
   */
  public function build_join($select_query, $table, $view_query) {
    if ($this->left_table) {
      $this->left_field = "CONCAT('node/', $this->left_table.$this->left_field)";
      $this->left_table = NULL;
    }
    parent::build_join($select_query, $table, $view_query);
  }

}
