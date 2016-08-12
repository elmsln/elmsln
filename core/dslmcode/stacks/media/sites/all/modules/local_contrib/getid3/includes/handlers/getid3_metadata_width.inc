<?php

/**
 * Field handler to render width
 */
class getid3_metadata_width extends getid3_metadata_handler {
  function render($values) {
    return $this->sanitize_value(parent::render($values)['width']);
  }
}
