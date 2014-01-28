<?php
/**
 * @file
 * cis_account_required.features.inc
 */

/**
 * Implements hook_user_default_permissions_alter().
 */
function cis_account_required_user_default_permissions_alter(&$data) {
  if (isset($data['access content'])) {
    unset($data['access content']['roles']['anonymous user']);
  }
  if (isset($data['view regions_right_slideout region'])) {
    unset($data['view regions_right_slideout region']['roles']['anonymous user']);
  }
}
