<?php

/**
 * @file
 * Contains .
 */

/**
 * Field handler to present a link to edit a translation.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_locale_link_edit extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['lid'] = 'lid';
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
  public function access() {
    // Ensure user has access to edit translations.
    return user_access('translate interface');
  }

  /**
   * {@inheritdoc}
   */
  public function render($values) {
    $value = $this->get_value($values, 'lid');
    return $this->render_link($this->sanitize_value($value), $values);
  }

  /**
   * {@inheritdoc}
   */
  public function render_link($data, $values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = 'admin/config/regional/translate/edit/' . $data;
    $this->options['alter']['query'] = drupal_get_destination();

    return $text;
  }

}
