<?php

/**
 * @file
 * Contains HarmonyCoreViewsHandlerFieldPublic.
 */

class HarmonyCoreViewsHandlerFieldPublic extends views_handler_field {
  /**
   * Target the fields we need.
   *
   * Overrides views_handler_field::construct().
   */
  public function construct() {
    parent::construct();

    // We want the status property.
    $this->real_field = 'status';
  }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   *
   * Overrides views_handler_field::render().
   */
  public function render($values) {
    $value = $this->get_value($values);
    $vars = array(
      'status' => $value,
      'hidden' => NULL,
    );

    if (in_array('hidden', $this->additional_fields)) {
      $vars['hidden'] = $this->get_value($values, 'hidden');
    }

    return theme('harmony_public_state', $vars);
  }
}
