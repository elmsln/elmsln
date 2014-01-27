<?php
/**
 * @file
 * Base sort handler for views_xml_backend.
 */

class views_xml_backend_handler_sort extends views_handler_sort {
  function option_definition() {
    $options = parent::option_definition();
    $options['xpath_selector'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['xpath_selector'] = array(
      '#type' => 'textfield',
      '#title' => t('Field'),
      '#description' => t('The field name in the table that will be used as the filter.'),
      '#default_value' => $this->options['xpath_selector'],
      '#required' => TRUE,
    );
  }

  /**
   * Called to add the sort to a query.
   */
  function query() {
    $this->query->add_field($this->table_alias, $this->options['xpath_selector'], '', $this->options);
    $this->query->add_orderby($this);
  }

  function sort(&$result) {
    $this->field = $this->options['xpath_selector'];

    // Do not try to sort multiple-valued fields. Can we some how?
    if (!empty($this->options['multiple'])) {
      return;
    }
    if (strtolower($this->options['order']) == 'asc') {
      usort($result, array($this, 'sort_asc'));
    }
    else {
      usort($result, array($this, 'sort_desc'));
    }
  }

  function sort_asc($a, $b) {
    $a_value = isset($a->{$this->field}) ? $a->{$this->field} : '';
    $b_value = isset($b->{$this->field}) ? $b->{$this->field} : '';

    return strcasecmp($a_value, $b_value);
  }

  function sort_desc($a, $b) {
    return -$this->sort_asc($a, $b);
  }

  function ui_name($short = FALSE) {
    if (!empty($this->options['ui_name'])) {
      $title = check_plain($this->options['ui_name']);
      return $title;
    }
    $title = ($short && isset($this->definition['title short'])) ? $this->definition['title short'] : $this->definition['title'];
    return t('!xpath: !title', array('!xpath' => $this->options['xpath_selector'], '!title' => $title));
  }
}
