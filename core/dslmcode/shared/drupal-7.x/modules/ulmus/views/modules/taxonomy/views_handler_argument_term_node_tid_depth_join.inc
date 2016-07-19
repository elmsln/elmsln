<?php

/**
 * @file
 * Definition of views_handler_argument_term_node_tid_depth_join.
 */

/**
 * Argument handler for taxonomy terms with depth.
 *
 * This handler is actually part of the node table and has some restrictions,
 * because it uses a subquery to find nodes with.
 *
 * @ingroup views_argument_handlers
 */
class views_handler_argument_term_node_tid_depth_join extends views_handler_argument {
  function option_definition() {
    $options = parent::option_definition();

    $options['depth'] = array('default' => 0);
    $options['break_phrase'] = array('default' => FALSE, 'bool' => TRUE);
    $options['set_breadcrumb'] = array('default' => FALSE, 'bool' => TRUE);
    $options['use_taxonomy_term_path'] = array('default' => FALSE, 'bool' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['depth'] = array(
      '#type' => 'weight',
      '#title' => t('Depth'),
      '#default_value' => $this->options['depth'],
      '#description' => t('The depth will match nodes tagged with terms in the hierarchy. For example, if you have the term "fruit" and a child term "apple", with a depth of 1 (or higher) then filtering for the term "fruit" will get nodes that are tagged with "apple" as well as "fruit". If negative, the reverse is true; searching for "apple" will also pick up nodes tagged with "fruit" if depth is -1 (or lower).'),
    );

    $form['break_phrase'] = array(
      '#type' => 'checkbox',
      '#title' => t('Allow multiple values'),
      '#description' => t('If selected, users can enter multiple values in the form of 1+2+3. Due to the number of JOINs it would require, AND will be treated as OR with this filter.'),
      '#default_value' => !empty($this->options['break_phrase']),
    );

    $form['set_breadcrumb'] = array(
      '#type' => 'checkbox',
      '#title' => t("Set the breadcrumb for the term parents"),
      '#description' => t('If selected, the breadcrumb trail will include all parent terms, each one linking to this view. Note that this only works if just one term was received.'),
      '#default_value' => !empty($this->options['set_breadcrumb']),
    );

    $form['use_taxonomy_term_path'] = array(
      '#type' => 'checkbox',
      '#title' => t("Use Drupal's taxonomy term path to create breadcrumb links"),
      '#description' => t('If selected, the links in the breadcrumb trail will be created using the standard drupal method instead of the custom views method. This is useful if you are using modules like taxonomy redirect to modify your taxonomy term links.'),
      '#default_value' => !empty($this->options['use_taxonomy_term_path']),
      '#dependency' => array('edit-options-set-breadcrumb' => array(TRUE)),
    );
    parent::options_form($form, $form_state);
  }

  function set_breadcrumb(&$breadcrumb) {
    if (empty($this->options['set_breadcrumb']) || !is_numeric($this->argument)) {
      return;
    }

    return views_taxonomy_set_breadcrumb($breadcrumb, $this);
  }

  /**
   * Override default_actions() to remove summary actions.
   */
  function default_actions($which = NULL) {
    if ($which) {
      if (in_array($which, array('ignore', 'not found', 'empty', 'default'))) {
        return parent::default_actions($which);
      }
      return;
    }
    $actions = parent::default_actions();
    unset($actions['summary asc']);
    unset($actions['summary desc']);
    unset($actions['summary asc by count']);
    unset($actions['summary desc by count']);
    return $actions;
  }

  function query($group_by = FALSE) {
    $this->ensure_my_table();

    if (!empty($this->options['break_phrase'])) {
      $tids = new stdClass();
      $tids->value = $this->argument;
      $tids = views_break_phrase($this->argument, $tids);
      if ($tids->value == array(-1)) {
        return FALSE;
      }

      if (count($tids->value) > 1) {
        $operator = 'IN';
      }
      else {
        $operator = '=';
      }

      $tids = $tids->value;
    }
    else {
      $operator = "=";
      $tids = $this->argument;
    }

    // The tids variable can be an integer or an array of integers.
    $tids = is_array($tids) ? $tids : array($tids);

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

    // Distinct is required to prevent duplicate rows.
    $this->query->distinct = TRUE;
  }

  function title() {
    $term = taxonomy_term_load($this->argument);
    if (!empty($term)) {
      return check_plain($term->name);
    }

    return t('No name');
  }
}
