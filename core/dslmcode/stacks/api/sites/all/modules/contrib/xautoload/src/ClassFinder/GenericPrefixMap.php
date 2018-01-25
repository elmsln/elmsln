<?php

namespace Drupal\xautoload\ClassFinder;

use Drupal\xautoload\DirectoryBehavior\DirectoryBehaviorInterface;
use Drupal\xautoload\ClassFinder\InjectedApi\LoadClassInjectedAPI;
use Drupal\xautoload\ClassFinder\InjectedApi\InjectedApiInterface;
use Drupal\xautoload\DirectoryBehavior\DefaultDirectoryBehavior;
use xautoload_FinderPlugin_Interface;
use Drupal\xautoload\DirectoryBehavior\Psr0DirectoryBehavior;

/**
 * Helper class for the class finder.
 * This is not part of ClassFinder, because we want to use the same logic for
 * namespaces (PSR-0) and prefixes (PEAR).
 *
 * This thing does not actually deal with class names, but with transformed
 * paths.
 *
 * Example A:
 * When looking for a class \Aaa\Bbb\Ccc_Ddd, the class finder will
 * 1. Determine that this class is within a namespace.
 * 2. Transform that into "Aaa/Bbb/Ccc/Ddd.php".
 * 3. Check if the namespace map evaluator has anything registered for
 *   3.1. "Aaa/Bbb/"
 *   3.2. "Aaa/"
 *   3.3. ""
 *
 * Example A:
 * When looking for a class Aaa_Bbb_Ccc, the class finder will
 * 1. Determine that this class is NOT within a namespace.
 * 2. Check if a file is explicitly registered for the class itself.
 * 3. Transform the class name into "Aaa/Bbb/Ccc.php".
 * 4. Check if the prefix map evaluator has anything registered for
 *   4.1. "Aaa/Bbb/"
 *   4.2. "Aaa/"
 *   4.3. ""
 */
class GenericPrefixMap {

  /**
   * @var DirectoryBehaviorInterface[][]
   *   Format: $[$logical_base_path][$deep_path] = $behavior
   */
  protected $paths = array();

  /**
   * @var string
   *   Either '\\' or '_'.
   */
  protected $separator;

  /**
   * @param string $separator
   */
  function __construct($separator) {
    $this->separator = $separator;
  }

  /**
   * If a class file would be in
   *   $psr0_root . '/' . $path_fragment . $path_suffix
   * then instead, we look in
   *   $deep_path . $path_suffix
   *
   * @param string $logical_base_path
   *   The would-be namespace path relative to PSR-0 root.
   *   That is, the namespace with '\\' replaced by '/'.
   * @param string $deep_path
   *   The filesystem location of the (PSR-0) subfolder for the given namespace.
   * @param DirectoryBehaviorInterface $behavior
   *   Behavior in this directory.
   */
  function registerDeepPath($logical_base_path, $deep_path, $behavior) {
    $this->paths[$logical_base_path][$deep_path] = $behavior;
  }

  /**
   * @param string $logical_base_path
   *   The would-be namespace path relative to PSR-0 root.
   *   That is, the namespace with '\\' replaced by '/'.
   * @param string $deep_path
   *   The filesystem location of the (PSR-0) subfolder for the given namespace.
   * @param DirectoryBehaviorInterface $behavior
   *   Behavior in this directory.
   */
  function prependDeepPath($logical_base_path, $deep_path, $behavior) {
    $this->paths[$logical_base_path]
      = isset($this->paths[$logical_base_path])
      ? array($deep_path => $behavior) + $this->paths[$logical_base_path]
      : array($deep_path => $behavior);
  }

  /**
   * Register a bunch of those paths ..
   *
   * @param array[] $map
   *
   * @throws \Exception
   */
  function registerDeepPaths(array $map) {
    foreach ($map as $key => $paths) {
      if (isset($this->paths[$key])) {
        $paths += $this->paths[$key];
      }
      $this->paths[$key] = $paths;
    }
  }

  /**
   * Delete a registered path mapping.
   *
   * @param string $logical_base_path
   * @param string $deep_path
   */
  function unregisterDeepPath($logical_base_path, $deep_path) {
    unset($this->paths[$logical_base_path][$deep_path]);
  }


  /**
   * @param string $class
   * @param string $logical_path
   *   Class name translated into a logical path, either with PSR-4 or with PEAR
   *   translation rules.
   * @param int|bool $lastpos
   *   Position of the last directory separator in $logical_path.
   *   FALSE, if there is no directory separator in $logical_path.
   *
   * @return bool|NULL
   *   TRUE, if the class was found.
   */
  function loadClass($class, $logical_path, $lastpos) {
    $pos = $lastpos;
    while (TRUE) {
      $logical_base_path = (FALSE === $pos)
        ? ''
        : substr($logical_path, 0, $pos + 1);

      if (isset($this->paths[$logical_base_path])) {
        foreach ($this->paths[$logical_base_path] as $dir => $behavior) {
          if ($behavior instanceof DefaultDirectoryBehavior) {
            // PSR-4 and PEAR
            if (file_exists($file = $dir . substr($logical_path, $pos + 1))) {
              require $file;

              return TRUE;
            }
          }
          elseif ($behavior instanceof Psr0DirectoryBehavior) {
            // PSR-0
            if (file_exists(
              $file = $dir
                . substr($logical_path, $pos + 1, $lastpos - $pos)
                . str_replace('_', '/', substr($logical_path, $lastpos + 1))
            )) {
              require $file;

              return TRUE;
            }
          }
          elseif ($behavior instanceof xautoload_FinderPlugin_Interface) {
            // Legacy "FinderPlugin".
            $api = new LoadClassInjectedAPI($class);
            if ($behavior->findFile($api, $logical_base_path, substr($logical_path, $pos + 1), $dir)) {
              return TRUE;
            }
          }
        }
      }

      // Continue with parent fragment.
      if (FALSE === $pos) {
        return NULL;
      }

      $pos = strrpos($logical_base_path, '/', -2);
    }

    return NULL;
  }

  /**
   * Find the file for a class that in PSR-0 or PEAR would be in
   * $psr_0_root . '/' . $path_fragment . $path_suffix
   *
   * @param InjectedApiInterface $api
   * @param string $logical_path
   *   Class name translated into a logical path, either with PSR-4 or with PEAR
   *   translation rules.
   * @param int|bool $lastpos
   *   Position of the last directory separator in $logical_path.
   *   FALSE, if there is no directory separator in $logical_path.
   *
   * @return bool|NULL
   *   TRUE, if the class was found.
   */
  function apiFindFile($api, $logical_path, $lastpos) {
    $pos = $lastpos;
    while (TRUE) {
      $logical_base_path = (FALSE === $pos)
        ? ''
        : substr($logical_path, 0, $pos + 1);

      if (isset($this->paths[$logical_base_path])) {
        foreach ($this->paths[$logical_base_path] as $dir => $behavior) {
          if ($behavior instanceof DefaultDirectoryBehavior) {
            // PSR-4 and PEAR
            if ($api->suggestFile($dir . substr($logical_path, $pos + 1))) {
              return TRUE;
            }
          }
          elseif ($behavior instanceof Psr0DirectoryBehavior) {
            // PSR-0
            if ($api->suggestFile(
              $dir
              . substr($logical_path, $pos + 1, $lastpos - $pos)
              . str_replace('_', '/', substr($logical_path, $lastpos + 1))
            )) {
              return TRUE;
            }
          }
          elseif ($behavior instanceof xautoload_FinderPlugin_Interface) {
            // Legacy "FinderPlugin".
            if ($behavior->findFile($api, $logical_base_path, substr($logical_path, $pos + 1), $dir)) {
              return TRUE;
            }
          }
        }
      }

      // Continue with parent fragment.
      if (FALSE === $pos) {
        return NULL;
      }

      $pos = strrpos($logical_base_path, '/', -2);
    }

    return NULL;
  }
}
