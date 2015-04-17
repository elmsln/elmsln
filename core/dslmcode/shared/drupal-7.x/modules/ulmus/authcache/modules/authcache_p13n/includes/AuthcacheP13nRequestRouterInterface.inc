<?php
/**
 * @file
 * Defines the interface for mapping routes to requests and vice versa.
 */

/**
 * Interface for routes to requests and vice versa.
 */
interface AuthcacheP13nRequestRouterInterface {
  /**
   * Return a list of existing route ids.
   *
   * @return array
   *   List of existing route ids.
   */
  public function getRoutes();

  /**
   * Return an instance of AuthcacheP13nRequestHandlerInterface.
   *
   * @param String $route_id
   *   The identifier of a request (e.g., frag/form-token).
   *
   * @return AuthcacheP13nRequestHandlerInterface|FALSE
   *   An appropriate request handler.
   */
  public function getHandler($route_id);

  /**
   * Given a request id and an optional argument, return the appropriate URL.
   *
   * @param String $route_id
   *   The identifier of a request (e.g., frag/form-token).
   *
   * @return String|FALSE
   *   An URL which can be used to call back to the request with the given
   *   argument.
   */
  public function generateURL($route_id, $arg = NULL);

  /**
   * Rebuild the routing information after configuration changes.
   */
  public function rebuild();
}
