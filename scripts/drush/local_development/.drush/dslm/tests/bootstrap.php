<?php
require_once('simpletest/autorun.php');
require_once('../lib/dslm.class.php');

/**
 * Check to make sure we have a DSLM_BASE environment variable set for the test
 */
if (!isset($_ENV['DSLM_BASE'])) {
  echo "You need to set the base in the DSLM_BASE environment variable to run these tests.\n";
  exit(1);
}
