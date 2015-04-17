<?php
/**
 * @file
 * Defines request handler interface.
 */

/**
 * Request handler interface.
 */
interface AuthcacheP13nRequestHandlerInterface {
  /**
   * Render and print the response according to the given parameters.
   */
  public function handle($params);
}
