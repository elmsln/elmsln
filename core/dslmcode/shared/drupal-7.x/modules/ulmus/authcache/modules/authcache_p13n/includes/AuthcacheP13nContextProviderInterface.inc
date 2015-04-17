<?php

/**
 * @file
 * Defines context provider.
 */

/**
 * Interface for context providers.
 */
interface AuthcacheP13nContextProviderInterface {
  /**
   * Build and return context for the current request.
   *
   * @param array $input
   *   The GET parameters in key-value form
   *
   * @return any
   *   Context value
   */
  public function get($input);
}
