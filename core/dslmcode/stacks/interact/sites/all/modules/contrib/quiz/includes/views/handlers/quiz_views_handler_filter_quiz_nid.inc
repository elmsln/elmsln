<?php

/*
 * @file
 * // options are either a) show only the most recent version, b) show the original version.
 */
class quiz_views_handler_filter_quiz_nid extends views_handler_filter {

  /**
   * An array that the subselect will fill with all the corresponding quiz node,
   * according to the configuration on the argument settings form. These vids
   * will then be the actual ones used while generating the real query.
   *
   * @var array
   */
  var $corresponding_vids = array();
  var $group_by;
  var $group_by_table;
  var $secondary_group_by;
  var $secondary_table;
  var $secondary_table_alias;
  var $secondary_tables = array(
    'none' => array(
      'secondary_group_by' => 'nid',
      'secondary_table' => 'quiz_node_results',
      'secondary_vid' => 'vid',
      'secondary_nid' => 'nid',
    ),
    'results' => array(
      'secondary_group_by' => 'uid',
      'secondary_table' => 'quiz_node_results',
      'secondary_vid' => 'vid',
      'secondary_nid' => 'nid',
    ),
    'questions' => array(
      'secondary_group_by' => 'child_nid',
      'secondary_table' => 'quiz_node_relationship',
      'secondary_vid' => 'parent_vid',
      'secondary_nid' => 'parent_nid',
    ),
  );

  function construct() {
    parent::construct();
    $this->vid_field = !empty($this->definition['vid field']) ? $this->definition['vid field'] : 'vid';
    $this->group_by = $this->definition['group by'];
    if (!empty($this->definition['secondary group by'])) {
      $this->secondary_group_by = $this->definition['secondary group by'];
    }
  }

  function can_expose() {
    return FALSE;
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['which_vid'] = array('default' => 'latest');
    $options['secondary'] = array('default' => 'none');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['which_vid'] = array(
      '#type' => 'select',
      '#title' => t('Quiz revision(s) to use'),
      '#options' => array(
        'latest' => t('Latest: most recent version of the quiz ONLY.'),
        'initial' => t('Initial: original version of the quiz ONLY.'),
        // 'all' => t('All: ALL versions of the quiz.')
      ),
      '#description' => t('The filter will limit score results for a particular quiz node id(s) into one or more quiz node revision ids, depending on your selection.'),
      '#default_value' => $this->options['which_vid'],
    );

    $tables = array('none' => t('None'));
    $tables['results'] = t('Use Quiz Results');
    $tables['questions'] = t('Use Quiz Questions');
    $form['secondary'] = array(
      '#type' => 'radios',
      '#title' => t('Secondary Grouping'),
      '#options' => $tables,
      '#default_value' => $this->options['secondary'],
      '#description' => t('If you are looking to generate a list of either quiz questions or quiz results, you must select the appropriate option from this list.'),
    );
  }

  function value_submit($form, &$form_state) {
    $form_state['values']['options']['secondaries'] = $this->secondary_tables[$form_state['values']['options']['secondary']];
  }

  /**
   * Override the default behavior of query() to introduce the medial step of
   * retrieving vids from the provided nids.
   */
  function query() {
    $this->ensure_my_table();

    foreach ($this->options['secondaries'] as $key => $value) {
      if (!is_null($value)) {
        $this->$key = $value;
      }
    }

    $this->group_by_table = !empty($this->definition['group by table']) ?
      $this->query->ensure_table($this->definition['group by table']) :
      $this->table_alias;
    //    $this->query->add_groupby("$this->group_by_table.$this->group_by");
    $this->query->add_groupby("$this->table_alias.$this->field");
    $this->query->add_groupby("$this->table_alias.$this->vid_field");

    //    if (!empty($this->secondary_group_by) || !empty($this->options['secondary_group_by'])) {
    if (!empty($this->secondary_group_by)) {
      $this->secondary_table_alias = $this->query->ensure_table($this->secondary_table);
      $this->query->add_groupby("$this->secondary_table_alias.$this->secondary_group_by");
    }
    $this->query->add_where(0, "$this->secondary_table_alias.$this->secondary_vid", $this->subselect());
  }

  /**
   * Helper method to retrieve the vid(s) the final view query should actually
   * be run against.
   *
   * Would be done in pre_query(), but $this->argument is not yet available at
   * that time. So, called from set_argument().
   */
  function subselect() {
    $operation = ($this->options['which_vid'] == 'initial' ? 'MIN' : 'MAX');
    $subalias = $this->secondary_table_alias . '__subselect';
    $subselect = "SELECT $operation($subalias.$this->secondary_vid) FROM ";
    $subselect .= '{' . $this->secondary_table . "} $subalias WHERE ";
    $subselect .= "$subalias.$this->secondary_group_by = $this->secondary_table_alias.$this->secondary_group_by AND ";
    $subselect .= "$subalias.$this->secondary_nid = $this->secondary_table_alias.$this->secondary_nid";
    return $subselect;

  }
}
