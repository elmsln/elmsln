<?php

/**
 * @file
 * Definition of views_handler_sort_ncs_last_comment_name.
 */

/**
 * Sort by last comment name, which might be in two different fields.
 *
 * @ingroup views_sort_handlers
 */
class views_handler_sort_ncs_last_comment_name extends views_handler_sort {

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();
    $join = new views_join();
    $join->construct('users', $this->table_alias, 'last_comment_uid', 'uid');

    // @todo This might be safer if we had an ensure_relationship rather than
    // guessing the table alias. Though if we did that we'd be guessing the
    // relationship name so that doesn't matter that much.
    // $this->user_table = $this->query
    //   ->add_relationship(NULL, $join, 'users', $this->relationship);
    $this->user_table = $this->query->ensure_table('ncs_users', $this->relationship, $join);
    $this->user_field = $this->query->add_field($this->user_table, 'name');

    // Add the field.
    $this->query->add_orderby(NULL, "LOWER(COALESCE($this->user_table.name, $this->table_alias.$this->field))", $this->options['order'], $this->table_alias . '_' . $this->field);
  }

}
