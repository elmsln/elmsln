<?php

/*
 * @file
 * Handles argument quiz nid.
 */

class quiz_views_handler_argument_quiz_nid extends views_handler_argument_numeric {
  /**
   * An array that the subselect will fill with all the corresponding quiz node,
   * according to the configuration on the argument settings form. These vids
   * will then be the actual ones used while generating the real query.
   *
   * @var array
   */
  var $corresponding_vids = array();
  var $phrase_broken = FALSE;

  function construct() {
    parent::construct();
    $this->nid_field = $this->definition['nid field'];
    $this->vid_field = isset($this->definition['vid field']) ? $this->definition['vid field'] : 'vid';
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['which_vid'] = array('default' => 'latest');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Set weighting so that our element can sanely ordered
    $form['title']['#weight'] = -2;
    //    $form['default_action']['#weight'] = -3;
    //    $form['wildcard']['#weight'] = -4;
    //    $form['wildcard_substitution']['#weight'] = -4;
    $form['which_vid'] = array(
      '#type' => 'select',
      '#title' => t('Quiz revision(s) to use'),
      '#options' => array(
        'latest' => t('Latest: most recent version of the quiz ONLY.'),
        'initial' => t('Initial: original version of the quiz ONLY.'),
        'all' => t('All: ALL versions of the quiz.')
      ),
      '#description' => t('The validator will transform the incoming quiz node id(s) into one or more quiz node revisions, depending on your selection.'),
      '#default_value' => $this->options['which_vid'],
      '#weight' => -1,
    );
  }

  function title_query() {
    $titles = array();

    $result = db_query("SELECT n.title FROM {node_revision} n WHERE n.vid IN (:vids)", array(':vids' => implode(', ', $this->corresponding_vids)));
    while ($term = $result->fetch()) {
      $titles[] = check_plain($term->title);
    }
    return $titles;
  }

  /**
   * Override the default behavior of query() to introduce the medial step of
   * retrieving vids from the provided nids.
   */
  function query($group_by = FALSE) {
    $this->ensure_my_table();
    $this->break_phrase();

    // Do subselect to get relevant vids, then add where clause
    $this->subselect_vids();
    $this->query->add_where(0, "$this->table_alias.$this->nid_field", $this->corresponding_vids);
  }

  /**
   * Set up the argument with the vids extracted from nids.
   *
   * Needs to be done here, because this is the earliest stage at which we can
   * guarantee the contents of $this->argument to be available.
   *
   * @param string $arg
   *   The argument, as delivered in the URL.
   */
  function set_argument($arg) {
    $this->argument = $arg;
    if ($this->validate_arg($arg)) {
      $this->break_phrase();
      $this->subselect_vids();
      return TRUE;
    }
    return FALSE;
  }

  function break_phrase() {
    if (!$this->phrase_broken) {
      // Handle multiple argument inputs
      if (!empty($this->options['break_phrase'])) {
        views_break_phrase($this->argument, $this);
      }
      else {
        $this->value = array($this->argument);
      }
      $this->phrase_broken = TRUE;
    }
  }

  /**
   * Helper method to retrieve the vid(s) the final view query should actually
   * be run against.
   *
   * Would be done in pre_query(), but $this->argument is not yet available at
   * that time. So, called from set_argument().
   */
  function subselect_vids() {
    $query = db_select('quiz_node_properties', 'qnp');
    if (count($this->value) > 1) {
      // Guaranteed to produce multiple values; therefore may need the group by
      $use_group_by = TRUE;
      $operator = empty($this->options['not']) ? 'IN' : 'NOT IN';
      $query->condition('nid', $this->value, $operator);
    }
    else {
      // Multiple values only possible with a NOT; only then do we need group by
      $use_group_by = !empty($this->options['not']);
      $operator = empty($this->options['not']) ? '=' : '!=';
      $query->condition('nid', reset($this->value), $operator);
    }

    switch ($this->options['which_vid']) {
      case 'initial':
        // SQL operation for getting the initial vids based on view config settings
        $query->addExpression('MIN(vid)', 'vid');
        break;
      case 'latest':
        // SQL operation for getting the latest vids based on view config settings
        $query->addExpression('MAX(vid)', 'vid');
        break;
      default:
        // Get them all
        $query->addField('qnp', 'vid');
        break;
    }
    if ($use_group_by) {
      $query->groupBy('nid');
    }
    $result = $query->execute();

    $this->nid_field = $this->vid_field;

    $this->corresponding_vids = array();
    foreach ($result as $item) {
      $this->corresponding_vids[] = $item->vid;
    }
    return (count($this->corresponding_vids) > 1);
  }
}