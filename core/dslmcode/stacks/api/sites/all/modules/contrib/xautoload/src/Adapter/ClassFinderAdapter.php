<?php


namespace Drupal\xautoload\Adapter;

use Drupal\xautoload\Discovery\ClassMapGenerator;
use Drupal\xautoload\Util;
use Drupal\xautoload\DirectoryBehavior\DefaultDirectoryBehavior;
use Drupal\xautoload\Discovery\ComposerDir;
use Drupal\xautoload\Discovery\ComposerJson;
use Drupal\xautoload\ClassFinder\GenericPrefixMap;
use Drupal\xautoload\DirectoryBehavior\Psr0DirectoryBehavior;
use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;
use Drupal\xautoload\Discovery\ClassMapGeneratorInterface;

/**
 * An instance of this class is passed around to implementations of
 * hook_xautoload(). It acts as a wrapper around the ClassFinder, to register
 * stuff.
 */
class ClassFinderAdapter implements ClassFinderAdapterInterface {

  /**
   * @var ExtendedClassFinderInterface
   */
  protected $finder;

  /**
   * @var GenericPrefixMap
   */
  protected $prefixMap;

  /**
   * @var GenericPrefixMap
   */
  protected $namespaceMap;

  /**
   * @var ClassMapGeneratorInterface
   */
  protected $classMapGenerator;

  /**
   * @param ExtendedClassFinderInterface $finder
   *
   * @return self
   */
  static function create($finder) {
    return new self($finder, new ClassMapGenerator());
  }

  /**
   * @param ExtendedClassFinderInterface $finder
   *   The class finder object.
   * @param ClassMapGeneratorInterface $classmap_generator
   */
  function __construct($finder, $classmap_generator) {
    $this->finder = $finder;
    $this->prefixMap = $finder->getPrefixMap();
    $this->namespaceMap = $finder->getNamespaceMap();
    $this->defaultBehavior = new DefaultDirectoryBehavior();
    $this->psr0Behavior = new Psr0DirectoryBehavior();
    $this->classMapGenerator = $classmap_generator;
  }

  /**
   * @return \Drupal\xautoload\ClassFinder\GenericPrefixMap
   */
  function getNamespaceMap() {
    return $this->namespaceMap;
  }

  /**
   * @return GenericPrefixMap
   */
  function getPrefixMap() {
    return $this->prefixMap;
  }

  /**
   * @return ClassMapGeneratorInterface
   */
  function getClassmapGenerator() {
    return $this->classMapGenerator;
  }

  /**
   * @return ClassMapGeneratorInterface
   */
  function getFinder() {
    return $this->finder;
  }

  //                                                                   Discovery
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function addClassmapSources($paths) {
    $map = $this->classMapGenerator->wildcardPathsToClassmap($paths);
    $this->addClassMap($map);
  }

  //                                                              Composer tools
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function composerJson($file) {
    $json = ComposerJson::createFromFile($file);
    $json->writeToAdapter($this);
  }

  /**
   * {@inheritdoc}
   */
  function composerDir($dir) {
    $dir = ComposerDir::create($dir);
    $dir->writeToAdapter($this);
  }

  //                                                      multiple PSR-0 / PSR-4
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function addMultiplePsr0(array $prefixes) {
    $namespace_map = array();
    $prefix_map = array();
    foreach ($prefixes as $prefix => $paths) {
      if (FALSE === strpos($prefix, '\\')) {
        $logical_base_path = Util::prefixLogicalPath($prefix);
        foreach ((array) $paths as $root_path) {
          $deep_path = strlen($root_path)
            ? rtrim($root_path, '/') . '/' . $logical_base_path
            : $logical_base_path;
          $prefix_map[$logical_base_path][$deep_path] = $this->defaultBehavior;
        }
      }
      $logical_base_path = Util::namespaceLogicalPath($prefix);
      foreach ((array) $paths as $root_path) {
        $deep_path = strlen($root_path)
          ? rtrim($root_path, '/') . '/' . $logical_base_path
          : $logical_base_path;
        $namespace_map[$logical_base_path][$deep_path] = $this->psr0Behavior;
      }
    }
    if (!empty($prefix_map)) {
      $this->prefixMap->registerDeepPaths($prefix_map);
    }
    $this->namespaceMap->registerDeepPaths($namespace_map);
  }

  /**
   * {@inheritdoc}
   */
  function addMultiplePsr4(array $map) {
    $namespace_map = array();
    foreach ($map as $namespace => $paths) {
      $logical_base_path = Util::namespaceLogicalPath($namespace);
      foreach ($paths as $root_path) {
        $deep_path = strlen($root_path)
          ? rtrim($root_path, '/') . '/'
          : '';
        $namespace_map[$logical_base_path][$deep_path] = $this->defaultBehavior;
      }
    }
    $this->namespaceMap->registerDeepPaths($namespace_map);
  }

  //                                                        Composer ClassLoader
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function addClassMap(array $classMap) {
    $this->finder->registerClasses($classMap);
  }

  /**
   * {@inheritdoc}
   */
  function add($prefix, $paths) {
    if (FALSE === strpos($prefix, '\\')) {
      // Due to the ambiguity of PSR-0, this could be either PEAR-like or namespaced.
      $logical_base_path = Util::prefixLogicalPath($prefix);
      foreach ((array) $paths as $root_path) {
        $deep_path = strlen($root_path)
          ? rtrim($root_path, '/') . '/' . $logical_base_path
          : $logical_base_path;
        $this->prefixMap->registerDeepPath(
          $logical_base_path,
          $deep_path,
          $this->defaultBehavior);
      }
    }
    // Namespaced PSR-0
    $logical_base_path = Util::namespaceLogicalPath($prefix);
    foreach ((array) $paths as $root_path) {
      $deep_path = strlen($root_path)
        ? rtrim($root_path, '/') . '/' . $logical_base_path
        : $logical_base_path;
      $this->namespaceMap->registerDeepPath(
        $logical_base_path,
        $deep_path,
        $this->psr0Behavior);
    }
  }

  /**
   * {@inheritdoc}
   */
  function addPsr0($prefix, $paths) {
    $this->add($prefix, $paths);
  }

  /**
   * {@inheritdoc}
   */
  function addPsr4($prefix, $paths) {
    // Namespaced PSR-4
    $logical_base_path = Util::namespaceLogicalPath($prefix);
    foreach ((array) $paths as $deep_path) {
      $deep_path = strlen($deep_path)
        ? rtrim($deep_path, '/') . '/'
        : '';
      $this->namespaceMap->registerDeepPath(
        $logical_base_path,
        $deep_path,
        $this->defaultBehavior);
    }
  }

  //                                                      More convenience stuff
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function addNamespacePsr0($prefix, $paths) {
    $logical_base_path = Util::namespaceLogicalPath($prefix);
    foreach ((array) $paths as $root_path) {
      $deep_path = strlen($root_path)
        ? rtrim($root_path, '/') . '/' . $logical_base_path
        : $logical_base_path;
      $this->namespaceMap->registerDeepPath(
        $logical_base_path,
        $deep_path,
        $this->psr0Behavior);
    }
  }

  /**
   * {@inheritdoc}
   */
  function addPear($prefix, $paths) {
    $logical_base_path = Util::prefixLogicalPath($prefix);
    foreach ((array) $paths as $root_path) {
      $deep_path = strlen($root_path)
        ? rtrim($root_path, '/') . '/' . $logical_base_path
        : $logical_base_path;
      $this->prefixMap->registerDeepPath(
        $logical_base_path,
        $deep_path,
        $this->defaultBehavior);
    }
  }

  /**
   * {@inheritdoc}
   */
  function addPearFlat($prefix, $paths) {
    $logical_base_path = Util::prefixLogicalPath($prefix);
    foreach ((array) $paths as $deep_path) {
      $deep_path = strlen($deep_path) ? (rtrim($deep_path, '/') . '/') : '';
      $this->prefixMap->registerDeepPath(
        $logical_base_path,
        $deep_path,
        $this->defaultBehavior
      );
    }
  }
}
