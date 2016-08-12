<?php

/**
 * Field handler to render duration
 */
class getid3_metadata_duration extends getid3_metadata_handler {
  function render($values) {
    return $this->sanitize_value(parent::render($values)['duration']);
  }
}
