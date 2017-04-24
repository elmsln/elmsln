<?php

/**
 * Field handler that shows a jump link to the save button.
 *
 * This is intended for use on very long views.
 */
class editableviews_handler_field_save_button_jump_link extends views_handler_field {

  function option_definition() {
    $options = parent::option_definition();

    $options['jump_link_text'] = array('default' => t('Jump to save button'));

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['jump_link_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Jump link text'),
      '#default_value' => $this->options['jump_link_text'],
      '#description' => t("The text to show for the link."),
    );
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    // Do nothing: fake field.
  }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    return '<a href="#edit-actions-submit">' . check_plain($this->options['jump_link_text']) . '</a>';
  }

}
