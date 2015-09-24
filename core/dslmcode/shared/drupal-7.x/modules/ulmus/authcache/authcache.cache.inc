<?php
/**
 * @file
 * Defines authcache aware copy of drupal_serve_page_from_cache().
 */

/**
 * @defgroup authcache_backend Cache backend
 * @{
 */

/**
 * Sets HTTP headers in preparation for a cached page response.
 *
 * @see drupal_serve_page_from_cache()
 */
function authcache_serve_page_from_cache(stdClass $cache, $authcache_key) {
  // Negotiate whether to use compression.
  $page_compression = !empty($cache->data['page_compressed']);
  $return_compressed = $page_compression && isset($_SERVER['HTTP_ACCEPT_ENCODING']) && strpos($_SERVER['HTTP_ACCEPT_ENCODING'], 'gzip') !== FALSE;

  // Get headers set in hook_boot(). Keys are lower-case.
  $hook_boot_headers = drupal_get_http_header();

  // Headers generated in this function, that may be replaced or unset using
  // drupal_add_http_headers(). Keys are mixed-case.
  $default_headers = array();

  foreach ($cache->data['headers'] as $name => $value) {
    // In the case of a 304 response, certain headers must be sent, and the
    // remaining may not (see RFC 2616, section 10.3.5). Do not override
    // headers set in hook_boot().
    $name_lower = strtolower($name);
    if (in_array($name_lower, array('content-location', 'expires', 'cache-control', 'vary')) && !isset($hook_boot_headers[$name_lower])) {
      drupal_add_http_header($name, $value);
      unset($cache->data['headers'][$name]);
    }
  }

  // Authcache modification: Unconditionally add Cache-Control: public.
  $default_headers['Cache-Control'] = 'public, max-age=' . variable_get('page_cache_maximum_age', 0);

  // Entity tag should change if the output changes.
  // Authcache modification: Add authcache key to entity tag.
  $key_tag = !authcache_is_default_key($authcache_key) ? '-' . $authcache_key : '';
  $etag = '"' . $cache->created . '-' . intval($return_compressed) .  $key_tag . '"';
  header('Etag: ' . $etag);

  // See if the client has provided the required HTTP headers.
  $if_modified_since = isset($_SERVER['HTTP_IF_MODIFIED_SINCE']) ? strtotime($_SERVER['HTTP_IF_MODIFIED_SINCE']) : FALSE;
  $if_none_match = isset($_SERVER['HTTP_IF_NONE_MATCH']) ? stripslashes($_SERVER['HTTP_IF_NONE_MATCH']) : FALSE;

  if ($if_modified_since && $if_none_match
      && $if_none_match == $etag // etag must match
      && $if_modified_since == $cache->created) {  // if-modified-since must match
    header($_SERVER['SERVER_PROTOCOL'] . ' 304 Not Modified');
    drupal_send_headers($default_headers);
    return;
  }

  // Send the remaining headers.
  foreach ($cache->data['headers'] as $name => $value) {
    drupal_add_http_header($name, $value);
  }

  $default_headers['Last-Modified'] = gmdate(DATE_RFC7231, $cache->created);

  // HTTP/1.0 proxies does not support the Vary header, so prevent any caching
  // by sending an Expires date in the past. HTTP/1.1 clients ignores the
  // Expires header if a Cache-Control: max-age= directive is specified (see RFC
  // 2616, section 14.9.3).
  $default_headers['Expires'] = 'Sun, 19 Nov 1978 05:00:00 GMT';

  drupal_send_headers($default_headers);

  // Allow HTTP proxies to cache pages for anonymous users without a session
  // cookie. The Vary header is used to indicates the set of request-header
  // fields that fully determines whether a cache is permitted to use the
  // response to reply to a subsequent request for a given URL without
  // revalidation. If a Vary header has been set in hook_boot(), it is assumed
  // that the module knows how to cache the page.
  if (!isset($hook_boot_headers['vary']) && !variable_get('omit_vary_cookie')) {
    header('Vary: Cookie');
  }

  if ($page_compression) {
    header('Vary: Accept-Encoding', FALSE);
    // If page_compression is enabled, the cache contains gzipped data.
    if ($return_compressed) {
      // $cache->data['body'] is already gzip'ed, so make sure
      // zlib.output_compression does not compress it once more.
      ini_set('zlib.output_compression', '0');
      header('Content-Encoding: gzip');
    }
    else {
      // The client does not support compression, so unzip the data in the
      // cache. Strip the gzip header and run uncompress.
      $cache->data['body'] = gzinflate(substr(substr($cache->data['body'], 10), 0, -8));
    }
  }

  // Print the page.
  print $cache->data['body'];
}

/**
 * Collect document and headers and pass them to cache backends.
 *
 * @return object
 *   A fake-cache object suitable for passing to drupal_serve_page_from_cache.
 *
 * @see drupal_page_set_cache()
 */
function authcache_backend_cache_save() {
  // Restore preferred header names based on the lower-case names returned
  // by drupal_get_http_header().
  $headers = array();
  $header_names = _drupal_set_preferred_header_name();
  foreach (drupal_get_http_header() as $name_lower => $value) {
    $headers[$header_names[$name_lower]] = $value;
  }

  // Retrieve the document body. Note that we do not call ob_get_clean() here in
  // order to allow cache-backends to access the buffer directly if necessary.
  // Only after the backend was invoked, ob_clean() is called.
  $body = ob_get_contents();

  // Check whether the current page might be compressed.
  $page_compressed = variable_get('page_compression', TRUE) && extension_loaded('zlib');
  if ($page_compressed) {
    $body = gzencode($body, 9, FORCE_GZIP);
  }

  // Invoke cache backend.
  module_invoke(authcache_backend(), 'authcache_backend_cache_save', $body, $headers, $page_compressed);

  // Remove buffer content.
  ob_clean();

  // Construct dummy cache object which is later served using
  // drupal_serve_page_from_cache.
  $cache = (object) array(
    'data' => array(
      'body' => $body,
      'headers' => $headers,
      'page_compressed' => $page_compressed,
    ),
    'created' => REQUEST_TIME,
  );

  return $cache;
}

/**
 * Initialize the cache backend module.
 */
function authcache_backend_init($module, $vary_header, $initial_key) {
  if (drupal_is_cli()) {
    return FALSE;
  }

  // Determine whether a cache backend already has been chosen.
  if (authcache_backend()) {
    return FALSE;
  }

  // Determine whether we can savely set the given vary header.
  if (!authcache_backend_check_vary($vary_header)) {
    return FALSE;
  }

  // Finally set vary header and cache backend.
  drupal_add_http_header('Vary', $vary_header);
  authcache_backend($module);
  authcache_backend_initial_key($initial_key);
  $initial_session_id = isset($_COOKIE[session_name()]) ? $_COOKIE[session_name()] : FALSE;
  authcache_backend_initial_session_id($initial_session_id);

  return TRUE;
}

/**
 * Return the active cache backend module.
 */
function authcache_backend($set_cache_backend = NULL) {
  $cache_backend = &drupal_static(__FUNCTION__);

  if (isset($set_cache_backend)) {
    $cache_backend = $set_cache_backend;
  }

  return $cache_backend;
}

/**
 * Return the key suitable for this request if no session is open.
 */
function authcache_backend_anonymous_key() {
  global $base_root;

  $generator = variable_get('authcache_key_generator');
  if (is_callable($generator)) {
    $key = call_user_func($generator);
  }
  else {
    $key = $base_root;
  }

  return $key;
}

/**
 * Return the authcache key and session captured during backend initialization.
 */
function authcache_backend_initial_key($set_key = NULL) {
  $initial_key = &drupal_static(__FUNCTION__);

  if (isset($set_key)) {
    $initial_key = $set_key;
  }

  return $initial_key;
}

/**
 * Return the session id captured during backend initialization.
 */
function authcache_backend_initial_session_id($set_session_id = NULL) {
  $initial_session_id = &drupal_static(__FUNCTION__);

  if (isset($set_session_id)) {
    $initial_session_id = $set_session_id;
  }

  return $initial_session_id;
}

/**
 * Return true if the vary header is suitable for the active cache backend.
 */
function authcache_backend_check_vary($set_vary_header = NULL) {
  $vary_header = &drupal_static(__FUNCTION__);

  if (isset($set_vary_header)) {
    $vary_header = $set_vary_header;
  }

  $hook_boot_headers = drupal_get_http_header();
  if (isset($hook_boot_headers['vary']) && $hook_boot_headers['vary'] !== $vary_header) {
    return FALSE;
  }
  else {
    return TRUE;
  }
}

/**
 * @} End of "defgroup authcache_backend"
 */

/**
 * @defgroup authcache_key Key computation and management
 * @{
 */

/**
 * Returns true if this request is using the default cache-key.
 */
function authcache_is_default_key($key) {
  global $base_root;

  // Check whether a key-generator for anonymous users is in place.
  $generator = variable_get('authcache_key_generator');
  if (is_callable($generator)) {
    return FALSE;
  }

  return $key === $base_root;
}

/**
 * @} End of "defgroup authcache_key"
 */
