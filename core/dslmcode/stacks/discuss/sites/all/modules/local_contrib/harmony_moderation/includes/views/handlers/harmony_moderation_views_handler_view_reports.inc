<?php
/**
 * @file
 * Provide views handlers for the post entity.
 */

/**
 * Field handler to present a link which opens a modal with the post text.
 */
class harmony_moderation_views_handler_view_reports extends views_handler_field {
  function construct() {
    parent::construct();
    $this->real_field = 'post_id';
  }

  function pre_render(&$values) {
    parent::construct();
    ctools_include('ajax');
    ctools_include('modal');
    ctools_modal_add_js();
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => t('View reports'), 'translatable' => TRUE);
    $options['newline_prepend'] = array('default' => TRUE, 'bool' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link text'),
      '#default_value' => $this->options['text'],
    );
    $form['newline_prepend'] = array(
      '#type' => 'checkbox',
      '#title' => t('Output a newline before the link'),
      '#default_value' => $this->options['newline_prepend'],
    );
    parent::options_form($form, $form_state);

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    if ($row_id = $this->get_value($values)) {
      $text = check_plain($this->options['text']);
      $url = "ajax/harmony/moderation/view-reports/{$values->post_id}/nojs";

      $output = '';
      if ($this->options['newline_prepend']) {
        $output = '<br>';
      }
      $output = '<div id="post-moderate-view-reports-' . $values->post_id . '">' . ctools_modal_text_button($text, $url, '') . '</div>';
      return $output;
    }
  }
}
