<?php
/**
 * @file
 * Defines authcache personalized setting getter.
 */

/**
 * Interface for personalization setting getters.
 */
interface AuthcacheP13nSettingInterface {
  /**
   * Return a setting.
   *
   * @param any $params
   *   Params set by the client.
   *
   * @param array $context
   *   Additional run-time per-request context (key-value pairs).
   *
   * @return string
   *   Return an associative array.
   */
  public function get($params, $context);
}
