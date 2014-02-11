<?php

/**
 * @file
 * Definition of views_handler_argument_file_type.
 */

/**
 * Argument handler to accept a file type.
 */
class views_handler_argument_file_type extends views_handler_argument_string {

  /**
   * Override the behavior of summary_name(). Get the user friendly version
   * of the file type.
   */
  function summary_name($data) {
    return $this->file_type($data->{$this->name_alias});
  }

  /**
   * Override the behavior of title(). Get the user friendly version of the
   * file type.
   */
  function title() {
    return $this->file_type($this->argument);
  }

  /**
   * Helper function to return the human-readable type of the file.
   */
  function file_type($type) {
    $output = file_entity_type_get_name($type);
    if (empty($output)) {
      $output = t('Unknown file type');
    }
    return check_plain($output);
  }
}
