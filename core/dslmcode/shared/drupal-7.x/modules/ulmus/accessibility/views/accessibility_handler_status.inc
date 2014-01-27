<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying the test status
 * as fields.
 */

class accessibility_handler_status extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['status'] = 'status';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {
    return ($values->{$this->aliases['status']}) ? t('Active') : t('Inactive');
  }
}
