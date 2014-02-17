<?php

/*
 * @file
 * Handles filter nullable user.
 */
class quiz_views_handler_filter_user_nullable extends views_handler_filter {
  function option_definition() {
    $options = parent::option_definition();

    $options['allow_null'] = array('default' => FALSE);
    $options['use_current'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['use_current'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use Current User'),
      '#description' => t('Filter using the current user; only quiz results owned by the current user will be shown.'),
      '#default_value' => $this->options['use_current'],
    );
    $form['allow_null'] = array(
      '#type' => 'checkbox',
      '#title' => t('Used for Quiz Status'),
      '#description' => t('If you are using the Quiz Status, this box must be checked; otherwise, the field will not work properly.'),
      '#default_value' => $this->options['allow_null'],
    );
  }

  function admin_summary() {
    return !empty($this->options['use_current']) ? t('Current User') : t('NOT Current User');
  }

  function query() {
    $group = $this->query->set_where_group('AND', 'qnr_user');
    $this->ensure_my_table();

    $operator = empty($this->options['use_current']) ? '!=' : '=';
    // By adding the isNull, joins can properly inform us about quiz state
    $this->query->add_where(
        $group,
        db_or()
          ->condition("$this->table_alias.$this->real_field", "***CURRENT_USER***", $operator)
          ->isNull("$this->table_alias.$this->real_field")
    );
  }
}
