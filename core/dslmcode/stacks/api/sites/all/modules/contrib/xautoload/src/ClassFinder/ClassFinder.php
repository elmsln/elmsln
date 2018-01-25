<?php


namespace Drupal\xautoload\ClassFinder;

use Drupal\xautoload\ClassLoader\AbstractClassLoader;
use Drupal\xautoload\DirectoryBehavior\DefaultDirectoryBehavior;
use Drupal\xautoload\DirectoryBehavior\Psr0DirectoryBehavior;
use Drupal\xautoload\Util;

class ClassFinder extends AbstractClassLoader implements ExtendedClassFinderInterface {

  /**
   * @var array[]
   */
  protected $classes = array();

  /**
   * @var GenericPrefixMap
   */
  protected $prefixMap;

  /**
   * @var GenericPrefixMap
   */
  protected $namespaceMap;

  /**
   * @var DefaultDirectoryBehavior
   */
  protected $defaultBehavior;

  /**
   * @var Psr0DirectoryBehavior
   */
  protected $psr0Behavior;

  function __construct() {
    $this->prefixMap = new GenericPrefixMap('_');
    $this->namespaceMap = new GenericPrefixMap('\\');
    $this->defaultBehavior = new DefaultDirectoryBehavior();
    $this->psr0Behavior = new Psr0DirectoryBehavior();
  }

  /**
   * {@inheritdoc}
   */
  function getPrefixMap() {
    return $this->prefixMap;
  }

  /**
   * {@inheritdoc}
   */
  function getNamespaceMap() {
    return $this->namespaceMap;
  }

  //                                                      Composer compatibility
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function addClassMap(array $classMap) {
    $this->registerClasses($classMap);
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
      $deep_path = strlen($deep_path)
        ? (rtrim($deep_path, '/') . '/')
        : '';
      $this->prefixMap->registerDeepPath(
        $logical_base_path,
        $deep_path,
        $this->defaultBehavior
      );
    }
  }

  //                                                             Class map stuff
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function registerClass($class, $file_path) {
    $this->classes[$class][$file_path] = TRUE;
  }

  /**
   * {@inheritdoc}
   */
  function registerClasses($classes) {
    foreach ($classes as $class => $file_path) {
      $this->classes[$class][$file_path] = TRUE;
    }
  }

  //                                                                Prefix stuff
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function registerPrefixRoot($prefix, $root_path, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $logical_base_path = Util::prefixLogicalPath($prefix);
    $deep_path = strlen($root_path)
      ? rtrim($root_path, '/') . '/' . $logical_base_path
      : $logical_base_path;
    $this->prefixMap->registerDeepPath(
      $logical_base_path,
      $deep_path,
      $behavior);

    if (strlen($prefix)) {
      // We assume that the class named $prefix is also found at this path.
      $filepath = substr($deep_path, 0, -1) . '.php';
      $this->registerClass($prefix, $filepath);
    }
  }

  /**
   * {@inheritdoc}
   */
  function registerPrefixesRoot($map, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $deep_map = array();
    foreach ($map as $prefix => $root_path) {
      $logical_base_path = Util::prefixLogicalPath($prefix);
      $deep_path = strlen($root_path)
        ? rtrim($root_path, '/') . '/' . $logical_base_path
        : $logical_base_path;
      $deep_map[$logical_base_path][$deep_path] = $behavior;

      // Register the class with name $prefix.
      if (strlen($prefix)) {
        $filepath = substr($deep_path, 0, -1) . '.php';
        $this->classes[$prefix][$filepath] = TRUE;
      }
    }
    $this->prefixMap->registerDeepPaths($deep_map);
  }

  /**
   * {@inheritdoc}
   */
  function registerPrefixDeep($prefix, $deep_path, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $this->registerPrefixDeepLocation($prefix, $deep_path, $behavior);
  }

  /**
   * {@inheritdoc}
   */
  function registerPrefixesDeep($map, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $deep_map = array();
    foreach ($map as $prefix => $deep_path) {
      $logical_base_path = Util::prefixLogicalPath($prefix);
      $deep_path = strlen($deep_path)
        ? rtrim($deep_path, '/') . '/'
        : '';
      $deep_map[$logical_base_path][$deep_path] = $behavior;
    }
    $this->prefixMap->registerDeepPaths($deep_map);
  }

  /**
   * {@inheritdoc}
   */
  function registerPrefixDeepLocation($prefix, $deep_path, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $logical_base_path = Util::prefixLogicalPath($prefix);
    $deep_path = strlen($deep_path)
      ? rtrim($deep_path, '/') . '/'
      : '';
    $this->prefixMap->registerDeepPath(
      $logical_base_path,
      $deep_path,
      $behavior);
  }

  //                                                             Namespace stuff
  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function registerNamespaceRoot($namespace, $root_path, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $logical_base_path = Util::namespaceLogicalPath($namespace);
    $deep_path = strlen($root_path)
      ? rtrim($root_path, '/') . '/' . $logical_base_path
      : $logical_base_path;
    $this->namespaceMap->registerDeepPath(
      $logical_base_path,
      $deep_path,
      $behavior);
  }

  /**
   * {@inheritdoc}
   */
  function registerNamespacesRoot($map, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $deep_map = array();
    foreach ($map as $namespace => $root_path) {
      $logical_base_path = Util::namespaceLogicalPath($namespace);
      $deep_path = strlen($root_path)
        ? rtrim($root_path, '/') . '/' . $logical_base_path
        : $logical_base_path;
      $deep_map[$logical_base_path][$deep_path] = $behavior;
    }
    $this->namespaceMap->registerDeepPaths($deep_map);
  }

  /**
   * {@inheritdoc}
   */
  function registerNamespaceDeep($namespace, $path, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $logical_base_path = Util::namespaceLogicalPath($namespace);
    $deep_path = strlen($path)
      ? $path . '/'
      : '';
    $this->namespaceMap->registerDeepPath(
      $logical_base_path,
      $deep_path,
      $behavior);
  }

  /**
   * {@inheritdoc}
   */
  function registerNamespacesDeep($map, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $deep_map = array();
    foreach ($map as $namespace => $deep_path) {
      $logical_base_path = Util::namespaceLogicalPath($namespace);
      $deep_path = strlen($deep_path)
        ? rtrim($deep_path, '/') . '/'
        : '';
      $deep_map[$logical_base_path][$deep_path] = $behavior;
    }
    $this->namespaceMap->registerDeepPaths($deep_map);
  }

  /**
   * {@inheritdoc}
   */
  function registerNamespaceDeepLocation($namespace, $path, $behavior = NULL) {
    if (!isset($behavior)) {
      $behavior = $this->defaultBehavior;
    }
    $namespace_path_fragment = Util::namespaceLogicalPath($namespace);
    $deep_path = strlen($path)
      ? $path . '/'
      : '';
    $this->namespaceMap->registerDeepPath(
      $namespace_path_fragment,
      $deep_path,
      $behavior);
  }

  // ---------------------------------------------------------------------------

  /**
   * {@inheritdoc}
   */
  function loadClass($class) {

    // Fix the behavior of some PHP versions that prepend '\\' to the class name.
    if ('\\' === $class[0]) {
      $class = substr($class, 1);
    }

    // First check if the literal class name is registered.
    if (!empty($this->classes[$class])) {
      foreach ($this->classes[$class] as $filepath => $true) {
        if (file_exists($filepath)) {
          require $filepath;

          return TRUE;
        }
      }
    }

    // Check if the class has a namespace.
    if (FALSE !== $pos = strrpos($class, '\\')) {

      // Build the "logical path" based on PSR-4 replacement rules.
      $logical_path = str_replace('\\', '/', $class) . '.php';

      return $this->namespaceMap->loadClass($class, $logical_path, $pos);
    }

    // Build the "logical path" based on PEAR replacement rules.
    $pear_logical_path = str_replace('_', '/', $class) . '.php';

    // Clean up surplus '/' resulting from duplicate underscores, or an
    // underscore at the beginning of the class.
    while (FALSE !== $pos = strrpos('/' . $pear_logical_path, '//')) {
      $pear_logical_path{$pos} = '_';
    }

    // Check if the class has any underscore.
    $pos = strrpos($pear_logical_path, '/');

    return $this->prefixMap->loadClass($class, $pear_logical_path, $pos);
  }

  /**
   * {@inheritdoc}
   */
  function apiFindFile($api, $class) {

    // Fix the behavior of some PHP versions that prepend '\\' to the class name.
    if ('\\' === $class[0]) {
      $class = substr($class, 1);
    }

    // First check if the literal class name is registered.
    if (!empty($this->classes[$class])) {
      foreach ($this->classes[$class] as $filepath => $true) {
        if ($api->suggestFile($filepath)) {
          return TRUE;
        }
      }
    }

    // Check if the class has a namespace.
    if (FALSE !== $pos = strrpos($class, '\\')) {

      // Build the "logical path" based on PSR-4 replacement rules.
      $logical_path = str_replace('\\', '/', $class) . '.php';

      return $this->namespaceMap->apiFindFile($api, $logical_path, $pos);
    }

    // Build the "logical path" based on PEAR replacement rules.
    $pear_logical_path = str_replace('_', '/', $class) . '.php';

    // Clean up surplus '/' resulting from duplicate underscores, or an
    // underscore at the beginning of the class.
    while (FALSE !== $pos = strrpos('/' . $pear_logical_path, '//')) {
      $pear_logical_path{$pos} = '_';
    }

    // Check if the class has any underscore.
    $pos = strrpos($pear_logical_path, '/');

    return $this->prefixMap->apiFindFile($api, $pear_logical_path, $pos);
  }
}
