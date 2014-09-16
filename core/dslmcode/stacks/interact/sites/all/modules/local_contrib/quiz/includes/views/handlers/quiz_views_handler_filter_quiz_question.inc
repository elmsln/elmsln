<?php

/**
 * A filter that allows the user to show or hide all quiz questions.
 */
class quiz_views_handler_filter_quiz_question extends views_handler_filter_boolean_operator {

  function query() {
    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";
    $types = array_keys(_quiz_get_question_types());
    $in = $this->value ? 'IN' : 'NOT IN';
    $this->query->add_where($this->options['group'], db_and()->condition($field, $types, $in));
  }

  function get_value_options() {
    $this->value_options = array(
      1 => t('Yes'),
      0 => t('No'),
    );
  }

}
