<?php

/**
 * @file
 * Definition of harmony_core_views_handler_field_reverse_counter.
 */

/**
 * Field handler to show a counter of the current row.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_field_reverse_counter extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['prepend'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['prepend'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to prepend'),
      '#default_value' => $this->options['prepend'],
      '#description' => t('Specify the text that should appear before the number.'),
    );

    parent::options_form($form, $form_state);
  }

  function query() {
    // do nothing -- to override the parent query.
  }

  function render($values) {
    $pager = $this->view->query->pager;
    $count = $pager->get_total_items() - $this->view->row_index;

    if ($pager->use_pager()) {
      $count -= ($pager->get_items_per_page() * $pager->get_current_page());
    }

    if ($pager->get_offset()) {
      $count -= $pager->get_offset() - 1;
    }

    return check_plain($this->options['prepend']) . $count;
  }
}
