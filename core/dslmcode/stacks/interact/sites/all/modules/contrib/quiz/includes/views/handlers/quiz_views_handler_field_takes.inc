<?php

/*
 * @file
 * Hanldes field takes.
 */
class quiz_views_handler_field_takes extends views_handler_field {
  function render($values) {
    $value = $values->{$this->field_alias};
    if ((int) $value === 0) {
      return 'Unlimited';
    }
    return $value;
  }
}
