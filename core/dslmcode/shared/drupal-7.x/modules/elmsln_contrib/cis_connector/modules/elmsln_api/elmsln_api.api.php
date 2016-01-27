<?php
/**
 * @file
 * elmsln_api.api.php
 *
 * This file contains no working PHP code; it exists to provide documentation
 * for this module's API.
 */

/**
 * Register ELMSLN API callbacks. Read the documentation for a detailed explanation.
 *
 * @return array
 *   An associative array of callbacks where the key indicates name of the path
 *   callback that the info should be loaded. The value of each path callback
 *   is also an associative array containing the following possible keys:
 *   - callback function: (optional) The function to invoke for this callback.
 *     If omitted, the default function name is: MODULE_elmsln_api_callback_CALLBACK.
 *   - callback arguments: (optional) Select which arguments from the URL to
 *     pass to the callback. Starting with 0 with the v1/[module] stripped from
 *     the path. Please note that 0 will contain the used callback.
 *   - access callback: (optional) The function to invoke for determining
 *     access to the callback. If set, the minimum bootstrap level must be
 *     DRUPAL_BOOTSTRAP_SESSION to ensure proper access validation against the
 *     current user. WARNING: If not set, no access checks are performed at all.
 *     Defaults to "user_access" if the below option (access arguments) has
 *     a value.
 *   - access arguments: (optional) Arguments for the access callback.
 *   - delivery callback: (optional) The function to call to package the results
 *     of the callback function and send it to the browser. Defaults to
 *     elmsln_api_deliver_json(). Note that this function is called even if the
 *     access checks fail, so any custom delivery callback function should take
 *     that into account. See elmsln_api_deliver_json() for an example.
 *   - bootstrap: (optional) The bootstrap level Drupal should boot to,
 *     defaults to DRUPAL_BOOTSTRAP_DATABASE. If an access argument/callback or
 *     tokens are used, defaults to DRUPAL_BOOTSTRAP_SESSION.
 *   - includes: (optional) Load additional files from the /includes directory,
 *     without the extension.
 *   - dependencies: (optional) Load additional modules for this callback.
 *   - file: (optional) The file where the callback function is defined.
 *   - path: (optional) The path where the callback function is defined.
 *   - methods: (optional) The request methods allowed. This must be an array
 *     of string values. If the request does not match any of the allowed
 *     methods defined by the callback, it will be rejected.
 *   - process request: (optional) Process $_REQUEST data and provide them as
 *     matched arguments against the callback's parameter names (or as a single
 *     $data parameter). Defaults to TRUE. If unsure what this does, it's best
 *     to just leave this enabled. See elmsln_api_process_post_data() for more
 *     information.
 *   - skip init: (optional) Set to TRUE to skip the init hooks. Warning:
 *     This might cause unwanted behavior and should only be disabled with care.
 *   - xss: (optional) Filters data in drupal_deliver_json() before it's sent to
 *     browser. It is strongly recommended that this is not disabled, otherwise
 *     your site will be susceptible to XSS attacks and be considered
 *     "insecure".
 */
function hook_elmsln_api_info() {
  // Simple callback definition:
  $callbacks['simple'] = array();

  // Example of a more complex definition:
  $callbacks['complex'] = array(
    'access callback'  => 'my_module_custom_access_check',
    'access arguments' => array(1, 2),
    'bootstrap' => DRUPAL_BOOTSTRAP_SESSION,
    'callback function' => 'my_module_custom_callback_function',
    'callback arguments' => array(1, 2),
    'delivery callback' => 'my_module_custom_delivery_callback',
    'includes' => array('path', 'authorize', 'form'),
    'dependencies' => array('system', 'views'),
    'method' => array('PUT'),
    'skip init' => TRUE,
    'process request' => FALSE,
  );
  return $callbacks;
}

/**
 * Alter allowed tags used in XSS filtering. Uses filter_xss_admin() defaults.
 *
 * @see filter_xss_admin()
 */
function hook_elmsln_api_callback_filter_xss_alter(array &$allowed_tags = array()) {
  $allowed_tags[] = 'button';
}
