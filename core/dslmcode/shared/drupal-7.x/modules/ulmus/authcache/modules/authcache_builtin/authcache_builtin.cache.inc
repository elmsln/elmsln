<?php

/**
 * @file
 * Attempt to deliver a cached version of a page depending on the users role.
 *
 * This file gets included by _drupal_bootstrap_page_cache in bootstrap.inc
 * during the drupal bootstrap stage DRUPAL_BOOTSTRAP_PAGE_CACHE. This script
 * delegates the request to the underlying cache handler and attempts to deliver
 * a cached version of a page for this request.
 *
 * In the event of a cache-miss or if a page is not cachable, execution is
 * passed back to _drupal_bootstrap_page_cache and the page will be served
 * using a full bootstrap.
 *
 * @see _drupal_bootstrap_page_cache()
 */

$delivered = authcache_builtin_cacheinc_retrieve_cache_page();
if ($delivered) {
  exit;
}

/**
 * Check whether client is allowed to skip the cache for this request.
 *
 * The default implementation allows cache bypass for all clients having a
 * session cookie.
 *
 * @see _authcache_default_nocache_set()
 */
function _authcache_builtin_cacheinc_default_nocache_get() {
  if (isset($_COOKIE['nocache']) && isset($_COOKIE[session_name()])) {
    return TRUE;
  }
}

/**
 * Retrieve the authcache key for a session from the key-cache.
 */
function _authcache_builtin_cacheinc_cache_key_get($session_id) {
  global $base_root;

  $cache = cache_get($base_root . ':' . $session_id, 'cache_authcache_key');

  if ($cache === FALSE || $cache->expire > 0 && $cache->expire < REQUEST_TIME) {
    // Need a full bootstrap when key was not found or entry expired.
    return FALSE;
  }
  else {
    return $cache->data;
  }
}

/**
 * Add headers required to make stupid browsers behave.
 *
 * When modifying this function, do not forget to adapt the respective VCL
 * snipped shipping with the Authcache Varnish Backend.
 */
function _authcache_builtin_cacheinc_fix_browsers() {
  // Disable browser caching in Safari
  //
  // @see:
  // - https://bugs.webkit.org/show_bug.cgi?id=71509
  // - https://groups.drupal.org/node/191453
  // - https://drupal.org/node/1910178
  if (!empty($_SERVER['HTTP_USER_AGENT']) && strpos($_SERVER['HTTP_USER_AGENT'], 'Safari') !== FALSE && strpos($_SERVER['HTTP_USER_AGENT'], 'Chrome') === FALSE) {
    drupal_add_http_header('Cache-Control', 'no-cache, must-revalidate, post-check=0, pre-check=0');
  }
}

/**
 * Send cached page to browser, if found.
 *
 * @return bool
 *   TRUE if page was delivered, FALSE otherwise
 */
function authcache_builtin_cacheinc_retrieve_cache_page() {
  global $base_root;

  // Connect to database and initialize configuration if not disabled from
  // within settings.php
  if (!variable_get('authcache_builtin_cache_without_database')) {
    drupal_bootstrap(DRUPAL_BOOTSTRAP_VARIABLES, FALSE);
  }

  // The following three basic exclusion rules are mirrored in
  // authcache_authcache_request_exclude() in authcache.module
  // BEGIN: basic exclusion rules.
  if (!function_exists('authcache_backend_init')) {
    return FALSE;
  }

  // Only GET and HEAD requests allowed.
  if (!($_SERVER['REQUEST_METHOD'] === 'GET' || $_SERVER['REQUEST_METHOD'] === 'HEAD')) {
    return FALSE;
  }

  // Drupal core page caching for anonymous users active.
  if (variable_get('cache') || variable_get('page_cache_without_database')) {
    return FALSE;
  }

  // Not invoked using an allowed front controller.
  $frontscripts = variable_get('authcache_frontcontroller_whitelist',
    array(DRUPAL_ROOT . '/index.php'));
  $frontscripts = array_map('realpath', $frontscripts);
  if (!in_array(realpath($_SERVER['SCRIPT_FILENAME']), $frontscripts)) {
    return FALSE;
  }
  // END: basic exclusion rules.
  //
  // Determine whether caching is disabled for this request.
  $nocache_get = variable_get('authcache_builtin_nocache_get', '_authcache_builtin_cacheinc_default_nocache_get');
  if (is_callable($nocache_get) && call_user_func($nocache_get)) {
    return FALSE;
  }

  // Try to retrieve a key when the session cookie is present on the request.
  if (isset($_COOKIE[session_name()])) {
    $key = _authcache_builtin_cacheinc_cache_key_get($_COOKIE[session_name()]);
  }
  else {
    $key = authcache_backend_anonymous_key();
  }

  // Initialize the backend.
  $vary_header = variable_get('authcache_builtin_vary', 'Cookie');
  if (!authcache_backend_init('authcache_builtin', $vary_header, $key)) {
    return FALSE;
  }

  // When key needs to be regenerated, return and trigger a full bootstrap.
  if ($key === FALSE) {
    return FALSE;
  }

  // Attempt to retrieve page from cache.
  $cid = $key . request_uri();
  $cache = cache_get($cid, 'cache_page');

  if (empty($cache)) {
    header('X-Drupal-Cache: MISS');
    return FALSE;
  }
  else {
    // Render cache benchmark.
    if (isset($_COOKIE['cache_render'])) {
      setcookie('cache_render', timer_read('page'), 0, ini_get('session.cookie_path'), ini_get('session.cookie_domain'), ini_get('session.cookie_secure') == '1');
    }

    header('X-Drupal-Cache: HIT');
    _authcache_builtin_cacheinc_fix_browsers();
    authcache_serve_page_from_cache($cache, $key);
    return TRUE;
  }
}
