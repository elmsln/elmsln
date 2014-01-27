<?php

/**
 * @file
 * Argument handler for subqueues.
 */

/**
 * Subqueues have titles that are determined by doing substitution from
 * the subqueue_title on the queue using the title on the subqueue, which
 * takes a little extra work to do here.
 */
class nodequeue_handler_argument_subqueue_qid extends views_handler_argument_numeric {
  function summary_name_field() {
    $this->queue_alias = $this->query->ensure_table('nodequeue_queue', $this->relationship);
    $this->subqueue_alias = $this->name_table_alias = $this->query->ensure_table('nodequeue_subqueue', $this->relationship);

    $this->queue_title_alias = $this->query->add_field($this->queue_alias, 'subqueue_title');
    $this->subqueue_title_alias = $this->name_alias = $this->query->add_field($this->subqueue_alias, 'title');
  }

  function summary_name($data) {
    $queue_title = $data->{$this->queue_title_alias};
    $subqueue_title = $data->{$this->subqueue_title_alias};

    $value = empty($queue_title) ? $subqueue_title : str_replace('%subqueue', $subqueue_title, $queue_title);

    if (empty($value) && !empty($this->definition['empty field name'])) {
      $value = $this->definition['empty field name'];
    }
    return check_plain($value);
  }
}
