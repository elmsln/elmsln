<?php

class quiz_views_handler_field_quiz_question_result_answer extends views_handler_field_prerender_list {

  /**
   * Working with node table, adding active credit types to it.
   */
  function construct() {
    parent::construct();
    $this->additional_fields['result_id'] = array(
      'table' => 'quiz_node_results',
      'field' => 'result_id',
    );
  }

  /**
   * Add fields, alias.
   */
  function query() {
    $this->add_additional_fields();
    $this->field_alias = $this->aliases['result_id'];
  }

  function option_definition() {
    $options = parent::option_definition();

    $options['question_nid'] = array(
      'default' => NULL,
    );
    $options['question_vid'] = array(
      'default' => NULL,
    );
    $options['data_type'] = array(
      'default' => NULL,
    );
    return $options;
  }

  function pre_render(&$values) {
    $this->items = array();

    $result_ids = array();
    foreach ($values as $value) {
      $result_ids[] = $value->result_id;
    }

    $nid = $this->options['question_nid'];
    $vid = $this->options['question_vid'];
    $node = node_load($nid, $vid);
    $info = quiz_question_get_info();
    $className = $info[$node->type]['response provider'];

    if ($result_ids) {
      $raids = db_query('SELECT result_answer_id
        FROM {quiz_node_results_answers} qnra
        LEFT JOIN {quiz_node_results} qnr ON (qnra.result_id = qnr.result_id)
        WHERE question_nid = :nid
          AND question_vid = :vid
          AND qnr.result_id IN (:result_id)', array(':nid' => $nid, ':vid' => $vid, ':result_id' => $result_ids))->fetchAllKeyed(0, 0);

      $this->items = $className::viewsGetAnswers($raids);
    }
  }

  function render_item($count, $item) {
    return parent::render_items($item);
  }

}
