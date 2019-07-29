<?php

/**
 * @file
 * Definition of views_handler_field_last_comment_timestamp.
 */

/**
 * Field handler to display the timestamp of a comment with the comments count.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_last_comment_timestamp extends views_handler_field_date {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['comment_count'] = 'comment_count';
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    $comment_count = $this->get_value($values, 'comment_count');
    if (empty($this->options['empty_zero']) || $comment_count) {
      return parent::render($values);
    }
    else {
      return NULL;
    }
  }

}
