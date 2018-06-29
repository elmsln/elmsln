<?php


namespace Drupal\xautoload\Phases;


use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;
use Drupal\xautoload\ClassFinder\Plugin\DrupalExtensionNamespaceFinderPlugin;
use Drupal\xautoload\ClassFinder\Plugin\DrupalExtensionUnderscoreFinderPlugin;
use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;

class ExtensionNamespaces implements PhaseObserverInterface {

  /**
   * @var ExtendedClassFinderInterface
   */
  private $finder;

  /**
   * @var (string|false)[]
   */
  private $queue = array();

  /**
   * Which modules are already registered.
   *
   * @var bool[]
   */
  private $registered = array();

  /**
   * @var DrupalSystemInterface
   */
  private $system;

  /**
   * @param DrupalSystemInterface $system
   */
  public function __construct(DrupalSystemInterface $system) {
    $this->system = $system;
  }

  /**
   * Registers the namespaces for a module even though it might be currently
   * disabled, or even though it might be early in the request.
   *
   * @param string $__FILE__
   */
  public function registerExtension($__FILE__) {
    if (NULL === $this->finder) {
      // Sleeping..
      $this->queue[$__FILE__] = FALSE;

      return;
    }

    $info = pathinfo($__FILE__);
    $name = $info['filename'];

    // Check if something was registered before.
    if (isset($this->registered[$name])) {
      // Already registered.
      return;
    }

    $this->_registerExtension($name, $info['dirname']);
  }

  /**
   * Registers the namespace with PSR-4 for a module even though it might be
   * currently disabled, or even though it might be early in the request.
   *
   * @param string $__FILE__
   * @param string $subdir
   */
  public function registerExtensionPsr4($__FILE__, $subdir) {
    if (NULL === $this->finder) {
      // Sleeping..
      $this->queue[$__FILE__] = $subdir;

      return;
    }

    $info = pathinfo($__FILE__);
    $name = $info['filename'];

    // Check if something was registered before.
    if (isset($this->registered[$name])) {
      if ('psr-4' === $this->registered[$name]) {
        // It already happened.
        return;
      }
      // Unregister the lazy plugins.
      $this->finder->getNamespaceMap()->unregisterDeepPath(
        'Drupal/' . $name . '/',
        $name
      );
      $this->finder->getPrefixMap()->unregisterDeepPath(
        str_replace('_', '/', $name) . '/',
        $name
      );
    }
    $this->_registerExtensionPsr4($name, $info['dirname'], $subdir);
  }

  /**
   * Wake up after a cache fail.
   *
   * @param ExtendedClassFinderInterface $finder
   * @param string[] $extensions
   *   Extension type by extension name.
   */
  public function wakeUp(ExtendedClassFinderInterface $finder, array $extensions) {
    $this->finder = $finder;

    // Register queued extensions.
    foreach ($this->queue as $__FILE__ => $subdir) {
      $info = pathinfo($__FILE__);
      $name = $info['filename'];
      $dir = $info['dirname'];
      if (FALSE === $subdir) {
        // This is not PSR-4.
        $this->_registerExtension($name, $dir);
      }
      else {
        // This is PSR-4.
        $this->_registerExtensionPsr4($name, $dir, $subdir);
      }
    }

    $extensions = array_diff_key($extensions, $this->registered);

    // Register remaining extensions, using the lazy plugins.
    $this->_registerLazyExtensionPlugins($extensions);
  }

  /**
   * Enter the boot phase of the request, where all bootstrap module files are included.
   */
  public function enterBootPhase() {
    // Nothing.
  }

  /**
   * Enter the main phase of the request, where all module files are included.
   */
  public function enterMainPhase() {
    // Nothing.
  }

  /**
   * React to new extensions that were just enabled.
   *
   * @param string $name
   * @param string $type
   */
  public function welcomeNewExtension($name, $type) {
    if (isset($this->registered[$name])) {
      // Already registered.
      return;
    }
    $dir = $this->system->drupalGetPath($type, $name);
    $this->_registerExtension($name, $dir);
  }

  /**
   * React to xautoload_modules_enabled()
   *
   * @param string[] $modules
   *   New module names.
   */
  public function modulesEnabled($modules) {
    // Nothing.
  }

  /**
   * @param string $name
   * @param string $dir
   */
  private function _registerExtension($name, $dir) {
    if (is_dir($lib = $dir . '/lib')) {
      $this->finder->addPsr0('Drupal\\' . $name . '\\', $lib);
      $this->finder->addPearFlat($name . '_', $lib);
    }
    if (is_dir($src = $dir . '/src')) {
      $this->finder->addPsr4('Drupal\\' . $name . '\\', $src);
    }

    $this->registered[$name] = TRUE;
  }

  /**
   * @param string $name
   * @param string $dir
   * @param string $subdir
   */
  private function _registerExtensionPsr4($name, $dir, $subdir) {
    $this->finder->addPsr4('Drupal\\' . $name . '\\', $dir . '/' . $subdir);

    // Re-add the PSR-0 test directory, for consistency's sake.
    if (is_dir($lib_tests = $dir . '/lib/Drupal/' . $name . '/Tests')) {
      $this->finder->addPsr0('Drupal\\' . $name . '\\Tests\\', $lib_tests);
    }
    $this->registered[$name] = 'psr-4';
  }

  /**
   * Register lazy plugins for enabled Drupal modules and themes, assuming that
   * we don't know yet whether they use PSR-0, PEAR-Flat, or none of these.
   *
   * @param string[] $extensions
   *   An array where the keys are extension names, and the values are extension
   *   types like 'module' or 'theme'.
   */
  private function _registerLazyExtensionPlugins(array $extensions) {

    $namespaceBehaviors = array();
    $prefixBehaviors = array();
    foreach (array('module', 'theme') as $extension_type) {
      $namespaceBehaviors[$extension_type] = new DrupalExtensionNamespaceFinderPlugin(
        $extension_type,
        $this->finder->getNamespaceMap(),
        $this->finder->getPrefixMap(),
        $this->system);
      $prefixBehaviors[$extension_type] = new DrupalExtensionUnderscoreFinderPlugin(
        $extension_type,
        $this->finder->getNamespaceMap(),
        $this->finder->getPrefixMap(),
        $this->system);
    }

    $prefix_map = array();
    $namespace_map = array();
    foreach ($extensions as $name => $type) {
      if (empty($namespaceBehaviors[$type])) {
        // Unsupported extension type, e.g. "theme_engine".
        // This can happen if a site was upgraded from Drupal 6.
        // See https://drupal.org/comment/8503979#comment-8503979
        continue;
      }
      if (!empty($this->registered[$name])) {
        // The extension has already been processed.
        continue;
      }
      $namespace_map['Drupal/' . $name . '/'][$name] = $namespaceBehaviors[$type];
      $prefix_map[str_replace('_', '/', $name) . '/'][$name] = $prefixBehaviors[$type];
      $this->registered[$name] = TRUE;
    }

    $this->finder->getNamespaceMap()->registerDeepPaths($namespace_map);
    $this->finder->getPrefixMap()->registerDeepPaths($prefix_map);
  }
}
