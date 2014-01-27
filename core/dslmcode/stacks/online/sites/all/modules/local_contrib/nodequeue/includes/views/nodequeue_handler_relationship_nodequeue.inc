<?php

/**
 * @file
 * Specialized relationship handler to add nodequeues.
 */
class nodequeue_handler_relationship_nodequeue extends views_handler_relationship {
  /**
   * Init handler to let relationships live on tables other than
   * the table they operate on.
   */
  function init(&$view, &$options) {
    parent::init($view, $options);

    // Tranlate an older setting which was using qids instead of machine names.
    if (!empty($options['qids'])) {
      $map = array_flip(nodequeue_get_qid_map());
      foreach ($options['qids'] as $key => $value) {
        $this->options['names'][$map[$key]] = ($value) ? $map[$key] : 0;
      }
      unset($this->options['qids']);
    }
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['limit']['default'] = FALSE;
    $options['names']['default'] = array();
    return $options;
  }

  /**
   * Default options form that provides the label widget that all fields
   * should have.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['limit'] = array(
      '#type' => 'checkbox',
      '#title' => t('Limit to one or more queues (recommended)'),
      '#default_value' => $this->options['limit'],
    );

    $options = array();
    $queues = nodequeue_load_queues(nodequeue_get_all_qids(0, 0, TRUE), TRUE);
    foreach ($queues as $queue) {
      $options[$queue->name] = $queue->title;
    }

    $form['names'] = array(
      '#prefix' => '<div><div id="edit-options-names">',
      '#suffix' => '</div></div>',
      '#type' => 'checkboxes',
      '#title' => t('Queues'),
      '#options' => $options,
      '#default_value' => $this->options['names'],
      '#process' => array('form_process_checkboxes', 'ctools_dependent_process'),
      '#dependency' => array('edit-options-limit' => array(TRUE)),
    );
  }

  /**
   * Called to implement a relationship in a query.
   */
  function query() {
    // Figure out what base table this relationship brings to the party.
    $join = new views_join();
    $join->definition = array(
      'table' => 'nodequeue_nodes',
      'field' => 'nid',
      'left_table' => 'node',
      'left_field' => 'nid',
    );

    if (!empty($this->options['required'])) {
      $join->definition['type'] = 'INNER';
    }

    if (!empty($this->options['limit'])) {
      $names = array_keys(array_filter($this->options['names']));
      $qids = array();
      $map = nodequeue_get_qid_map();
      foreach ($names as $name) {
        if (isset($map[$name])) {
          $qids[] = $map[$name];
        }
      }

      $join->definition['extra'] = array(array(
        'field' => 'qid',
        'value' => $qids,
      ));
    }

    $join->construct();
    $alias = $join->definition['table'] . '_' . $join->definition['left_table'];
    $this->alias = $this->query->add_relationship($alias, $join, 'nodequeue_nodes', $this->relationship);
  }
}
