<?php

/**
 * @file
 * Shortcode API documentation.
 */

/**
 * hook_shortcode_info()
 * Declare shortcodes
 *
 * @return
 *     An associative array of shortcodes, whose keys are internal shortcode names,
 *     which should be unique..
 *     Each value is an associative array describing the shortcode, with the
 *     following elements (all are optional except as noted):
 *   - title: (required) An administrative summary of what the shortcode does.
 *   - description: Additional administrative information about the shortcode's
 *     behavior, if needed for clarification.
 *   - settings callback: The name of a function that returns configuration form
 *     elements for the shortcode. TODO
 *   - default settings: An associative array containing default settings for
 *     the shortcode, to be applied when the shortcode has not been configured yet.
 *   - process callback: (required) The name the function that performs the
 *     actual shortcodeing.
 *   - tips callback: The name of a function that returns end-user-facing shortcode
 *     usage guidelines for the shortcode.
 *
 *   - TODO: wysiwyg or attributes? WYSIWYG callback: The name of a function that returns a FAPI array with
 *     configuration input for the shortcode
 *
 */
function hook_shortcode_info() {
  // Quote shortcode example
  $shortcodes['quote'] = array(
    'title' => t('Quote'),
    'description' => t('Replace a given text formatted like a quote.'),
    'process callback' => 'shortcode_basic_tags_shortcode_quote',
    //'settings callback' => '_shortcode_settings_form', TODO
    'tips callback' => 'shortcode_basic_tags_shortcode_quote_tip',
    'attributes callback' => '_shortcode_settings_form',
    'default settings' => array(),
  );

  return $shortcodes;
}

/**
 * hook_shortcode_info_alter()
 * Alter existing shortcodes
 *
 * @param $shortcodes
 *    An associative array of shortcodes
 *
 * @return
 *     An associative array of shortcodes, whose keys are internal shortcode names,
 *     which should be unique..
 *     Each value is an associative array describing the shortcode, with the
 *     following elements (all are optional except as noted):
 *   - title: (required) An administrative summary of what the shortcode does.
 *   - description: Additional administrative information about the shortcode's
 *     behavior, if needed for clarification.
 *   - settings callback: The name of a function that returns configuration form
 *     elements for the shortcode.
 *   - default settings: An associative array containing default settings for
 *     the shortcode, to be applied when the shortcode has not been configured yet.
 *   - process callback: (required) The name the function that performs the
 *     actual shortcodeing.
 *   - tips callback: The name of a function that returns end-user-facing shortcode
 *     usage guidelines for the shortcode.
 */
/**
 * @param $shortcodes
 */
function hook_shortcode_info_alter(&$shortcodes) {
  // Example to change the process callback for quotes.
  $shortcodes['quote']['process callback'] = 'MYMODULE_shortcode_quote';
}
