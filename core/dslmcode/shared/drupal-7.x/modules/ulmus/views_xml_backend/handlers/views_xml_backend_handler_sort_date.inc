<?php
/**
 * @file
 * Numeric sort handler for views_xml_backend.
 */

class views_xml_backend_handler_sort_date extends views_xml_backend_handler_sort_numeric {

  function sort_asc($a, $b) {

    $a_value = isset($a->{$this->field}) ? $a->{$this->field} : '';
    $b_value = isset($b->{$this->field}) ? $b->{$this->field} : '';

    if (!is_numeric($a_value)) {
      $a_value = strtotime($a_value);
    }

    if (!is_numeric($b_value)) {
      $b_value = strtotime($b_value);
    }

    return $a_value - $b_value;
  }

  function sort_desc($a, $b) {
    return -$this->sort_asc($a, $b);
  }
}
