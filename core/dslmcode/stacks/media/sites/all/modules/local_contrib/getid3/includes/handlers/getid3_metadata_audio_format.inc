<?php

/**
 * Field handler to render audio_format
 */
class getid3_metadata_audio_format extends getid3_metadata_handler {
  function render($values) {
    return $this->sanitize_value(parent::render($values)['audio_format']);
  }
}
