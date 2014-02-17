<?php
/**
 * @file
 * cle_private_files.features.inc
 */

/**
 * Implements hook_field_default_fields_alter().
 */
function cle_private_files_field_default_fields_alter(&$data) {
  if (isset($data['node-cle_submission-field_images'])) {
    $data['node-cle_submission-field_images']['field_config']['settings']['uri_scheme'] = 'private'; /* WAS: 'public' */
  }
}
