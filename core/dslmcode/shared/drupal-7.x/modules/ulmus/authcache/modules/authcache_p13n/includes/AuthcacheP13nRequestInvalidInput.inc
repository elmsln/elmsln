<?php
/**
 * @file
 * Defines a request exception for 400 errors.
 */

/**
 * Defines a request exception for 400 errors.
 *
 * @ignore sniffer_files_linelength_toolong
 * @see http://stackoverflow.com/questions/1959947/whats-an-appropriate-http-status-code-to-return-by-a-rest-api-service-for-a-val
 */
class AuthcacheP13nRequestInvalidInput extends AuthcacheP13nRequestException {
  /**
   * Construct a 400 request exception.
   */
  public function __construct(Exception $previous = NULL) {
    parent::__construct('400 Bad Request', 400, $previous);
  }
}
