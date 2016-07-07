<?php

/**
 * hook_textformatter_field_list_info().
 *
 * Declare new field types/callbacks that are available as text formatter lists.
 */
function hook_textformatter_field_info() {
  $info = array();

  $info['example'] = array( // key array with module name.
    'fields' => array('example', 'example_other'), // This must be an array.
    // Callback to process $items from hook_field_formatter_view.
    'callback' => 'textformatter_example_field_create_list',
  );

  return $info;
}

/**
 * Sample callback implementation.
 * @see textformatter_default_field_create_list.
 */
function textformatter_example_field_create_list($entity_type, $entity, $field, $instance, $langcode, $items, $display) {
  $list_items = array();

  foreach ($items as $delta => $item) {
    $list_items[$delta] = check_plain($item['value']);
  }

  return $list_items;
}

/**
 * hook_textformatter_field_list_info_alter().
 *
 * @param $info
 *  An array of info as declared by hook_textformatter_field_list_info() to alter
 *  passed by reference.
 */
function hook_textformatter_field_info_alter(&$info) {
  // Change the callback used for fields from the text module.
  $info['text']['callback'] = 'textformatter_example_text_callback';
}

/**
 * hook_textformatter_field_formatter_settings_form_alter().
 */
function hook_textformatter_field_formatter_settings_form_alter(&$form, &$form_state, $context) {
  // Sample form element here.
}
