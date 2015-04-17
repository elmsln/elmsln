INSTALLATION
============

* Install and enable authcache and authcache_varnish modules.
* Navigate to Administration » Configuration » Development and set "Expiration
  of cached pages" to an appropriate value (> 0).
* Install and enable the varnish and expire modules in order to have means to
  invalidate the cache when necessary.
* The example.vcl file includes snippets of code to add to your Varnish
  configuration to make authcache_varnish work. If you have an existing
  Varnish configuration file, it is recommended to start with example.vcl
  and add bits from your own file to it.
* Optionally enable authcache_debug. Uncommenting the appropriate lines in
  vcl_deliver in order to make the cache-hit indicator on the debug widget
  work.

The module and the VCL is based on the ideas of Josh Waihi. Please refer to
his excellent blog post for further background:
* http://joshwaihi.com/content/authenticated-page-caching-varnish-drupal

The test folder contains a test-suite for the example.vcl. Run it by issuing
"make check". If you like to test your own version of the VCL, point the
AUTHCACHE_VCL variable to your file, e.g.:

    make check AUTHCACHE_VCL_FILE=/path/to/my/authcache.vcl


SETTINGS
========

Authcache Varnish verifies whether a request is coming in through a trusted
proxy server. Therefore it is necessary to properly configure reverse proxy
support in settings.php. E.g:

    $conf['reverse_proxy'] = TRUE;
    $conf['reverse_proxy_addresses'] = array('a.b.c.d');
    // Replace 'a.b.c.d' with the IP address of the revers proxy server.

For testing purposes it is possible to disable the reverse proxy check by
placing the following line into the settings.php file:

    $conf['authcache_varnish_validate_reverse_proxy_address'] = FALSE;

Beside the reverse proxy address Authcache Varnish also tests whether the
X-Varnish header is on the request. In order to disable this check, place the
following line into settings.php:

    $conf['authcache_varnish_header'] = FALSE;

Also it is possible to specify another header which should be checked by
specifying the $_SERVER-key accordingly. E.g. when Authcache Varnish should
verify the presence of X-Fancy-Proxy, introduce the following line into your
settings.php:

    $conf['authcache_varnish_header'] = 'HTTP_X_FANCY_PROXY';
