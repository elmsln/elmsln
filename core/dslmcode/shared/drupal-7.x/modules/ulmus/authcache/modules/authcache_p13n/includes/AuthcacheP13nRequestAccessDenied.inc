<?php
/**
 * @file
 * Defines a request exception for 403 errors
 */

/**
 * Defines a request exception for 403 errors
 */
class AuthcacheP13nRequestAccessDenied extends AuthcacheP13nRequestException {
  /**
   * Construct a new access denied exception.
   */
  public function __construct(Exception $previous = NULL) {
    parent::__construct('403 Forbidden', 403, $previous);
  }
}
