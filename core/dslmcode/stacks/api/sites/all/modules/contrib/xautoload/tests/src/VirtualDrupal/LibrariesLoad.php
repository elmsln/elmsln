<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


class LibrariesLoad {

  /**
   * @var DrupalStatic
   */
  private $drupalStatic;

  /**
   * @var Cache
   */
  private $cache;

  /**
   * @var LibrariesInfo
   */
  private $librariesInfo;

  /**
   * @param DrupalStatic $drupalStatic
   * @param Cache $cache
   * @param LibrariesInfo $librariesInfo
   */
  function __construct(DrupalStatic $drupalStatic, Cache $cache, LibrariesInfo $librariesInfo) {
    $this->drupalStatic = $drupalStatic;
    $this->cache = $cache;
    $this->librariesInfo = $librariesInfo;
  }

  /**
   * @param string $name
   *
   * @see libraries_load()
   */
  function librariesLoad($name) {
    $loaded = &$this->drupalStatic->get('libraries_load', array());

    if (!isset($loaded[$name])) {
      $library = $this->cache->cacheGet($name, 'cache_libraries');
      if ($library) {
        $library = $library->data;
      }
      else {
        $library = $this->librariesDetect($name);
        $this->cache->cacheSet($name, $library, 'cache_libraries');
      }

      // If a variant was specified, override the top-level properties with the
      // variant properties.
      if (isset($variant)) {
        // Ensure that the $variant key exists, and if it does not, set its
        // 'installed' property to FALSE by default. This will prevent the loading
        // of the library files below.
        $library['variants'] += array($variant => array('installed' => FALSE));
        $library = array_merge($library, $library['variants'][$variant]);
      }
      // Regardless of whether a specific variant was requested or not, there can
      // only be one variant of a library within a single request.
      unset($library['variants']);

      // Invoke callbacks in the 'pre-dependencies-load' group.
      $this->librariesInvoke('pre-dependencies-load', $library);

      // If the library (variant) is installed, load it.
      $library['loaded'] = FALSE;
      if ($library['installed']) {
        // Load library dependencies.
        if (isset($library['dependencies'])) {
          foreach ($library['dependencies'] as $dependency) {
            $this->librariesLoad($dependency);
          }
        }

        // Invoke callbacks in the 'pre-load' group.
        $this->librariesInvoke('pre-load', $library);

        // Load all the files associated with the library.
        $library['loaded'] = $this->librariesLoadFiles($library);

        // Invoke callbacks in the 'post-load' group.
        $this->librariesInvoke('post-load', $library);
      }
      $loaded[$name] = $library;
    }

    return $loaded[$name];
  }

  /**
   * Tries to detect a library and its installed version.
   *
   * @param $name
   *   The machine name of a library to return registered information for.
   *
   * @return array|false
   *   An associative array containing registered information for the library
   *   specified by $name, or FALSE if the library $name is not registered.
   *   In addition to the keys returned by libraries_info(), the following keys
   *   are contained:
   *   - installed: A boolean indicating whether the library is installed. Note
   *     that not only the top-level library, but also each variant contains this
   *     key.
   *   - version: If the version could be detected, the full version string.
   *   - error: If an error occurred during library detection, one of the
   *     following error statuses: "not found", "not detected", "not supported".
   *   - error message: If an error occurred during library detection, a detailed
   *     error message.
   *
   * @see libraries_info()
   * @see libraries_detect()
   */
  private function librariesDetect($name) {
    // Re-use the statically cached value of libraries_info() to save memory.
    $library = & $this->librariesInfo->getLibrariesInfo($name);

    if ($library === FALSE) {
      return $library;
    }
    // If 'installed' is set, library detection ran already.
    if (isset($library['installed'])) {
      return $library;
    }

    $library['installed'] = FALSE;

    // Check whether the library exists.
    if (!isset($library['library path'])) {
      $library['library path'] = $this->librariesInfo->librariesGetPath($library['machine name']);
    }
    if ($library['library path'] === FALSE || !file_exists($library['library path'])) {
      $library['error'] = 'not found';
      $library['error message'] = t(
        'The %library library could not be found.', array(
          '%library' => $library['name'],
        )
      );

      return $library;
    }

    // Invoke callbacks in the 'pre-detect' group.
    $this->librariesInvoke('pre-detect', $library);

    // Detect library version, if not hardcoded.
    if (!isset($library['version'])) {
      // We support both a single parameter, which is an associative array, and an
      // indexed array of multiple parameters.
      if (isset($library['version arguments'][0])) {
        // Add the library as the first argument.
        $library['version'] = call_user_func_array($library['version callback'], array_merge(array($library), $library['version arguments']));
      }
      elseif ('libraries_get_version' === $library['version callback']) {
        $library['version'] = $this->librariesGetVersion($library, $library['version arguments']);
      }
      else {
        $library['version'] = $library['version callback']($library, $library['version arguments']);
      }
      if (empty($library['version'])) {
        $library['error'] = 'not detected';
        $library['error message'] = t(
          'The version of the %library library could not be detected.', array(
            '%library' => $library['name'],
          )
        );

        return $library;
      }
    }

    // Determine to which supported version the installed version maps.
    if (!empty($library['versions'])) {
      ksort($library['versions']);
      $version = 0;
      foreach ($library['versions'] as $supported_version => $version_properties) {
        if (version_compare($library['version'], $supported_version, '>=')) {
          $version = $supported_version;
        }
      }
      if (!$version) {
        $library['error'] = 'not supported';
        $library['error message'] = t(
          'The installed version %version of the %library library is not supported.', array(
            '%version' => $library['version'],
            '%library' => $library['name'],
          )
        );

        return $library;
      }

      // Apply version specific definitions and overrides.
      $library = array_merge($library, $library['versions'][$version]);
      unset($library['versions']);
    }

    // Check each variant if it is installed.
    if (!empty($library['variants'])) {
      foreach ($library['variants'] as $variant_name => &$variant) {
        // If no variant callback has been set, assume the variant to be
        // installed.
        if (!isset($variant['variant callback'])) {
          $variant['installed'] = TRUE;
        }
        else {
          // We support both a single parameter, which is an associative array,
          // and an indexed array of multiple parameters.
          if (isset($variant['variant arguments'][0])) {
            // Add the library as the first argument, and the variant name as the second.
            $variant['installed'] = call_user_func_array(
              $variant['variant callback'], array_merge(
                array(
                  $library,
                  $variant_name
                ), $variant['variant arguments']
              )
            );
          }
          else {
            $variant['installed'] = $variant['variant callback']($library, $variant_name, $variant['variant arguments']);
          }
          if (!$variant['installed']) {
            $variant['error'] = 'not found';
            $variant['error message'] = t(
              'The %variant variant of the %library library could not be found.', array(
                '%variant' => $variant_name,
                '%library' => $library['name'],
              )
            );
          }
        }
      }
    }

    // If we end up here, the library should be usable.
    $library['installed'] = TRUE;

    // Invoke callbacks in the 'post-detect' group.
    $this->librariesInvoke('post-detect', $library);

    return $library;
  }

  /**
   * Invokes library callbacks.
   *
   * @param string $group
   *   A string containing the group of callbacks that is to be applied. Should be
   *   either 'info', 'pre-detect', 'post-detect', or 'load'.
   * @param array $library
   *   An array of library information, passed by reference.
   *
   * @see libraries_invoke()
   */
  private function librariesInvoke($group, &$library) {
    foreach ($library['callbacks'][$group] as $callback) {
      if ('libraries_detect_dependencies' === $callback) {
        continue;
      }
      $this->librariesTraverseLibrary($library, $callback);
    }
  }

  /**
   * Helper function to apply a callback to all parts of a library.
   *
   * Because library declarations can include variants and versions, and those
   * version declarations can in turn include variants, modifying e.g. the 'files'
   * property everywhere it is declared can be quite cumbersome, in which case
   * this helper function is useful.
   *
   * @param array $library
   *   An array of library information, passed by reference.
   * @param callback $callback
   *   A string containing the callback to apply to all parts of a library.
   *
   * @see libraries_traverse_library()
   */
  private function librariesTraverseLibrary(&$library, $callback) {
    // Always apply the callback to the top-level library.
    $callback($library, NULL, NULL);

    // Apply the callback to versions.
    if (isset($library['versions'])) {
      foreach ($library['versions'] as $version_string => &$version) {
        $callback($version, $version_string, NULL);
        // Versions can include variants as well.
        if (isset($version['variants'])) {
          foreach ($version['variants'] as $version_variant_name => &$version_variant) {
            $callback($version_variant, $version_string, $version_variant_name);
          }
        }
      }
    }

    // Apply the callback to variants.
    if (isset($library['variants'])) {
      foreach ($library['variants'] as $variant_name => &$variant) {
        $callback($variant, NULL, $variant_name);
      }
    }
  }

  /**
   * Loads a library's files.
   *
   * @param array $library
   *   An array of library information as returned by libraries_info().
   *
   * @return int
   *   The number of loaded files.
   *
   * @see libraries_load_files()
   */
  private function librariesLoadFiles($library) {
    // Not doing anything here, since library files are not relevant for
    // xautoload.
    return 0;
  }

  /**
   * @param $library
   * @param $options
   *
   * @return string
   *
   * @see libraries_get_version()
   */
  private function librariesGetVersion($library, $options) {
    return '1.0.0';
  }

} 
