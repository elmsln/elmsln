<?php

/**
 * @file
 * Definition of views_test_plugin_access_test_static.
 */

/**
 * Tests a static access plugin.
 */
class views_test_plugin_access_test_static extends views_plugin_access {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    $options['access'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function access($account) {
    return !empty($this->options['access']);
  }

  /**
   * {@inheritdoc}
   */
  public function get_access_callback() {
    return array('views_test_test_static_access_callback', array(!empty($options['access'])));
  }

}
