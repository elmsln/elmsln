<?php

/**
 * @file
 * Allow for mapping values from an external roles system to drupal roles
 */
/**
 * feeds_tamper API definition for drupal role mapping
 */
$plugin = array(
  'form' => 'feeds_node_get_form',
  'callback' => 'feeds_node_get_callback',
  'name' => 'Convert to GET value',
  'multi' => 'single',
  'category' => 'Transform',
  'description' => 'Set the value to a variable in the address',
);

/**
 * Form for building the user ID map, no options needed
 */
function feeds_node_get_form($importer, $element_key, $settings) {
  $form = array();
  $form['get_arg'] = array(
    '#type' => 'textfield',
    '#title' => t('GET argument to use'),
    '#default_value' => isset($settings['get_arg']) ? $settings['get_arg'] : ''
  );
  return $form;
}

/**
 * Helper function to process the value conversion
 */
function feeds_node_get_callback($result, $item_key, $element_key, &$field, $settings) {
  // build the list of arguments that existed at form time
  $args = unserialize($result->config['FeedsHTTPFetcher']['feeds_node_helper_args']);
  // only set a value if the key exists
  // scrub the get_argument as well since it's a text input
  $get_arg = filter_xss(check_plain($settings['get_arg']));
  if (isset($args[$get_arg])) {
    // even though we filtered already, do it again
    $field = filter_xss(check_plain($args[$get_arg]));
  }
}
