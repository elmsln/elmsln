<?php

namespace Drupal\xautoload\ClassFinder;

/**
 * Class finder interface with additional registration methods.
 */
interface CommonRegistrationInterface {

  //                                                      Composer compatibility
  // ---------------------------------------------------------------------------

  /**
   * Registers an array ("map") of classes to file paths.
   *
   * @param array $classMap
   *   Class to filename map. E.g. $classMap['Acme\Foo'] = 'lib/Acme/Foo.php'
   */
  function addClassMap(array $classMap);

  /**
   * Adds a PSR-0 style prefix. Alias for ->addPsr0().
   *
   * @param string $prefix
   * @param string[]|string $paths
   */
  function add($prefix, $paths);

  /**
   * Adds a PSR-0 style prefix. Alias for ->add().
   *
   * @param string $prefix
   * @param string[]|string $paths
   */
  function addPsr0($prefix, $paths);

  /**
   * Adds a PSR-4 style namespace.
   *
   * @param string $prefix
   * @param string[]|string $paths
   */
  function addPsr4($prefix, $paths);

  //                                                      More convenience stuff
  // ---------------------------------------------------------------------------

  /**
   * Adds a PSR-0 style namespace.
   *
   * This will assume that we are really dealing with a namespace, even if it
   * has no '\\' included.
   *
   * @param string $prefix
   * @param string[]|string $paths
   */
  function addNamespacePsr0($prefix, $paths);

  /**
   * Adds a PEAR-like prefix.
   *
   * This will assume with no further checks that $prefix contains no namespace
   * separator.
   *
   * @param string $prefix
   * @param string[]|string $paths
   */
  function addPear($prefix, $paths);

  /**
   * Adds a prefix similar to PEAR, but with flat directories.
   *
   * This will assume with no further checks that $prefix contains no namespace
   * separator.
   *
   * @param string $prefix
   * @param string[]|string $paths
   */
  function addPearFlat($prefix, $paths);

}
