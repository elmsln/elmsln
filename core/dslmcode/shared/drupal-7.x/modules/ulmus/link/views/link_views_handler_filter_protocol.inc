<?php

/**
 * @file
 * Contains filter handlers for protocol filters with views.
 */

/**
 * Filter handler for limiting a view to URLs of a certain protocol.
 *
 * @codingStandardsIgnoreStart
 */
class link_views_handler_filter_protocol extends views_handler_filter_string {

  /**
   * Set defaults for the filter options.
   *
   * @codingStandardsIgnoreEnd
   */
  function option_definition() {
    $options = parent::option_definition();

    $options['operator'] = 'OR';
    $options['value'] = 'http';
    $options['case'] = 0;

    return $options;
  }

  /**
   * Define the operators supported for protocols.
   */
  public function operators() {
    $operators = array(
      'OR' => array(
        'title' => t('Is one of'),
        'short' => t('='),
        'method' => 'op_protocol',
        'values' => 1,
      ),
    );

    return $operators;
  }

  /**
   * Options form.
   *
   * @codingStandardsIgnoreStart
   */
  public function options_form(&$form, &$form_state) {
    //@codingStandardsIgnoreEnd
    parent::options_form($form, $form_state);
    $form['case'] = array(
      '#type' => 'value',
      '#value' => 0,
    );
  }

  /**
   * Provide a select list to choose the desired protocols.
   *
   * @codingStandardsIgnoreStart
   */
  public function value_form(&$form, &$form_state) {
    // @codingStandardsIgnoreEnd
    // We have to make some choices when creating this as an exposed
    // filter form. For example, if the operator is locked and thus
    // not rendered, we can't render dependencies; instead we only
    // render the form items we need.
    $which = 'all';
    if (!empty($form_state['exposed']) && empty($this->options['expose']['operator'])) {
      $which = in_array($this->operator, $this->operator_values(1)) ? 'value' : 'none';
    }

    if ($which == 'all' || $which == 'value') {
      $form['value'] = array(
        '#type' => 'select',
        '#title' => t('Protocol'),
        '#default_value' => $this->value,
        '#options' => drupal_map_assoc(variable_get('filter_allowed_protocols', array(
          'http',
          'https',
          'ftp',
          'news',
          'nntp',
          'telnet',
          'mailto',
          'irc',
          'ssh',
          'sftp',
          'webcal',
        ))),
        '#multiple' => 1,
        '#size' => 4,
        '#description' => t('The protocols displayed here are those globally available. You may add more protocols by modifying the <em>filter_allowed_protocols</em> variable in your installation.'),
      );
    }
  }

  /**
   * Filter down the query to include only the selected protocols.
   *
   * @codingStandardsIgnoreStart
   */
  public function op_protocol($field, $upper) {
    // @codingStandardsIgnoreEnd
    $db_type = db_driver();

    $protocols = $this->value;

    $where_conditions = array();
    foreach ($protocols as $protocol) {
      // Simple case, the URL begins with the specified protocol.
      $condition = $field . ' LIKE \'' . $protocol . '%\'';

      // More complex case, no protocol specified but is automatically cleaned
      // up by link_cleanup_url(). RegEx is required for this search operation.
      if ($protocol == 'http') {
        $link_domains = _link_domains();
        if ($db_type == 'pgsql') {
          // PostGreSQL code has NOT been tested. Please report any problems to
          // the link issue queue.
          // pgSQL requires all slashes to be double escaped in regular
          // expressions.
          // @codingStandardsIgnoreLine
          // See http://www.postgresql.org/docs/8.1/static/functions-matching.html#FUNCTIONS-POSIX-REGEXP
          $condition .= ' OR ' . $field . ' ~* \'' . '^(([a-z0-9]([a-z0-9\\-_]*\\.)+)(' . $link_domains . '|[a-z][a-z]))' . '\'';
        }
        else {
          // mySQL requires backslashes to be double (triple?) escaped within
          // character classes.
          // @codingStandardsIgnoreLine
          // See http://dev.mysql.com/doc/refman/5.0/en/string-comparison-functions.html#operator_regexp
          $condition .= ' OR ' . $field . ' REGEXP \'' . '^(([a-z0-9]([a-z0-9\\\-_]*\.)+)(' . $link_domains . '|[a-z][a-z]))' . '\'';
        }
      }

      $where_conditions[] = $condition;
    }

    $this->query->add_where($this->options['group'], implode(' ' . $this->operator . ' ', $where_conditions));
  }

}
