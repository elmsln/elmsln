<?php
// $Id: DrupalStream.php,v 1.1.2.1 2011/01/01 21:43:47 hugowetterberg Exp $

/**
 * @file
 * Stream wrapper for php://input.
 *
 * Allow more than one module to access php://input at the same time, via the
 * drupal://input stream.
 *
 * For more information on the implementation refer to
 * http://php.net/streamwrapper
 */

/**
 * drupal://input Stream wrapper class.
 */
class DrupalStream {
  private static $tmpStream;
  private static $lastAccess;
  private $position = 0;
  /**
   * The current context, or NULL if no context was passed to the caller function.
   */
  public $context;

  /**
   * Handle the stream open event.
   */
  public function stream_open($path, $mode, $options, &$opened_path) {
    $url = parse_url($path);
    if ($url["host"] === 'input' && ($mode==='r' || $mode==='rb')) {
      if (!self::$tmpStream) {
        self::$tmpStream = $this->getTempStream();
        self::$lastAccess = $this;
      }
      return TRUE;
    }
    return FALSE;
  }

  /**
   * Read from the stream.
   *
   * @param int The number of characters to read from the stream.
   *
   * @return String the characters from the stream.
   */
  public function stream_read($count) {
    $this->consistencyCheck();
    $ret = fread(self::$tmpStream, $count);
    $this->position += strlen($ret);
    return $ret;
  }

  /**
   * Retrieve the current position of a stream.
   *
   * @return int The current position of the stream.
   */
  public function stream_tell() {
    return $this->position;
  }

  /**
   * Tests for end-of-file on a file pointer
   *
   * @return bool Has the end of the stream been reached?
   */
  public function stream_eof() {
    $this->consistencyCheck();
    return feof(self::$tmpStream);
  }

  /**
   * Seeks to specific location in a stream
   */
  public function stream_seek($offset, $whence=SEEK_SET) {
    $this->consistencyCheck();
    if (fseek(self::$tmpStream, $offset, $whence)) {
      switch ($whence) {
        case SEEK_SET:
          $this->position = $offset;
          break;
        case SEEK_CUR:
          $this->position += $offset;
          break;
        case SEEK_END:
          $this->position = ftell(self::$tmpStream);
          break;
      }
    }
    return FALSE;
  }

  /**
   * Ensures that two DrupalStream instances can operate on the
   * same temporary stream without affecting each other.
   *
   * @return void
   */
  private function consistencyCheck() {
    if (!(self::$lastAccess === $this)) {
      fseek(self::$tmpStream, $this->position, SEEK_SET);
      self::$lastAccess = $this;
    }
  }

  /**
   * Returns a php://temp stream handle that wraps the php://input stream.
   *
   * @return resource
   *  A stream resource.
   */
  private function getTempStream() {
    $handle = fopen("php://temp", "r+");
    $input = fopen("php://input", "r");
    if ($input) {
      while (!feof($input)) {
        $data = fread($input, 8192);
        fwrite($handle, $data);
      }
      fclose($input);
    }
    fseek($handle, 0, SEEK_SET);
    return $handle;
  }
}
