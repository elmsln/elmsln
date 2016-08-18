<?php

/**
 * Field handler to render width
 */
class getid3_metadata_audio_bitrate extends getid3_metadata_handler {
  function option_definition() {
    $options = parent::option_definition();

    $options['format'] = array('default' => 'default', 'translatable' => TRUE);

    // Remove the separator options since we don't need them.
    unset($options['separator']);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Remove the separator and alter options since we don't need them.
    unset($form['separator']);

    $form['prefix']['#weight'] = 10;
    $form['suffix']['#weight'] = 10;
    $form['format'] = array(
      '#type' => 'select',
      '#title' => t('Format'),
      '#default_value' => $this->options['format'],
      '#options' => array(
        'default' => t('Default (Mbps or Kbps)'),
        'raw' => t('Raw numberic value'),
      ),
    );
  }

  function render($values) {
    $value = parent::render($values)['audio_bitrate'];

    // Check to see if hiding should happen before adding prefix and suffix.
    if ($this->options['hide_empty'] && empty($value) && ($value !== 0 || $this->options['empty_zero'])) {
      return '';
    }

    switch ($this->options['format']) {
      case 'raw':
        $output = $value;
        break;
      default:
        $output = theme('getid3_bitrate', array('bitrate' => $value));
    }

    return $this->sanitize_value($this->options['prefix']) . $output . $this->sanitize_value($this->options['suffix']);
  }
}
