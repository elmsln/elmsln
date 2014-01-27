<?php
TEST: Variable assignments

--INPUT--
function db_status_report($phase) {
  $foo = 2;
  $t   = get_t();
  $baz = bay();

  $version = db_version();
}

--INPUT--
class CoderTestFile extends SimpleExpectation {
  private $expected;

  /** Filename of test */
  var $filename;

  // Filename of test
  var $filename;

  protected function describeException($exception) {
    return get_class($exception) .": ". $exception->getMessage();
  }
}

