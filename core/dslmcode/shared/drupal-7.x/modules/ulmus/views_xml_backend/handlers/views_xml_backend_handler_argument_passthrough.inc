<?php

class views_xml_backend_handler_argument_passthrough extends views_handler_argument {

  /**
   * Override options_form() so that only the relevant options
   * are displayed to the user.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    unset($form['exception']);
  }

  /**
   * Override the behavior of query() to prevent the query
   * from being changed in any way.
   */
  function query($group_by = FALSE) {}
}
