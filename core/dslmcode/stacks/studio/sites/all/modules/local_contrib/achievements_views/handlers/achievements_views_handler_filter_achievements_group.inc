<?php

/**
 * @file
 * Definition of views_handler_filter_string.
 */

/**
 * Basic textfield filter to handle string filtering commands
 * including equality, like, not like, etc.
 *
 * @ingroup views_filter_handlers
 */
class achievements_views_handler_filter_achievements_group extends views_handler_filter_string {
  function query() {
    $info = $this->operators();
    if (!empty($info[$this->operator]['method'])) {
      $this->{$info[$this->operator]['method']}('group');
    }
  }

  function op_equal($field) {
    $op = $this->operator();
    $this->query->achievement_filters = array(
        'group' => array(
            $op => $this->value,
        ),
    );
  }

/* TODO
  function op_contains($field) {
    $this->query->add_where($this->options['group'], $field, '%' . db_like($this->value) . '%', 'LIKE');
  }

  function op_word($field) {
    $where = $this->operator == 'word' ? db_or() : db_and();

    // Don't filter on empty strings.
    if (empty($this->value)) {
      return;
    }

    preg_match_all('/ (-?)("[^"]+"|[^" ]+)/i', ' ' . $this->value, $matches, PREG_SET_ORDER);
    foreach ($matches as $match) {
      $phrase = false;
      // Strip off phrase quotes
      if ($match[2]{0} == '"') {
        $match[2] = substr($match[2], 1, -1);
        $phrase = true;
      }
      $words = trim($match[2], ',?!();:-');
      $words = $phrase ? array($words) : preg_split('/ /', $words, -1, PREG_SPLIT_NO_EMPTY);
      foreach ($words as $word) {
        $placeholder = $this->placeholder();
        $where->condition($field, '%' . db_like(trim($word, " ,!?")) . '%', 'LIKE');
      }
    }

    if (!$where) {
      return;
    }

    // previously this was a call_user_func_array but that's unnecessary
    // as views will unpack an array that is a single arg.
    $this->query->add_where($this->options['group'], $where);
  }

  function op_starts($field) {
    $this->query->add_where($this->options['group'], $field, db_like($this->value) . '%', 'LIKE');
  }

  function op_not_starts($field) {
    $this->query->add_where($this->options['group'], $field, db_like($this->value) . '%', 'NOT LIKE');
  }

  function op_ends($field) {
    $this->query->add_where($this->options['group'], $field, '%' . db_like($this->value), 'LIKE');
  }

  function op_not_ends($field) {
    $this->query->add_where($this->options['group'], $field, '%' . db_like($this->value), 'NOT LIKE');
  }

  function op_not($field) {
    $this->query->add_where($this->options['group'], $field, '%' . db_like($this->value) . '%', 'NOT LIKE');
  }

  function op_shorter($field) {
    $placeholder = $this->placeholder();
    $this->query->add_where_expression($this->options['group'], "LENGTH($field) < $placeholder", array($placeholder => $this->value));
  }

  function op_longer($field) {
    $placeholder = $this->placeholder();
    $this->query->add_where_expression($this->options['group'], "LENGTH($field) > $placeholder", array($placeholder => $this->value));
  }

  function op_regex($field) {
    $this->query->add_where($this->options['group'], $field, $this->value, 'RLIKE');
  }

  function op_empty($field) {
    if ($this->operator == 'empty') {
      $operator = "IS NULL";
    }
    else {
      $operator = "IS NOT NULL";
    }

    $this->query->add_where($this->options['group'], $field, NULL, $operator);
  }
*/

}
