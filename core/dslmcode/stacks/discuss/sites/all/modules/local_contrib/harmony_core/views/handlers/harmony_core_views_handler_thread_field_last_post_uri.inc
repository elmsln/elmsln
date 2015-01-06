<?php

/**
 * @file
 * Contains the Last post URI field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a thread.
 * Definition terms:
 * - link_to_thread default: Should this field have the checkbox "link to thread" enabled by default.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_thread_field_last_post_uri extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();
    $options['absolute'] = array('default' => FALSE, 'translatable' => FALSE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['absolute'] = array(
      '#type' => 'checkbox',
      '#title' => t('Generate an absolute URL?'),
      '#default_value' => !empty($this->options['absolute']),
    );
    parent::options_form($form, $form_state);
  }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    $value = $this->get_value($values);

    if ($value) {
      if (!empty($this->options['absolute'])) {
        $value = harmony_core_get_last_post_uri(unserialize($value), TRUE);
      }
      else {
        $value = substr(harmony_core_get_last_post_uri(unserialize($value)), 1);
      }
    }

    return $this->sanitize_value($value);
  }
}
