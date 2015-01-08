<?php

/**
 * @file
 * Contains the basic 'post' field handler.
 */

/**
 * Field handler to provide simple renderer that allows linking to a post.
 * Definition terms:
 * - link_to_post default: Should this field have the checkbox "link to post" enabled by default.
 *
 * @ingroup views_field_handlers
 */
class harmony_core_views_handler_post_field extends views_handler_field {

  function init(&$view, &$options) {
    parent::init($view, $options);
    // Don't add the additional fields to groupby
    if (!empty($this->options['link_to_post'])) {
      $this->additional_fields['post_id'] = array('table' => 'harmony_post', 'field' => 'post_id');
      /* @todo do we use this? */
      if (module_exists('translation')) {
        $this->additional_fields['language'] = array('table' => 'harmony_post', 'field' => 'language');
      }
    }
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['link_to_post'] = array('default' => isset($this->definition['link_to_post default']) ? $this->definition['link_to_post default'] : FALSE, 'bool' => TRUE);
    return $options;
  }

  /**
   * Provide link to post option
   */
  function options_form(&$form, &$form_state) {
    $form['link_to_post'] = array(
      '#title' => t('Link this field to the original piece of content'),
      '#description' => t("Enable to override this field's links."),
      '#type' => 'checkbox',
      '#default_value' => !empty($this->options['link_to_post']),
    );

    parent::options_form($form, $form_state);
  }

  /**
   * Render whatever the data is as a link to the post.
   *
   * Data should be made XSS safe prior to calling this function.
   */
  function render_link($data, $values) {
    if (!empty($this->options['link_to_post']) && !empty($this->additional_fields['post_id'])) {
      if ($data !== NULL && $data !== '') {
        $this->options['alter']['make_link'] = TRUE;
        $this->options['alter']['path'] = "post/" . $this->get_value($values, 'post_id');
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
