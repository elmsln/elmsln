<?php

/**
 * @file
 * Hooks provided by the LTI Tool Provider Memberships module.
 */

/**
 * Implements hook_lti_tool_provider_memberships_get_alter().
 */
function hook_lti_tool_provider_memberships_get_alter(&$member, &$member_data) {
  /*
   * Do stuff at the time of an LTI memberships get data
   *   $member is the array being created to represent the new member.
   *   $member_data is the object containing the data decoded from xml.
   */
}