<?php

use Drupal\xautoload\Adapter\LocalDirectoryAdapter;
use Drupal\xautoload\Util;
use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;
use Drupal\xautoload\Adapter\ClassFinderAdapter;

/**
 * An instance of this class is passed around to implementations of
 * hook_xautoload(). It acts as a wrapper around the ClassFinder, to register
 * stuff.
 *
 * Most of the methods here are deprecated. You should use the methods inherited
 * from the base class, LocalDirectoryAdapter, instead.
 */
class xautoload_InjectedAPI_hookXautoload extends LocalDirectoryAdapter {

  /**
   * @var ExtendedClassFinderInterface
   */
  protected $finder;

  /**
   * @param ExtendedClassFinderInterface $finder
   *   The class finder object.
   * @param string $localDirectory
   *
   * @return self
   */
  static function create($finder, $localDirectory) {
    $adapter = ClassFinderAdapter::create($finder);
    return new self($adapter, $localDirectory);
  }

  /**
   * @param ClassFinderAdapter $adapter
   *   The class finder object.
   * @param string $localDirectory
   */
  function __construct($adapter, $localDirectory) {
    parent::__construct($adapter, $localDirectory);
    $this->finder = $adapter->getFinder();
  }

  //                                                                Prefix stuff
  // ---------------------------------------------------------------------------

  /**
   * Register an additional prefix for this module.
   * Note: Drupal\<module name>\ is already registered for <module dir>/lib.
   *
   * @deprecated
   *
   * @param string $prefix
   *   The prefix.
   * @param string $prefix_root_dir
   *   Prefix root dir.
   *   If $relative is TRUE, this is relative to the extension module dir.
   *   If $relative is FALSE, this is an absolute path.
   * @param boolean $relative
   *   Whether or not the path is relative to the current extension dir.
   */
  function prefixRoot($prefix, $prefix_root_dir = NULL, $relative = TRUE) {
    $prefix_root_dir = $this->processDir($prefix_root_dir, $relative);
    $this->finder->registerPrefixRoot($prefix, $prefix_root_dir);
  }

  /**
   * Register an additional namespace for this module.
   * Note: Drupal\<module name>\ is already registered for <module dir>/lib.
   *
   * @deprecated
   *
   * @param string $prefix
   *   The namespace
   * @param string $prefix_deep_dir
   *   PSR-0 root dir.
   *   If $relative is TRUE, this is relative to the current extension dir.
   *   If $relative is FALSE, this is an absolute path.
   * @param boolean $relative
   *   Whether or not the path is relative to the current extension dir.
   */
  function prefixDeep($prefix, $prefix_deep_dir = NULL, $relative = TRUE) {
    $prefix_deep_dir = $this->processDir($prefix_deep_dir, $relative);
    $this->finder->registerPrefixDeep($prefix, $prefix_deep_dir);
  }

  /**
   * Legacy: Plugins were called "Handler" before.
   *
   * @deprecated
   *
   * @param string $prefix
   * @param xautoload_FinderPlugin_Interface $plugin
   *
   * @return string
   *   The key under which the plugin was registered. This can later be used to
   *   unregister the plugin again.
   */
  function prefixHandler($prefix, $plugin) {
    $key = Util::randomString();
    $this->finder->registerPrefixDeep($prefix, $key, $plugin);

    return $key;
  }

  /**
   * Register a prefix plugin object
   *
   * @deprecated
   *
   * @param string $prefix
   * @param xautoload_FinderPlugin_Interface $plugin
   *
   * @return string
   *   The key under which the plugin was registered. This can later be used to
   *   unregister the plugin again.
   */
  function prefixPlugin($prefix, $plugin) {
    $key = Util::randomString();
    $this->finder->registerPrefixDeep($prefix, $key, $plugin);

    return $key;
  }

  //                                                             Namespace stuff
  // ---------------------------------------------------------------------------

  /**
   * Register an additional namespace for this module.
   * Note: Drupal\<module name>\ is already registered for <module dir>/lib.
   *
   * @deprecated
   *
   * @param string $namespace
   *   The namespace
   * @param string $psr_0_root_dir
   *   PSR-0 root dir.
   *   If $relative is TRUE, this is relative to the current module dir.
   *   If $relative is FALSE, this is an absolute path.
   * @param boolean $relative
   *   Whether or not the path is relative to the current extension dir.
   */
  function namespaceRoot($namespace, $psr_0_root_dir = NULL, $relative = TRUE) {
    $psr_0_root_dir = $this->processDir($psr_0_root_dir, $relative);
    $this->finder->registerNamespaceRoot($namespace, $psr_0_root_dir);
  }

  /**
   * Register an additional namespace for this module.
   * Note: Drupal\<module name>\ is already registered for <module dir>/lib.
   *
   * @deprecated
   *
   * @param string $namespace
   *   The namespace
   * @param string $namespace_deep_dir
   *   PSR-0 root dir.
   *   If $relative is TRUE, this is relative to the current extension dir.
   *   If $relative is FALSE, this is an absolute path.
   * @param boolean $relative
   *   Whether or not the path is relative to the current extension dir.
   */
  function namespaceDeep($namespace, $namespace_deep_dir = NULL, $relative = TRUE) {
    $namespace_deep_dir = $this->processDir($namespace_deep_dir, $relative);
    $this->finder->registerNamespaceDeep($namespace, $namespace_deep_dir);
  }

  /**
   * Register a namespace plugin object
   *
   * @deprecated
   *
   * @param string $namespace
   * @param xautoload_FinderPlugin_Interface $plugin
   *
   * @return string
   *   The key under which the plugin was registered. This can later be used to
   *   unregister the plugin again.
   */
  function namespacePlugin($namespace, $plugin) {
    $key = Util::randomString();
    $this->finder->registerNamespaceDeep($namespace, $key, $plugin);

    return $key;
  }

  /**
   * Legacy: Plugins were called "Handler" before.
   *
   * @deprecated
   *
   * @param string $namespace
   * @param xautoload_FinderPlugin_Interface $plugin
   *
   * @return string
   *   The key under which the plugin was registered. This can later be used to
   *   unregister the plugin again.
   */
  function namespaceHandler($namespace, $plugin) {
    $key = Util::randomString();
    $this->finder->registerNamespaceDeep($namespace, $key, $plugin);

    return $key;
  }

  /**
   * Process a given directory to make it relative to Drupal root,
   * instead of relative to the current extension dir.
   *
   * @deprecated
   *
   * @param string $dir
   *   The directory path that we want to make absolute.
   * @param boolean $relative
   *   If TRUE, the $dir will be transformed from relative to absolute.
   *   If FALSE, the $dir is assumed to already be absolute, and remain unchanged.
   *
   * @return string
   *   The modified (absolute) directory path.
   */
  protected function processDir($dir, $relative) {
    if (!isset($dir)) {
      return $this->localDirectory . 'lib/';
    }
    $dir = strlen($dir)
      ? rtrim($dir, '/') . '/'
      : '';

    return $relative
      ? $this->localDirectory . $dir
      : $dir;
  }

  /**
   * Explicitly set the base for relative paths.
   *
   * Alias for LocalDirectoryAdapter::setLocalDirectory()
   *
   * @param string $dir
   *   New relative base path.
   */
  function setExtensionDir($dir) {
    $this->localDirectory = strlen($dir)
      ? rtrim($dir, '/') . '/'
      : '';
  }
}
