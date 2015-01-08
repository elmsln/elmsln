<?php

/**
 * @file
 * Definition of harmony_core_views_handler_filter_thread_read_history_timestamp.
 */

/**
 * Filter for new content.
 *
 * The handler is named such because of compability reasons, the table
 * is thread_read_history.
 *
 * @ingroup views_filter_handlers
 */
class harmony_core_views_handler_filter_thread_read_history_timestamp extends views_handler_filter {
  // Don't display empty space where the operator would be.
  var $no_operator = TRUE;

  function expose_form(&$form, &$form_state) {
    parent::expose_form($form, $form_state);

    unset($form['expose']['required']);
    unset($form['expose']['multiple']);
    unset($form['expose']['remember']);
  }

  function value_form(&$form, &$form_state) {
    // Only present a checkbox for the exposed filter itself. There's no way
    // to tell the difference between not checked and the default value, so
    // specifying the default value via the views UI is meaningless.
    if (!empty($form_state['exposed'])) {
      if (isset($this->options['expose']['label'])) {
        $label = check_plain($this->options['expose']['label']);
      }
      else {
        $label = t('Has new content');
      }
      $form['value'] = array(
        '#type' => 'checkbox',
        '#title' => $label,
        '#default_value' => $this->value,
      );
    }
  }

  function query() {
    global $user;
    // This can only work if we're logged in.
    if (!$user || !$user->uid) {
      return;
    }

    // Don't filter if we're exposed and the checkbox isn't selected.
    if ((!empty($this->options['exposed'])) && empty($this->value)) {
      return;
    }

    // Hey, Drupal kills old history, so nodes that haven't been updated
    // since NODE_NEW_LIMIT are bzzzzzzzt outta here!
    // I copy pasta'd this file, but am keeping this awesome comment :3

    $limit = REQUEST_TIME - variable_get('harmony_core_thread_new_limit', 2592000);

    $this->ensure_my_table();
    $field = "$this->table_alias.$this->real_field";
    $thread = $this->query->ensure_table('harmony_thread', $this->relationship);

    // NULL means a history record doesn't exist. That's clearly new content.
    // Unless it's very very old content. Everything in the query is already
    // type safe cause none of it is coming from outside here.
    $this->query->add_where_expression($this->options['group'], "($field IS NULL AND ($thread.updated > (***CURRENT_TIME*** - $limit))) OR $field < $thread.updated");
  }

  function admin_summary() {
    if (!empty($this->options['exposed'])) {
      return t('exposed');
    }
  }
}
