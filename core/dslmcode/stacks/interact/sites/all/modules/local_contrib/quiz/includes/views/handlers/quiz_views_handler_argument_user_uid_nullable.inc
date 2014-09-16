<?php

/*
 * @file
 * Handles argument user id nullable.
 */

class quiz_views_handler_argument_user_uid_nullable extends views_handler_argument_user_uid {
  function option_definition() {
    $options = parent::option_definition();

    $options['allow_null'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['break_phrase']);
    $form['allow_null'] = array(
      '#type' => 'checkbox',
      '#title' => t('Used for Quiz Status'),
      '#description' => t('When this agument is used, this box must be checked if the Quiz Status field is to work properly.'),
      '#default_value' => $this->options['allow_null'],
    );
  }

  function query($group_by = FALSE) {
    $this->ensure_my_table();
    $operator = empty($this->options['not']) ? '=' : '!=';
    $where = "$this->table_alias.$this->real_field";
    if ($this->options['allow_null']) {
      $group = $this->query->set_where_group('AND', 'qnr_user');
      //$where .= " OR ISNULL($this->table_alias.$this->real_field)";
    }
    else {
      $group = 0;
    }

    // By adding the ISNULL, joins can properly inform us about quiz state
    $this->query->add_where($group, $where, $this->argument);
  }
}
