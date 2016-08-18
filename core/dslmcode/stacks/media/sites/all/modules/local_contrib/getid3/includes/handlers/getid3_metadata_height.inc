<?php

/**
 * Field handler to render height
 */
class getid3_metadata_height extends getid3_metadata_handler {
  function render($values) {
    return $this->sanitize_value(parent::render($values)['height']);
  }
}
