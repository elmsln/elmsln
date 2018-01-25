<?php

namespace Drupal\xautoload\Adapter;

use Drupal\xautoload\DirectoryBehavior\DefaultDirectoryBehavior;
use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;
use Drupal\xautoload\ClassFinder\Plugin\DrupalExtensionNamespaceFinderPlugin;
use Drupal\xautoload\ClassFinder\Plugin\DrupalExtensionUnderscoreFinderPlugin;
use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;

/**
 * Service that knows how to register module namespaces and prefixes into the
 * class loader, and that remembers which modules have already been registered.
 */
class DrupalExtensionAdapter {

  /**
   * @var \Drupal\xautoload\DrupalSystem\DrupalSystemInterface
   */
  protected $system;

  /**
   * @var ExtendedClassFinderInterface
   */
  protected $finder;

  /**
   * One finder plugin for each extension type ('module', 'theme').
   *
   * @var DrupalExtensionNamespaceFinderPlugin[]
   */
  protected $namespaceBehaviors = array();

  /**
   * One finder plugin for each extension type ('module', 'theme').
   *
   * @var DrupalExtensionUnderscoreFinderPlugin[]
   */
  protected $prefixBehaviors = array();

  /**
   * The namespace map used in the class loader.
   *
   * @var \Drupal\xautoload\ClassFinder\GenericPrefixMap
   */
  protected $namespaceMap;

  /**
   * The prefix map used in the class loader.
   *
   * @var \Drupal\xautoload\ClassFinder\GenericPrefixMap
   */
  protected $prefixMap;

  /**
   * Which modules have already been processed.
   *
   * @var bool[]
   */
  protected $registered = array();

  /**
   * Directory behavior for PSR-4
   *
   * @var DefaultDirectoryBehavior
   */
  protected $defaultBehavior;

  /**
   * @param DrupalSystemInterface $system
   * @param ExtendedClassFinderInterface $finder
   */
  function __construct(DrupalSystemInterface $system, ExtendedClassFinderInterface $finder) {
    $this->system = $system;
    $this->finder = $finder;
    $this->namespaceMap = $finder->getNamespaceMap();
    $this->prefixMap = $finder->getPrefixMap();
    foreach (array('module', 'theme') as $extension_type) {
      $this->namespaceBehaviors[$extension_type] = new DrupalExtensionNamespaceFinderPlugin(
        $extension_type,
        $this->namespaceMap,
        $this->prefixMap,
        $this->system);
      $this->prefixBehaviors[$extension_type] = new DrupalExtensionUnderscoreFinderPlugin(
        $extension_type,
        $this->namespaceMap,
        $this->prefixMap,
        $this->system);
    }
    $this->defaultBehavior = new DefaultDirectoryBehavior();
  }

  /**
   * Register lazy plugins for enabled Drupal modules and themes, assuming that
   * we don't know yet whether they use PSR-0, PEAR-Flat, or none of these.
   *
   * @param string[] $extensions
   *   An array where the keys are extension names, and the values are extension
   *   types like 'module' or 'theme'.
   */
  function registerExtensions(array $extensions) {

    $prefix_map = array();
    $namespace_map = array();
    foreach ($extensions as $name => $type) {
      if (empty($this->namespaceBehaviors[$type])) {
        // Unsupported extension type, e.g. "theme_engine".
        // This can happen if a site was upgraded from Drupal 6.
        // See https://drupal.org/comment/8503979#comment-8503979
        continue;
      }
      if (!empty($this->registered[$name])) {
        // The extension has already been processed.
        continue;
      }
      $namespace_map['Drupal/' . $name . '/'][$name] = $this->namespaceBehaviors[$type];
      $prefix_map[str_replace('_', '/', $name) . '/'][$name] = $this->prefixBehaviors[$type];
      $this->registered[$name] = TRUE;
    }
    $this->namespaceMap->registerDeepPaths($namespace_map);
    $this->prefixMap->registerDeepPaths($prefix_map);
  }

  /**
   * Register lazy plugins for a given extension, assuming that we don't know
   * yet whether it uses PSR-0, PEAR-Flat, or none of these.
   *
   * @param string $name
   * @param string $type
   */
  function registerExtension($name, $type) {
    if (!empty($this->registered[$name])) {
      // The extension has already been processed.
      return;
    }
    $this->namespaceMap->registerDeepPath('Drupal/' . $name . '/', $name, $this->namespaceBehaviors[$type]);
    $this->prefixMap->registerDeepPath(str_replace('_', '/', $name) . '/', $name, $this->prefixBehaviors[$type]);
    $this->registered[$name] = TRUE;
  }

  /**
   * Register PSR-4 directory for an extension.
   * Override previous settings for this extension.
   *
   * @param string $name
   *   The extension name.
   * @param string $extension_dir
   *   The directory of the extension.
   * @param string $subdir
   *   The PSR-4 base directory, relative to the extension directory.
   *   E.g. 'lib' or 'src'.
   */
  function registerExtensionPsr4($name, $extension_dir, $subdir) {
    if (!empty($this->registered[$name])) {
      if ('psr-4' === $this->registered[$name]) {
        // It already happened.
        return;
      }
      // Unregister the lazy plugins.
      $this->namespaceMap->unregisterDeepPath('Drupal/' . $name . '/', $name);
      $this->prefixMap->unregisterDeepPath(str_replace('_', '/', $name) . '/', $name);
    }

    $dir = strlen($subdir)
      ? $extension_dir . '/' . trim($subdir, '/') . '/'
      : $extension_dir . '/';
    $this->namespaceMap->registerDeepPath('Drupal/' . $name . '/', $dir, $this->defaultBehavior);

    // Re-add the PSR-0 test directory, for consistency's sake.
    if (is_dir($psr0_tests_dir = $extension_dir . '/lib/Drupal/' . $name . '/Tests')) {
      $this->namespaceMap->registerDeepPath('Drupal/' . $name . '/Tests/', $psr0_tests_dir, $this->defaultBehavior);
    }
  }
}
