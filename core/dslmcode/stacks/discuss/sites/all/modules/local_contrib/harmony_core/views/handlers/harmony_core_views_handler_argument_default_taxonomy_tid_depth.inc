<?php

/**
 * @file
 * Definition of
 * harmony_core_views_handler_argument_default_taxonomy_tid_depth.
 */

/**
 * Argument handler for taxonomy terms with depth.
 *
 * This handler is actually part of the harmony_thread table and has some
 * restrictions, because it uses a subquery to find threads with.
 *
 * @ingroup views_argument_handlers
 */
class harmony_core_views_handler_argument_default_taxonomy_tid_depth extends views_handler_argument {

  function option_definition() {
    $options = parent::option_definition();

    $options['depth'] = array('default' => 0);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['depth'] = array(
      '#type' => 'weight',
      '#title' => t('Depth'),
      '#default_value' => $this->options['depth'],
      '#description' => t('The depth will match threads tagged with terms in the hierarchy. For example, if you have the term "fruit" and a child term "apple", with a depth of 1 (or higher) then filtering for the term "fruit" will get nodes that are tagged with "apple" as well as "fruit". If negative, the reverse is true; searching for "apple" will also pick up nodes tagged with "fruit" if depth is -1 (or lower).'),
    );

    parent::options_form($form, $form_state);
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

    $operator = "=";
    $tids = $this->argument;

    $field_name = variable_get('harmony_core_category_field', 'field_harmony_category');

    // Now build the subqueries.
    $subquery = db_select('field_data_' . $field_name, 'fhc');
    $subquery->addField('fhc', 'entity_id');
    $where = db_or()->condition('fhc.' . $field_name . '_tid', $tids, $operator);
    $last = "tn";

    if ($this->options['depth'] > 0) {
      $subquery->leftJoin('taxonomy_term_hierarchy', 'th', "th.tid = fhc." . $field_name . '_tid');
      $last = "th";
      foreach (range(1, abs($this->options['depth'])) as $count) {
        $subquery->leftJoin('taxonomy_term_hierarchy', "th$count", "$last.parent = th$count.tid");
        $where->condition("th$count.tid", $tids, $operator);
        $last = "th$count";
      }
    }
    elseif ($this->options['depth'] < 0) {
      foreach (range(1, abs($this->options['depth'])) as $count) {
        $subquery->leftJoin('taxonomy_term_hierarchy', "th$count", "$last.tid = th$count.parent");
        $where->condition("th$count.tid", $tids, $operator);
        $last = "th$count";
      }
    }

    $subquery->condition($where);
    $this->query->add_where(0, "$this->table_alias.$this->real_field", $subquery, 'IN');
  }

}
