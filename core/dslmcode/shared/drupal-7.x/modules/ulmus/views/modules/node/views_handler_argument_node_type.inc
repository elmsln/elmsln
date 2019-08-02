<?php

/**
 * @file
 * Definition of views_handler_argument_node_type.
 */

/**
 * Argument handler to accept a node type.
 */
class views_handler_argument_node_type extends views_handler_argument_string {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct('type');
  }

  /**
   * Override the behavior of summary_name(). Get the user friendly version
   * of the node type.
   */
  public function summary_name($data) {
    return $this->node_type($data->{$this->name_alias});
  }

  /**
   * Override the behavior of title(). Get the user friendly version of the
   * node type.
   */
  public function title() {
    return $this->node_type($this->argument);
  }

  /**
   * Get the friendly version of a content type's name.
   *
   * @param string $type
   *   The content type to check.
   *
   * @return string
   *   The system friendly version of a content type's name.
   */
  public function node_type($type) {
    $output = node_type_get_name($type);
    if (empty($output)) {
      $output = t('Unknown content type');
    }
    return check_plain($output);
  }

}
