<?php

/**
 * @file
 * Defines base class for request exceptions.
 */

/**
 * Defines base class for request exceptions.
 */
class AuthcacheP13nRequestException extends Exception {
  /**
   * Construct a new request exception.
   *
   * @param string $message
   *   The error message (e.g., Not Found).
   * @param int $code
   *   A HTTP status code (e.g., 404).
   * @param Exception $previous
   *   The original exception which caused this failure.
   */
  public function __construct($message = NULL, $code = NULL, Exception $previous = NULL) {
    if ($message === NULL) {
      $message = '500 Internal Server Error';
    }
    if ($code === NULL) {
      $code = intval($message);
    }
    parent::__construct($message, $code, $previous);
  }
}
