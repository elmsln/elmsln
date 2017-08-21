<?php
/**
 * @file
 * cle_textbook.features.inc
 */

/**
 * Implements hook_filter_default_formats_alter().
 */
function cle_textbook_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['filters']['cis_filter'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -50,
    ); /* WAS: '' */
  }
}
