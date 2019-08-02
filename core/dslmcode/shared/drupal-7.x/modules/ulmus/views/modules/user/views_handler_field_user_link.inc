<?php

/**
 * @file
 * Definition of views_handler_field_user_link.
 */

/**
 * Field handler to present a link to the user.
 *
 * @ingroup views_field_handlers
 */
class views_handler_field_user_link extends views_handler_field {

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->additional_fields['uid'] = 'uid';
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
   * An example of field level access control.
   */
  public function access() {
    return user_access('access user profiles');
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
  public function render($values) {
    $value = $this->get_value($values, 'uid');
    return $this->render_link($this->sanitize_value($value), $values);
  }

  /**
   * {@inheritdoc}
   */
  public function render_link($data, $values) {
    $text = !empty($this->options['text']) ? $this->options['text'] : t('view');

    $this->options['alter']['make_link'] = TRUE;
    $this->options['alter']['path'] = "user/" . $data;

    return $text;
  }

}
