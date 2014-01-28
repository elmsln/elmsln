<?php
/**
 * @file
 * cis_service_restws.features.inc
 */

/**
 * Implements hook_user_default_permissions_alter().
 */
function cis_service_restws_user_default_permissions_alter(&$data) {
  if (isset($data['access content'])) {
    $data['access content']['roles']['SERVICE ACCOUNT'] = 'SERVICE ACCOUNT'; /* WAS: '' */
  }
  if (isset($data['bypass node access'])) {
    $data['bypass node access']['roles']['SERVICE ACCOUNT'] = 'SERVICE ACCOUNT'; /* WAS: '' */
  }
}
