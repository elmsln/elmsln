<?php

/**
 * @file
 * Definition of views_handler_field_file_filename.
 */

/**
 * Field handler to provide simple renderer that allows linking to a file.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_file_filename extends views_handler_field_file {
  /**
   * Constructor to provide additional field to add.
   */
  function init(&$view, &$options) {
    if (!empty($this->options['link_to_file'])) {
      $this->additional_fields['fid'] = 'fid';
    }
    parent::init($view, $options);
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_file'] = array('default' => TRUE, 'bool' => TRUE);
    return $options;
  }

  /**
   * Provide link to file option
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['link_to_file']['#title'] = t('Link this field to the original file');
  }

  /**
   * Render whatever the data is as a link to the file.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_file']) && !empty($this->additional_fields['fid'])) {
      if ($data !== NULL && $data !== '') {
        $this->options['alter']['make_link'] = TRUE;
        $this->options['alter']['path'] = 'file/' . $this->get_value($values, 'fid');
      }
    }
    return $data;
  }
}
