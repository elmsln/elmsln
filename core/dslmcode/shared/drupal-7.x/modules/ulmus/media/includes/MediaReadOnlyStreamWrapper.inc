<?php

/**
 * @file
 * Implements a base class for Resource Stream Wrappers.
 */

/**
 * A base class for Resource Stream Wrappers.
 *
 * This class provides a complete stream wrapper implementation. It passes
 * incoming  URL's through an interpolation method then recursively calls
 * the invoking PHP filesystem function.
 *
 * MediaReadOnlyStreamWrapper implementations need to override at least the
 * interpolateUrl method to rewrite the URL before is it passed back into the
 * calling function.
 */
abstract class MediaReadOnlyStreamWrapper implements DrupalStreamWrapperInterface {
  protected $parameters = array();
  protected $base_url = NULL;
  private $_DEBUG_MODE = NULL;

  /**
   * Utility function to return paramenters.
   */
  public function get_parameters() {
    return $this->parameters;
  }

  // As part of the inode protection mode returned by stat(), identifies the
  // file as a regular file, as opposed to a directory, symbolic link, or other
  // type of "file".
  // @see http://linux.die.net/man/2/stat
  const S_IFREG = 0100000;

  /**
   * Template for stat calls.
   *
   * All elements must be initialized.
   */
  protected $_stat = array(
    0 => 0, // Device number
    'dev' => 0,
    1 => 0, // Inode number
    'ino' => 0,
    // Inode protection mode. file_unmanaged_delete() requires is_file() to
    // return TRUE.
    2 => self::S_IFREG,
    'mode' => self::S_IFREG,
    3 => 0, // Number of links.
    'nlink' => 0,
    4 => 0, // Userid of owner.
    'uid' => 0,
    5 => 0, // Groupid of owner.
    'gid' => 0,
    6 => -1, // Device type, if inode device *
    'rdev' => -1,
    7 => 0, // Size in bytes.
    'size' => 0,
    8 => 0, // Time of last access (Unix timestamp).
    'atime' => 0,
    9 => 0, // Time of last modification (Unix timestamp).
    'mtime' => 0,
    10 => 0, // Time of last inode change (Unix timestamp).
    'ctime' => 0,
    11 => -1, // Blocksize of filesystem IO.
    'blksize' => -1,
    12 => -1, // Number of blocks allocated.
    'blocks' => -1,
  );

  /**
   * Handles parameters on the URL string.
   */
  public function interpolateUrl() {
    if ($parameters = $this->get_parameters()) {
      return $this->base_url . '?' . http_build_query($parameters);
    }
  }

  /**
   * Returns a web accessible URL for the resource.
   *
   * This function should return a URL that can be embedded in a web page
   * and accessed from a browser. For example, the external URL of
   * "youtube://xIpLd0WQKCY" might be
   * "http://www.youtube.com/watch?v=xIpLd0WQKCY".
   *
   * @return string
   *   Returns a string containing a web accessible URL for the resource.
   */
  public function getExternalUrl() {
    return $this->interpolateUrl();
  }

  /**
   * Base implementation of getMimeType().
   */
  public static function getMimeType($uri, $mapping = NULL) {
    return 'application/octet-stream';
  }

  /**
   * Base implementation of realpath().
   */
  public function realpath() {
    return $this->getExternalUrl();
  }

  /**
   * Stream context resource.
   *
   * @var Resource
   */
  public $context;

  /**
   * A generic resource handle.
   *
   * @var Resource
   */
  public $handle = NULL;

  /**
   * Instance URI (stream).
   *
   * A stream is referenced as "scheme://target".
   *
   * @var String
   */
  protected $uri;

  /**
   * Base implementation of setUri().
   */
  public function setUri($uri) {
    $this->uri = $uri;
    $this->parameters = $this->_parse_url($uri);
  }

  /**
   * Base implementation of getUri().
   */
  public function getUri() {
    return $this->uri;
  }

  /**
   * Report an error.
   *
   * @param string $message
   *   The untranslated string to report.
   * @param array $options
   *   An optional array of options to send to t().
   * @param bool $display
   *   If TRUE, then we display the error to the user.
   *
   * @return bool
   *   We return FALSE, since we sometimes pass that back from the reporting
   *   function.
   */
  private function _report_error($message, $options = array(), $display = FALSE) {
    watchdog('resource', $message, $options, WATCHDOG_ERROR);
    if ($display) {
      drupal_set_message(t($message, $options), 'error');
    }
    return FALSE;
  }

  /**
   * Sets the debug mode.
   */
  private function _debug($message, $type = 'status') {
    if ($this->_DEBUG_MODE) {
      drupal_set_message($message, $type);
    }
  }

  /**
   * Returns an array of any parameters stored in the URL's path.
   *
   * @param string $url
   *   The URL to parse, such as youtube://v/[video-code]/t/[tags+more-tags].
   *
   * @return array
   *   An associative array of all the parameters in the path,
   *   or FALSE if the $url is ill-formed.
   */
  protected function _parse_url($url) {
    $path = explode('://', $url);
    $parts = explode('/', $path[1]);
    $params = array();
    $count = 0;
    $total = count($parts);
    if (!$total || ($total % 2)) {
      // If we have no parts, or an odd number of parts, it's malformed.
      return FALSE;
    }
    while ($count < $total) {
      // We iterate count for each step of the assignment to keep us honest.
      $params[$parts[$count++]] = $parts[$count++];
    }
    return $params;
  }

  /**
   * Support for fopen(), file_get_contents(), file_put_contents() etc.
   *
   * @param string $url
   *   A string containing the path to the file to open.
   * @param string $mode
   *   The file mode ("r", "wb" etc.).
   * @param bitmask $options
   *   A bit mask of STREAM_USE_PATH and STREAM_REPORT_ERRORS.
   * @param string &$opened_url
   *   A string containing the path actually opened.
   *
   * @return bool
   *   TRUE if file was opened successfully.
   */
  public function stream_open($url, $mode, $options, &$opened_url) {
    $this->_debug(t('Stream open: %url', array('%url' => $url)));

    // We only handle Read-Only mode by default.
    if ($mode != 'r' && $mode != 'rb') {
      return $this->_report_error('Attempted to open %url as mode: %mode.', array('%url' => $url, '%mode' => $mode), ($options & STREAM_REPORT_ERRORS));
    }

    // We parse a URL as youtube://v/dsyiufo34/t/cats+dogs to store
    // the relevant code(s) in our private array of parameters.
    $this->parameters = $this->_parse_url($url);

    if ($this->parameters === FALSE) {
      return $this->_report_error('Attempted to parse an ill-formed url: %url.', array('%url' => $url), ($options & STREAM_REPORT_ERRORS));
    }

    if ((bool) $this->parameters && ($options & STREAM_USE_PATH)) {
      $opened_url = $url;
    }

    $this->_debug(t('Stream opened: %parameters', array('%parameters' => print_r($this->parameters, TRUE))));

    return (bool) $this->parameters;
  }

  /**
   * Undocumented PHP stream wrapper method.
   */
  function stream_lock($operation) {
    return FALSE;
  }

  /**
   * Support for fread(), file_get_contents() etc.
   *
   * @param int $count
   *   Maximum number of bytes to be read.
   *
   * @return bool
   *   The string that was read, or FALSE in case of an error.
   */
  public function stream_read($count) {
    return FALSE;
  }

  /**
   * Support for fwrite(), file_put_contents() etc.
   *
   * Since this is a read only stream wrapper this always returns false.
   *
   * @param string $data
   *   The string to be written.
   *
   * @return bool
   *   Returns FALSE.
   */
  public function stream_write($data) {
    return FALSE;
  }

  /**
   * Support for feof().
   *
   * @return bool
   *   TRUE if end-of-file has been reached.
   */
  public function stream_eof() {
    return FALSE;
  }

  /**
   * Support for fseek().
   *
   * @todo document why this returns false.
   *
   * @param int $offset
   *   The byte offset to got to.
   * @param string $whence
   *   SEEK_SET, SEEK_CUR, or SEEK_END.
   *
   * @return bool
   *   TRUE on success
   */
  public function stream_seek($offset, $whence) {
    return FALSE;
  }

  /**
   * Support for fflush().
   *
   * @todo document why this returns false.
   *
   * @return bool
   *   TRUE if data was successfully stored (or there was no data to store).
   */
  public function stream_flush() {
    return FALSE;
  }

  /**
   * Support for ftell().
   *
   * @todo document why this returns false.
   *
   * @return bool
   *   The current offset in bytes from the beginning of file.
   */
  public function stream_tell() {
    return FALSE;
  }

  /**
   * Support for fstat().
   *
   * @return array
   *   An array with file status, or FALSE in case of an error - see fstat()
   *   for a description of this array.
   */
  public function stream_stat() {
    return $this->_stat;
  }

  /**
   * Support for fclose().
   *
   * @todo document why this returns TRUE.
   *
   * @return bool
   *   TRUE if stream was successfully closed.
   */
  public function stream_close() {
    return TRUE;
  }

  /**
   * Support for stat().
   *
   * @param string $url
   *   A string containing the url to get information about.
   * @param bitmask $flags
   *   A bit mask of STREAM_URL_STAT_LINK and STREAM_URL_STAT_QUIET.
   *
   * @return array
   *   An array with file status, or FALSE in case of an error - see fstat()
   *   for a description of this array.
   */
  public function url_stat($url, $flags) {
    return $this->stream_stat();
  }

  /**
   * Support for opendir().
   *
   * @param string $url
   *   A string containing the url to the directory to open.
   * @param int $options
   *   Whether or not to enforce safe_mode (0x04).
   *
   * @return bool
   *   TRUE on success.
   */
  public function dir_opendir($url, $options) {
    return FALSE;
  }

  /**
   * Support for readdir().
   *
   * @return bool
   *   The next filename, or FALSE if there are no more files in the directory.
   */
  public function dir_readdir() {
    return FALSE;
  }

  /**
   * Support for rewinddir().
   *
   * @return bool
   *   TRUE on success.
   */
  public function dir_rewinddir() {
    return FALSE;
  }

  /**
   * Support for closedir().
   *
   * @return bool
   *   TRUE on success.
   */
  public function dir_closedir() {
    return FALSE;
  }

  /**
   * Undocumented.
   *
   * @todo document.
   */
  public function getDirectoryPath() {
    return '';
  }

  /**
   * DrupalStreamWrapperInterface requires that these methods be implemented,
   * but none of them apply to a read-only stream wrapper. On failure they
   * are expected to return FALSE.
   */

  /**
   * Implements DrupalStreamWrapperInterface::unlink().
   */
  public function unlink($uri) {
    // Although the remote file itself can't be deleted, return TRUE so that
    // file_delete() can remove the file record from the Drupal database.
    return TRUE;
  }

  /**
   * Implements DrupalStreamWrapperInterface::rename().
   */
  public function rename($from_uri, $to_uri) {
    return FALSE;
  }

  /**
   * Implements DrupalStreamWrapperInterface::mkdir().
   */
  public function mkdir($uri, $mode, $options) {
    return FALSE;
  }

  /**
   * Implements DrupalStreamWrapperInterface::rmdir().
   */
  public function rmdir($uri, $options) {
    return FALSE;
  }

  /**
   * Implements DrupalStreamWrapperInterface::chmod().
   */
  public function chmod($mode) {
    return FALSE;
  }

  /**
   * Implements DrupalStreamWrapperInterface::dirname().
   */
  public function dirname($uri = NULL) {
    return FALSE;
  }

}
