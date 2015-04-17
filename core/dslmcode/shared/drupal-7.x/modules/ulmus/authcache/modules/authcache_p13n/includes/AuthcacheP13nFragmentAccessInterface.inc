<?php
/**
 * @file
 * Defines authcache personalized fragment access checker.
 */

/**
 * Interface for personalization fragment access checkers.
 */
interface AuthcacheP13nFragmentAccessInterface {
  /**
   * Check whether the user has access to the given fragment.
   *
   * @param object $account
   *   The user account to check.
   *
   * @param string $key
   *   The key for the fragment to be checked.
   *
   * @param var $subject
   *   The result of the loader function for the given key. If no
   *   AuthcacheP13nFragmentLoader is associated with this fragment, subject is
   *   equal to key.
   *
   * @param array $context
   *   Additional run-time per-request context (key-value pairs).
   *
   * @return bool
   *   Return TRUE when the user has access, FALSE otherwise.
   */
  public function check($account, $key, $subject, $context);
}
