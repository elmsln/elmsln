<?php

/**
 * @file
 * Set of tests for the coder_format script.
 */

/**
 * Represents coder test file for full coder_format_string_all() tests.
 */
class CoderTestFile extends SimpleExpectation {
  /* Filename of test */
  var $filename;

  /* Test name */
  var $test;

  /* PHP to be parsed */
  var $input = array();

  /* Expected output */
  var $expect = array();

  /* Actual result */
  var $actual = array();

  /* Whether or not <?php and CVS Id should be added */
  var $full = 0;

  /* Whether or not a specific test should be the only one tested */
  var $only = array();

  /**
   * Loads this class from a file.
   *
   * @param string $filename
   *   A filename to load.
   */
  function load($filename) {
    $this->filename = $filename;
    $fh             = fopen($filename, 'r');
    $state          = '';
    $unit           = 0;

    while (($line = fgets($fh)) !== FALSE) {
      // Normalize newlines.
      $line = rtrim($line, "\n\r");
      // Detect INPUT and EXPECT sections.
      if (substr($line, 0, 2) == '--') {
        $state = trim($line, ' -');

        // If a new INPUT section begins, start a new unit.
        if ($state == 'INPUT') {
          // If previous section has been marked with the keyword 'ONLY', break
          // immediately to process only the marked section.
          if ($this->only[$unit]) {
            break;
          }
          $unit++;
        }
        continue;
      }
      // Process other keywords only outside of INPUT and EXPECT sections.
      if (!$state) {
        list($keyword, $line) = explode(': ', $line, 2);
      }
      // Assign previous keyword, if there is no new one.
      else {
        $keyword = $state;
      }
      switch ($keyword) {
        case 'TEST':
          $this->test = $line;
          break;

        case 'FULL':
          $this->full = (bool)$line;
          break;

        case 'INPUT':
          $this->input[$unit] .= $line . "\n";
          break;

        case 'EXPECT':
          $this->expect[$unit] .= $line . "\n";
          break;

        case 'ONLY':
          $this->only[$unit] = TRUE;
          break;
      }
    }
    fclose($fh);
    foreach (range(1, $unit) as $unit) {
      // If no EXPECTed code was defined, INPUT is expected.
      if (!isset($this->expect[$unit])) {
        $this->expect[$unit] = $this->input[$unit];
      }
      // If FULL was *not* defined, add a PHP header to contents.
      if (!$this->full) {
        $prepend             = "<?php\n// $" . "Id$\n\n";
        $this->input[$unit]  = $prepend . rtrim($this->input[$unit], "\n") . "\n\n";
        $this->expect[$unit] = $prepend . rtrim($this->expect[$unit], "\n") . "\n\n";
      }
    }
    if (!empty($this->only[$unit])) {
      $this->input = array($this->input[$unit]);
      $this->expect = array($this->expect[$unit]);
    }
  }

  /**
   * Implements SimpleExpectation::test().
   *
   * @param $filename Filename of test file to test.
   */
  function test($filename = FALSE) {
    if ($filename) {
      $this->load($filename);
    }

    // Perform test.
    // Test passes until proven invalid.
    $valid = TRUE;
    foreach ($this->input as $unit => $content) {
      // Parse input and store results.
      $this->actual[$unit] = coder_format_string_all($this->input[$unit]);

      // Let this test fail, if a unit fails.
      if ($this->expect[$unit] !== $this->actual[$unit]) {
        $valid = FALSE;
      }
    }

    return $valid;
  }

  /**
   * Implements SimpleExpectation::testMessage().
   */
  function testMessage() {
    $message = $this->test . ' test in ' . htmlspecialchars(basename($this->filename));
    return $message;
  }

  /**
   * Renders the test with an HTML diff table.
   */
  function render() {
    drupal_add_css(drupal_get_path('module', 'coder') . '/scripts/coder_format/tests/coder-diff.css', 'module', 'all', FALSE);

    foreach ($this->input as $unit => $content) {
      // Do not output passed units.
      if ($this->expect[$unit] === $this->actual[$unit]) {
        continue;
      }

      $diff     = new Text_Diff('auto', array(explode("\n", $this->expect[$unit]), explode("\n", $this->actual[$unit])));
      $renderer = new Text_Diff_Renderer_parallel($this->test . ' test in ' . htmlspecialchars(basename($this->filename)));

      $message .= $renderer->render($diff);
    }

    return $message;
  }
}

/**
 * Parallel diff renderer for HTML tables with original text on left,
 * new text on right, and changed text highlighted with appropriate classes.
 */
class Text_Diff_Renderer_parallel extends Text_Diff_Renderer {
  /* String header for left column */
  var $original = 'Expected';

  /* String header for right column */
  var $final = 'Actual';

  // These are big to ensure entire string is output.
  var $_leading_context_lines  = 10000;
  var $_trailing_context_lines = 10000;
  var $title;

  function Text_Diff_Renderer_parallel($title) {
    $this->title = $title;
  }

  function _blockHeader() {}

  function _startDiff() {
    return '<table class="diff"><thead><tr><th colspan="2">' . $this->title . '</th></tr><tr><th>' . $this->original . '</th><th>' . $this->final . '</th></tr></thead><tbody>';
  }

  function _endDiff() {
    return '</tbody></table>';
  }

  function _context($lines) {
    return '<tr><td><pre>' . $this->_renderLines($lines) . '</pre></td>
          <td><pre>' . $this->_renderLines($lines) . '</pre></td></tr>';
  }

  function _added($lines) {
    return '<tr><td>&nbsp;</td><td class="added"><pre>' . $this->_renderLines($lines) . '</pre></td></tr>';
  }

  function _deleted($lines) {
    return '<tr><td class="deleted"><pre>' . $this->_renderLines($lines) . '</pre></td><td>&nbsp;</td></tr>';
  }

  function _changed($orig, $final) {
    return '<tr class="changed"><td><pre>' . $this->_renderLines($orig) . '</pre></td>
        <td><pre>' . $this->_renderLines($final) . '</pre></td></tr>';
  }

  function _renderLines($lines) {
    return str_replace("\n", "<strong>&para;</strong>\n", htmlspecialchars(implode("\n", $lines) . "\n"));
  }

}

