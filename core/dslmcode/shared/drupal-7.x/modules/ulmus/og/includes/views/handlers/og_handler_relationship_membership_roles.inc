<?php

/**
 * Specialized relationship handler between OG membership and the OG user roles.
 *
 * @ingroup views
 */
class og_handler_relationship_membership_roles extends views_handler_relationship {

  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    // Set our join handler class.
    // We can't add an extra condition to the join as an expression here because
    // we don't have the alias for the right hand table here.
    $this->definition['join_handler'] = 'og_users_roles_join';

    parent::query();
  }

}

/**
 * Views join handler for the join from {og_membership} to {og_users_roles}.
 */
class og_users_roles_join extends views_join {

  function build_join($select_query, $table, $view_query) {
    // We can't use the $this->extra array to add on our conditions, as they
    // relate two fields rather than a field to a value, and the parent method
    // doesn't allow this. Rather than completely rewrite it, we can call the
    // parent and then add our conditions to the SelectQuery directly.
    parent::build_join($select_query, $table, $view_query);

    $tables =& $select_query->getTables();

    $left_table = $view_query->get_table_info($this->left_table);

    // The left table is {og_membership}, the right table {og_users_roles}.
    $og_membership_alias = $left_table['alias'];
    $og_users_roles_alias = $table['alias'];

    // Add the condition that the group_type and gid fields match in the join
    // from the {og_membership} table to the {og_users_roles} table.
    $tables[$og_users_roles_alias]['condition'] .=
      " AND $og_membership_alias.group_type = $og_users_roles_alias.group_type" .
      " AND $og_membership_alias.gid = $og_users_roles_alias.gid";
  }

}
