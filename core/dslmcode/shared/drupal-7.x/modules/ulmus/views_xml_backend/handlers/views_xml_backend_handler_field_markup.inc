<?php
/**
 * @file
 * HTML field handler for views_xml_backend.
 */

class views_xml_backend_handler_field_markup extends views_xml_backend_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['format'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    global $user;
    foreach (filter_formats($user) as $id => $format) {
      $options[$id] = $format->name;
    }
    $form['format'] = array(
      '#title' => t('Format'),
      '#description' => t('The filter format'),
      '#type' => 'select',
      '#default_value' => $this->options['format'],
      '#required' => TRUE,
      '#options' => $options,
    );
  }

  function render_field($value) {
    if ($value) {
      $value = str_replace('<!--break-->', '', $value);
      return check_markup($value, $this->options['format'], '');
    }
  }

  function element_type($none_supported = FALSE, $default_empty = FALSE, $inline = FALSE) {
    if ($inline) {
      return 'span';
    }

    if (isset($this->definition['element type'])) {
      return $this->definition['element type'];
    }

    return 'div';
  }
}
