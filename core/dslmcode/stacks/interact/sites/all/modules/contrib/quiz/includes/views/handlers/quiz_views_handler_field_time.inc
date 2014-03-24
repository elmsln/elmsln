<?php
/**
 * @file A handler to provide proper displays for dates.
 *
 * @ingroup views_field_handlers
 */
class quiz_views_handler_field_time extends views_handler_field {
  function render($values) {
    $value = $values->{$this->field_alias};
    return _quiz_format_duration($value);
  }
}
