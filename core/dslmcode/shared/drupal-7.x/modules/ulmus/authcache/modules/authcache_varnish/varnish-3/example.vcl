/**
 * Example VCL for Authcache Varnish / Authcache ESI
 * =================================================
 *
 * See also core.vcl for detailed information.
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
 * Define all your backends here.
 */
backend default {
  .host = "127.0.0.1";
  .port = "3000";
}

/**
 * Include Authcache Varnish core.vcl.
 */
include "/tmp/authcache_varnish/core.vcl";

/**
 * Defines where the authcache varnish key callback is located.
 *
 * Note that the key-retrieval path must start with a slash and must include
 * the path prefix if any (e.g. on multilingual sites or if Drupal is installed
 * in a subdirectory).
 */
sub authcache_key_path {
  set req.http.X-Authcache-Key-Path = "/authcache-varnish-get-key";

  // Example of a multilingual site relying on path prefixes.
  # set req.http.X-Authcache-Key-Path = "/en/authcache-varnish-get-key";

  // Example of a drupal instance installed in a subdirectory.
  # set req.http.X-Authcache-Key-Path = "/drupal/authcache-varnish-get-key";
}

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

/**
 * Place your custom vcl_recv code here.
 */
sub authcache_recv {
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
  //  * requests with cookies. This is required in any of the following situations:
  //  * - If pages delivered to anonymous users contain Authcache ESI fragments.
  //  * - A custom key generator is in place for anonymous users. E.g. to separate
  //  *   cache bins according to language / region / device type.
  //  * - The Authcache Debug widget is enabled for all users (including anonymous).
  //  */
  // if (!req.http.X-Authcache-Get-Key) {
  //   set req.http.X-Authcache-Get-Key = "get";
  // }
}

sub vcl_miss {
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
  // if (bereq.http.X-Authcache-Get-Key != "skip") {
  //   set bereq.http.X-Authcache-Varnish-Passphrase = "correct horse battery staple";
  // }
}

sub vcl_fetch {
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
