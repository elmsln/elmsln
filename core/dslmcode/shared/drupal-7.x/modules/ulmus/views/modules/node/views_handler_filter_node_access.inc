<?php

/**
 * @file
 * Definition of views_handler_filter_node_access.
 */

/**
 * Filter by node_access records.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_node_access extends views_handler_filter {

  /**
   * {@inheritdoc}
   */
  public function admin_summary() {
  }

  /**
   * {@inheritdoc}
   */
  public function operator_form(&$form, &$form_state) {
  }

  /**
   * {@inheritdoc}
   */
  public function can_expose() {
    return FALSE;
  }

  /**
   * See _node_access_where_sql() for a non-views query based implementation.
   */
  public function query() {
    if (!user_access('administer nodes') && module_implements('node_grants')) {
      $table = $this->ensure_my_table();
      $grants = db_or();
      foreach (node_access_grants('view') as $realm => $gids) {
        foreach ($gids as $gid) {
          $grants->condition(db_and()
            ->condition($table . '.gid', $gid)
            ->condition($table . '.realm', $realm)
          );
        }
      }

      $this->query->add_where('AND', $grants);
      $this->query->add_where('AND', $table . '.grant_view', 1, '>=');
    }
  }

}
