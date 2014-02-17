<?php

/*
 * @file
 * Handles field question number.
 */

class quiz_views_handler_field_number_questions extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();
    $options['include_random'] = array(
      'default' => TRUE,
    );
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['include_random'] = array(
      '#type' => 'checkbox',
      '#title' => t('Include random questions?'),
      '#description' => t('Whether or not questions set to "random" should be included in the count.'),
      '#default_value' => $this->options['include_random'],
    );
  }

  function query() {
    $this->ensure_my_table();
    $this->field_alias = 'question_count';
    $formula = "COUNT($this->table_alias.child_vid)";
    if ($this->options['include_random']) {
      $properties_alias = $this->query->ensure_table('quiz_node_properties');

      $formula .= " + (SELECT number_of_random_questions FROM {quiz_node_properties} WHERE vid = $this->table_alias.parent_vid)";
    }
    $this->query->add_field(NULL, "$formula", $this->field_alias);
  }
}
