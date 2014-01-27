<?php

/**
 * @file
 * Functions used to run a function in the background.
 */

/**
 * Menu Callback; run given function.
 */
function httprl_async_page() {
  // Exit if
  //  The master_key is not set.
  //  The temp_key is not set.
  //  The temp_key does not start with httprl_.
  //  The master_key does not match the md5 of drupal_get_private_key().
  if (   empty($_POST['master_key'])
      || empty($_POST['temp_key'])
      || strpos($_POST['temp_key'], 'httprl_') !== 0
        ) {
    httprl_fast403();
  }

  // Get the private key.
  $private_key = httprl_drupal_get_private_key();

  // Exit if the master_key does not match the md5 of $private_key.
  if (   empty($private_key)
      || $_POST['master_key'] != hash('sha512', $private_key)
        ) {
    httprl_fast403();
  }

  // Exit if the temp_key does not match a lock that has been taken.
  // Wait up to 2.5 seconds for the lock to propagate out.
  $tries = 0;
  while (lock_may_be_available($_POST['temp_key'])) {
    $tries++;
    if ($tries > 5) {
      httprl_fast403();
    }
    // Sleep for 500 miliseconds.
    usleep(500000);
  }

  // If request was a non blocking one, cut the connection right here.
  if (empty($_POST['mode']) && !empty($_POST['context']['session'])) {
    httprl_background_processing('httprl async function callback running', FALSE);
  }

  // Release the lock.
  httprl_lock_release($_POST['temp_key']);

  // Set time limit.
  if (isset($_POST['php_timeout']) && is_numeric($_POST['php_timeout'])) {
    // Copy of drupal_set_time_limit().
    if (function_exists('set_time_limit')) {
      @set_time_limit($_POST['php_timeout']);
    }
  }

  // Set context.
  if (!empty($_POST['context']) && is_array($_POST['context'])) {
    if (!empty($_POST['context']['uid'])) {
      httprl_set_user($_POST['context']['uid']);
    }
    if (!empty($_POST['context']['q'])) {
      httprl_set_q($_POST['context']['q']);
    }
  }

  // Extract Data.
  // Follow rfc4648 for base64url
  // @see http://tools.ietf.org/html/rfc4648#page-7
  $args = unserialize(base64_decode(strtr($_POST['args'], array('-' => '+', '_' => '/'))));

  // Run the function.
  if (!empty($_POST['function'])) {
    $data = httprl_run_function($_POST['function'], $args);
  }
  // Run an array of functions.
  else {
    $args = current($args);
    $data = httprl_run_array($args);
  }

  // Return data to caller.
  if (!empty($_POST['mode']) && isset($data)) {
    header('Content-Type: application/x-www-form-urlencoded');
    // Follow rfc4648 for base64url
    // @see http://tools.ietf.org/html/rfc4648#page-7
    echo http_build_query(array(0 => strtr(base64_encode(serialize($data)), array('+' => '-', '/' => '_'))), '', '&');
  }

  // Exit Script.
  httprl_call_exit();
}
