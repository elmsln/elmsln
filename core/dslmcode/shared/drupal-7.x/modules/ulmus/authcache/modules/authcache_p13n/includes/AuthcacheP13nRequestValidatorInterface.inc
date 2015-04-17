<?php
/**
 * @file
 * Defines interface for request validators.
 */

/**
 * Interface for request validators.
 */
interface AuthcacheP13nRequestValidatorInterface {
  /**
   * Validate and sanitize a request.
   *
   * Implementations must throw an AuthcacheP13nRequestInvalidInput exception
   * when params contain invalid or unexpected values.
   *
   * @throws AuthcacheP13nRequestInvalidInput
   *
   * @param array $params
   *   The GET parameters in key-value form
   *
   * @return array
   *   Sanitized GET parameters used in subsequent processing
   */
  public function validate($params);
}
