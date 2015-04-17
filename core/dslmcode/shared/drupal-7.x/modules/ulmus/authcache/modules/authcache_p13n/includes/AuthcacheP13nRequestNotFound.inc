<?php

/**
 * @file
 * Defines a request exception for 404 errors.
 */

/**
 * Defines a request exception for 404 errors.
 */
class AuthcacheP13nRequestNotFound extends AuthcacheP13nRequestException {
  /**
   * Construct new 404 not found exception.
   */
  public function __construct(Exception $previous = NULL) {
    parent::__construct('404 Not Found', 404, $previous);
  }
}
