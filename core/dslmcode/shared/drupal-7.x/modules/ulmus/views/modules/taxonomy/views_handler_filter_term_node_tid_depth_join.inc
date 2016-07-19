<?php

/**
 * @file
 * Definition of views_handler_filter_term_node_tid_depth_join.
 */

/**
 * Filter handler for taxonomy terms with depth.
 *
 * This handler is actually part of the node table and has some restrictions,
 * because it uses a subquery to find nodes with.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_term_node_tid_depth_join extends views_handler_filter_term_node_tid {
  function operator_options($which = 'title') {
    return array(
      'or' => t('Is one of'),
    );
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['depth'] = array('default' => 0);

    return $options;
  }

  function extra_options_form(&$form, &$form_state) {
    parent::extra_options_form($form, $form_state);

    $form['depth'] = array(
      '#type' => 'weight',
      '#title' => t('Depth'),
      '#default_value' => $this->options['depth'],
      '#description' => t('The depth will match nodes tagged with terms in the hierarchy. For example, if you have the term "fruit" and a child term "apple", with a depth of 1 (or higher) then filtering for the term "fruit" will get nodes that are tagged with "apple" as well as "fruit". If negative, the reverse is true; searching for "apple" will also pick up nodes tagged with "fruit" if depth is -1 (or lower).'),
    );
  }

  function query() {
    // If no filter values are present, then do nothing.
    if (count($this->value) == 0) {
      return;
    }
    elseif (count($this->value) == 1) {
      // Somethis $this->value is an array with a single element so convert it.
      if (is_array($this->value)) {
        $this->value = current($this->value);
      }
      $operator = '=';
    }
    else {
      $operator = 'IN';# " IN (" . implode(', ', array_fill(0, sizeof($this->value), '%d')) . ")";
    }

    // The normal use of ensure_my_table() here breaks Views.
    // So instead we trick the filter into using the alias of the base table.
    // See http://drupal.org/node/271833
    // If a relationship is set, we must use the alias it provides.
    if (!empty($this->relationship)) {
      $this->table_alias = $this->relationship;
    }
    // If no relationship, then use the alias of the base table.
    elseif (isset($this->query->table_queue[$this->query->base_table]['alias'])) {
      $this->table_alias = $this->query->table_queue[$this->query->base_table]['alias'];
    }
    // This should never happen, but if it does, we fail quietly.
    else {
      return;
    }

    // The tids variable can be an integer or an array of integers.
    $tids = is_array($this->value) ?  $this->value : array($this->value);

    if ($this->options['depth'] > 0) {
      // When the depth is positive search the children.
      foreach ($tids as $tid) {
        // The term must be loaded to get vid for use in taxonomy_get_tree().
        if ($term = taxonomy_term_load($tid)) {
          // For every tid argument find all the children down to the depth set
          // in the options and save the tids for the condition.
          $tree = taxonomy_get_tree($term->vid, $term->tid, (int) $this->options['depth']);
          $tids = array_merge($tids, array_map('_taxonomy_get_tid_from_term', $tree));
        }
      }
    }
    elseif ($this->options['depth'] < 0) {
      // When the depth is negative search the parents.
      foreach ($tids as $tid) {
        // For every tid argument find all the parents up to the depth set
        // in the options and add the tids into the array. Since there is
        // no taxonomy function to get all parents with a depth limit it
        // is done here building a multidimensional array.
        if ($term = taxonomy_term_load($tid)) {
          // A variable is needed to track the current depth level.
          $n = 0;
          // Initialise our depth based parents array with the leaf term.
          $parents[$n--][] = $term;
          while ($n >= $this->options['depth']) {
            // At each depth find the parents of the current terms.
            // It is important to note that it is possible for a term to have
            // multiple parents so get the parents of every parent and so on.
            $parents[$n] = array();
            foreach ($parents[$n + 1] as $term) {
              $parents[$n] += taxonomy_get_parents($term->tid);
            }
            // Save all the tids for the condition.
            $tids = array_merge($tids, array_map('_taxonomy_get_tid_from_term', $parents[$n]));
            $n--;
          }
        }
      }
    }

    // Check the size of the array and set the operator accordingly.
    if (count($tids) > 1) {
      $operator = 'IN';
    }
    else {
      $tids = current($tids);
      $operator = '=';
    }

    // Join on taxonomy index table.
    $join = new views_join();
    $join->table = 'taxonomy_index';
    $join->field = 'nid';
    $join->left_table = $this->table_alias;
    $join->left_field = $this->real_field;
    $join->type = 'INNER';
    $join->extra = array(
      array(
        'field' => 'tid',
        'value' => $tids,
        'operator' => $operator,
      )
    );
    $taxonomy_index_alias = $this->query->add_relationship('taxonomy_index', $join, 'node');
  }
}
