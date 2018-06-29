<?php

namespace Drupal\xautoload\Adapter;

use Drupal\xautoload\ClassFinder\CommonRegistrationInterface;

interface ClassFinderAdapterInterface extends CommonRegistrationInterface {

  //                                                                   Discovery
  // ---------------------------------------------------------------------------

  /**
   * @param string[] $paths
   *   File paths or wildcard paths for class discovery.
   */
  function addClassmapSources($paths);

  //                                                              Composer tools
  // ---------------------------------------------------------------------------

  /**
   * Scan a composer.json file provided by a Composer package.
   *
   * @param string $file
   *
   * @throws \Exception
   */
  function composerJson($file);

  /**
   * Scan a directory containing Composer-generated autoload files.
   *
   * @param string $dir
   *   Directory to look for Composer-generated files. Typically this is the
   *   ../vendor/composer dir.
   */
  function composerDir($dir);

  //                                                      multiple PSR-0 / PSR-4
  // ---------------------------------------------------------------------------

  /**
   * Add multiple PSR-0 namespaces
   *
   * @param array $prefixes
   */
  function addMultiplePsr0(array $prefixes);

  /**
   * Add multiple PSR-4 namespaces
   *
   * @param array $map
   */
  function addMultiplePsr4(array $map);

} 