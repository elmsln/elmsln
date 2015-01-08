<?php
/**
 * @file
 * Provide views handlers for post revisions.
 */

/**
 * Field handler to present a link to the node.
 */
class harmony_core_views_handler_post_field_view_diff extends views_handler_field {
  /**
   * Stores all entities which are in the result.
   */
  public $entities;

  function construct() {
    parent::construct();
    $this->real_field = 'post_id';
    $this->additional_fields = array('vid');
  }

  function pre_render(&$values) {
    $this->entities = array();

    if (!empty($values)) {
      ctools_include('ajax');
      ctools_include('modal');
      ctools_modal_add_js();

      $diff_theme = variable_get('diff_theme', 'default');
      drupal_add_css(drupal_get_path('module', 'diff') . "/css/diff.{$diff_theme}.css");

      foreach ($values as $row_index => $value) {
        if (!empty($value->{$this->field_alias}) && !empty($value->{$this->aliases['vid']})) {
          $this->entities[$row_index] = harmony_post_load($value->{$this->field_alias}, $value->{$this->aliases['vid']});
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
    $options['text'] = array('default' => t('Show differences'), 'translatable' => TRUE);
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
    if ($entity = $this->get_value($values)) {
      if (harmony_core_post_revision_access_callback('view', $entity) && harmony_post_get_first_vid($entity->post_id) != $entity->vid) {
        $text = check_plain($this->options['text']);
        $diff_url = "ajax/harmony/post/{$entity->post_id}/revisions/{$entity->vid}/nojs";

        return '<div id="post-revision-' . $entity->vid . '">' . ctools_modal_text_button($text, $diff_url, '') . '</div>';
      }
    }
  }
}
