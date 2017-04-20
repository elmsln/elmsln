<?php

/**
 * @file
 * Hooks defined by the Field collection fieldset module.
 */

/**
 * Define callbacks used for field collection labels.
 *
 * @param array $field
 *   The field collection for which field label options should be returned.
 *
 * @return array
 *   callback functions.
 */
function hook_field_collection_fieldset_field_as_label_info(array $field) {
  return array(
    'text' => array(
      'label' => 'Field collection: text field',
      'callback' => 'field_collection_fieldset_field_as_label_callback',
    ),
  );
}

/**
 * Callback to return a field collection label.
 *
 * @param array $context
 *   An array with contextual information used to build the title:
 *     - field_as_label the name of the field used as label.
 *     - field_collection_item_wrapper the field collection for which
 *     a label is created.
 *
 * @return string
 *   Title for the field collection.
 */
function field_collection_fieldset_field_as_label_callback(array $context) {
  $title = '';
  if ($field_value = $context['field_collection_item_wrapper']->{$context['field_as_label']}->value()) {
    $info = field_info_field($context['field_as_label']);
    switch ($info['field_type']) {
      case 'text':
        $title = is_array($field_value) ? strip_tags($field_value['value']) : strip_tags($field_value);
        break;
    }
  }
  return $title;
}

/**
 * Allows modules to alter the field collection label.
 *
 * @param string $title
 *   Title to alter.
 * @param array $context
 *   An array with contextual information used to build the title:
 *     - field_as_label the name of the field used as label.
 *     - field_collection_item_wrapper the field collection for which
 *     a label is created.
 */
function hook_field_collection_fieldset_field_as_label_alter(&$title, array $context) {
  $title = '[' . $title . ']';
}
