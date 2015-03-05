<?php

/**
 * @file
 * Handler for number of replies to a thread.
 */

class harmony_core_views_handler_thread_field_replies extends views_handler_field {
  function option_definition() {
    $options = parent::option_definition();

    // These defaults will be passed through t() eventually.
    $options['singular'] = array(
      'default' => 'reply',
    );
    $options['plural'] = array(
      'default' => 'replies',
    );

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $form['singular'] = array(
      '#type' => 'textfield',
      '#title' => t('Single reply text'),
      '#default_value' => $this->options['singular'],
      '#description' => t('The text to be used when there is a single reply to the thread.'),
    );

    $form['plural'] = array(
      '#type' => 'textfield',
      '#title' => t('Multiple replies text'),
      '#default_value' => $this->options['plural'],
      '#description' => t('The text to be used when there is either no replies or more than one.'),
    );
  }

  /**
   * Return an array of items for the field.
   */
  /*function set_items($values, $row_id) {
    // In some cases the instance on the entity might be easy, see
    // https://drupal.org/node/1161708 and https://drupal.org/node/1461536 for
    // more information.
    if (empty($values->_field_data[$this->field_alias]) || empty($values->_field_data[$this->field_alias]['entity']) || !isset($values->_field_data[$this->field_alias]['entity']->{$this->definition['field_name']})) {
      return array();
    }

    $display = array(
      'type' => $this->options['type'],
      'settings' => $this->options['settings'],
      'label' => 'hidden',
      // Pass the View object in the display so that fields can act on it.
      'views_view' => $this->view,
      'views_field' => $this,
      'views_row_id' => $row_id,
    );


    $entity_type = $values->_field_data[$this->field_alias]['entity_type'];
    $entity = $this->get_value($values, 'entity');
    if (!$entity) {
      return array();
    }

    $langcode = $this->field_language($entity_type, $entity);

    // Reduce the count.
    $entity->field_harmony_post_count[$langcode][0]['value']--;

    $render_array = field_view_field($entity_type, $entity, $this->definition['field_name'], $display, $langcode);

    $items = array();
    if ($this->options['field_api_classes']) {
      // Make a copy.
      $array = $render_array;
      return array(array('rendered' => drupal_render($render_array)));
    }

    foreach (element_children($render_array) as $count) {
      $items[$count]['rendered'] = $render_array[$count];
      // field_view_field() adds an #access property to the render array that
      // determines whether or not the current user is allowed to view the
      // field in the context of the current entity. We need to respect this
      // parameter when we pull out the children of the field array for
      // rendering.
      if (isset($render_array['#access'])) {
        $items[$count]['rendered']['#access'] = $render_array['#access'];
      }
      // Only add the raw field items (for use in tokens) if the current user
      // has access to view the field content.
      if ((!isset($items[$count]['rendered']['#access']) || $items[$count]['rendered']['#access']) && !empty($render_array['#items'][$count])) {
        $items[$count]['raw'] = $render_array['#items'][$count];
      }
    }
    return $items;
  }

  function render_item($count, $item) {
    // Append our text.
    $text = $item['raw']['value'] == 1 ? check_plain($this->options['singular']) : check_plain($this->options['plural']);
    return render($item['rendered']) . ' ' . t($text);
  }*/

  /**
   * Get the value that's supposed to be rendered.
   *
   * This api exists so that other modules can easy set the values of the field
   * without having the need to change the render method as well.
   *
   * @param $values
   *   An object containing all retrieved values.
   * @param $field
   *   Optional name of the field where the value is stored.
   */
  function get_value($values, $field = NULL) {
    $alias = isset($field) ? $this->aliases[$field] : $this->field_alias;
    if (isset($values->{$alias})) {
      return $values->{$alias} - 1;
    }
  }

  /**
   * Render the field.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    $value = $this->get_value($values);
    $text = $value == 1 ? check_plain($this->options['singular']) : check_plain($this->options['plural']);
    return rtrim($this->sanitize_value($value) . ' ' . $text);
  }
}
