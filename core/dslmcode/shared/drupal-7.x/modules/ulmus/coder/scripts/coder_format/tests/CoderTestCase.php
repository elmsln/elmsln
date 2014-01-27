<?php

/**
 * @file
 * Set of tests for the coder_format script.
 */

require_once drupal_get_path('module', 'coder') . '/scripts/coder_format/coder_format.inc';

class CoderTestCase extends DrupalTestCase {
  function assertFormat($input, $expect) {
    $result = coder_format_string_all($input);
    $this->assertIdentical($result, $input);
  }
}

