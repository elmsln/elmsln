<?php

namespace Drupal\xautoload\ClassFinder\Plugin;

class DrupalExtensionUnderscoreFinderPlugin extends DrupalExtensionNamespaceFinderPlugin {

  /**
   * {@inheritdoc}
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
    $lib = dirname($extension_file) . '/lib/';
    $lib_psr0 = $lib . 'Drupal/' . $extension_name . '/';

    // Try PEAR-Flat.
    if ($api->guessPath($lib . $relative_path)) {
      // Register PEAR-Flat.
      $this->prefixMap->registerDeepPath($uspath, $lib, $this->defaultBehavior);
      // Unregister the lazy plugins.
      $this->namespaceMap->unregisterDeepPath($nspath, $extension_name);
      $this->prefixMap->unregisterDeepPath($uspath, $extension_name);
      // See if there are PSR-0 or PSR-4 test classes.
      if (is_dir($lib_psr0 . 'Tests/')) {
        $this->namespaceMap->registerDeepPath(
          $testpath,
          $lib_psr0 . 'Tests/',
          $this->psr0Behavior);
      }
      if (is_dir($lib . 'Tests/')) {
        $this->namespaceMap->registerDeepPath(
          $testpath,
          $lib . 'Tests/',
          $this->defaultBehavior);
      }

      // The class was found, so return TRUE.
      return TRUE;
    }

    // The class was not found, so return FALSE.
    return FALSE;
  }
}
