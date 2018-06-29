<?php

namespace Drupal\xautoload\ClassFinder\Plugin;

use Drupal\xautoload\ClassFinder\GenericPrefixMap;
use Drupal\xautoload\DirectoryBehavior\DefaultDirectoryBehavior;
use Drupal\xautoload\DirectoryBehavior\Psr0DirectoryBehavior;
use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;

/**
 * There are different dimensions of state for each module:
 *
 * 1) Classes outside of Drupal\\$modulename\\Tests\\
 *   a) We don't know yet whether these classes are using PSR-0, PSR-4,
 *     PEAR-Flat, or none of these.
 *   b) We know these classes use PSR-0 only.
 *   c) We know these classes use PSR-4 only.
 *   d) We know these classes use PEAR-Flat only.
 *
 * 2) Classes inside Drupal\\$modulename\\Tests\\
 *   a) We don't know yet whether these classes are using PSR-0, PSR-4, or none
 *     of these.
 *   b) We know these classes all use PSR-0.
 *   c) We know these classes all use PSR-4.
 *
 * Any combination of a state from (1) with a state from (2) is possible.
 *
 * The state could even change during the execution of the findClass() method,
 * due to another autoloader instance being fired during a file inclusion, e.g.
 * for a base class.
 */
class DrupalExtensionNamespaceFinderPlugin implements FinderPluginInterface {

  /**
   * @var string
   *   E.g. 'theme' or 'module'.
   */
  protected $type;

  /**
   * Namespace map used in the class finder for PSR-0/4-like mappings.
   *
   * @var GenericPrefixMap
   */
  protected $namespaceMap;

  /**
   * Prefix map used in the class finder for PEAR-like mappings.
   *
   * @var GenericPrefixMap
   */
  protected $prefixMap;

  /**
   * Directory behavior for PSR-4.
   *
   * @var DefaultDirectoryBehavior
   */
  protected $defaultBehavior;

  /**
   * Directory behavior with the special underscore handling for PSR-0.
   *
   * @var Psr0DirectoryBehavior
   */
  protected $psr0Behavior;

  /**
   * @var DrupalSystemInterface
   */
  protected $system;

  /**
   * @param string $type
   *   E.g. 'theme' or 'module'.
   * @param GenericPrefixMap $namespace_map
   * @param GenericPrefixMap $prefix_map
   * @param DrupalSystemInterface $system
   */
  function __construct($type, $namespace_map, $prefix_map, $system) {
    $this->type = $type;
    $this->prefixMap = $prefix_map;
    $this->namespaceMap = $namespace_map;
    $this->defaultBehavior = new DefaultDirectoryBehavior();
    $this->psr0Behavior = new Psr0DirectoryBehavior();
    $this->system = $system;
  }

  /**
   * Looks up a class starting with "Drupal\$extension_name\\".
   *
   * This plugin method will be called for every class beginning with
   * "Drupal\\$extension_name\\", as long as the plugin is registered for
   * $logical_base_path = 'Drupal/$extension_name/'.
   *
   * A similar plugin will is registered along with this one for the PEAR-FLAT
   * pattern, called for every class beginning with $modulename . '_'.
   *
   * The plugin will eventually unregister itself and its cousin, once it has
   * - determined the correct path for the module, and
   * - determined that the module is using either PSR-0 or PSR-4.
   *   It does that by including the file candidate for PSR-0 and/or PSR-4 and
   *   checking whether the class is now defined.
   *
   * The plugin will instead register a direct
   *
   * @param \Drupal\xautoload\ClassFinder\InjectedApi\InjectedApiInterface $api
   *   An object with methods like suggestFile() and guessFile().
   * @param string $logical_base_path
   *   The logical base path determined from the registered namespace.
   *   E.g. 'Drupal/menupoly/'.
   * @param string $relative_path
   *   Remaining part of the logical path following $logical_base_path.
   *   E.g. 'FooNamespace/BarClass.php'.
   * @param string|null $extension_name
   *   Second key that the plugin was registered with. Usually this would be the
   *   physical base directory where we prepend the relative path to get the
   *   file path. But in this case it is simply the extensions name.
   *   E.g. 'menupoly'.
   *
   * @return bool|null
   *   TRUE, if the file was found.
   *   FALSE or NULL, otherwise.
   */
  function findFile($api, $logical_base_path, $relative_path, $extension_name = NULL) {

    $extension_file = $this->system->drupalGetFilename($this->type, $extension_name);
    if (empty($extension_file)) {
      // Extension does not exist, or is not installed.
      return FALSE;
    }

    $nspath = 'Drupal/' . $extension_name . '/';
    $testpath = $nspath . 'Tests/';
    $uspath = $extension_name . '/';
    $extension_dir = dirname($extension_file);
    $src = $extension_dir . '/src/';
    $lib_psr0 = $extension_dir . '/lib/Drupal/' . $extension_name . '/';
    $is_test_class = (0 === strpos($relative_path, 'Tests/'));

    // Try PSR-4.
    if ($api->guessPath($src . $relative_path)) {
      if ($is_test_class) {
        // Register PSR-0 directory for "Drupal\\$modulename\\Tests\\"
        // This generally happens only once per module, because for subsequent
        // test classes the class will be found before this plugin is triggered.
        // However, for class_exists() with nonexistent test files, this line
        // will occur more than once.
        $this->namespaceMap->registerDeepPath($testpath, $src . 'Tests/', $this->defaultBehavior);
        // We found the class, but it is a test class, so it does not tell us
        // anything about whether non-test classes are in PSR-0 or PSR-4.
        return TRUE;
      }

      // Register PSR-4 directory for "Drupal\\$modulename\\".
      $this->namespaceMap->registerDeepPath($nspath, $src, $this->defaultBehavior);

      // Unregister the lazy plugins, including this one, for
      // "Drupal\\$modulename\\" and for $modulename . '_'.
      $this->namespaceMap->unregisterDeepPath($nspath, $extension_name);
      $this->prefixMap->unregisterDeepPath($uspath, $extension_name);

      // Test classes in PSR-4 are already covered by the PSR-4 plugin we just
      // registered. But test classes in PSR-0 would slip through. So we check
      // if a separate behavior needs to be registered for those.
      if (is_dir($lib_psr0 . 'Tests/')) {
        $this->namespaceMap->registerDeepPath($testpath, $lib_psr0 . 'Tests/', $this->psr0Behavior);
      }

      // The class was found, so return TRUE.
      return TRUE;
    }

    // Build PSR-0 relative path.
    if (FALSE === $nspos = strrpos($relative_path, '/')) {
      // No namespace separators in $relative_path, so all underscores must be
      // replaced.
      $relative_path = str_replace('_', '/', $relative_path);
    }
    else {
      // Replace only those underscores in $relative_path after the last
      // namespace separator, from right to left. On average there is no or very
      // few of them, so this loop rarely iterates even once.
      while ($nspos < $uspos = strrpos($relative_path, '_')) {
        $relative_path{$uspos} = '/';
      }
    }

    // Try PSR-0
    if ($api->guessPath($lib_psr0 . $relative_path)) {
      if ($is_test_class) {
        // We know now that there are test classes using PSR-0.
        $this->namespaceMap->registerDeepPath($testpath, $lib_psr0 . 'Tests/', $this->psr0Behavior);
        // We found the class, but it is a test class, so it does not tell us
        // anything about whether non-test classes are in PSR-0 or PSR-4.
        return TRUE;
      }

      // Unregister the lazy plugins, including this one.
      $this->namespaceMap->unregisterDeepPath($nspath, $extension_name);
      $this->prefixMap->unregisterDeepPath($uspath, $extension_name);

      // Register PSR-0 for regular namespaced classes.
      $this->namespaceMap->registerDeepPath($nspath, $lib_psr0, $this->psr0Behavior);

      // Test classes in PSR-0 are already covered by the PSR-0 plugin we just
      // registered. But test classes in PSR-4 would slip through. So we check
      // if a separate behavior needs to be registered for those.
      # if (is_dir($src . 'Tests/')) {
      #   $this->namespaceMap->registerDeepPath($testpath, $src . 'Tests/', $this->psr0Behavior);
      # }

      // The class was found, so return TRUE.
      return TRUE;
    }

    return FALSE;
  }
}
