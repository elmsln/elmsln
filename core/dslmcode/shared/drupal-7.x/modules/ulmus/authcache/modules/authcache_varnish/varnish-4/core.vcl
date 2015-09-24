vcl 4.0;

/**
 * Core VCL for Authcache Varnish / Authcache ESI
 * ==============================================
 *
 * WARNING: Do not modify this file but instead start with example.vcl and
 * include the core.vcl from there.
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
 * Code sections for the key-retrieval are spread over vcl_recv,
 * vcl_backend_response and vcl_deliver.
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
 * the markup. This allows vcl_backend_response to selectively enable ESI
 * processing only when necessary.
 *
 * Also Drupal/Authcache ESI will only emit ESI tags, if the X-Authcache-Do-ESI
 * header is on the request to the backend. This header is added from within
 * vcl_recv. As a consequence the backend will not emit ESI tags when caching
 * is bypassed, e.g. due to an earlier "return (pass)" in vcl_recv.
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

sub vcl_recv {
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
      return (hash);
    }
    else {
      return (pass);
    }
  }

  /**
   * BEGIN builtin.vcl
   */
  if (req.method == "PRI") {
    /* We do not support SPDY or HTTP/2.0 */
    return (synth(405));
  }

  /**
   * EDIT for authcache: In order to allow a site to configure PURGE and inject
   * additional vcl_recv code, branch to a custom function defined in
   * example.vcl here.
   */
  call authcache_recv;

  if (req.method != "GET" &&
    req.method != "HEAD" &&
    req.method != "PUT" &&
    req.method != "POST" &&
    req.method != "TRACE" &&
    req.method != "OPTIONS" &&
    req.method != "DELETE") {
      /* Non-RFC2616 or CONNECT which is weird. */
      return (pipe);
  }

  if (req.method != "GET" && req.method != "HEAD") {
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
  /* END builtin.vcl */

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
    call authcache_key_path;
    set req.http.X-Original-URL = req.url;
    set req.url = req.http.X-Authcache-Key-Path;
    set req.http.X-Authcache-Get-Key = "sent";
    unset req.http.X-Authcache-Key-Path;
  }

  // Tell the backend that ESI processing is available. The Authcache ESI
  // module will only emit tags if this header is present on the request.
  // If the X-Authcache key is already present on an incoming request (e.g.
  // triggered by Authcache Ajax), do not enable ESI.
  if (req.http.X-Authcache-Get-Key != "skip" && !req.http.X-Authcache) {
    set req.http.X-Authcache-Do-ESI = 1;
  }

  // Add authcache-header for ESI requests going to the authcache_p13n front
  // controller.
  if (req.http.X-Authcache-Do-ESI && req.esi_level > 0) {
    set req.http.X-Authcache = 1;
  }

  return (hash);
}

sub vcl_backend_response {
  // Store result of key retrieval for 10 minutes. Do this regardless of
  // whether the request was successful or not. E.g. when the Authcache Varnish
  // module is disabled in the backend (no matter whether on purpose or not),
  // it is still desirable to cache the resulting 404.
  if (bereq.http.X-Authcache-Get-Key == "sent") {
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

  // Turn on ESI processing when requested by backend
  if (beresp.http.X-Authcache-Do-ESI) {
    set beresp.do_esi = true;
  }

  // Ensure that the result is cached individually for each session if
  // Cache-Control header on the response of an Authcache ESI request
  // contains the "private" keyword.
  if (bereq.http.X-Authcache-Do-ESI && bereq.http.X-Authcache) {
    if (beresp.http.Cache-Control ~ "(private)" && beresp.http.Vary !~ "Cookie") {
      set beresp.http.Vary = beresp.http.Vary + ", Cookie";
      set beresp.http.Vary = regsub(beresp.http.Vary, "^,\s*", "");
      // Remove the private directive from the Cache-Control response header
      // such that the fragment gets stored by Varnish 4.
      set beresp.http.Cache-Control = regsub(beresp.http.Cache-Control, "(^|,\s*)private", "");
      set beresp.http.Cache-Control = regsub(beresp.http.Cache-Control, "^,\s*", "");
    }
    elseif (beresp.http.Cache-Control ~ "(public)" && beresp.http.Vary !~ "X-Authcache-Key") {
      set beresp.http.Vary = beresp.http.Vary + ", X-Authcache-Key";
      set beresp.http.Vary = regsub(beresp.http.Vary, "^,\s*", "");
    }
  }
}

sub vcl_deliver {
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
    // 2. Remove all X-Authcache-* directives from the Vary header.
    set resp.http.Vary = regsuball(resp.http.Vary, "(^|,\s*)X-Authcache[-a-zA-Z]*", "");
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
  unset resp.http.X-Authcache-Key-CID;
  unset resp.http.X-Authcache-Key;
}
