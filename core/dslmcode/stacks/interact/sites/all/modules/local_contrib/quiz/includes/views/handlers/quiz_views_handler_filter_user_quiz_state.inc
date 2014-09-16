<?php

/*
 * @file
 * Handles filter user quiz state.
 */
class quiz_views_handler_filter_user_quiz_state extends views_handler_filter {
  var $states = array();
  var $no_operator = TRUE; // for nicer formatting of the form
  var $no_single = TRUE; // always only a single value, at least for now

  function init(&$view, &$options) {
    parent::init($view, $options);
    $this->states = array(
      'any' => t('All Results (Do not filter)'),
      'not_started' => t('Not Started'),
      'in_progress' => t('In Progress'),
      'finished' => t('Finished'),
    );
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['value']['quiz_state'] = array('default' => 'finished');
    return $options;
  }

  function value_form(&$form, &$form_state) {
    $form['value'] = array();
    $form['value']['quiz_state'] = $this->base_form_item();
  }

  function base_form_item() {
    return array(
      '#type' => 'radios',
      '#title' => t('Quiz State'),
      '#description' => t('Output will be limited to only include quiz results in this state. If the filter is exposed, the value set here will be used as the default. Note that "Any" is only useful for exposed filters.'),
      '#options' => $this->states,
      '#default_value' => !empty($this->value['quiz_state']) ? $this->value['quiz_state'] : 'any',
    );
  }

  function exposed_form(&$form, &$form_state) {
    if (empty($this->options['exposed'])) {
      return;
    }
    if (!empty($this->options['expose']['identifier'])) {
      $value = $this->options['expose']['identifier'];

      $form[$value]['quiz_state'] = $this->base_form_item();
      unset($form[$value]['quiz_state']['#title'], $form[$value]['quiz_state']['#description']);
    }
  }

  function admin_summary() {
    return 'is ' . $this->states[$this->value['quiz_state']];
  }

  function query() {
    $val = is_array($this->value) ? $this->value['quiz_state'] : $this->value;
    if (empty($val) || $val == 'any') {
      return;
    }
    $this->ensure_my_table();
    if ($val == 'not_started') {
      $this->query->add_where($this->options['group'], "$this->table_alias.time_end", NULL, "IS NULL");
    }
    else {
      $operator = $val == 'in_progress' ? '=' : '>';
      $this->query->add_where($this->options['group'], "$this->table_alias.time_end", 0, $operator);
    }
  }
}
