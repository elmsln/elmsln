<?php

/**
 * @file
 * Contains HarmonyCoreViewsHandlerFilterPublic.
 */

class HarmonyCoreViewsHandlerFilterPublic extends views_handler_filter_boolean_operator {
  public $apply_hidden = FALSE;

  /**
   * Alter the "Real" field.
   *
   * Overrides views_handler_filter_boolean_operator::construct().
   */
  function construct() {
    parent::construct();

    $this->real_field = 'status';
    $this->value_value = t('Public');
    $this->accept_null = FALSE;
  }

  /**
   * Only allow yes or no for this filter.
   *
   * Overrides views_handler_filter_boolean_operator::get_value_options().
   */
  function get_value_options() {
    $this->value_options = array(1 => t('Yes'), 0 => t('No'));
  }

  /**
   * Set filter defaults.
   *
   * Overrides views_handler_filter_boolean_operator::option_definition().
   */
  function option_definition() {
    $options = parent::option_definition();
    $options['value']['default'] = TRUE;
    $options['include_nonpublic_if_permitted']['default'] = FALSE;

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['include_nonpublic_if_permitted'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include non-public posts if current user has "view unpublished harmony_posts" permission'),
      '#default_value' => $this->options['include_nonpublic_if_permitted'],
    );
  }

  /**
   * Add the field(s) to the query.
   *
   * Overrides views_handler_filter::query().
   */
  function query() {
    $this->ensure_my_table();
    $status = empty($this->value) ? 0 : 1;
    $hidden = $status ? 0 : 1;

    // If we are allowing nonpublic posts for users with the permission
    // 'view unpublished harmony_posts', then we do not need to alter the query.
    if ($this->options['include_nonpublic_if_permitted'] && user_access('view unpublished harmony_posts')) {
      return;
    }

    if (!$this->apply_hidden) {
      $this->query->add_where($this->options['group'], "$this->table_alias.$this->real_field", $status, '=');
    }
    else {
      // If True is selected then both status and hiden need to be true and
      // false.
      if ($status) {
        $conditions = db_and()
          ->condition("$this->table_alias.$this->real_field", $status, '=')
          ->condition("$this->table_alias.hidden", $hidden, '=');
      }
      // If false then status OR hidden must be false and true.
      else {
        $conditions = db_or()
          ->condition("$this->table_alias.$this->real_field", $status, '=')
          ->condition("$this->table_alias.hidden", $hidden, '=');
      }

      $this->query->add_where(
        $this->options['group'],
        $conditions
      );
    }
  }
}
