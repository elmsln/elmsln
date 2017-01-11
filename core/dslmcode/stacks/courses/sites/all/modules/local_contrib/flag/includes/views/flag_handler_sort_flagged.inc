<?php

/**
 * @file
 * Contains the flagged content sort handler.
 */

/**
 * Handler to sort on whether objects are flagged or not.
 *
 * @ingroup views
 */
class flag_handler_sort_flagged extends views_handler_sort {

  /**
   * Provide a list of options for the default sort form.
   *
   * Should be overridden by classes that don't override sort_form.
   */
  function sort_options() {
    return array(
      'ASC' => t('Unflagged first'),
      'DESC' => t('Flagged first'),
    );
  }

  /**
   * Display whether or not the sort order is ascending or descending
   */
  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('Exposed');
    }

    // Get the labels defined in sort_options().
    $sort_options = $this->sort_options();
    return $sort_options[strtoupper($this->options['order'])];
  }

  function query() {
    $this->ensure_my_table();
    // Add the ordering.
    // Using IS NOT NULL means that the ASC/DESC ordering work in the same
    // direction as sorting by flagging date: empty results come first.
    $this->query->add_orderby(NULL, "($this->table_alias.uid IS NOT NULL)", $this->options['order']);
  }

}
