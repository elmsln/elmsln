<?php

/**
 * @file
 * Definition of views_handler_filter_node_tnid.
 */

/**
 * Filter by whether the node is the original translation.
 *
 * @ingroup views_filter_handlers
 */
class views_handler_filter_node_tnid extends views_handler_filter {

  /**
   * {@inheritdoc}
   */
  public function admin_summary() {
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['operator']['default'] = 1;

    return $options;
  }

  /**
   * Provide simple boolean operator.
   */
  public function operator_form(&$form, &$form_state) {
    $form['operator'] = array(
      '#type' => 'radios',
      '#title' => t('Include untranslated content'),
      '#default_value' => $this->operator,
      '#options' => array(
        1 => t('Yes'),
        0 => t('No'),
      ),
    );
  }

  /**
   * {@inheritdoc}
   */
  public function can_expose() {
    return FALSE;
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $table = $this->ensure_my_table();
    // Select for source translations (tnid = nid). Conditionally, also accept
    // either untranslated nodes (tnid = 0).
    $expression = "$table.tnid = $table.nid";
    if ($this->operator) {
      $expression .= " OR $table.tnid = 0";
    }
    $this->query->add_where_expression($this->options['group'], $expression);
  }

}
