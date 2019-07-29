<?php

/**
 * @file
 * Definition of views_handler_field_term_link_edit.
 */

/**
 * Field handler to present a term edit link.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_term_link_edit extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['tid'] = 'tid';
    $this->additional_fields['vid'] = 'vid';
    $this->additional_fields['vocabulary_machine_name'] = array(
      'table' => 'taxonomy_vocabulary',
      'field' => 'machine_name',
    );
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();

    $options['text'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  /**
   * {@inheritdoc}
   */
  function render($values) {
    $value = $this->get_value($values, 'tid');
    return $this->render_link($this->sanitize_value($value), $values);
  }

  /**
   * {@inheritdoc}
   */
  function render_link($data, $values) {
    // Mock a term object for taxonomy_term_edit_access(). Use machine name and
    // vid to ensure compatibility with vid based and machine name based
    // access checks. See http://drupal.org/node/995156
    $term = new stdClass();
    $term->vid = $values->{$this->aliases['vid']};
    $term->vocabulary_machine_name = $values->{$this->aliases['vocabulary_machine_name']};
    if ($data && taxonomy_term_edit_access($term)) {
      $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
      $this->options['alter']['path'] = "taxonomy/term/$data/edit";
      $this->options['alter']['query'] = drupal_get_destination();
      return $text;
    }
  }

}
