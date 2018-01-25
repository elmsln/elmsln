<?php


namespace Drupal\xautoload\Tests\Filesystem;


use Drupal\xautoload\Util;

class VirtualFilesystem {

  /**
   * @var VirtualFilesystem[]
   */
  protected static $instances = array();

  /**
   * Called from generated PHP included over a stream wrapper.
   *
   * @param string $instance_key
   * @param string $file
   */
  static function reportFileIncluded($instance_key, $file) {
    self::$instances[$instance_key]->reportedOperations[] = $file . ' - include';
  }

  /**
   * @var string
   */
  protected $instanceKey;

  /**
   * @var string[]
   */
  protected $knownPaths = array();

  /**
   * @var string[]
   */
  protected $reportedOperations = array();

  const NOTHING = FALSE;
  const DIR = '(dir)';
  const FILE = '(file)';

  function __construct() {
    $this->instanceKey = Util::randomString();
    self::$instances[$this->instanceKey] = $this;
  }

  /**
   * @return array[]
   */
  function getReportedOperations() {
    return $this->reportedOperations;
  }

  /**
   * Delete all reported operations and start fresh.
   */
  function resetReportedOperations() {
    $this->reportedOperations = array();
  }

  /**
   * @param string $file
   * @param string $class
   * @throws \Exception
   */
  function addClass($file, $class) {
    $this->addKnownFile($file);
    if (self::FILE !== ($existing = $this->knownPaths[$file])) {
      throw new \Exception("A non-empty file already exists at '$file'. Cannot overwrite with class '$class'.");
    }
    $this->knownPaths[$file] = $class;
  }

  /**
   * @param string $file
   * @param string $php
   *   File contents starting with '<?php'.
   * @param bool $overwrite
   *
   * @throws \Exception
   */
  function addPhpFile($file, $php, $overwrite = FALSE) {
    $this->addKnownFile($file);
    if (!$overwrite && self::FILE !== ($existing = $this->knownPaths[$file])) {
      throw new \Exception("A non-empty file already exists at '$file'. Cannot overwrite with PHP code.");
    }
    if (0 !== strpos($php, '<?php')) {
      throw new \Exception("PHP files must begin with '<?php'.");
    }
    $this->knownPaths[$file] = $php;
  }

  /**
   * @param string[] $files
   */
  function addKnownFiles(array $files) {
    foreach ($files as $file) {
      $this->addKnownFile($file);
    }
  }

  /**
   * @param string $file
   *
   * @throws \Exception
   */
  function addKnownFile($file) {
    if (!isset($this->knownPaths[$file])) {
      $this->knownPaths[$file] = self::FILE;
      $this->addKnownDir(dirname($file));
    }
    elseif (self::DIR === $this->knownPaths[$file]) {
      throw new \Exception("A directory already exists at '$file', cannot overwrite with a file.");
    }
  }

  /**
   * @param string $dir
   */
  function addKnownDir($dir) {
    if (FALSE === strpos($dir, '://')) {
      return;
    }
    if (!isset($this->knownPaths[$dir])) {
      // Need to set parents first.
      $this->addKnownDir(dirname($dir));
    }
    $this->knownPaths[$dir] = self::DIR;
  }

  /**
   * @param string $path
   * @return string|bool
   *   One of self::NOTHING, self::DIR, self::FILE, or a class name for a class
   *   that is supposed to be defined in the file.
   */
  function resolvePath($path) {
    if (isset($this->knownPaths[$path])) {
      return $this->knownPaths[$path];
    }
    else {
      return self::NOTHING;
    }
  }

  /**
   * @param string $dir
   * @return array|bool
   */
  function getDirContents($dir) {
    if (empty($this->knownPaths[$dir]) || self::DIR !== $this->knownPaths[$dir]) {
      return FALSE;
    }
    $pos = strlen($dir . '/');
    $contents = array('.', '..');
    foreach ($this->knownPaths as $path => $type) {
      if ($dir . '/' !== substr($path, 0, $pos)) {
        continue;
      }
      $name = substr($path, $pos);
      if (FALSE !== strpos($name, '/')) {
        // This is a deeper subdirectory.
        continue;
      }
      if ('' === $name) {
        continue;
      }
      $contents[] = $name;
    }
    return $contents;
  }

  /**
   * @param string $path
   * @param bool $report
   *
   * @return array
   */
  function getStat($path, $report = TRUE) {
    if ($report) {
      $this->reportedOperations[] = $path . ' - stat';
    }
    if (!isset($this->knownPaths[$path])) {
      // File does not exist.
      return FALSE;
    }
    elseif (self::DIR === $this->knownPaths[$path]) {
      return stat(__DIR__);
    }
    else {
      // Create a tmp file with the contents and get its stats.
      $contents = $this->getFileContents($path);
      $resource = tmpfile();
      fwrite($resource, $contents);
      $stat = fstat($resource);
      fclose($resource);
      return $stat;
    }
  }

  /**
   * @param $path
   *   The file path.
   *
   * @return string
   *   The file contents.
   *
   * @throws \Exception
   *   Exception thrown if there is no file at $path.
   */
  function getFileContents($path) {
    if (!isset($this->knownPaths[$path])) {
      // File does not exist.
      throw new \Exception("Assumed file '$path' does not exist.");
    }
    elseif (self::DIR === $this->knownPaths[$path]) {
      throw new \Exception("Assumed file '$path' is a directory.");
    }

    $instance_key_export = var_export($this->instanceKey, TRUE);
    $path_export = var_export($path, TRUE);
    if (self::FILE === $this->knownPaths[$path]) {
      // Empty PHP file..
      return <<<EOT
<?php
Drupal\\xautoload\\Tests\\Filesystem\\VirtualFilesystem::reportFileIncluded($instance_key_export, $path_export);

EOT;
    }

    if (0 === strpos($this->knownPaths[$path], '<?php')) {
      // PHP file.
      $php = substr($this->knownPaths[$path], 5);
      return <<<EOT
<?php
Drupal\\xautoload\\Tests\\Filesystem\\VirtualFilesystem::reportFileIncluded($instance_key_export, $path_export);
$php
EOT;
    }

    if (preg_match('#\s#', $this->knownPaths[$path])) {
      // File with arbitrary contents.
      return $this->knownPaths[$path];
    }

    // PHP file with class definition.
    $class = $this->knownPaths[$path];

    if (FALSE === ($pos = strrpos($class, '\\'))) {
      // Class without namespace.
      return <<<EOT
<?php
Drupal\\xautoload\\Tests\\Filesystem\\VirtualFilesystem::reportFileIncluded($instance_key_export, $path_export);
class $class {}

EOT;
    }

    // Class without namespace.
    $namespace = substr($class, 0, $pos);
    $classname = substr($class, $pos + 1);
    return <<<EOT
<?php
namespace $namespace;
\\Drupal\\xautoload\\Tests\\Filesystem\\VirtualFilesystem::reportFileIncluded($instance_key_export, $path_export);
class $classname {}

EOT;
  }
} 
