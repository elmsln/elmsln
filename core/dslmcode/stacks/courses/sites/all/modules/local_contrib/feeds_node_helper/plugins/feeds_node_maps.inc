<?php

/**
 * @file
 * Allow for mapping values from an external roles system to drupal roles
 */
/**
 * feeds_tamper API definition for drupal role mapping
 */
$plugin = array(
  'form' => 'feeds_node_maps_form',
  'callback' => 'feeds_node_maps_callback',
  'name' => 'Current User ID',
  'multi' => 'single',
  'category' => 'Transform',
  'description' => 'Set the value to the currently logged in user',
);

/**
 * Form for building the user ID map, no options needed
 */
function feeds_node_maps_form($importer, $element_key, $settings) {
  $form = array();
  return $form;
}

/**
 * Helper function to process the value conversion
 */
function feeds_node_maps_callback($result, $item_key, $element_key, &$field, $settings) {
  // account for drush / command line interfaces
  if (!drupal_is_cli()) {
    global $user;
    $field = $user->uid;	
  }
  // CLI comes up as anonymous so ignore field tamper
}
