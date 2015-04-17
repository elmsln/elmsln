<?php
/**
 * @file
 * Defines authcache personalized setting access checker.
 */

/**
 * Interface for personalization setting access checkers.
 */
interface AuthcacheP13nSettingAccessInterface {
  /**
   * Check whether the user has access to the given setting.
   *
   * @param object $account
   *   The user account to check.
   *
   * @param any $params
   *   Params set by the client.
   *
   * @param array $context
   *   Additional run-time per-request context (key-value pairs).
   *
   * @return bool
   *   Return TRUE when the user has access, FALSE otherwise.
   */
  public function check($account, $params, $context);
}
