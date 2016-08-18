<?php

/**
 * Field handler to render audio_channel_mode
 */
class getid3_metadata_audio_channel_mode extends getid3_metadata_handler {
  function render($values) {
    return $this->sanitize_value(parent::render($values)['audio_channel_mode']);
  }
}
