<?php


namespace Drupal\xautoload\Tests\Filesystem;


/**
 * Intercept calls to the filesystem, so we don't have to create fixture files.
 */
class StreamWrapper {

  //                                                        Static / Constructor
  // ---------------------------------------------------------------------------

  /**
   * @var VirtualFilesystem
   */
  protected static $filesystem;

  /**
   * @param string $protocol
   *
   * @return VirtualFilesystem
   *   A newly created virtual filesystem.
   *
   * @throws \Exception
   */
  static function register($protocol) {
    if (!stream_wrapper_register($protocol, 'Drupal\xautoload\Tests\Filesystem\StreamWrapper')) {
      throw new \Exception("Failed to register stream wrapper.");
    }
    self::$filesystem = new VirtualFilesystem();
    return self::$filesystem;
  }

  /**
   * Constructor is protected, to force people to use the register() method.
   */
  protected function __construct() {
    // Do nothing.
  }

  //                                                                  Properties
  // ---------------------------------------------------------------------------

  /**
   * @var string
   *   Path of the currently opened file or directory.
   */
  protected $path;

  /**
   * @var string
   *   Contents of the currently opened file.
   */
  protected $contents;

  /**
   * @var int
   *   Position within the currently open file.
   */
  protected $position;

  /**
   * @var string[]
   */
  protected $dirContents;

  //                                                      Stream wrapper methods
  // ---------------------------------------------------------------------------

  /**
   * @param string $path
   * @param int $flags
   *
   * @return array
   */
  function url_stat($path, $flags) {
    return self::$filesystem->getStat($path);
  }

  /**
   * @param $path
   * @param $mode
   * @param $options
   * @param $opened_path
   *
   * @return bool
   *
   * @throws \Exception
   */
  function stream_open($path, $mode, $options, &$opened_path) {

    $this->contents = self::$filesystem->getFileContents($path);

    $this->path = $path;
    $this->position = 0;

    return TRUE;
  }

  /**
   * @return array
   *   Stat for the currently open stream.
   * @throws \Exception
   */
  function stream_stat() {
    if (!isset($this->path)) {
      throw new \Exception("No file currently open.");
    }
    return self::$filesystem->getStat($this->path, FALSE);
  }

  /**
   * @param int $count
   *   Number of characters to read.
   *
   * @return string
   *   Snippet read from the file.
   */
  function stream_read($count) {
    $ret = substr($this->contents, $this->position, $count);
    $this->position += strlen($ret);

    return $ret;
  }

  /**
   * @return bool
   */
  function stream_eof() {
    return $this->position >= strlen($this->contents);
  }

  /**
   * @param string $path
   * @param int $options
   *
   * @return bool
   */
  function dir_opendir($path, $options) {
    $contents = self::$filesystem->getDirContents($path);
    if (FALSE === $contents) {
      return FALSE;
    }
    $this->path = $path;
    $this->dirContents = $contents;
    return TRUE;
  }

  /**
   * @return string
   */
  function dir_readdir() {
    $name = current($this->dirContents);
    next($this->dirContents);
    return $name;
  }
}