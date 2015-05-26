<?php
/**
 * @file
 * cis_service_icor.features.inc
 */

/**
 * Implements hook_views_api().
 */
function cis_service_icor_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_wysiwyg_default_profiles_alter().
 */
function cis_service_icor_wysiwyg_default_profiles_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['settings']['buttons']['icor'] = array(
      'icor' => 1,
    ); /* WAS: '' */
  }
}
