<?php

/**
 * @file
 * Contains the basic 'thread' field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a thread.
 * Definition terms:
 * - link_to_thread default: Should this field have the checkbox "link to thread" enabled by default.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_thread_field extends views_handler_field {
  function init(&$view, &$options) {
    parent::init($view, $options);
    // Don't add the additional fields to groupby
    if (!empty($this->options['link_to_thread'])) {
      $this->additional_fields['thread_id'] = array('table' => 'harmony_thread', 'field' => 'thread_id');
      /* @todo do we use this? */
      if (module_exists('translation')) {
        $this->additional_fields['language'] = array('table' => 'harmony_thread', 'field' => 'language');
      }
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_thread'] = array('default' => isset($this->definition['link_to_thread default']) ? $this->definition['link_to_thread default'] : FALSE, 'bool' => TRUE);
    return $options;
  }

  /**
   * Provide link to thread option
   */
  function options_form(&$form, &$form_state) {
    $form['link_to_thread'] = array(
      '#title' => t('Link this field to the original piece of content'),
      '#description' => t("Enable to override this field's links."),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_thread']),
    );

    parent::options_form($form, $form_state);
  }

  /**
   * Render whatever the data is as a link to the thread.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_thread']) && !empty($this->additional_fields['thread_id'])) {
      if ($data !== NULL && $data !== '') {
        $this->options['alter']['make_link'] = TRUE;
        $this->options['alter']['path'] = "thread/" . $this->get_value($values, 'thread_id');
        if (isset($this->aliases['language'])) {
          $languages = language_list();
          $language = $this->get_value($values, 'language');
          if (isset($languages[$language])) {
            $this->options['alter']['language'] = $languages[$language];
          }
          else {
            unset($this->options['alter']['language']);
          }
        }
      }
      else {
        $this->options['alter']['make_link'] = FALSE;
      }
    }
    return $data;
  }

  function render($values) {
    $value = $this->get_value($values);
    return $this->render_link($this->sanitize_value($value), $values);
  }
}
