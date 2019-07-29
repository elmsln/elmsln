<?php

/**
 * @file
 * Definition of views_test_area_access.
 */

/**
 * A test access plugin.
 */
class views_test_area_access extends views_handler_area {

  /**
   * {@inheritdoc}
   */
  public function access() {
    return $this->options['custom_access'];
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['custom_access'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

}
