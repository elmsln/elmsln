<?php

namespace Drupal\xautoload\ClassFinder\Plugin;

use Drupal\xautoload\ClassFinder\InjectedApi\FindFileInjectedApi;

class Psr4FinderPlugin implements FinderPluginInterface {

  /**
   * @param FindFileInjectedApi $api
   *   An object with a suggestFile() method.
   *   We are supposed to suggest files until suggestFile() returns TRUE, or we
   *   have no more suggestions.
   * @param string $logical_base_path
   *   The key that this plugin was registered with.
   *   With trailing '/'.
   * @param string $relative_path
   *   Second part of the canonical path, ending with '.php'.
   * @param int|string $base_dir
   *   Id under which the plugin was registered.
   *   This should be the PSR-4 base directory.
   *
   * @return bool|null
   *   TRUE, if the file was found.
   *   FALSE, otherwise.
   */
  function findFile($api, $logical_base_path, $relative_path, $base_dir = NULL) {
    // The $relative_path has the replacements from PSR-0, which we don't want.
    // So we need to re-calculate it.
    $relative_classname = substr($api->getClass(), strlen($logical_base_path));
    $relative_path = str_replace('\\', '/', $relative_classname) . '.php';
    return $api->suggestFile($base_dir . '/' . $relative_path);
  }
}
