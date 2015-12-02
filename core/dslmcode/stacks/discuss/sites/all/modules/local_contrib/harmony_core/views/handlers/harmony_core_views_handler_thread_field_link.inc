<?php

/**
 * @file
 * Definition of harmony_core_views_handler_thread_field_link.
 */

/**
 * Field handler to present a link to the thread content.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_thread_field_link extends views_handler_field_entity {
  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => '', 'translatable' => TRUE, 'tokenize' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#description' => t('This field will accept replacement patterns.'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    if ($thread = $this->get_value($values)) {
      return $this->render_link($thread, $values);
    }
  }

  function render_link($thread, $values) {
    if (harmony_core_thread_access_callback('view', $thread)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = "thread/$thread->thread_id";
      $text = !empty($this->options['text']) ? $this->tokenize_value(check_plain($this->options['text'])) : t('view');

      return $text;
    }
  }
}
