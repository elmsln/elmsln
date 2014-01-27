<?php

/**
 * Basic textfield filter to handle string filtering commands
 * including equality, like, not like, etc.
 */
class views_autocomplete_filters_handler_filter_string extends views_handler_filter_string {
  // exposed filter options
  var $always_multiple = TRUE;

  function option_definition() {
    $options = parent::option_definition();

    $options['expose']['contains'] += array(
      'autocomplete_filter' => array('default' => 0),
      'autocomplete_items' => array('default' => 10),
      'autocomplete_field' => array('default' => ''),
      'autocomplete_raw_suggestion' => array('default' => TRUE),
      'autocomplete_raw_dropdown' => array('default' => TRUE),
      'autocomplete_dependent' => array('default' => FALSE),
    );

    return $options;
  }

  function expose_form(&$form, &$form_state) {
    parent::expose_form($form, $form_state);

    $field_options_all = $this->view->display_handler->get_field_labels();
    // limit options to fields with the same name
    foreach ($this->view->display_handler->get_handlers('field') as $id => $handler) {
      if ($handler->real_field == $this->real_field) {
        $field_options[$id] = $field_options_all[$id];
      }
    }
    if (empty($field_options)) {
      $field_options[''] = t('<Add some fields to view>');
    }
    elseif (empty($this->options['expose']['autocomplete_field']) && !empty($field_options[$this->options['id']])) {
      $this->options['expose']['autocomplete_field'] = $this->options['id'];
    }

    // Build form elements for the right side of the exposed filter form
    $form['expose'] += array(
      'autocomplete_filter' => array(
        '#type' => 'checkbox',
        '#title' => t('Use Autocomplete'),
        '#default_value' => $this->options['expose']['autocomplete_filter'],
        '#description' => t('Use Autocomplete for this filter.'),
      ),
      'autocomplete_items' => array(
        '#type' => 'textfield',
        '#title' => t('Maximum number of items in Autocomplete'),
        '#default_value' => $this->options['expose']['autocomplete_items'],
        '#description' => t('Enter 0 for no limit.'),
        '#dependency' => array('edit-options-expose-autocomplete-filter' => array(TRUE)),
      ),
      'autocomplete_dependent' => array(
        '#type' => 'checkbox',
        '#title' => t('Suggestions depend on other filter fields'),
        '#default_value' => $this->options['expose']['autocomplete_dependent'],
        '#description' => t('Autocomplete suggestions will be filtered by other filter fields'),
        '#dependency' => array('edit-options-expose-autocomplete-filter' => array(TRUE)),
      ),
      'autocomplete_field' => array(
        '#type' => 'select',
        '#title' => t('Field with autocomplete results'),
        '#default_value' => $this->options['expose']['autocomplete_field'],
        '#options' => $field_options,
        '#description' => t('Selected field will be used for dropdown results of autocomplete. In most cases it should be the same field you use for filter.'),
        '#dependency' => array('edit-options-expose-autocomplete-filter' => array(TRUE)),
      ),
      'autocomplete_raw_dropdown' => array(
        '#type' => 'checkbox',
        '#title' => t('Unformatted dropdown'),
        '#default_value' => $this->options['expose']['autocomplete_raw_dropdown'],
        '#description' => t('Use unformatted data from database for dropdown list instead of field formatter result. Value will be printed as plain text.'),
        '#dependency' => array('edit-options-expose-autocomplete-filter' => array(TRUE)),
      ),
      'autocomplete_raw_suggestion' => array(
        '#type' => 'checkbox',
        '#title' => t('Unformatted suggestion'),
        '#default_value' => $this->options['expose']['autocomplete_raw_suggestion'],
        '#description' => t('The same as above, but for suggestion (text appearing inside textfield when item is selected).'),
        '#dependency' => array('edit-options-expose-autocomplete-filter' => array(TRUE)),
      ),
    );
  }

  public function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);

    if (empty($form_state['exposed']) || empty($this->options['expose']['autocomplete_filter'])) {
      // It's not an exposed form or autocomplete is not enabled.
      return;
    }
    
    if (empty($form['value']['#type']) || $form['value']['#type'] !== 'textfield') {
      // Not a textfield.
      return;
    }
    
    // Add autocomplete path to the exposed textfield.
    $form['value']['#autocomplete_path'] = 'autocomplete_filter/' . $this->options['id'] . '/' . $this->view->name . '/' . $this->view->current_display;
    
    // Add JS script with core autocomplete overrides to the end of JS files
    // list to be sure it is added after the "misc/autocomplete.js" file. Also
    // mark the field with special class.
    if (!empty($this->options['expose']['autocomplete_dependent'])) {
      $file_path = drupal_get_path('module', 'views_autocomplete_filters') . '/js/views-autocomplete-filters-dependent.js';
      drupal_add_js($file_path, array(
        'weight' => 99,
      ));

      $form['value']['#attributes']['class'][] = 'views-ac-dependent-filter';
    }
  }

  public function validate() {
    $errors = parent::validate();

    if (!empty($this->options['exposed']) && !empty($this->options['expose']['autocomplete_filter'])) {
      $fields = $this->view->display_handler->get_handlers('field');
      $field_name = !empty($this->options['expose']['autocomplete_field']) ? $this->options['expose']['autocomplete_field'] : $this->options['id'];
      if (empty($field_name) || empty($fields[$field_name])) {
        $current_display = $this->view->display[$this->view->current_display];
        $errors[] = t('Field with autocomplete results is not selected for %label filter in %display display.', array(
          '%label' => $this->ui_name(TRUE),
          '%display' => $current_display->display_title . ' (' . $this->view->current_display . ')',
        ));
      }
    }

    return $errors;
  }
}
