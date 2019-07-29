<?php

/**
 * @file
 * Definition of views_handler_filter_user_name.
 */

/**
 * Filter handler for usernames.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_user_name extends views_handler_filter_in_operator {

  /**
   *
   */
  public $always_multiple = TRUE;

  /**
   * {@inheritdoc}
   */
  public function value_form(&$form, &$form_state) {
    $values = array();
    if ($this->value) {
      $result = db_query("SELECT * FROM {users} u WHERE uid IN (:uids)", array(':uids' => $this->value));
      foreach ($result as $account) {
        if ($account->uid) {
          $values[] = $account->name;
        }
        else {
          // Intentionally NOT translated.
          $values[] = 'Anonymous';
        }
      }
    }

    sort($values);
    $default_value = implode(', ', $values);
    $form['value'] = array(
      '#type' => 'textfield',
      '#title' => t('Usernames'),
      '#description' => t('Enter a comma separated list of user names.'),
      '#default_value' => $default_value,
      '#autocomplete_path' => 'admin/views/ajax/autocomplete/user',
    );

    if (!empty($form_state['exposed']) && !isset($form_state['input'][$this->options['expose']['identifier']])) {
      $form_state['input'][$this->options['expose']['identifier']] = $default_value;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function value_validate($form, &$form_state) {
    $values = drupal_explode_tags($form_state['values']['options']['value']);
    $uids = $this->validate_user_strings($form['value'], $values);

    if ($uids) {
      $form_state['values']['options']['value'] = $uids;
    }
  }

  /**
   * {@inheritdoc}
   */
  public function accept_exposed_input($input) {
    $rc = parent::accept_exposed_input($input);

    if ($rc) {
      // If we have previously validated input, override.
      if (isset($this->validated_exposed_input)) {
        $this->value = $this->validated_exposed_input;
      }
    }

    return $rc;
  }

  /**
   * {@inheritdoc}
   */
  public function exposed_validate(&$form, &$form_state) {
    if (empty($this->options['exposed'])) {
      return;
    }

    if (empty($this->options['expose']['identifier'])) {
      return;
    }

    $identifier = $this->options['expose']['identifier'];
    $input = $form_state['values'][$identifier];

    if ($this->options['is_grouped'] && isset($this->options['group_info']['group_items'][$input])) {
      $this->operator = $this->options['group_info']['group_items'][$input]['operator'];
      $input = $this->options['group_info']['group_items'][$input]['value'];
    }

    $values = drupal_explode_tags($input);

    if (!$this->options['is_grouped'] || ($this->options['is_grouped'] && ($input != 'All'))) {
      $uids = $this->validate_user_strings($form[$identifier], $values);
    }
    else {
      $uids = FALSE;
    }

    if ($uids) {
      $this->validated_exposed_input = $uids;
    }
  }

  /**
   * Validate the user string.
   *
   * Since this can come from either the form or the exposed filter, this is
   * abstracted out a bit so it can handle the multiple input sources.
   */
  public function validate_user_strings(&$form, $values) {
    $uids = array();
    $placeholders = array();
    $args = array();
    $results = array();
    foreach ($values as $value) {
      if (strtolower($value) == 'anonymous') {
        $uids[] = 0;
      }
      else {
        $missing[strtolower($value)] = TRUE;
        $args[] = $value;
        $placeholders[] = "'%s'";
      }
    }

    if (!$args) {
      return $uids;
    }

    $result = db_query("SELECT * FROM {users} WHERE name IN (:names)", array(':names' => $args));
    foreach ($result as $account) {
      unset($missing[strtolower($account->name)]);
      $uids[] = $account->uid;
    }

    if ($missing) {
      form_error($form, format_plural(count($missing), 'Unable to find user: @users', 'Unable to find users: @users', array('@users' => implode(', ', array_keys($missing)))));
    }

    return $uids;
  }

  /**
   * {@inheritdoc}
   */
  public function value_submit($form, &$form_state) {
    // Prevent array filter from removing our anonymous user.
  }

  /**
   * {@inheritdoc}
   */
  public function get_value_options() {
  }

  /**
   * {@inheritdoc}
   */
  public function admin_summary() {
    // Set up $this->value_options for the parent summary.
    $this->value_options = array();

    if ($this->value) {
      $result = db_query("SELECT * FROM {users} u WHERE uid IN (:uids)", array(':uids' => $this->value));

      foreach ($result as $account) {
        if ($account->uid) {
          $this->value_options[$account->uid] = $account->name;
        }
        else {
          // Intentionally NOT translated.
          $this->value_options[$account->uid] = 'Anonymous';
        }
      }
    }

    return parent::admin_summary();
  }

}
