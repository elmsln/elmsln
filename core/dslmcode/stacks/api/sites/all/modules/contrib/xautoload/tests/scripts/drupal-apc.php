<?php
/**
 * @file
 *
 * File to test bootstrap with APC.
 */

if (!extension_loaded('apc') || !function_exists('apc_store')) {
  print "APC not available. Aborting.\n";
  return;
}

require_once dirname(__DIR__) . '/bootstrap.php';

# $filesystem = StreamWrapper::register('test');

