<?php
/**
 * @file
 * Provide views handlers for the post entity.
 */

/**
 * Field handler to present a link which removes a specific report.
 */
class harmony_moderation_views_handler_remove_report extends views_handler_field {
  function construct() {
    parent::construct();
    $this->real_field = 'flagging_id';
    $this->additional_fields['flagging_id'] = array('table' => 'flagging', 'field' => 'flagging_id');
  }

  function pre_render(&$values) {
    parent::construct();
    drupal_add_library('system', 'drupal.ajax');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => t('Remove report'), 'translatable' => TRUE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['text'] = array(
      '#type' => 'textfield',
      '#title' => t('Link text'),
      '#default_value' => $this->options['text'],
    );
    parent::options_form($form, $form_state);

    // The path is set by render_link function so don't allow to set it.
    $form['alter']['path'] = array('#access' => FALSE);
    $form['alter']['external'] = array('#access' => FALSE);
  }

  function render($values) {
    if ($row_id = $this->get_value($values, 'flagging_id')) {
      global $user;

      $text = check_plain($this->options['text']);
      $token = drupal_get_token($user->uid);
      $url = "ajax/harmony/moderation/remove-report/{$row_id}/{$token}/nojs";

      // Don't use ctools_ajax_text_button as we've already added the library.
      $link = l($text, $url, array('html' => TRUE, 'attributes' => array('class' => array('use-ajax'), 'title' => t('Remove report'))));
      return '<div id="post-moderate-remove-report-' . $row_id . '">' . $link . '</div>';
    }
  }
}
