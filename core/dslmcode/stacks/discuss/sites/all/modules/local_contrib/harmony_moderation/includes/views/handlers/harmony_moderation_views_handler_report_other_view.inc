<?php
/**
 * @file
 * Provide views handlers for flagging.
 */

/**
 * Field handler to present a link to the node.
 */
class harmony_moderation_views_handler_report_other_view extends views_handler_field {
  /**
   * Stores all entities which are in the result.
   */
  public $entities;

  function construct() {
    parent::construct();
    $this->real_field = 'flagging_id';
  }

  function pre_render(&$values) {
    $this->entities = array();

    if (!empty($values)) {
      ctools_include('ajax');
      ctools_include('modal');
      ctools_modal_add_js();

      foreach ($values as $row_index => $value) {
        if (!empty($value->flagging_harmony_post_flagging_id)) {
          $this->entities[$row_index] = flagging_load($value->flagging_harmony_post_flagging_id);
        }
      }
    }
  }

  /**
   * Overridden to return the entity object.
   */
  function get_value($values, $field = NULL) {
    return isset($this->entities[$this->view->row_index]) ? $this->entities[$this->view->row_index] : FALSE;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['text'] = array('default' => t('View'), 'translatable' => TRUE);
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
    if ($entity = $this->get_value($values)) {
      if (user_access('moderate harmony_posts') && !empty($entity->field_harmony_moderation_text)) {
        $text = check_plain($this->options['text']);
        $url = "ajax/harmony/moderation/view-report-text/{$entity->flagging_id}/nojs";

        $output = '';
        if ($this->options['newline_prepend']) {
          $output = '<br>';
        }
        $output = '<div id="post-moderate-view-' . $entity->flagging_id . '">' . ctools_modal_text_button($text, $url, '') . '</div>';
        return $output;
      }
    }
  }
}
