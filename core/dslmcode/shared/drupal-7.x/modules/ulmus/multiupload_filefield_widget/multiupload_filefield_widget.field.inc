<?php

/**
 * @file
 * Field module functionality for the Multiple File Widget module.
 */

/**
 * Implements hook_field_widget_info().
 */
function multiupload_filefield_widget_field_widget_info() {
  return array(
    'file_mfw' => array(
      'label' => t('Multiupload'),
      'field types' => array('file'),
      'behaviors' => array(
        'multiple values' => FIELD_BEHAVIOR_CUSTOM,
        'default value' => FIELD_BEHAVIOR_NONE,
      ),
      'settings' => array(
        'progress_indicator' => 'throbber',
      ),
    ),
  );
}

 /**
 * Implements hook_field_widget_form().
 *
 * Mostly copied from drupal core module /modules/file/file.field.inc
 */
function multiupload_filefield_widget_field_widget_form(&$form, &$form_state, $field, $instance, $langcode, $items, $delta, $element) {
  // This is essentially copied from file.field.inc.
  $defaults = array(
    'fid' => 0,
    'display' => !empty($field['settings']['display_default']),
    'description' => '',
  );

  // Load the items for form rebuilds from the field state as they might not be
  // in $form_state['values'] because of validation limitations. Also, they are
  // only passed in as $items when editing existing entities.
  $field_state = field_form_get_state($element['#field_parents'], $field['field_name'], $langcode, $form_state);
  if (isset($field_state['items'])) {
    $items = $field_state['items'];
  }

  // Essentially we use the mfw_managed_file type, extended with some enhancements.
  $element_info = element_info('mfw_managed_file');
  $element += array(
    '#type' => 'mfw_managed_file',
    '#upload_location' => file_field_widget_uri($field, $instance),
    '#upload_validators' => file_field_widget_upload_validators($field, $instance),
    '#value_callback' => 'mfw_field_widget_value',
    '#process' => array_merge($element_info['#process'], array('mfw_field_widget_process')),
    '#progress_indicator' => $instance['widget']['settings']['progress_indicator'],
    // Allows this field to return an array instead of a single value.
    '#extended' => TRUE,
  );

  if ($field['cardinality'] == 1) {
    // Set the default value.
    $element['#default_value'] = !empty($items) ? $items[0] : $defaults;
    // If there's only one field, return it as delta 0.
    if (empty($element['#default_value']['fid'])) {
      $element['#description'] = theme('file_upload_help', array('description' => $element['#description'], 'upload_validators' => $element['#upload_validators']));
    }
    $elements = array($element);
  }
  else {
    // If there are multiple values, add an element for each existing one.
    foreach ($items as $item) {
      $elements[$delta] = $element;
      $elements[$delta]['#default_value'] = $item;
      $elements[$delta]['#weight'] = $delta;
      $delta++;
    }
    // And then add one more empty row for new uploads except when this is a
    // programmed form as it is not necessary.
    if (($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED || $delta < $field['cardinality']) && empty($form_state['programmed'])) {
      $elements[$delta] = $element;
      $elements[$delta]['#default_value'] = $defaults;
      $elements[$delta]['#weight'] = $delta;
      $elements[$delta]['#required'] = ($element['#required'] && $delta == 0);
    }
    // The group of elements all-together need some extra functionality
    // after building up the full list (like draggable table rows).
    $elements['#file_upload_delta'] = $delta;
    $elements['#theme'] = 'file_widget_multiple';
    $elements['#theme_wrappers'] = array('fieldset');
    $elements['#process'] = array('mfw_field_widget_process_multiple');
    $elements['#title'] = $element['#title'];
    $elements['#description'] = $element['#description'];
    $elements['#field_name'] = $element['#field_name'];
    $elements['#language'] = $element['#language'];
    $elements['#display_field'] = $field['settings']['display_field'];

    // Add some properties that will eventually be added to the file upload
    // field. These are added here so that they may be referenced easily through
    // a hook_form_alter().
    $elements['#file_upload_title'] = t('Add a new file');
    $elements['#file_upload_description'] = theme('file_upload_help', array('description' => '', 'upload_validators' => $elements[0]['#upload_validators']));
  }

  return $elements;
}

/**
 * Implements hook_field_widget_settings_form().
 */
function multiupload_filefield_widget_field_widget_settings_form($field, $instance) {
  $form = file_field_widget_settings_form($field, $instance) ;
  $form['#attached']['js'] = array(drupal_get_path('module', 'multiupload_filefield_widget') . '/mfw.js');
  return $form;
}

/**
 * Get the upload validators for a file field.
 *
 * @param $field
 *   A field array.
 * @return
 *   An array suitable for passing to file_save_upload() or the file field
 *   element's '#upload_validators' property.
 */

function multiupload_filefield_widget_field_widget_upload_validators($field, $instance) {
  return file_field_widget_upload_validators($field, $instance);
}

/**
 * The #value_callback for the file_mfw field element.
 */
function mfw_field_widget_value($element, $input = FALSE, &$form_state) {
  if ($input) {
    // Checkboxes lose their value when empty.
    // If the display field is present make sure its unchecked value is saved.
    $field = field_widget_field($element, $form_state);
    if (empty($input['display'])) {
      $input['display'] = $field['settings']['display_field'] ? 0 : 1;
    }
  }

  // We depend on the mfw managed file element to handle uploads.
  $return = mfw_managed_file_value($element, $input, $form_state);

  // Ensure that all the required properties are returned even if empty.
  $return += array(
      'fid' => 0,
      'display' => 1,
      'description' => '',
  );

  $last_parent = $element['#parents'][count($element['#parents']) - 1];
  $form_state['values'][$element['#field_name']]['und'][$last_parent] = $return;

  return $return;
}

/**
 * An element #process callback for the mfw_file field type.
 *
 * Expands the mfw_file type to include the description and display fields.
 */
function mfw_field_widget_process($element, &$form_state, &$form) {
  return file_field_widget_process($element, $form_state, $form);
}

/**
 * An element #process callback for a group of mfw_file fields.
 *
 * Mostly copied from drupal core module /module/file/file.field.inc.
 *
 * Adds the weight field to each row so it can be ordered and adds a new AJAX
 * wrapper around the entire group so it can be replaced all at once.
 */
function mfw_field_widget_process_multiple($element, &$form_state, $form) {
  $upload_name = implode('_', $element['#parents']) . '_' . $element['#file_upload_delta'];
  if (isset($_FILES['files']['name']) && array_key_exists($upload_name, $_FILES['files']['name'])) {
    $count = count($_FILES['files']['name'][$upload_name]);
    // Supposing #file_upload_delta is always the last delta this will work
    for ($i = 1; $i < $count; $i++) {
      $element[] = $element[$element['#file_upload_delta']];
    }
  }
  $element_children = element_children($element);
  $count = count($element_children);

  foreach ($element_children as $delta => $key) {
    if ($key < $element['#file_upload_delta']) {
      $description = _file_field_get_description_from_element($element[$key]);
      $element[$key]['_weight'] = array(
        '#type' => 'weight',
        '#title' => $description ? t('Weight for @title', array('@title' => $description)) : t('Weight for new file'),
        '#title_display' => 'invisible',
        '#delta' => $count,
        '#default_value' => $delta,
      );
    }
    else {
      // The title needs to be assigned to the upload field so that validation
      // errors include the correct widget label.
      $element[$key]['#title'] = $element['#title'];
      $element[$key]['_weight'] = array(
        '#type' => 'hidden',
        '#default_value' => $delta,
      );
    }
  }

  // Add a new wrapper around all the elements for AJAX replacement.
  $element['#prefix'] = '<div id="' . $element['#id'] . '-ajax-wrapper">';
  $element['#suffix'] = '</div>';

  return $element;
}

/**
 * Submit handler for upload and remove buttons of file_mfw fields.
 *
 * This runs in addition to and after file_managed_file_submit().
 *
 * @see file_managed_file_submit()
 * @see file_field_widget_form()
 * @see file_field_widget_process()
 */
function multiupload_filefield_widget_field_widget_submit($form, &$form_state) {
  return file_field_widget_submit($form, $form_state);
}
