<?php

/**
 * Field handler for toggling between rendered value and edit form element.
 *
 * TODO: figure out a way to show the widget type in the admin summary??
 */
class editableviews_handler_field_field_edit extends views_handler_field_field {

  /**
   * Boolean to indicate to the style plugin that this field is editable.
   *
   * We do this here rather than just check the class parentage to allow field
   * handlers to provide form elements for non-FieldAPI entity properties.
   */
  public $editable = TRUE;

  function option_definition() {
    $options = parent::option_definition();

    // We can't realistically provide a default widget type, because there may
    // be entities of different bundles in the view result, and therefore
    // different field instances with different widgets.
    $options['widget_type'] = array('default' => NULL);
    $options['suppress_label'] = array('default' => FALSE);
    $options['suppress_description'] = array('default' => FALSE);

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);

    $field = field_info_field($this->definition['field_name']);
    module_load_include('inc', 'field_ui', 'field_ui.admin');

    $widget_options = array(
      // Banking on there being no widget type called '0', which is a reasonable
      // assumption to make!
      0 => t('Default'),
    );
    $widget_options += field_ui_widget_type_options($field['type']);
    $form['widget_type'] = array(
      '#type' => 'select',
      '#title' => t('Widget type'),
      '#options' => $widget_options,
      '#default_value' => $this->options['widget_type'],
      '#description' => t("The type of form element you would like to present to the user when editing this field." . ' ' .
        "'Default' will use the widget from field settings, and may result in different widgets showing if the entities are of different bundles."),
    );

    $form['suppress_label'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide widget label'),
      '#description' => t('If selected, the label on field widget is hidden. (If the field is required, the * will still show.)'),
      '#default_value' => $this->options['suppress_label'],
    );

    $form['suppress_description'] = array(
      '#type' => 'checkbox',
      '#title' => t('Hide field widget description'),
      '#description' => t('If selected, the description on field widgets is hidden.'),
      '#default_value' => $this->options['suppress_description'],
    );
  }

  /**
   * Return the name of the entity property this handler controls.
   */
  function field_name() {
    return $this->definition['field_name'];
  }

  /**
   * Add the form element for this handler's field to the form.
   *
   * We break this out into the handler to allow other handlers that work with
   * non-FieldAPI fields (eg node title) to also provide a form element.
   *
   * @param $entity_type
   *  The entity type.
   * @param $entity
   *  The entity.
   * @param &$element
   *  The partial form, at $form[ENTITY_ID]. This is passed by reference and
   *  should be altered in place.
   * @param &$form_state
   *  The form state.
   */
  function edit_form($entity_type, $entity, &$element, &$form_state) {
    list($entity_id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);

    // TODO: this prevents this method being static. This would mean we could
    // store class names in the form rather than handler objects, which would
    // considerably save on form cache size!
    $field_name = $this->definition['field_name'];
    $field_instance = field_info_instance($entity_type, $field_name, $bundle);

    // Because a View result can show entities of different bundles, it is
    // essential that we check the field actually exists on the current entity.
    // ctools_field_invoke_field() does actually check for this too, but that
    // only works when it's passed a field name rather than a whole instance.
    if (empty($field_instance)) {
      return;
    }

    // TODO: Faffy to have to keep doing this for the entity in each handler!!!!
    if (isset($entity->language)) {
      $langcode = field_valid_language($entity->language);
    }
    else {
      $langcode = field_valid_language(NULL);
    }

    if (!empty($this->options['suppress_label'])) {
      $field_instance['label'] = '';
    }
    if (!empty($this->options['suppress_description'])) {
      $field_instance['description'] = '';
    }

    // Only doctor the widget type if the option is set; otherwise the widget
    // type set for the entity's bundle will be used.
    if (!empty($this->options['widget_type'])) {
      $field_instance['widget']['type'] = $this->options['widget_type'];

      // We also need to set the module for the widget, in case this differs
      // from the module for the original widget, because this is used to
      // determine which module's hook_field_widget_form() gets invoked.
      $widget_info = field_info_widget_types();
      $widget_info = $widget_info[$this->options['widget_type']];
      $field_instance['widget']['module'] = $widget_info['module'];
    }

    // On new entities, force this to not be required, to allow the user to not
    // create the new entity.
    // Obviously, problems arise when there are multiple editable fields on
    // this entity, since the title *is* required if actually creating an
    // entity!
    // TODO: consider this thorny problem.
    if (!empty($entity->is_new)) {
      $field_instance['required'] = FALSE;
    }

    // If no language is provided use the default site language.
    $field_invoke_options = array(
      'language' => $langcode,
      'default' => TRUE,
    );

    $element += (array) ctools_field_invoke_field($field_instance, 'form', $entity_type, $entity, $element, $form_state, $field_invoke_options);
  }

  /**
   * Handle the form validation for this field's form element.
   *
   * @param $entity_type
   *  The entity type.
   * @param $entity
   *  The entity.
   * @param &$element
   *  The partial form, at $form[ENTITY_ID].
   * @param &$form_state
   *  The form state.
   * @param &$errors
   *  An array of errors, in the same format as expected by
   *  hook_field_attach_validate().
   */
  function edit_form_validate($entity_type, $entity, &$element, &$form_state, &$errors) {
    list($entity_id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
    $field_name = $this->definition['field_name'];
    $field_instance = field_info_instance($entity_type, $field_name, $bundle);

    // Because a View result can show entities of different bundles, it is
    // essential that we check the field actually exists on the current entity.
    // ctools_field_invoke_field() does actually check for this too, but that
    // only works when it's passed a field name rather than a whole instance.
    if (empty($field_instance)) {
      return;
    }

    // Extract field values from submitted values.
    // We pass a partial $form array to the Field API hook. This contains at
    // its base the #parents array, which tells Field API where to look for
    // the values in $form_state.
    ctools_field_invoke_field_default($field_instance, 'extract_form_values', $entity_type, $entity, $element, $form_state);

    // Check generic, field-type-agnostic errors first.
    ctools_field_invoke_field_default($field_instance, 'validate', $entity_type, $entity, $errors);
    // Check field-type specific errors.
    ctools_field_invoke_field($field_instance, 'validate', $entity_type, $entity, $errors);
  }

  /**
   * Set form validation errors for this field's form element.
   *
   * @param $entity_type
   *  The entity type.
   * @param $entity
   *  The entity.
   * @param &$element
   *  The partial form, at $form[ENTITY_ID].
   * @param &$form_state
   *  The form state.
   * @param &$errors
   *  An array of errors, in the same format as expected by
   *  hook_field_attach_validate().
   */
  function edit_form_validate_errors($entity_type, $entity, &$element, &$form_state, &$errors) {
    list($entity_id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
    $field_name = $this->definition['field_name'];
    $field_instance = field_info_instance($entity_type, $field_name, $bundle);

    // Pass field-level validation errors back to widgets for accurate error
    // flagging.
    foreach ($errors as $field_errors) {
      foreach ($field_errors as $langcode => $errors) {
        $field_state = field_form_get_state($element['#parents'], $field_name, $langcode, $form_state);
        $field_state['errors'] = $errors;
        field_form_set_state($element['#parents'], $field_name, $langcode, $form_state, $field_state);
      }
    }
    ctools_field_invoke_field_default($field_instance, 'form_errors', $entity_type, $entity, $element, $form_state);
  }

  /**
   * Handle the form submission for this field's form element.
   */
  function edit_form_submit($entity_type, $entity, &$element, &$form_state) {
    list($entity_id, $vid, $bundle) = entity_extract_ids($entity_type, $entity);
    $field_name = $this->definition['field_name'];
    $field_instance = field_info_instance($entity_type, $field_name, $bundle);

    // Because a View result can show entities of different bundles, it is
    // essential that we check the field actually exists on the current entity.
    // ctools_field_invoke_field() does actually check for this too, but that
    // only works when it's passed a field name rather than a whole instance.
    if (empty($field_instance)) {
      return;
    }

    // Extract field values from submitted values.
    // We pass the partial $form array to the Field API hook. This contains at
    // its base the #parents array, which tells Field API where to look for
    // the values in $form_state.
    ctools_field_invoke_field_default($field_instance, 'extract_form_values', $entity_type, $entity, $element, $form_state);

    ctools_field_invoke_field_default($field_instance, 'submit',              $entity_type, $entity, $element, $form_state);
  }

}
