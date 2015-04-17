<?php
/**
 * @file
 * Authcache API documentation.
 */

/**
 * Exclude a page from being cached based on the request.
 *
 * @return string
 *   A transalted string specifying the reason of exclusion or null.
 */
function hook_authcache_request_exclude() {
  if (authcache_ajax_is_authcache_ajax_request()) {
    return t('Authcache Ajax request');
  }
}

/**
 * Exclude a page from being cached based on the given account.
 *
 * @return string
 *   A translated string specifying the reason of exclusion or null.
 */
function hook_authcache_account_exclude($account) {
  // Bail out from requests by superuser (uid=1)
  if ($account->uid == 1 && !variable_get('authcache_su', 0)) {
    return t('Caching disabled for superuser');
  }
}

/**
 * Perform an action when a page has been excluded from caching.
 *
 * This hook is called very early in authcache_init().
 *
 * @param string $reason
 *   A translated string giving the reason why the page was excluded from being
 *   cached.
 *
 * @see hook_authcache_request_exclude()
 * @see hook_authcache_account_exclude()
 */
function hook_authcache_excluded($reason) {
  if (authcache_debug_access()) {
    drupal_add_js(array('authcacheDebug' => array('nocacheReason' => $reason)), 'setting');
  }
}

/**
 * Perform last-minute checks before a built page is saved to the cache.
 *
 * @return string
 *   A translated string specifying the reason for cancelation or null.
 *
 * @see authcache_page_set_cache()
 */
function hook_authcache_cancel() {
  // Make sure "Location" redirect isn't used.
  foreach (headers_list() as $header) {
    if (strpos($header, 'Location:') === 0) {
      return t('Location header detected');
    }
  }
}

/**
 * Perform an action when page caching has been canceled.
 *
 * This hook may be called very late, i.e. after the page was built und just
 * before it is sent to the browser.
 *
 * @param string $reason
 *   A translated string giving the reason why page caching has been canceled.
 *
 * @see authcache_cancel()
 */
function hook_authcache_canceled($reason) {
  if (authcache_debug_access()) {
    setcookie('nocache_reason', $reason, 0, ini_get('session.cookie_path'), ini_get('session.cookie_domain'), ini_get('session.cookie_secure') == '1');
  }
}

/**
 * Prevent that that next page request is served from the cache.
 *
 * @return string
 *   A translated string specifying the reason of exclusion or null.
 */
function hook_authcache_preclude() {
  // After a POST, do not serve the next page request from cache.
  if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    return t('POST request');
  }
}

/**
 * Perform an action if next page request will not be served from cache.
 *
 * This hook is called late in authcache_exit() just before cookies are set and
 * the page is cached / sent to the client.
 *
 * @param string $reason
 *   A translated string giving the reason why the next page will not be served
 *   from the cache.
 *
 * @see hook_authcache_preclude()
 */
function hook_authcache_precluded($reason) {
  if (authcache_debug_access()) {
    setcookie('preclude_reason', $reason, 0, ini_get('session.cookie_path'), ini_get('session.cookie_domain'), ini_get('session.cookie_secure') == '1');
  }
}

/**
 * Return key property values used to calculate the authcache key.
 *
 * @return array
 *   An associative array of key-value pairs.
 */
function hook_authcache_key_properties() {
  return array(
    'js' => !empty($_COOKIE['has_js']),
  );
}

/**
 * Modify the properties used to calculate the authcache key.
 *
 * @see authcache_key_properties()
 * @see authcache_key()
 */
function hook_authcache_key_properties_alter(&$properties) {
  global $user;

  // Paranoia-mode: Make sure the authcache-key for logged in users changes
  // every hour.
  if ($user->uid) {
    $properties['timeslice'] = floor(REQUEST_TIME / 3600);
  }
}

/**
 * Return information about cookies in use.
 *
 * Modules and themes may declare the characteristics of cookies they use by
 * implementing this hook. Doing so will allow authcache to manage those
 * cookies, i.e. setting and deleting them when a user-session is started and
 * terminated respectively.
 *
 * @param object $account
 *   The user object on which the operation was just performed.
 *
 * @return array
 *   An array of cookie items. Each cookie item has a key corresponding
 *   to the cookie-name. The corresponding array value is an associative array
 *   that may contain the following key-value pairs:
 *   - "present": TRUE if the cookie should be present in the users browser,
 *     FALSE otherwise. Defaults to FALSE.
 *   - "value": The cookies value. Defaults to NULL.
 *   - "lifetime": An integer value specifying how many seconds the cookie
 *     should be kept by the browser. Defaults to the PHP ini value
 *     session.cookie_lifetime.
 *   - "path": The path in which the cookie will be available on. Defaults to
 *     the PHP ini value session.cookie_path.
 *   - "domain": The domain that the cookie is available to. Defaults to the
 *     PHP ini value session.cookie_domain.
 *   - "secure": Indicates that the cookie should only be transmitted over a
 *     secure HTTPS connection from the client. Defaults to the PHP in value
 *     session.cookie_secure.
 *   - "httponly": When TRUE the cookie will be made accessible only through
 *     the HTTP protocol. This means that the cookie won't be accessible by
 *     scripting languages, such as JavaScript. Defaults to FALSE.
 *
 * @see authcache_fix_cookies()
 * @see setcookie()
 */
function hook_authcache_cookie($account) {
  $authenticated = $account->uid;
  $enabled = authcache_account_allows_caching();
  $present = $authenticated && $enabled;

  $cookies['aceuser']['present'] = $present;

  if ($present) {
    $cookies['aceuser']['value'] = $account->name;
  }

  return $cookies;
}

/**
 * Modify information about cookies set by other modules.
 *
 * In this example the simple nocache-cookie is replaced with a a HMAC bound to
 * the session. Note that for this example to be effective it is necessary to
 * implement a corresponding validation function suitable for the caching
 * backend in place. Point the variable authcache_builtin_nocache_get to the
 * name of an appropriate implementation when the default builtin cache backend
 * is used.
 *
 * $conf['authcache_builtin_nocache_get'] = 'my_nocache_get';
 *
 * @see hook_authcache_cookie()
 * @see authcache_fix_cookies()
 * @see _authcacheinc_default_nocache_get()
 */
function hook_authcache_cookie_alter(&$cookies, $account) {
  global $user;

  if (!empty($cookies['nocache']['present'])) {
    if ($user->uid) {
      $hmac = drupal_hmac_base64('nocache', session_id() . variable_get('my_nocache_auth_key'));
    }
    else {
      $hmac = drupal_hmac_base64('nocache', ip_address() . variable_get('my_nocache_auth_key'));
    }

    $cookies['nocache']['value'] = $hmac;
  }
}

/**
 * Save a page to the cache.
 *
 * @param string $body
 *   The body of the document, when page_compression is true and the gzip
 *   extension is available, this will contain gzipped data. It is still
 *   possible to get hold of the original uncompressed data using
 *   ob_get_contents().
 * @param array $headers
 *   The headers which will be delivered along with the document.
 * @param bool $page_compressed
 *   Flag set to TRUE when $body contains gzipped data.
 */
function hook_authcache_backend_cache_save($body, $headers, $page_compressed) {
  $cid = authcache_builtin_cid();
  $data = array(
    'path' => $_GET['q'],
    'body' => $body,
    'title' => drupal_get_title(),
    'headers' => $headers,
    // We need to store whether page was compressed or not,
    // because by the time it is read, the configuration might change.
    'page_compressed' => $page_compressed,
  );

  cache_set($cid, $data, 'cache_page', CACHE_TEMPORARY);
}

/**
 * Make the key available for subsequent request from the same client.
 */
function hook_authcache_backend_key_set($key, $lifetime, $has_session) {
  if ($previous_session && $previous_session !== $current_session) {
    cache_clear_all($previous_session, 'cache_authcache_key');
  }

  // Update cached key if necessary.
  $cache = cache_get($current_session, 'cache_authcache_key');
  if ($cache === FALSE || $cache->expire > 0 && $cache->expire < REQUEST_TIME || $cache->data !== $current_key) {
    $expires = $lifetime ? REQUEST_TIME + $lifetime : CACHE_TEMPORARY;
    cache_set($current_session, $key, 'cache_authcache_key', $expires);
  }
}
