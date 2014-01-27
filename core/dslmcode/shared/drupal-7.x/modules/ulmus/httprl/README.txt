
------------------------------------------------
HTTP PARALLEL REQUEST & THREADING LIBRARY MODULE
------------------------------------------------


CONTENTS OF THIS FILE
---------------------

 * About HTTPRL
 * Requirements
 * Configuration
 * API Overview
 * Technical Details
 * Code Examples


ABOUT HTTPRL
------------

http://drupal.org/project/httprl

HTTPRL is a flexible and powerful HTTP client implementation. Correctly handles
GET, POST, PUT or any other HTTP requests & the sending of data. Issue blocking
or non-blocking requests in parallel. Set timeouts, max simultaneous connection
limits, chunk size, and max redirects to follow. Can handle data with
content-encoding and transfer-encoding headers set. Correctly follows
redirects. Option to forward the referrer when a redirect is found. Cookie
extraction and parsing into key value pairs. Can multipart encode data so files
can easily be sent in a HTTP request. Will emulate a range request if the server
does not support range requests.


REQUIREMENTS
------------

Requires PHP 5. The following functions must be available on the server:
 * stream_socket_client
 * stream_select
 * stream_set_blocking
 * stream_get_meta_data
 * stream_socket_get_name
Some hosting providers disable these functions; but they do come standard with
PHP 5.


CONFIGURATION
-------------

Settings page is located at:
6.x: admin/settings/httprl
7.x: admin/config/development/httprl

 * IP Address to send all self server requests to. If left blank it will use the
   same server as the request. If set to -1 it will use the host name instead of
   an IP address. This controls the output of httprl_build_url_self().
 * Enable background callbacks. If disabled all background_callback keys will
   be turned into callback & httprl_queue_background_callback will return NULL
   and not queue up the request. Note that background callbacks will
   automatically be disabled if the site is in maintenance mode.


API OVERVIEW
------------

Issue HTTP Requests:
httprl_build_url_self()
 - Helper function to build an URL for asynchronous requests to self. Note that
   you should set the Host name in the headers when using this.
httprl_request()
 - Queue up a HTTP request in httprl_send_request().
httprl_send_request()
 - Perform many HTTP requests.

Create and use a thread:
httprl_queue_background_callback()
 - Queue a special HTTP request (used for threading) in httprl_send_request().

Other Functions:
httprl_is_background_callback_capable()
 - See if httprl can issue a background callback.
httprl_background_processing()
 - Output text, close connection, continue processing in the background.
httprl_strlen()
 - Get the length of a string in bytes.
httprl_glue_url()
 - Alt to http_build_url().
httprl_get_server_schema()
 - Return the server schema (http or https).
httprl_pr()
 - Pretty print data.
httprl_fast403()
 - Issue a 403 and exit.


TECHNICAL DETAILS
-----------------

Using stream_select() HTTPRL will send http requests out in parallel. These
requests can be made in a blocking or non-blocking way. Blocking will wait for
the http response; Non-Blocking will close the connection not waiting for the
response back. The API for httprl is similar to the Drupal 7 version of
drupal_http_request().

HTTPRL can be used independent of drupal. For basic operations it doesn't
require any built in drupal functions.


CODE EXAMPLES
-------------

See examples/httprl.examples.php for code examples.
