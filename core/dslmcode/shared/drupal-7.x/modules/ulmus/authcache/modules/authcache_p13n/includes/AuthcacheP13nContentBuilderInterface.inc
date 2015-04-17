<?php
/**
 * @file
 * Define content builder interface.
 */

/**
 * Interface for request response content builders.
 */
interface AuthcacheP13nContentBuilderInterface {
  /**
   * Build and return the content defined by the input parameters.
   *
   * When no appropriate content is present, implementations should throw an
   * AuthcacheP13nRequsetNotFound exception.
   *
   * @param array $input
   *   The GET parameters in key-value form
   *
   * @param array $context
   *   Additional run-time per-request context (key-value pairs).
   *
   * @return array|string
   *   The built content suitable for passing to the content encoder.
   *
   * @throws AuthcacheP13nRequestNotFound
   */
  public function build($input, $context);
}
