/**
 * Example VCL for Authcache Varnish / Authcache ESI
 * =================================================
 *
 * By default, the Varnish Cache is bypassed whenever there is a Cookie-Header
 * present on the request. This is a reasonable default behavior because the
 * rationale behind HTTP cookies is essentially to enable personalization of
 * web applications. The results would be disastrous if personalized pages
 * would be cached and delivered regardless of the contents of the Cookie
 * header. For example on an E-commerce site users could end up seeing each
 * others shopping cart, only to name a rather harmless case.
 *
 * This VCL together with Drupal, Authcache Varnish and Authcache ESI allows
 * Varnish to cache personalized content in a safe way without risking the
 * side-effects mentioned above.
 *
 *
 * 1. Backend sets "Vary: X-Authcache-Key" header
 * ----------------------------------------------
 * When the Drupal core option "Cache pages for anonymous users" is enabled, a
 * "Vary: Cookie" header is added to each response from the site. This
 * essentially mandates an intermediate cache server (and also the browser
 * cache) to only deliver a cached version of the page when the Cookie header
 * on a subsequent request is identical to the one of the original request,
 * when the page was first stored in the cache. However it is rather
 * inefficient to store every page for every user separately in a caching
 * server.
 *
 * Because of this, a Drupal site with the Authcache Varnish module enabled
 * will send a "Vary: X-Authcache-Key" header instead of "Vary: Cookie". The
 * caching server now will compare X-Authcache-Key request headers when
 * determining whether a cached version of a page can be sent to the client.
 * However because no browser is sending an X-Authcache-Key header along with a
 * HTTP request, it is necessary to add this header from within the VCL before
 * looking up the object in the cache.
 *
 *
 * 2. Retrieve X-Authcache-Key form the backend and add it onto the request
 * ------------------------------------------------------------------------
 * The authcache key is a value which is unique for every combination of Drupal
 * user roles. The keys of two users are only equal if both of them have the
 * exact same combination of user roles and therefore identical permissions.
 *
 * Authcache Varnish exposes the callback /authcache-varnish-get-key which
 * returns the authcache key for the currently logged in user. Except when one
 * of the roles is excluded from caching, in that case no key is returned from
 * the callback.
 *
 * When a client requests the page /original-url, effectively two requests will
 * be issued by this VCL:
 *   1. GET /authcache-varnish-get-key
 *       -> add resulting X-Authcache-Key to the request and restart.
 *   2. GET /original-url
 *       -> deliver result to client
 * Unfortunately the VCL implementation of this logic is somewhat complicated.
 * Code sections for the key-retrieval are spread over vcl_recv, vcl_fetch and
 * vcl_deliver.
 *
 *
 * 3. Embed personalized fragments using ESI
 * -----------------------------------------
 * The process described in the preceding section only helps with improving
 * cache efficiency but not with personalization. A site configured like this
 * still is prone to information leakage (e.g. Eve seeing the shopping cart of
 * Alice). In order to solve this problem, personalized items on a page (like a
 * shopping cart block) need to be identified and substituted with ESI tags.
 * Authcache provides a set of modules out of the box helping with substituting
 * personalized content (e.g. Blocks, Views, Form Tokens, Menu Tabs and Action
 * Links, ...).
 *
 * When Authcache ESI is enabled in Drupal, the HTTP header X-Authcache-Do-ESI
 * is added to every response from the backend whenever an ESI tag was added to
 * the markup. This allows vcl_fetch to selectively enable ESI processing only
 * when necessary.
 *
 * Also Drupal/Authcache ESI will only emit ESI tags, if the X-Authcache-Do-ESI
 * header is on the request to the backend. This header is added from within
 * vcl_miss. As a consequence the backend will not emit ESI tags when caching
 * is bypassed, e.g. due to a "return (pass)" from within vcl_recv.
 *
 *
 * Credits & Sources
 * -----------------
 * * Josh Waihi - Authenticated page caching with Varnish & Drupal:
 *   http://joshwaihi.com/content/authenticated-page-caching-varnish-drupal
 * * Four Kitchens - Configure Varnish 3 for Drupal 7:
 *   https://fourkitchens.atlassian.net/wiki/display/TECH/Configure+Varnish+3+for+Drupal+7
 * * The Varnish Book:
 *   https://www.varnish-software.com/static/book/
 * * The Varnish Book - VCL Request Flow:
 *   https://www.varnish-software.com/static/book/_images/vcl.png
 */

/**
 * Derive the cache identifier for the key cache.
 */
sub authcache_key_cid {
  if (req.http.Cookie ~ "(^|;)\s*S?SESS[a-z0-9]+=") {
    // Use the whole session cookie to differentiate between authenticated
    // users.
    set req.http.X-Authcache-Key-CID = "sess:"+regsuball(req.http.Cookie, "^(.*;\s*)?(S?SESS[a-z0-9]+=[^;]*).*$", "\2");
  }
  else {
    // If authcache key retrieval was enforced for anonymous traffic, the HTTP
    // host is used in order to keep apart anonymous users of different
    // domains.
    set req.http.X-Authcache-Key-CID = "host:"+req.http.host;
  }

  /* Optional: When using authcache_esi alongside with authcache_ajax */
  // if (req.http.Cookie ~ "(^|;)\s*has_js=1\s*($|;)") {
  //   set req.http.X-Authcache-Key-CID = req.http.X-Authcache-Key-CID + "+js";
  // }
  // else {
  //   set req.http.X-Authcache-Key-CID = req.http.X-Authcache-Key-CID + "-js";
  // }

  /* Optional: When serving HTTP/HTTPS */
  // if (req.http.X-Forwarded-Proto ~ "(?i)https") {
  //   set req.http.X-Authcache-Key-CID = req.http.X-Authcache-Key-CID + "+ssl";
  // }
  // else {
  //   set req.http.X-Authcache-Key-CID = req.http.X-Authcache-Key-CID + "-ssl";
  // }
}

sub vcl_recv {
  /**
   * BEGIN required authcache key-retrieval logic
   *
   * It should not be necessary to modify this section. Please file a bug or
   * feature request if you find a situation where this part of the VCL is not
   * appropriate.
   *
   * https://drupal.org/project/issues/authcache
   **/

  /**
   * Do not allow the client to pass in X-Authcache-Get-Key header unless the
   * VCL is under test (varnishtest uses -n /tmp/vtc.XXXXX.YYYYYYYY).
   */
  if (req.restarts == 0 && server.identity !~ "^/tmp/vtc.") {
    unset req.http.X-Authcache-Do-ESI;
    unset req.http.X-Authcache-Get-Key;
    unset req.http.X-Authcache-Key-CID;
    unset req.http.X-Authcache-Key;
  }

  /**
   * Do not allow outside access to key retrieval callback.
   */
  if (req.restarts == 0 && req.url ~ "^/authcache-varnish-get-key") {
    error 404 "Page not found.";
  }

  /**
   * Request was restarted from vcl_deliver after the authcache key was
   * obtained from the backend.
   */
  if (req.restarts > 0 && req.http.X-Authcache-Get-Key == "received") {
    // Restore the original URL.
    set req.url = req.http.X-Original-URL;
    unset req.http.X-Original-URL;

    // Remove cache id header.
    unset req.http.X-Authcache-Key-CID;

    // Key retrieval is over now
    set req.http.X-Authcache-Get-Key = "done";

    // If the backend delivered a key, we proceed with a lookup, otherwise the
    // cache needs to be bypassed.
    if (req.http.X-Authcache-Key) {
      return (lookup);
    }
    else {
      return (pass);
    }
  }
  /* END required authcache key-retrieval logic */



  // TODO: Add purge handler, access checks and other stuff relying on
  // non-standard HTTP verbs here.

  // /**
  //  * Example 1: Allow purge from all clients in the purge-acl. Note that
  //  * additional VCL is necessary to make this work, notably the acl and some
  //  * code in vcl_miss and vcl_hit.
  //  *
  //  * More information on:
  //  * https://www.varnish-cache.org/docs/3.0/tutorial/purging.html
  //  */
  // if (req.method == "PURGE") {
  //   if (!client.ip ~ purge) {
  //     error 405 "Not allowed.";
  //   }
  //   return (lookup);
  // }

  // /**
  //  * Example 2: Do not allow outside access to cron.php or install.php.
  //  */
  // if (req.url ~ "^/(cron|install)\.php$" && !client.ip ~ internal) {
  //   error 404 "Page not found.";
  // }



  /**
   * BEGIN default.vcl
   *
   * It should not be necessary to modify this section. Please file a bug or
   * feature request if you find a situation where this part of the VCL is not
   * appropriate.
   *
   * https://drupal.org/project/issues/authcache
   */
  if (req.restarts == 0) {
    if (req.http.x-forwarded-for) {
      set req.http.X-Forwarded-For =
        req.http.X-Forwarded-For + ", " + client.ip;
    } else {
      set req.http.X-Forwarded-For = client.ip;
    }
  }
  if (req.request != "GET" &&
      req.request != "HEAD" &&
      req.request != "PUT" &&
      req.request != "POST" &&
      req.request != "TRACE" &&
      req.request != "OPTIONS" &&
      req.request != "DELETE") {
    /* Non-RFC2616 or CONNECT which is weird. */
    return (pipe);
  }
  if (req.request != "GET" && req.request != "HEAD") {
    /* We only deal with GET and HEAD by default */
    return (pass);
  }

  /**
   * EDIT for authcache: We *need* to allow caching for clients having certain
   * cookies on their request.
   */
  if (req.http.Authorization /* || req.http.Cookie */) {
    /* Not cacheable by default */
    return (pass);
  }
  /* END default.vcl */



  // TODO: Place your custom *pass*-rules here. Do *not* introduce any lookups.

  // /* Example 1: Never cache admin/cron/user pages. */
  // if (
  //     req.url ~ "^/admin$" ||
  //     req.url ~ "^/admin/.*$" ||
  //     req.url ~ "^/batch.*$" ||
  //     req.url ~ "^/comment/edit.*$" ||
  //     req.url ~ "^/cron\.php$" ||
  //     req.url ~ "^/file/ajax/.*" ||
  //     req.url ~ "^/install\.php$" ||
  //     req.url ~ "^/node/*/edit$" ||
  //     req.url ~ "^/node/*/track$" ||
  //     req.url ~ "^/node/add/.*$" ||
  //     req.url ~ "^/system/files/*.$" ||
  //     req.url ~ "^/system/temporary.*$" ||
  //     req.url ~ "^/tracker$" ||
  //     req.url ~ "^/update\.php$" ||
  //     req.url ~ "^/user$" ||
  //     req.url ~ "^/user/.*$" ||
  //     req.url ~ "^/users/.*$") {
  //   return (pass);
  // }

  // /**
  //  * Example 2: Remove all but
  //  * - the session cookie (SESSxxx, SSESSxxx)
  //  * - the cache invalidation cookie for authcache p13n (aucp13n)
  //  * - the NO_CACHE cookie from the Bypass Advanced module
  //  * - the nocache cookie from authcache
  //  *
  //  * Note: Please also add the has_js cookie to the list if Authcache Ajax
  //  * is also enabled in the backend. Also if you have Authcache Debug enabled,
  //  * you should let through the aucdbg cookie.
  //  *
  //  * More information on:
  //  * https://www.varnish-cache.org/docs/3.0/tutorial/cookies.html
  //  */
  // if (req.http.Cookie) {
  //   set req.http.Cookie = ";" + req.http.Cookie;
  //   set req.http.Cookie = regsuball(req.http.Cookie, "; +", ";");
  //   set req.http.Cookie = regsuball(req.http.Cookie, ";(S?SESS[a-z0-9]+|aucp13n|NO_CACHE|nocache)=", "; \1=");
  //   set req.http.Cookie = regsuball(req.http.Cookie, ";[^ ][^;]*", "");
  //   set req.http.Cookie = regsuball(req.http.Cookie, "^[; ]+|[; ]+$", "");

  //   if (req.http.Cookie == "") {
  //     unset req.http.Cookie;
  //   }
  // }

  // /**
  //  * Example 3: Only attempt authcache key retrieval for the domain
  //  * example.com and skip it for all other domains.
  //  *
  //  * Note: When key retrieval is forcibly prevented, the default VCL rules
  //  * will kick in. I.e. only requests having no cookies at all will be
  //  * cacheable.
  //  */
  // if (req.http.host != "example.com" && req.http.host != "www.example.com") {
  //   set req.http.X-Authcache-Get-Key = "skip";
  // }

  // /**
  //  * Example 4: Trigger key-retrieval for all users, including anonymous.
  //  *
  //  * Forcing key-retrieval for users without a session enables caching even for
  //  * requests with cookies. This may come in handy in one of the following
  //  * situations:
  //  * - A custom key generator is in place for anonymous users. E.g. to separate
  //  *   cache bins according to language / region / device type.
  //  * - The Authcache Debug widget is enabled for all users (including anonymous).
  //  */
  // if (!req.http.X-Authcache-Get-Key) {
  //   set req.http.X-Authcache-Get-Key = "get";
  // }


  /**
   * BEGIN required authcache key-retrieval logic
   *
   * It should not be necessary to modify this section. Please file a bug or
   * feature request if you find a situation where this part of the VCL is not
   * appropriate.
   *
   * https://drupal.org/project/issues/authcache
   **/
  if (req.restarts == 0) {
    /**
     * Before fulfilling a request, the authcache-key needs to be retrieved
     * either from the cache or the backend.
     *
     * If the variable X-Authcache-Get-Key is set to "get", the request will
     * enter key-retrieval phase before the requested page is delivered. If
     * it is set to "skip", key-retrieval is not attempted.
     *
     * If the users VCL above did not specify whether key retrieval should be
     * performed or not, the default behavior is to skip it as long as there is
     * no session on the request.
     */
    if (!req.http.X-Authcache-Get-Key && req.http.Cookie ~ "(^|;)\s*S?SESS[a-z0-9]+=") {
      set req.http.X-Authcache-Get-Key = "get";
    }

    if (req.http.X-Authcache-Get-Key != "get") {
      set req.http.X-Authcache-Get-Key = "skip";
    }
  }

  // Skip cache if there are cookies on the request and key-retrieval is
  // disabled.
  if (req.http.X-Authcache-Get-Key == "skip" && req.http.Cookie) {
    return (pass);
  }

  // Skip cache when key-retrieval is enabled but nocache-cookie is on the
  // request.
  if (req.http.X-Authcache-Get-Key && req.http.X-Authcache-Get-Key != "skip" && req.http.Cookie ~ "(^|;)\s*nocache=1\s*($|;)") {
    return (pass);
  }

  // Retrieve the authcache-key from /authcache-varnish-get-key before each
  // request. Upon vcl_deliver the authcacke-key is copied over to the
  // X-Authcache-Key request header and the request is restarted.
  if (req.http.X-Authcache-Get-Key == "get") {
    call authcache_key_cid;
    set req.http.X-Original-URL = req.url;
    set req.url = "/authcache-varnish-get-key";
    set req.http.X-Authcache-Get-Key = "sent";
  }

  return (lookup);
  /* END required authcache key-retrieval logic */
}

/**
 * Tell the backend that ESI processing is available. The Authcache ESI
 * module will only emit tags if this header is present on the request.
 */
sub vcl_miss {
  /**
   * BEGIN required authcache ESI header
   *
   * It should not be necessary to modify this section. Please file a bug or
   * feature request if you find a situation where this part of the VCL is not
   * appropriate.
   *
   * https://drupal.org/project/issues/authcache
   **/
  if (req.http.X-Authcache-Get-Key && req.http.X-Authcache-Get-Key != "skip") {
    set bereq.http.X-Authcache-Do-ESI = 1;
  }

  // Add authcache-header for ESI requests going to the authcache_p13n front
  // controller.
  if (bereq.http.X-Authcache-Do-ESI && req.esi_level > 0) {
    set bereq.http.X-Authcache = 1;
  }
  /* END required authcache ESI header */

  // /**
  //  * Example 1: Use a passphrase to validate proxy requests.
  //  *
  //  * The standard Drupal way to verify whether a request came in via a proxy
  //  * is to compare the X-Forwarded-For header to a whitelist. By default
  //  * Authcache Varnish uses the same method. This fails however, if this
  //  * check is carried out by the webserver (e.g., when using Nginx with the
  //  * realip module).
  //  *
  //  * In that case, set a passphrase on the request and configure the same in
  //  * settings.php, e.g.:
  //  *
  //  *    $conf['authcache_varnish_passphrase'] = 'correct horse battery staple';
  //  *
  //  */
  // set bereq.http.X-Authcache-Varnish-Passphrase = "correct horse battery staple";
}

sub vcl_fetch {
  /**
   * BEGIN required authcache key-retrieval logic
   *
   * It should not be necessary to modify this section. Please file a bug or
   * feature request if you find a situation where this part of the VCL is not
   * appropriate.
   *
   * https://drupal.org/project/issues/authcache
   **/

  // Store result of key retrieval for 10 minutes. Do this regardless of
  // whether the request was successful or not. E.g. when the Authcache Varnish
  // module is disabled in the backend (no matter whether on purpose or not),
  // it is still desirable to cache the resulting 404.
  if (req.http.X-Authcache-Get-Key == "sent") {
    // If backend did not specify a max-age, assume 10 minutes.
    if (beresp.ttl <= 0 s) {
      set beresp.ttl = 10 m;
    }

    // Ensure that we vary on X-Authcache-Key-CID
    if (beresp.http.Vary !~ "X-Authcache-Key-CID") {
        set beresp.http.Vary = beresp.http.Vary + ", X-Authcache-Key-CID";
        set beresp.http.Vary = regsub(beresp.http.Vary, "^,\s*", "");
    }

    return (deliver);
  }
  /* END required authcache key-retrieval logic */

  /**
   * BEGIN required authcache ESI header
   *
   * It should not be necessary to modify this section. Please file a bug or
   * feature request if you find a situation where this part of the VCL is not
   * appropriate.
   *
   * https://drupal.org/project/issues/authcache
   **/
  // Turn on ESI processing when requested by backend
  if (beresp.http.X-Authcache-Do-ESI) {
    set beresp.do_esi = true;
  }

  // Ensure that the result is cached individually for each session if
  // Cache-Control header on the response of an Authcache ESI request
  // contains the "private" keyword.
  if (bereq.http.X-Authcache-Do-ESI && req.esi_level > 0) {
    if (beresp.http.Cache-Control ~ "(private)" && beresp.http.Vary !~ "Cookie") {
      set beresp.http.Vary = beresp.http.Vary + ", Cookie";
      set beresp.http.Vary = regsub(beresp.http.Vary, "^,\s*", "");
    }
    elseif (beresp.http.Cache-Control ~ "(public)" && beresp.http.Vary !~ "X-Authcache-Key") {
      set beresp.http.Vary = beresp.http.Vary + ", X-Authcache-Key";
      set beresp.http.Vary = regsub(beresp.http.Vary, "^,\s*", "");
    }
  }
  /* END required authcache ESI header */



  // TODO: Place your custom fetch policy here

  // /* Example 1: Cache 404s, 301s, 500s. */
  // if (beresp.status == 404 || beresp.status == 301 || beresp.status == 500) {
  //   set beresp.ttl = 10 m;
  // }

  // /*
  //  * Example 2: Do not cache when backend specifies Cache-Control: private,
  //  * no-cache or no-store.
  //  */
  // if (req.esi_level == 0 && beresp.http.Cache-Control ~ "(private|no-cache|no-store)") {
  //   set beresp.ttl = 0s;
  // }
}

sub vcl_deliver {
  /**
   * BEGIN required authcache key-retrieval logic
   *
   * It should not be necessary to modify this section. Please file a bug or
   * feature request if you find a situation where this part of the VCL is not
   * appropriate.
   *
   * https://drupal.org/project/issues/authcache
   **/
  // Process response from authcache-key callback
  if (req.http.X-Authcache-Get-Key == "sent") {
    // Copy over the X-Authcache-Key header if set
    if (resp.http.X-Authcache-Key) {
      set req.http.X-Authcache-Key = resp.http.X-Authcache-Key;
    }
    // Proceed to next state
    set req.http.X-Authcache-Get-Key = "received";
    return (restart);
  }

  // When sending a response from an authcache enabled backend to the browser:
  if (resp.http.Vary ~ "X-Authcache-Key") {
    // 1. Ensure that a Vary: Cookie is on the response
    if (resp.http.Vary !~ "Cookie") {
      set resp.http.Vary = resp.http.Vary + ", Cookie";
    }
    // 2. Ensure that Vary: X-Authcache-Key is *not* on the response
    set resp.http.Vary = regsub(resp.http.Vary, "(^|,\s*)X-Authcache-Key", "");
    // 3. Remove a "," prefix, if present.
    set resp.http.Vary = regsub(resp.http.Vary, "^,\s*", "");
  }

  // When checking whether it is possible to send a 304 instead of a full 200
  // response, Varnish does not respect the cache-characteristics of embedded
  // ESI fragments. In order to make this work it would be necessary to merge
  // all Last-Modified and ETag response headers of all ESI fragments and
  // generate a new value which is then delivered to the browser. Better 304
  // support has been on the ESI wishlist for some time but it did not happen
  // until now.
  // @see https://www.varnish-cache.org/trac/wiki/Future_ESI
  //
  // Disable HTTP revalidation when a page contains ESI fragments.
  if (resp.http.X-Authcache-Do-ESI) {
    unset resp.http.ETag;
    unset resp.http.Last-Modified;
  }

  // Remove variables placed on backend response.
  unset resp.http.X-Authcache-Do-ESI;

  /* END required authcache key-retrieval logic */



  // TODO: Modify response, add / remove headers
  // /**
  //  * Example 1: Disable browser cache in Safari.
  //  *
  //  * @see:
  //  *   - https://bugs.webkit.org/show_bug.cgi?id=71509
  //  *   - https://groups.drupal.org/node/191453
  //  *   - https://drupal.org/node/1910178
  //  */
  // if (resp.http.X-Generator ~ "Drupal" && req.http.user-agent ~ "Safari" && req.http.user-agent !~ "Chrome") {
  //   set resp.http.Cache-Control = "no-cache, must-revalidate, post-check=0, pre-check=0";
  // }

  // /**
  //  * Example 2: Add a hit-miss header to the response.
  //  *
  //  * See:
  //  * https://www.varnish-cache.org/trac/wiki/VCLExampleHitMissHeader
  //  */
  // if (obj.hits > 0) {
  //   set resp.http.X-Varnish-Cache = "HIT";
  // }
  // else {
  //   set resp.http.X-Varnish-Cache = "MISS";
  // }
}
