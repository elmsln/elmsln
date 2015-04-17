<?php
/**
 * @file
 * Defines the main function for the front controller.
 */

/**
 * Parse request parameters and restore original GET-parameters.
 *
 * @param array $get
 *   The GET-parameters operated on. Defaults to &$_GET
 *
 * @retrn array $req
 *   Parsed request parameters suitable for passing to
 *   authcache_p13n_frontcontroller_handle_request
 *
 * Note: This function must be called before drupal_bootstrap.
 *
 * @see authcache_p13n_frontcontroller_prepare_request()
 */
function authcache_p13n_frontcontroller_prepare_request(&$get = NULL) {
  if (!isset($get)) {
    $get = &$_GET;
  }

  // Copy $_GET into $req and remove original request GET-parameters.
  $req = $get;
  unset($req['o']);

  // Restore $_GET to original GET-parameters.
  $orig = isset($get['o']) ? $get['o'] : array();
  $get = $orig;

  return $req;
}

/**
 * Dispatch incomming requests to the appropriate request handler.
 *
 * @param array $req
 *   The request parameters as extracted by
 *   authcache_p13n_frontcontroller_prepare_request
 *
 * @see authcache_p13n_frontcontroller_prepare_request()
 */
function authcache_p13n_frontcontroller_handle_request($req) {
  // Front controller configuration.
  $check_header = variable_get('authcache_p13n_checkheader', TRUE);
  $routerclass = variable_get('authcache_p13n_router', 'AuthcacheP13nDefaultRequestRouter');

  ob_start();

  try {
    // This frontcontroller is only capable of responding to GET and HEAD
    // requests.
    if (!($_SERVER['REQUEST_METHOD'] === 'GET' || $_SERVER['REQUEST_METHOD'] === 'HEAD')) {
      drupal_add_http_header('Allow', 'GET, HEAD');
      throw new AuthcacheP13nRequestException('405 Method Not Allowed');
    }

    // Check whether the authcache HTTP header is present on the request.
    if ($check_header && empty($_SERVER['HTTP_X_AUTHCACHE'])) {
      watchdog('Authcache P13n Front Controller', 'X-Authcache header is missing on request', array(), WATCHDOG_ERROR);
      throw new AuthcacheP13nRequestInvalidInput();
    }

    // Check whether the client supplied a request-id.
    if (empty($req['r'])) {
      watchdog('Authcache P13n Front Controller', 'Missing r-parameter on request', array(), WATCHDOG_ERROR);
      throw new AuthcacheP13nRequestInvalidInput();
    }

    // Resolve and instantiate request handler.
    $router = new $routerclass();
    $handler = $router->getHandler($req['r']);
    unset($req['r']);
    if ($handler === FALSE) {
      throw new AuthcacheP13nRequestInvalidInput();
    }

    // Send response.
    $handler->handle($req);
    if ($_SERVER['REQUEST_METHOD'] === 'HEAD') {
      // Discard output if client does not care about it.
      ob_end_clean();
    }
    else {
      ob_end_flush();
    }
  }
  catch (Exception $e) {
    if (is_a($e, 'AuthcacheP13nRequestException')) {
      $status = $e->getMessage();
    }
    else {
      $status = '500 Internal Server Error';
      watchdog_exception('Authcache P13n Front Controller', $e);
    }
    drupal_add_http_header('Status', $status);

    // Discard output.
    ob_end_clean();
  }
}
