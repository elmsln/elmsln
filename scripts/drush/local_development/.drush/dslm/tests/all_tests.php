#!/usr/bin/env php
<?php
require_once('bootstrap.php');

/**
 * Simple test class to run all dslm tests
 */
class AllTests extends TestSuite {

    /**
     * Run all test in files ending in .test
     */
    function AllTests() {
        $this->TestSuite('All tests');

        // Load all tests from this directory
        $d = dir(dirname(__FILE__));
        while (FALSE !== ($entry = $d->read())) {
          if(preg_match('/\.test$/', $entry)) {
            $this->addFile($entry);
          }
        }
        $d->close();
    }
}
