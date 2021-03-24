
Link Checker
------------

Installation:

1. Install linkchecker via Modules page.
2. Go to Modules and enable the "Link checker" module.
3. Go to Configuration -> Content authoring -> Link checker and enable the node types to scan.
4. Under "Link extraction" check all HTML tags that should be scanned.
5. Adjust the other settings if the defaults don't suit your needs.
6. Save configuration
7. Wait for cron to check all your links... this may take some time! :-)

If links are broken they appear under Reports -> Broken links.

If not, make sure cron is configured and running properly on your Drupal
installation. The Link checker module also logs somewhat useful info about it's
activity under Reports -> Recent log messages.


Required:

1. For internal URL extraction you need to make sure that Cron always get called
   with your real public site URL (for e.g. http://example.com/cron.php). Make
   sure it's never executed with http://localhost/cron.php or any other
   hostnames or ports, not available from public. Otherwise all links may be
   reported as broken and cannot verified as they should be.

   To make sure it always works - it's required to configure the $base_url in
   the sites settings.php with your public sites URL. Better safe than sorry!


Known issues:

There are a lot of known issues in drupal_http_request(). These have been solved
in HTTPRL. As a workaround it's recommended to use HTTPRL in linkchecker.

Issues list:
 
* #997648: drupal_http_request() always calls fread() one more time than necessary
* #164365-12: drupal_http_request() does handle (invalid) non-absolute redirects
* #205969-11: drupal_http_request() assumes presence of Reason-Phrase in response Status-Line
* #371495: Error message from drupal_http_request() not UTF8 encoded
* #193073-11: drupal_http_request - socket not initialized
* #106506-8: drupal_http_request() does not handle 'chunked' responses - Make it support HTTP 1.1
* #1096890-15: drupal_http_request should return error if reaches max allowed redirects
* #875342-21: drupal_http_request() should pick up X-Drupal-Assertion-* HTTP headers
* #965078-31: HTTP request checking is unreliable and should be removed in favor of watchdog() calls
* #336367: HTTP client should protect commas when folding (compatibility with legacy HTTP/1.0)
* #45338: log fsockopen errors to watchdog
