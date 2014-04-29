<?php
/**
 * @file
 * HTTP Parallel Request Library code examples.
 */
?>

**Simple HTTP**
Request http://drupal.org/.

<?php
// Queue up the request.
httprl_request('http://drupal.org/');
// Execute request.
$request = httprl_send_request();

// Echo out the results.
echo httprl_pr($request);
?>


Request http://drupal.org/robots.txt and save it to tmp folder.

<?php
// Queue up the request.
httprl_request('http://drupal.org/robots.txt');
// Execute request.
$request = httprl_send_request();

// Save file if we got a 200 back.
if ($request['http://drupal.org/robots.txt']->code == 200) {
  file_put_contents('/tmp/robots.txt', $request['http://drupal.org/robots.txt']->data);
}
?>


Request this servers own front page & the node page.

<?php
$options = array(
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Build URL to point to front page of this server.
$url_front = httprl_build_url_self();
// Build URL to point to /node on this server.
$url_node = httprl_build_url_self('node');
// Queue up the requests.
httprl_request($url_front, $options);
httprl_request($url_node, $options);
// Execute requests.
$request = httprl_send_request();

// Echo out the results.
echo httprl_pr($request);
?>


**Non Blocking HTTP Operations**

Request 10 URLs in a non blocking manner on this server. Checkout watchdog as
this should generate 10 404s and the $request object won't contain much info.

<?php
// Set the blocking mode.
$options = array(
  'blocking' => FALSE,
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Queue up the requests.
$max = 10;
for ($i=1; $i <= $max; $i++) {
  // Build URL to a page that doesn't exist.
  $url = httprl_build_url_self('asdf-asdf-asdf-' . $i);
  httprl_request($url, $options);
}
// Execute requests.
$request = httprl_send_request();

// Echo out the results.
echo httprl_pr($request);
?>


Request 10 URLs in a non blocking manner with one httprl_request() call. These
URLs will all have the same options.

<?php
// Set the blocking mode.
$options = array(
  'method' => 'HEAD',
  'blocking' => FALSE,
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Queue up the requests.
$max = 10;
$urls = array();
for ($i=1; $i <= $max; $i++) {
  // Build URL to a page that doesn't exist.
  $urls[] = httprl_build_url_self('asdf-asdf-asdf-' . $i);
}
// Queue up the requests.
httprl_request($urls, $options);
// Execute requests.
$request = httprl_send_request();

// Echo out the results.
echo httprl_pr($request);
?>


Request 1000 URLs in a non blocking manner with one httprl_request() call. These
URLs will all have the same options. This will saturate the server and any
connections that couldn't be made will be dropped.

<?php
// Set the blocking mode.
$options = array(
  'method' => 'HEAD',
  'blocking' => FALSE,
  'domain_connections' => 1000,
  'global_connections' => 1000,
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Queue up the requests.
$max = 1000;
$urls = array();
for ($i=1; $i <= $max; $i++) {
  // Build URL to a page that doesn't exist.
  $urls[] = httprl_build_url_self('asdf-asdf-asdf-' . $i);
}
// Queue up the requests.
httprl_request($urls, $options);
// Execute requests.
$request = httprl_send_request();

// Echo out the results.
echo httprl_pr($request);
?>


Request 1000 URLs in a non blocking manner with one httprl_request() call. These
URLs will all have the same options. This will saturate the server. Usually all
1000 requests will eventually hit the server due to it waiting for the
connection to be established; `async_connect` is FALSE.

<?php
// Set the blocking mode.
$options = array(
  'method' => 'HEAD',
  'blocking' => FALSE,
  'async_connect' => FALSE,
  // domain_connections must be smaller than the servers max number of
  // clients.
  'domain_connections' => 32,
  'global_connections' => 1000,
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Queue up the requests.
$max = 1000;
$urls = array();
for ($i=1; $i <= $max; $i++) {
  // Build URL to a page that doesn't exist.
  $urls[] = httprl_build_url_self('asdf-asdf-asdf-' . $i);
}
// Queue up the requests.
httprl_request($urls, $options);
// Execute requests.
$request = httprl_send_request();

// Echo out the results.
echo httprl_pr($request);
?>


**HTTP Operations and Callbacks**

Use a callback in the event loop to do processing on the request. In this case
we are going to use httprl_pr() as the callback function.

<?php
// Setup return variable.
$x = '';
// Setup options array.
$options = array(
  'method' => 'HEAD',
  'callback' => array(
    array(
      'function' => 'httprl_pr',
      'return' => &$x,
    ),
  ),
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Build URL to point to front page of this server.
$url_front = httprl_build_url_self();
// Queue up the request.
httprl_request($url_front, $options);
// Execute request.
$request = httprl_send_request();

// Echo returned value from function callback.
echo $x;
?>


Use a background callback in the event loop to do processing on the request.
In this case we are going to use httprl_pr() as the callback function. A
background callback creates a new thread to run this function in.

<?php
// Setup return variable.
$x = '';
// Setup options array.
$options = array(
  'method' => 'HEAD',
  'background_callback' => array(
    array(
      'function' => 'httprl_pr',
      'return' => &$x,
    ),
  ),
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Build URL to point to front page of this server.
$url_front = httprl_build_url_self();
// Queue up the request.
httprl_request($url_front, $options);
// Execute request.
$request = httprl_send_request();

// Echo returned value from function callback.
echo $x;
?>


Use a background callback in the event loop to do processing on the request.
In this case we are going to use print_r() as the callback function. A
background callback creates a new thread to run this function in. The first
argument passed in is the request object, the FALSE tells print_r to echo out
instead of returning a value.

<?php
// Setup return & print variable.
$x = '';
$y = '';
// Setup options array.
$options = array(
  'method' => 'HEAD',
  'background_callback' => array(
    array(
      'function' => 'print_r',
      'return' => &$x,
      'printed' => &$y,
    ),
    FALSE,
  ),
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Build URL to point to front page of this server.
$url_front = httprl_build_url_self();
// Queue up the request.
httprl_request($url_front, $options);
// Execute request.
$request = httprl_send_request();

// Echo what was returned and printed from function callback.
echo $x . "<br />\n";
echo $y;
?>


**More Advanced HTTP Operations**

Hit 5 different URLs, Using at least 2 that has a status code of 200 and
erroring out the others that didn't return fast. Using the Range header so only
the first and last 128 bytes are returned.

<?php
// Array of URLs to get.
$urls = array(
  'http://google.com/',
  'http://bing.com/',
  'http://yahoo.com/',
  'http://www.duckduckgo.com/',
  'http://www.drupal.org/',
);

// Process list of URLs.
$options = array(
  'alter_all_streams_function' => 'need_two_good_results',
  'headers' => array('Range' => 'bytes=0-127,-128'),
);
// Queue up the requests.
httprl_request($urls, $options);

// Execute requests.
$requests = httprl_send_request();

// Print what was done.
echo httprl_pr($requests);

function need_two_good_results($id, &$responses) {
  static $counter = 0;
  foreach ($responses as $id => &$result) {
    // Skip if we got a 200 or 206.
    if ($result->code == 200 || $result->code == 206) {
      $counter += 1;
      continue;
    }
    if ($result->status == 'Done.') {
      continue;
    }

    if ($counter >= 2) {
      // Set the code to request was aborted.
      $result->code = HTTPRL_REQUEST_ABORTED;
      $result->error = 'Software caused connection abort.';
      // Set status to done and set timeout.
      $result->status = 'Done.';
      $result->options['timeout'] -= $result->running_time;

      // Close the file pointer and remove from the stream from the array.
      fclose($result->fp);
      unset($result->fp);
    }
  }
}
?>


Send 2 files in one field via a POST request.

<?php
// Set options.
$options = array(
  'method' => 'POST',
  'data' => array(
    'x' => 1,
    'y' => 2,
    'z' => 3,
    'files' => array(
      'core_js' => array(
        'misc/form.js',
        'misc/batch.js',
      ),
    ),
  ),
  'headers' => array(
    // Set the Host header to self.
    'Host' => $_SERVER['HTTP_HOST'],
  ),
);
// Send request to front page.
$url_front = httprl_build_url_self();

// Queue up the request.
httprl_request($url_front, $options);
// Execute request.
$request = httprl_send_request();
// Echo what was returned.
echo httprl_pr($request);
?>


Send out 8 requests. In this example we are going to stall the call to fread()
`'stall_fread' => TRUE,`. By doing this we can issue a bunch of requests, do
some other stuff and then get the results later on in the PHP process. A useful
example would be for ESI emulation. Issue a bunch of requests at the start of
the request, generate the main content and then add in the ESI-ed components at
the end of the request.

<?php
// Queue up the request.
$urls = array(
  'http://www.google.com/',
  'http://www.bing.com/',
  'http://www.yahoo.com/',
  'http://duckduckgo.com/',
  'http://drupal.org/',
  'http://drupal.org/robots.txt',
  'http://drupal.org/CHANGELOG.txt',
  'http://drupal.org/MAINTAINERS.txt',
);
$options = array(
  // Do fread in a second request.
  'stall_fread' => TRUE,
  'headers' => array(
    // Only grab the last 128 bytes of the request.
    'Range' => 'bytes=-128',
    // Accept Compression.
    'Accept-Encoding' => 'gzip, deflate',
  ),
  // Increase the read chunk size to 512KB.
  'chunk_size_read' => 524288,
  // Increase domain_connections to 4 (drupal.org).
  'domain_connections' => 4,
  // If we can't connect quick (0.5 seconds), bail out.
  'connect_timeout' => 0.5,
  'dns_timeout' => 0.5,
);
httprl_request($urls, $options);
// Execute request.
echo round(timer_read('page')/1000, 3) . " - Time taken to get requests ready.<br> \n";
$request = httprl_send_request();
echo strtoupper(var_export($request, TRUE)) . " - Output from first httprl_send_request() call<br> \n";

echo round(timer_read('page')/1000, 3) . " - Time taken to send out all fwrites().<br> \n";
sleep(2);
echo round(timer_read('page')/1000, 3) . " - Time taken for sleep(2).<br> \n";

$request = httprl_send_request();
echo round(timer_read('page')/1000, 3) . " - Time taken for all freads().<br> \n";
echo "Output from second httprl_send_request() below:<br> \n<br> \n";
echo httprl_pr($request);
?>


**Threading Examples**

Use 2 threads to load up 4 different nodes.

<?php
// Bail out here if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  return FALSE;
}

// List of nodes to load; 241-244.
$nodes = array(241 => '', 242 => '', 243 => '', 244 => '');
foreach ($nodes as $nid => &$node) {
  // Setup callback options array.
  $callback_options = array(
    array(
      'function' => 'node_load',
      'return' => &$node,
      // Setup options array.
      'options' => array(
        'domain_connections' => 2, // Only use 2 threads for this request.
      ),
    ),
    $nid,
  );
  // Queue up the request.
  httprl_queue_background_callback($callback_options);
}
// Execute request.
httprl_send_request();

// Echo what was returned.
echo httprl_pr($nodes);
?>



Load nodes 50-100 using httprl_batch_callback and node_load_multiple.

<?php
// List of nodes to load; 50-100.
$nids = range(50, 100);
// Run not parallel if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  $results = node_load_multiple($nids);
}
else {
  // Queue & Execute requests.
  $results = httprl_batch_callback('node_load_multiple', $nids);
}
// Echo what was returned.
echo httprl_pr($results);
?>



Load nodes 50-100 using httprl_batch_callback and node_load.

<?php
// List of nodes to load; 50-100.
$nids = range(50, 100);
// Run not parallel if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  // httprl_run_multiple does a foreach on $nids running every $value through
  // the given callback.
  $results = httprl_run_multiple('node_load', $nids);
}
else {
  // Set options.
  $options = array(
    'multiple_helper' => TRUE,
  );
  // Queue & Execute requests.
  $results = httprl_batch_callback('node_load', $nids, $options);
}
// Echo what was returned.
echo httprl_pr($results);
?>


Load nodes 50-100 using httprl_batch_callback and node_load_multiple as user 1.

<?php
// List of nodes to load; 50-100.
$nids = range(50, 100);
// Run not parallel if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  // Run node_load_multiple as user 1
  $current_account = $GLOBALS['user']->uid;
  $GLOBALS['user'] = user_load(1);
  $results = node_load_multiple($nids);
  // Set global user back.
  $GLOBALS['user'] = $current_account;
}
else {
  // Set options.
  $options = array(
    'context' => array(
      'uid' => 1,
    ),
  );
  // Queue & Execute requests.
  $results = httprl_batch_callback('node_load_multiple', $nids, $options);
}
// Echo what was returned.
echo httprl_pr($results);
?>



Run a function in the background. Notice that there is no return or printed key
in the callback options.

<?php
// Bail out here if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  return FALSE;
}

// Setup callback options array; call watchdog in the background.
$callback_options = array(
  array(
    'function' => 'watchdog',
  ),
  'httprl-test', 'background watchdog call done', array(), WATCHDOG_DEBUG,
);
// Queue up the request.
httprl_queue_background_callback($callback_options);

// Execute request.
httprl_send_request();
?>


Pass by reference example. Example is D7 only; pass by reference works in
D6 & D7.

<?php
// Code from system_rebuild_module_data().
$modules = _system_rebuild_module_data();
ksort($modules);

// Show first module before running system_get_files_database().
echo httprl_pr(current($modules));

// Bail out here if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  return FALSE;
}

$callback_options = array(
  array(
    'function' => 'system_get_files_database',
    'return' => '',
  ),
  &$modules, 'module'
);
httprl_queue_background_callback($callback_options);

// Execute requests.
httprl_send_request();

// Show first module after running system_get_files_database().
echo httprl_pr(current($modules));
?>


Get 2 results from 2 different queries at the hook_boot bootstrap level in D6.

<?php
// Run 2 queries and get the result.
$x = db_result(db_query_range("SELECT filename FROM {system} ORDER BY filename ASC", 0, 1));
$y = db_result(db_query_range("SELECT filename FROM {system} ORDER BY filename DESC", 0, 1));
echo $x . "<br \>\n" . $y . "<br \>\n";
unset($x, $y);


// Bail out here if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  return FALSE;
}

// Run above 2 queries and get the result via a background callback.
$args = array(
  // First query.
  array(
    'type' => 'function',
    'call' => 'db_query_range',
    'args' => array('SELECT filename FROM {system} ORDER BY filename ASC', 0, 1),
  ),
  array(
    'type' => 'function',
    'call' => 'db_result',
    'args' => array('last' => NULL),
    'return' => &$x,
  ),

  // Second Query.
  array(
    'type' => 'function',
    'call' => 'db_query_range',
    'args' => array('SELECT filename FROM {system} ORDER BY filename DESC', 0, 1),
  ),
  array(
    'type' => 'function',
    'call' => 'db_result',
    'args' => array('last' => NULL),
    'return' => &$y,
  ),
);
$callback_options = array(array('return' => ''), &$args);
// Queue up the request.
httprl_queue_background_callback($callback_options);
// Execute request.
httprl_send_request();

// Echo what was returned.
echo httprl_pr($x, $y);
?>


Get 2 results from 2 different queries at the hook_boot bootstrap level in D7.

<?php
$x = db_select('system', 's')
  ->fields('s', array('filename'))
  ->orderBy('filename', 'ASC')
  ->range(0, 1)
  ->execute()
  ->fetchField();
$y = db_select('system', 's')
  ->fields('s', array('filename'))
  ->orderBy('filename', 'DESC')
  ->range(0, 1)
  ->execute()
  ->fetchField();
echo $x . "<br \>\n" . $y . "<br \>\n";
unset($x, $y);


// Bail out here if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  return FALSE;
}

// Run above 2 queries and get the result via a background callback.
$args = array(
  // First query.
  array(
    'type' => 'function',
    'call' => 'db_select',
    'args' => array('system', 's',),
  ),
  array(
    'type' => 'method',
    'call' => 'fields',
    'args' => array('s', array('filename')),
  ),
  array(
    'type' => 'method',
    'call' => 'orderBy',
    'args' => array('filename', 'ASC'),
  ),
  array(
    'type' => 'method',
    'call' => 'range',
    'args' => array(0, 1),
  ),
  array(
    'type' => 'method',
    'call' => 'execute',
    'args' => array(),
  ),
  array(
    'type' => 'method',
    'call' => 'fetchField',
    'args' => array(),
    'return' => &$x,
  ),

  // Second Query.
  array(
    'type' => 'function',
    'call' => 'db_select',
    'args' => array('system', 's',),
  ),
  array(
    'type' => 'method',
    'call' => 'fields',
    'args' => array('s', array('filename')),
  ),
  array(
    'type' => 'method',
    'call' => 'orderBy',
    'args' => array('filename', 'DESC'),
  ),
  array(
    'type' => 'method',
    'call' => 'range',
    'args' => array(0, 1),
  ),
  array(
    'type' => 'method',
    'call' => 'execute',
    'args' => array(),
  ),
  array(
    'type' => 'method',
    'call' => 'fetchField',
    'args' => array(),
    'return' => &$y,
  ),
);
$callback_options = array(array('return' => ''), &$args);
// Queue up the request.
httprl_queue_background_callback($callback_options);
// Execute request.
httprl_send_request();

// Echo what was returned.
echo httprl_pr($x, $y);
?>


Run a cache clear at the DRUPAL_BOOTSTRAP_FULL level as the current user in a
non blocking background request.

<?php
// Normal way to do this.
drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
module_load_include('inc', 'system', 'system.admin');
system_clear_cache_submit();


// Bail out here if background callbacks are disabled.
if (!httprl_is_background_callback_capable()) {
  return FALSE;
}

// How to do it in a non blocking background request.
$args = array(
  array(
    'type' => 'function',
    'call' => 'drupal_bootstrap',
    'args' => array(DRUPAL_BOOTSTRAP_FULL),
  ),
  array(
    'type' => 'function',
    'call' => 'module_load_include',
    'args' => array('inc', 'system', 'system.admin'),
  ),
  array(
    'type' => 'function',
    'call' => 'system_clear_cache_submit',
    'args' => array('', ''),
  ),
  array(
    'type' => 'function',
    'call' => 'watchdog',
    'args' => array('httprl-test', 'background cache clear done', array(), WATCHDOG_DEBUG),
  ),
);

// Pass the current session to the sub request.
if (!empty($_COOKIE[session_name()])) {
  $options = array('headers' => array('Cookie' => session_name() . '=' . $_COOKIE[session_name()] . ';'));
}
else {
  $options = array();
}
$callback_options = array(array('options' => $options), &$args);

// Queue up the request.
httprl_queue_background_callback($callback_options);
// Execute request.
httprl_send_request();
?>


print 'My Text'; cut the connection by sending the data over the wire and do
processing in the background.

<?php
httprl_background_processing('My Text');
// Everything after this point does not affect page load time.
sleep(5);
echo 'You should not see this text';
?>
