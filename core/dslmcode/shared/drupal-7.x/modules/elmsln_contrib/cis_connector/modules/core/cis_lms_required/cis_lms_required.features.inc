<?php
/**
 * @file
 * cis_lms_required.features.inc
 */

/**
 * Implements hook_user_default_permissions_alter().
 */
function cis_lms_required_user_default_permissions_alter(&$data) {
  if (isset($data['access content'])) {
    $data['access content']['roles']['guest'] = 'guest'; /* WAS: '' */
    $data['access content']['roles']['instructor'] = 'instructor'; /* WAS: '' */
    $data['access content']['roles']['past student'] = 'past student'; /* WAS: '' */
    $data['access content']['roles']['staff'] = 'staff'; /* WAS: '' */
    $data['access content']['roles']['student'] = 'student'; /* WAS: '' */
    $data['access content']['roles']['teaching assistant'] = 'teaching assistant'; /* WAS: '' */
    unset($data['access content']['roles']['authenticated user']);
  }
  if (isset($data['view regions_right_slideout region'])) {
    $data['view regions_right_slideout region']['roles']['guest'] = 'guest'; /* WAS: '' */
    $data['view regions_right_slideout region']['roles']['instructor'] = 'instructor'; /* WAS: '' */
    $data['view regions_right_slideout region']['roles']['past student'] = 'past student'; /* WAS: '' */
    $data['view regions_right_slideout region']['roles']['staff'] = 'staff'; /* WAS: '' */
    $data['view regions_right_slideout region']['roles']['student'] = 'student'; /* WAS: '' */
    $data['view regions_right_slideout region']['roles']['teaching assistant'] = 'teaching assistant'; /* WAS: '' */
    unset($data['view regions_right_slideout region']['roles']['authenticated user']);
  }
}
