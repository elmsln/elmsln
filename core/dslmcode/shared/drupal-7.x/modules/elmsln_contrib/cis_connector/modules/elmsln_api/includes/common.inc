<?php
/**
 * @file
 * common.inc
 * Common functions used in any ELMSLN API request.
 */

/**
 * Determines the delivery callback to use for final output.
 *
 * @param string $function
 *   (Optional) The function name to set for of the callback.
 *
 * @return string
 *   The function name of the callback to invoke.
 */
function elmsln_api_delivery_callback($function = NULL) {
  $callback = &drupal_static(__FUNCTION__);
  if (!isset($callback)) {
    $callback = 'elmsln_api_deliver_json';
  }
  if (isset($function)) {
    $callback = $function;
  }
  return $callback;
}

/**
 * Sets the HTTP response code for ELMSLN API requests.
 *
 * @param int $code
 *   (optional) The HTTP response code to use. Defaults to: 200 OK.
 *
 * @return array
 *   An associative array with the key "response"; containing:
 *   - code: The response code set.
 *   - message: The corresponding response code message.
 */
function elmsln_api_http_response($code = 200) {
  static $codes = array(
    100 => 'Continue',
    101 => 'Switching Protocols',
    200 => 'OK',
    201 => 'Created',
    202 => 'Accepted',
    203 => 'Non-Authoritative Information',
    204 => 'No Content',
    205 => 'Reset Content',
    206 => 'Partial Content',
    300 => 'Multiple Choices',
    301 => 'Moved Permanently',
    302 => 'Found',
    303 => 'See Other',
    304 => 'Not Modified',
    305 => 'Use Proxy',
    307 => 'Temporary Redirect',
    400 => 'Bad Request',
    401 => 'Unauthorized',
    402 => 'Payment Required',
    403 => 'Forbidden',
    404 => 'Not Found',
    405 => 'Method Not Allowed',
    406 => 'Not Acceptable',
    407 => 'Proxy Authentication Required',
    408 => 'Request Time-out',
    409 => 'Conflict',
    410 => 'Gone',
    411 => 'Length Required',
    412 => 'Precondition Failed',
    413 => 'Request Entity Too Large',
    414 => 'Request-URI Too Large',
    415 => 'Unsupported Media Type',
    416 => 'Requested Range Not Satisfiable',
    417 => 'Expectation Failed',
    500 => 'Internal Server Error',
    501 => 'Not Implemented',
    502 => 'Bad Gateway',
    503 => 'Service Unavailable',
    504 => 'Gateway Time-out',
    505 => 'HTTP Version Not Supported',
  );
  if (!array_key_exists($code, $codes)) {
    // If this occurs, it's a programming error. Immediately throw a fatal error
    // so it can be quickly identified and fixed.
    throw new Exception(t('Invalid HTTP response code: @code', array(
      '@code' => $code,
    )));
  }
  drupal_add_http_header('Status', $code . ' ' . $codes[$code]);

  // Return the status code and message as an associative array.
  return array(
    'response' => array(
      'code' => $code,
      'message' => $codes[$code],
    ),
  );
}

/**
 * Helper function to determine if an array is renderable.
 *
 * @param array $array
 *   The array to check.
 * @param bool $recursive
 *   If TRUE, the entire array (children) is searched, otherwise only the first
 *   level is checked.
 *
 * @return bool
 *   TRUE if renderable, FALSE if not.
 */
function elmsln_api_is_renderable(array $array = array(), $recursive = TRUE) {
  static $keys = array(
    '#type', '#theme', '#theme_wrappers', '#children',
    '#markup', '#pre_render', '#post_render',
  );
  if (array_intersect($keys, element_properties($array))) {
    return TRUE;
  }
  if ($recursive) {
    foreach (element_children($array) as $child) {
      if (is_array($array[$child]) && elmsln_api_is_renderable($array[$child])) {
        return TRUE;
      }
    }
  }
  return FALSE;
}

/**
 * Helper function that re-initializes theme.
 */
function elmsln_api_reinitialize_theme() {
  global $_elmsln;
  if (!empty($_elmsln['theme'])) {
    $custom_theme = &drupal_static('menu_get_custom_theme');
    $custom_theme = $_elmsln['theme'];
    unset($GLOBALS['theme']);
    drupal_static_reset();
    drupal_theme_initialize();
  }
}
