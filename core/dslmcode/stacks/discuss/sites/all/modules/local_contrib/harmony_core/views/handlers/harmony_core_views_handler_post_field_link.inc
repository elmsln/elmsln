<?php

/**
 * @file
 * Definition of harmony_core_views_handler_post_field_link.
 */

/**
 * Field handler to present a link to the post content.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_post_field_link extends views_handler_field_entity {
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
    if ($post = $this->get_value($values)) {
      return $this->render_link($post, $values);
    }
  }

  function render_link($post, $values) {
    if (harmony_core_post_access_callback('view', $post)) {
      $this->options['alter']['make_link'] = TRUE;
      $this->options['alter']['path'] = $post->status == HARMONY_PUBLISHED ? "post/$post->post_id/permalink" : "post/$post->post_id";
      $text = !empty($this->options['text']) ? $this->tokenize_value(check_plain($this->options['text'])) : t('view');

      return $text;
    }
  }
}
