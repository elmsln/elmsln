<?php
/**
 * @file
 * Numeric sort handler for views_xml_backend.
 */

class views_xml_backend_handler_sort_numeric extends views_xml_backend_handler_sort {

  function sort_asc($a, $b) {
    $a_value = isset($a->{$this->field}) ? $a->{$this->field} : '';
    $b_value = isset($b->{$this->field}) ? $b->{$this->field} : '';
    return $a_value - $b_value;
  }

  function sort_desc($a, $b) {
    $a_value = isset($a->{$this->field}) ? $a->{$this->field} : '';
    $b_value = isset($b->{$this->field}) ? $b->{$this->field} : '';
    return -($a_value - $b_value);
  }
}
