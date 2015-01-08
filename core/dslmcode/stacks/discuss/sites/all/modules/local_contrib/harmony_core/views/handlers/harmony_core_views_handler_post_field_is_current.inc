<?php
/**
 * @file
 * Provide views handlers for post revisions.
 */

/**
 * Field handler to display if the revision is current or not.
 */
class harmony_core_views_handler_post_field_is_current extends views_handler_field {
  /**
   * Stores all entities which are in the result.
   */
  public $entities;

  function construct() {
    parent::construct();
    $this->additional_fields = array('post_id', 'vid');
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['current_text'] = array('default' => 'Current revision', 'translatable' => TRUE);
    $options['not_current_text'] = array('default' => '', 'translatable' => TRUE);
    return $options;
  }

  function options_form(&$form, &$form_state) {
    $form['current_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display if current'),
      '#default_value' => $this->options['current_text'],
    );

    $form['not_current_text'] = array(
      '#type' => 'textfield',
      '#title' => t('Text to display if not current'),
      '#default_value' => $this->options['not_current_text'],
    );

    parent::options_form($form, $form_state);
  }

  /**
   * Called to add the field to a query.
   */
  function query() {
    $this->ensure_my_table();

    // This isn't a real field, but we put it there nonetheless.
    $this->field_alias = $this->table_alias . '_is_current';

    $this->add_additional_fields();
  }

  function sanitize_value($value, $type = NULL) {
    return filter_xss_admin($value);
  }

  function pre_render(&$values) {
    $this->entities = array();
    if (!empty($values)) {
      $current_text = check_plain($this->options['current_text']);
      $not_current_text = check_plain($this->options['not_current_text']);

      foreach ($values as $row_index => $value) {
        if (!empty($value->{$this->aliases['post_id']}) && !empty($value->{$this->aliases['vid']})) {
          $this->entities[$row_index] = harmony_post_load($value->{$this->aliases['post_id']}, $value->{$this->aliases['vid']});

          if ($this->entities[$row_index]->vid == $this->entities[$row_index]->current_vid) {
            $values[$row_index]->{$this->field_alias} = $current_text;
          }
          else {
            $values[$row_index]->{$this->field_alias} = $not_current_text;
          }
        }
      }
    }
  }
}
