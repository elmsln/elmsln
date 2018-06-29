<?php

use Drupal\xautoload\ClassFinder\InjectedApi\InjectedApiInterface;
use Drupal\xautoload\DirectoryBehavior\DirectoryBehaviorInterface;

/**
 * X Autoload plugins are for:
 *   - More exotic autoload patterns that are incompatible with PSR-0 or PEAR
 *   - Situations where we don't want to register a ton of namespaces, and using
 *     a plugin instead gives us performance benefits.
 */
interface xautoload_FinderPlugin_Interface extends DirectoryBehaviorInterface {

  /**
   * Find the file for a class that in PSR-0 or PEAR would be in
   * $psr_0_root . '/' . $path_fragment . $path_suffix
   *
   * E.g.:
   *   - The class we look for is Some\Namespace\Some\Class
   *   - The file is actually in "exotic/location.php". This is not following
   *     PSR-0 or PEAR standard, so we need a plugin.
   *   -> The class finder will transform the class name to
   *     "Some/Namespace/Some/Class.php"
   *   - The plugin was registered for the namespace "Some\Namespace". This is
   *     because all those exotic classes all begin with Some\Namespace\
   *   -> The arguments will be:
   *     ($api = the API object, see below)
   *     $logical_base_path = "Some/Namespace/"
   *     $relative_path = "Some/Class.php"
   *     $api->getClass() gives the original class name, if we still need it.
   *   -> We are supposed to:
   *     if ($api->suggestFile('exotic/location.php')) {
   *       return TRUE;
   *     }
   *
   * @param InjectedApiInterface $api
   *   An object with a suggestFile() method.
   *   We are supposed to suggest files until suggestFile() returns TRUE, or we
   *   have no more suggestions.
   * @param string $logical_base_path
   *   The key that this plugin was registered with.
   *   With trailing '/'.
   * @param string $relative_path
   *   Second part of the canonical path, ending with '.php'.
   *
   * @return bool|null
   *   TRUE, if the file was found.
   *   FALSE or NULL, otherwise.
   */
  function findFile($api, $logical_base_path, $relative_path);
}
