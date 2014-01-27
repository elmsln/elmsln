<?php

/**
 * @file
 * Provide relationship handler for field collection fields.
 */
class field_collection_handler_relationship extends views_handler_relationship {

  function option_definition() {
    $options = parent::option_definition();
    $options['delta'] = array('default' => -1);

    return $options;
  }

  /**
   * Add a delta selector for multiple fields.
   */
  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $field = field_info_field($this->definition['field_name']);

    // Only add the delta selector if the field is multiple.
    if ($field['cardinality']) {
      $max_delta = ($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) ? 10 : $field['cardinality'];

      $options = array('-1' => t('All'));
      for ($i = 0; $i < $max_delta; $i++) {
        $options[$i] = $i + 1;
      }
      $form['delta'] = array(
        '#type' => 'select',
        '#options' => $options,
        '#default_value' => $this->options['delta'],
        '#title' => t('Delta'),
        '#description' => t('The delta allows you to select which item in a multiple value field to key the relationship off of. Select "1" to use the first item, "2" for the second item, and so on. If you select "All", each item in the field will create a new row, which may appear to cause duplicates.'),
      );
    }
  }

  function ensure_my_table() {
    $field = field_info_field($this->definition['field_name']);

    if (!isset($this->table_alias)) {
      $join = $this->get_join();
      if ($this->options['delta'] != -1 && $field['cardinality']) {
        $join->extra[] = array(
          'field' => 'delta',
          'value' => $this->options['delta'],
          'numeric' => TRUE,
        );
      }
      $this->table_alias = $this->query->add_table($this->table, $this->relationship, $join);
    }
    return $this->table_alias;
  }
}
