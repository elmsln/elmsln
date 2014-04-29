<?php

/**
 * Field handler for editing an entity metadata property.
 *
 * This allows editing of Entity API metadata properties, as defined in
 * hook_entity_property_info(). To qualify, a property have a 'setter callback'
 * defined.
 */
class editableviews_handler_field_entity_metadata_property extends views_handler_field {

  /**
   * Boolean to indicate to the style plugin that this field is editable.
   */
  public $editable = TRUE;

  function option_definition() {
    $options = parent::option_definition();

    $options['property'] = array('default' => NULL);
    $options['form_use_label'] = array('default' => FALSE);
    $options['reverse_boolean'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $table_data = views_fetch_data($this->table);
    $entity_info = entity_get_info($table_data['table']['entity type']);
    $entity_property_info = entity_get_property_info($table_data['table']['entity type']);

    // Create an array of grouped options.
    $options = array();

    // Common properties.
    $label_common = t('Common');
    $options[$label_common] = array();
    if (isset($entity_info['entity keys']['bundle'])) {
      // Entity API makes the bundle entity key settable, presumably for
      // creating new entities. That's really not going to fly here.
      // (No need to check it exists before we attempt to unset it.)
      unset($entity_property_info['properties'][$entity_info['entity keys']['bundle']]);
    }

    foreach ($entity_property_info['properties'] as $property_name => $property_info) {
      if (empty($property_info['setter callback'])) {
        // We can't do anything with a property that has no information about
        // how to set it.
        continue;
      }

      if (!empty($property_info['field'])) {
        // FieldAPI fields have their own handler that does a far better job
        // (with widgets, etc) than this can do.
        continue;
      }

      $options[$label_common][$property_name] = $property_info['label'];
    }

    // Bundle-specific properties.
    foreach ($entity_property_info['bundles'] as $bundle_name => $bundle_info) {
      $bundle_label = $entity_info['bundles'][$bundle_name]['label'];
      $options[$bundle_label] = array();
      foreach ($bundle_info['properties'] as $property_name => $property_info) {
        if (empty($property_info['setter callback'])) {
          // We can't do anything with a property that has no information about
          // how to set it.
          continue;
        }

        if (!empty($property_info['field'])) {
          // FieldAPI fields have their own handler that does a far better job
          // (with widgets, etc) than this can do.
          continue;
        }

        $options[$bundle_label][$property_name] = $property_info['label'];
      }
    }

    $form['property'] = array(
      '#type' => 'select',
      '#title' => t('Metadata property'),
      '#options' => $options,
      '#description' => t('Select the property to edit with this field. (Only properties that define how they may be set on an entity are available. Be sure to ensure the property applies to all entities the View will show.)'),
      '#default_value' => $this->options['property'],
      // Views AJAX magic which I don't pretend to understand, which allows a
      // dependent form element for 'reverse_boolean'.
      '#ajax' => array(
        'path' => views_ui_build_form_url($form_state),
      ),
      '#submit' => array('views_ui_config_item_form_submit_temporary'),
      '#executes_submit_callback' => TRUE,
    );

    $form['form_use_label'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use handler label for form element'),
      '#description' => t('Use the label for this handler on the form element, rather than the label set in metadata properties which is not always suited to non-developer consumption.'),
      '#default_value' => $this->options['form_use_label'],
    );

    if ($this->options['property']) {
      $entity_all_property_info = entity_get_all_property_info($table_data['table']['entity type']);
      $selected_property_info = $entity_all_property_info[$this->options['property']];

      if ($selected_property_info['type'] == 'boolean') {
        $form['reverse_boolean'] = array(
          '#type' => 'checkbox',
          '#title' => t('Reverse checkbox value'),
          '#description' => t('Reverse the value of the boolean property in the checkbox. Use this for properties which make more sense to the user when inverted.'),
          '#default_value' => $this->options['reverse_boolean'],
        );
      }
    }
  }

  /**
   * Return the name of the entity property this handler controls.
   */
  function field_name() {
    return $this->options['property'];
  }

  /**
   * Render the field.
   *
   * Override this as otherwise we'd just output the entity ID all the time.
   *
   * @param $values
   *   The values retrieved from the database.
   */
  function render($values) {
    // Don't return anything. We don't know the entity we're on at this point.
    // TODO: split up insert_form_elements() to do all the joining up of data
    // before parent::render_fields() is called, and set the entity on the
    // handlers. This would allow us to output the value of the property here.
    return '';
  }

  /**
   * Add the edit form for the field.
   */
  function edit_form($entity_type, $entity, &$element, &$form_state) {
    // Something weird in Views admin UI causes us to come here (because the
    // style plugin gets rendered) without the options set on this handler. This
    // then causes an AJAX error because further down we access a metadata
    // wrapper with no property. I have no time to go chasing this right now, so
    // for now, just bail here if we're not properly set up. Doing this appears
    // to have no adverse or visible side effects.
    if (empty($this->options['property'])) {
      return;
    }

    $wrapper = entity_metadata_wrapper($entity_type, $entity);

    // Get the info for the property we are working with. We only need to get
    // this once.
    if (!isset($this->property_info)) {
      $this->property_info = $wrapper->getPropertyInfo($this->options['property']);
    }

    if (isset($this->property_info['options list'])) {
      // Special case: if the property has an 'options list' defined, we can
      // show a select form element of options.
      $this->edit_form_element_select($element, $form_state, $wrapper);
    }
    else {
      // The type of form element we add depends on the type of the property.
      // This is just a best guess.
      // TODO: add an option to override this?
      switch ($this->property_info['type']) {
        case 'boolean':
          $this->edit_form_element_checkbox($element, $form_state, $wrapper);
          break;
        default:
          $this->edit_form_element_textfield($element, $form_state, $wrapper);
          break;
      }
    }

    // Set the title property.
    if ($this->options['form_use_label']) {
      $element[$this->options['property']]['#title'] = $this->options['label'];
    }
    else {
      $element[$this->options['property']]['#title'] = check_plain($this->property_info['label']);
    }
  }

  /**
   * Create a textfield element.
   *
   * @param &$element
   *  The element to alter.
   * @param &$form_state
   *  The form state.
   * @param $wrapper
   *  The wrapper for the entity whose property is to be shown in the element.
   */
  function edit_form_element_textfield(&$element, &$form_state, $wrapper) {
    // Just do the same thing as node_content_form().
    $element[$this->options['property']] = array(
      '#type' => 'textfield',
      '#required' => !empty($this->property_info['required']),
      // The value might not be set in the case where we're on a non-required
      // relationship with empty data. TODO???
      '#default_value' => $wrapper->{$this->options['property']}->raw(),
      //'#size' => $this->options['textfield_size'],
      '#maxlength' => 255,
    );
  }

  /**
   * Create a select element.
   *
   * @param &$element
   *  The element to alter.
   * @param &$form_state
   *  The form state.
   * @param $wrapper
   *  The wrapper for the entity whose property is to be shown in the element.
   */
  function edit_form_element_select(&$element, &$form_state, $wrapper) {
    // Just do the same thing as node_content_form().
    $element[$this->options['property']] = array(
      '#type' => 'select',
      '#required' => !empty($this->property_info['required']),
      '#options' => $wrapper->{$this->options['property']}->optionsList(),
      // The value might not be set in the case where we're on a non-required
      // relationship with empty data. TODO???
      '#default_value' => $wrapper->{$this->options['property']}->raw(),
    );
  }

  /**
   * Create a checkbox element.
   *
   * @param &$element
   *  The element to alter.
   * @param &$form_state
   *  The form state.
   * @param $wrapper
   *  The wrapper for the entity whose property is to be shown in the element.
   */
  function edit_form_element_checkbox(&$element, &$form_state, $wrapper) {
    $default_value = $wrapper->{$this->options['property']}->raw();
    if ($this->options['reverse_boolean']) {
      $default_value = !$default_value;
    }

    $element[$this->options['property']] = array(
      '#type' => 'checkbox',
      '#required' => !empty($this->property_info['required']),
      // The value might not be set in the case where we're on a non-required
      // relationship with empty data. TODO???
      '#default_value' => $default_value,
    );
  }

  /**
   * Helper to get the value out of the form element.
   */
  function get_element_value($element, $form_state) {
    // The element's '#parents' property gets us nearly all the way there.
    $parents = $element['#parents'];
    $parents[] = $this->options['property'];

    $value = drupal_array_get_nested_value($form_state['values'], $parents);

    return $value;
  }

  /**
   * Handle the form validation for this field's form element.
   */
  function edit_form_validate($entity_type, $entity, &$element, &$form_state) {
    // Wrappers don't have a way of testing the waters to validate, but we can
    // attempt to set the property and catch an exception.
    try {
      // Get the value out of the form state.
      $value = $this->get_element_value($element, $form_state);
      if ($this->options['reverse_boolean']) {
        $value = !$value;
      }

      // Set it on the wrapper, and stand back!
      $wrapper = entity_metadata_wrapper($entity_type, $entity);
      $wrapper->{$this->options['property']}->set($value);
    }
    catch (EntityMetadataWrapperException $e) {
      // TODO: the exception message from Entity API is not that end-user-friendly.
      form_error($element[$this->options['property']], $e->getMessage());
    }
  }

  /**
   * Handle the form submission for this field's form element.
   */
  function edit_form_submit($entity_type, $entity, &$element, &$form_state) {
    // Get the value out of the form state.
    $value = $this->get_element_value($element, $form_state);
    if ($this->options['reverse_boolean']) {
      $value = !$value;
    }

    // We can set this on the wrapper with inpunity, as the validate step
    // already caught any exception this might throw.
    $wrapper = entity_metadata_wrapper($entity_type, $entity);
    $wrapper->{$this->options['property']}->set($value);
  }

}
