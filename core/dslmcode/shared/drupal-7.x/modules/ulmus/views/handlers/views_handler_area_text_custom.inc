<?php

/**
 * @file
 * Definition of views_handler_area_text_custom.
 */

/**
 * Views area text custom handler.
 *
 * @ingroup views_area_handlers
 */
class views_handler_area_text_custom extends views_handler_area_text {

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    unset($options['format']);
    return $options;
  }

  /**
   * {@inheritdoc}
   */
  public function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    // Alter the form element, to be a regular text area.
    $form['content']['#type'] = 'textarea';
    unset($form['content']['#format']);
    unset($form['content']['#wysiwyg']);

    // @todo Use the token refactored base class.
  }

  /**
   * {@inheritdoc}
   */
  public function options_submit(&$form, &$form_state) {
    // Empty, so we don't inherit options_submit from the parent.
  }

  /**
   * {@inheritdoc}
   */
  public function render($empty = FALSE) {
    if (!$empty || !empty($this->options['empty'])) {
      return $this->render_textarea_custom($this->options['content']);
    }

    return '';
  }

  /**
   * Render a text area with filter_xss_admin.
   *
   * @param string $value
   *   The text area string to process.
   *
   * @return string
   *   The string after it has been sanitized, optionally tokenized too.
   */
  public function render_textarea_custom($value) {
    if ($value) {
      if ($this->options['tokenize']) {
        $value = $this->view->style_plugin->tokenize_value($value, 0);
      }
      return $this->sanitize_value($value, 'xss_admin');
    }
  }

}
