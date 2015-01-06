<?php

/**
 * @file
 * Definition of harmony_core_views_handler_post_field_position.
 */

/**
 * Field handler for figuring out a posts position within a thread.
 *
 * @ingroup views_field_handlers
 */

class harmony_core_views_handler_post_field_position extends views_handler_field_entity {
  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => 'Post #@position', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display'),
      '#default_value' => $this->options['text'],
      '#description' => t('Use of the text &quot;@position&quot; will be replaced with the posts position number.'),
    );
    parent::options_form($form, $form_state);
  }

  function render($values) {
    if ($post = $this->get_value($values)) {
      // @todo am sure there's a faster way to do this...
      $wrapper = entity_metadata_wrapper('harmony_post', $post);

      if ($wrapper->field_harmony_thread->value()) {
        $position = harmony_core_post_in_thread_position($wrapper->field_harmony_thread->thread_id->value(), $post->post_id);

        if (!empty($position['position'])) {
          $text = !empty($this->options['text']) ? check_plain($this->options['text']) : '@position';
          return format_string($text, array('@position' => $position['position']));
        }
      }

      return NULL;
    }
  }
}
