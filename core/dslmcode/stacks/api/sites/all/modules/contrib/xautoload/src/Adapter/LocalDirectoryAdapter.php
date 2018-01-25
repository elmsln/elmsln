<?php

namespace Drupal\xautoload\Adapter;

use Drupal\xautoload\Discovery\ComposerDir;
use Drupal\xautoload\Discovery\ComposerJson;

/**
 * An instance of this class is passed around to implementations of
 * hook_xautoload(). It acts as a wrapper around the ClassFinder, to register
 * stuff.
 */
class LocalDirectoryAdapter implements ClassFinderAdapterInterface {

  /**
   * @var string
   */
  protected $localDirectory;

  /**
   * @var ClassFinderAdapter
   */
  protected $master;

  /**
   * @param ClassFinderAdapter $adapter
   *   The class finder object.
   * @param string $localDirectory
   */
  function __construct(ClassFinderAdapter $adapter, $localDirectory) {
    // parent::__construct($adapter->finder, $adapter->getClassmapGenerator());
    $this->master = $adapter;
    $this->localDirectory = strlen($localDirectory)
      ? rtrim($localDirectory, '/') . '/'
      : '';
  }

  /**
   * Returns an adapter object that is not relative to a local directory.
   *
   * @return ClassFinderAdapter
   */
  function absolute() {
    return $this->master;
  }

  //                                                                   Discovery
  // ---------------------------------------------------------------------------

  /**
   * Adds source paths for classmap discovery.
   *
   * The classmap for each source will be cached between requests.
   * A "clear all caches" will trigger a rescan.
   *
   * @param string[] $paths
   *   File paths or wildcard paths for class discovery.
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addClassmapSources($paths, $relative = TRUE) {
    $relative && $this->prependToPaths($paths);
    $this->master->addClassmapSources($paths);
  }

  //                                                              Composer tools
  // ---------------------------------------------------------------------------

  /**
   * Scans a composer.json file provided by a Composer package.
   *
   * @param string $file
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   *
   * @throws \Exception
   */
  function composerJson($file, $relative = TRUE) {
    $relative && $file = $this->localDirectory . $file;
    $json = ComposerJson::createFromFile($file);
    $json->writeToAdapter($this->master);
  }

  /**
   * Scans a directory containing Composer-generated autoload files.
   *
   * @param string $dir
   *   Directory to look for Composer-generated files. Typically this is the
   *   ../vendor/composer dir.
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function composerDir($dir, $relative = TRUE) {
    $relative && $dir = $this->localDirectory . $dir;
    $dir = ComposerDir::create($dir);
    $dir->writeToAdapter($this->master);
  }

  //                                                      multiple PSR-0 / PSR-4
  // ---------------------------------------------------------------------------

  /**
   * Adds multiple PSR-0 prefixes.
   *
   * @param array $prefixes
   *   Each array key is a PSR-0 prefix, e.g. "Acme\\FooPackage\\".
   *   Each array value is either a PSR-0 base directory or an array of PSR-0
   *   base directories.
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addMultiplePsr0(array $prefixes, $relative = TRUE) {
    $relative && $this->prependMultiple($prefixes);
    $this->master->addMultiplePsr0($prefixes);
  }

  /**
   * Adds multiple PSR-4 namespaces.
   *
   * @param array $map
   *   Each array key is a namespace, e.g. "Acme\\FooPackage\\".
   *   Each array value is either a PSR-4 base directory or an array of PSR-4
   *   base directories.
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addMultiplePsr4(array $map, $relative = TRUE) {
    $relative && $this->prependMultiple($map);
    $this->master->addMultiplePsr4($map);
  }

  //                                                        Composer ClassLoader
  // ---------------------------------------------------------------------------

  /**
   * Registers an array ("map") of classes to file paths.
   *
   * @param array $classMap
   *   The map of classes to file paths.
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addClassMap(array $classMap, $relative = TRUE) {
    $relative && $this->prependToPaths($classMap);
    $this->master->addClassMap($classMap);
  }

  /**
   * Adds a PSR-0 style prefix. Alias for ->addPsr0().
   *
   * @param string $prefix
   * @param string|\string[] $paths
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function add($prefix, $paths, $relative = TRUE) {
    $relative && $this->prependToPaths($paths);
    $this->master->add($prefix, $paths);
  }

  /**
   * Adds a PSR-0 style prefix. Alias for ->add().
   *
   * @param string $prefix
   * @param string|\string[] $paths
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addPsr0($prefix, $paths, $relative = TRUE) {
    $relative && $this->prependToPaths($paths);
    $this->master->add($prefix, $paths);
  }

  /**
   * Adds a PSR-4 style namespace.
   *
   * @param string $prefix
   * @param string|\string[] $paths
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addPsr4($prefix, $paths, $relative = TRUE) {
    $relative && $this->prependToPaths($paths);
    $this->master->addPsr4($prefix, $paths);
  }

  //                                                      More convenience stuff
  // ---------------------------------------------------------------------------

  /**
   * Adds a PSR-0 style namespace.
   *
   * This will assume that we are really dealing with a namespace, even if it
   * has no '\\' included.
   *
   * @param string $prefix
   * @param string|\string[] $paths
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addNamespacePsr0($prefix, $paths, $relative = TRUE) {
    $relative && $this->prependToPaths($paths);
    $this->master->addNamespacePsr0($prefix, $paths);
  }

  /**
   * Adds a PEAR-like prefix.
   *
   * This will assume with no further checks that $prefix contains no namespace
   * separator.
   *
   * @param string $prefix
   *   The prefix, e.g. 'Acme_FooPackage_'
   * @param string|string[] $paths
   *   An array of paths, or one specific path.
   *   E.g. 'lib' for $relative = TRUE,
   *   or 'sites/all/libraries/AcmeFooPackage/lib' for $relative = FALSE.
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addPear($prefix, $paths, $relative = TRUE) {
    $relative && $this->prependToPaths($paths);
    $this->master->addPear($prefix, $paths);
  }

  /**
   * Adds a prefix similar to PEAR, but with flat directories.
   *
   * This will assume with no further checks that $prefix contains no namespace
   * separator.
   *
   * @param string $prefix
   *   The prefix, e.g. 'Acme_FooPackage_'
   * @param string|string[] $paths
   *   An array of paths, or one specific path.
   *   E.g. 'lib' for $relative = TRUE,
   *   or 'sites/all/libraries/AcmeFooPackage/lib' for $relative = FALSE.
   * @param bool $relative
   *   If TRUE, the paths will be relative to $this->localDirectory.
   */
  function addPearFlat($prefix, $paths, $relative = TRUE) {
    $relative && $this->prependToPaths($paths);
    $this->master->addPearFlat($prefix, $paths);
  }

  //                                                      Relative path handling
  // ---------------------------------------------------------------------------

  /**
   * Prepends $this->localDirectory to a number of paths.
   *
   * @param array $map
   */
  protected function prependMultiple(array &$map) {
    foreach ($map as &$paths) {
      $paths = (array) $paths;
      foreach ($paths as &$path) {
        $path = $this->localDirectory . $path;
      }
    }
  }

  /**
   * Prepends $this->localDirectory to a number of paths.
   *
   * @param string|string[] &$paths
   */
  protected function prependToPaths(&$paths) {
    if (!is_array($paths)) {
      $paths = $this->localDirectory . $paths;
    }
    else {
      foreach ($paths as &$path) {
        $path = $this->localDirectory . $path;
      }
    }
  }
}
