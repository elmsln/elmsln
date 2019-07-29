<?php

/**
 * @file
 * Definition of views_plugin_argument_validate_numeric.
 */

/**
 * Validate whether an argument is numeric or not.
 *
 * @ingroup views_argument_validate_plugins
 */
class views_plugin_argument_validate_numeric extends views_plugin_argument_validate {

  /**
   * {@inheritdoc}
   */
  public function validate_argument($argument) {
    return is_numeric($argument);
  }

}
