<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class DrupalGetFilename {

  /**
   * @var SystemTable
   */
  private $systemTable;

  /**
   * @var ExampleModulesInterface
   */
  private $exampleModules;

  /**
   * @var string[][]
   */
  private $files = array();

  /**
   * @param SystemTable $systemTable
   * @param ExampleModulesInterface $exampleModules
   */
  function __construct(SystemTable $systemTable, ExampleModulesInterface $exampleModules) {
    $this->systemTable = $systemTable;
    $this->exampleModules = $exampleModules;
  }

  /**
   * Replicates drupal_get_filename(*, *, $filename)
   *
   * @param string $type
   * @param string $name
   * @param string $filename
   */
  function drupalSetFilename($type, $name, $filename) {
    if (file_exists($filename)) {
      $this->files[$type][$name] = $filename;
    }
  }

  /**
   * Replicates drupal_get_filename(*, *, NULL)
   *
   * @param string $type
   * @param string $name
   *
   * @return string|null
   */
  function drupalGetFilename($type, $name) {

    // Profiles are a special case: they have a fixed location and naming.
    if ($type == 'profile') {
      $profile_filename = "profiles/$name/$name.profile";
      $this->files[$type][$name] = file_exists($profile_filename)
        ? $profile_filename
        : FALSE;
    }

    // Look in runtime cache.
    if (isset($this->files[$type][$name])) {
      return $this->files[$type][$name];
    }

    // Load from the database.
    $file = $this->systemTable->moduleGetFilename($name);
    if (isset($file) && file_exists($file)) {
      $this->files[$type][$name] = $file;
      return $file;
    }

    // Fallback: Search the filesystem.
    $this->files[$type] = $this->exampleModules->discoverModuleFilenames($type);

    if (isset($this->files[$type][$name])) {
      return $this->files[$type][$name];
    }

    return NULL;
  }

  /**
   * @see drupal_get_path()
   *
   * @param string $type
   * @param string $name
   *
   * @return string|null
   */
  function drupalGetPath($type, $name) {
    return dirname($this->drupalGetFilename($type, $name));
  }
} 
