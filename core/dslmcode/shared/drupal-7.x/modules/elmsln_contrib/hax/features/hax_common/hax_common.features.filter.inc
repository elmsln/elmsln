<?php
/**
 * @file
 * hax_common.features.filter.inc
 */

/**
 * Implements hook_filter_default_formats().
 */
function hax_common_filter_default_formats() {
  $formats = array();

  // Exported format: hax.
  $formats['hax'] = array(
    'format' => 'hax',
    'name' => 'hax',
    'cache' => 0,
    'status' => 1,
    'weight' => 0,
    'filters' => array(
      'filter_htmlcorrector' => array(
        'weight' => -50,
        'status' => 1,
        'settings' => array(),
      ),
      'webcomponents_cmstags' => array(
        'weight' => -49,
        'status' => 1,
        'settings' => array(),
      ),
      'filter_tokens' => array(
        'weight' => -39,
        'status' => 1,
        'settings' => array(),
      ),
      'webcomponents_cmstags_jsonfix' => array(
        'weight' => -37,
        'status' => 1,
        'settings' => array(),
      ),
    ),
  );

  return $formats;
}
