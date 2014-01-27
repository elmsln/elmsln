<?php

/**
 * @file
 * Hooks provided by the LTI Tool Provider module.
 */

/**
 * Implements hook_lti_tool_provider_launch_alter().
 */
function hook_lti_tool_provider_launch_alter(&$launch_info, $account) {
  /*
   * Do stuff at the time of an LTI launch including
   *   modifying context variables.
   * Invoked after user provisioned, authenticated and authorized,
   *   but before redirect to landing page.
   * LTI context variables are available in $launch_info, and
   * user account is $account.
   */
}

/**
 * Implements hook_lti_tool_provider_return().
 */
function hook_lti_tool_provider_return() {
  /*
   * Do stuff at the time of an LTI return.
   * Invoked before user logged out and session is destroyed.
   * LTI context variables are available in
   * $_SESSION['lti_tool_provider_context_info'].
   */
}

/**
 * Implements hook_lti_tool_provider_create_account_alter().
 */
function lti_tool_provider_create_account_alter(&$account, &$lti_info) {
  /*
   * Do stuff at the time of an LTI user being created.
   * Invoked after user $account provisioned.
   * $lti_info contains the array of info passed to the create account function.
   */
}
