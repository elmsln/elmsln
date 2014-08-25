<?php
/**
 * @file
 * mooc_textbook_nrhi.features.inc
 */

/**
 * Implements hook_filter_default_formats_alter().
 */
function mooc_textbook_nrhi_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['filters']['nrhi'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -42,
    ); /* WAS: '' */
  }
}
