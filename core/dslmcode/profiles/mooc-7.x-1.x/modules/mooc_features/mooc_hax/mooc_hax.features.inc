<?php
/**
 * @file
 * mooc_hax.features.inc
 */

/**
 * Implements hook_filter_default_formats_alter().
 */
function mooc_hax_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['filters']['webcomponents_cmstags'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -50,
    ); /* WAS: '' */
  }
}
