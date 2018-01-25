<?php

namespace Drupal\xautoload\ClassFinder\Plugin;

use Drupal\xautoload\ClassFinder\InjectedApi\InjectedApiInterface;
use xautoload_FinderPlugin_Interface;


/**
 * X Autoload plugins are for:
 *   - More exotic autoload patterns that are incompatible with PSR-0 or PEAR
 *   - Situations where we don't want to register a ton of namespaces, and using
 *     a plugin instead gives us performance benefits.
 */
interface FinderPluginInterface extends xautoload_FinderPlugin_Interface {

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
   *     $path_fragment = "Some/Namespace/"
   *     $path_suffix = "Some/Class.php"
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
   * @param string $path_fragment
   *   The key that this plugin was registered with.
   *   With trailing '/'.
   * @param string $path_suffix
   *   Second part of the canonical path, ending with '.php'.
   * @param int|string $id
   *   Id under which the plugin was registered.
   *   This may be a numeric id, or a string key.
   *
   * @return bool|null
   *   TRUE, if the file was found.
   *   FALSE, otherwise.
   *
   * NOTE:
   *   The signature of this method has changed since the legacy base interface,
   *   with a new optional parameter being added.
   *   Due to a bug in PHP 5.3.0 - 5.3.8, redeclaring the method with the
   *   modified signature would result in a fatal error in these PHP versions.
   *   This is why the method is commented out.
   *   The additional optional parameter can still be added in implementations.
   */
  # function findFile($api, $path_fragment, $path_suffix, $id = NULL);
}
