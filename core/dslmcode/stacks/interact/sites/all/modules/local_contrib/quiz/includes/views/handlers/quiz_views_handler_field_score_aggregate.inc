<?php

/*
 * @file
 *  Handler for field score.
 */

class quiz_views_handler_field_score_aggregate extends views_handler_field_numeric {

  function construct() {
    parent::construct();
    // This will have to change to be set by options if the methods are ever expanded
    $this->group_field = $this->definition['group field'];
  }

  function option_definition() {
    $options = parent::option_definition();
    return $options;
  }

  function query() {
    $this->ensure_my_table();
    $this->query->add_field($this->table_alias, $this->group_field);
    $this->field_alias = $this->query->add_field(
      NULL, "AVG($this->table_alias.$this->real_field)",
      $this->table_alias . '__average', array('aggregate' => TRUE)
    );
    $this->query->add_groupby("$this->table_alias.$this->group_field"); // nid is OK for average. Others maybe not so much
  }
}
