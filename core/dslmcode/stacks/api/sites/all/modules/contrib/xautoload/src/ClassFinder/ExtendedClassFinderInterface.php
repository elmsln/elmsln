<?php

namespace Drupal\xautoload\ClassFinder;

use Drupal\xautoload\DirectoryBehavior\DirectoryBehaviorInterface;

/**
 * Class finder interface with additional registration methods.
 */
interface ExtendedClassFinderInterface extends ClassFinderInterface, CommonRegistrationInterface {

  /**
   * @return GenericPrefixMap
   */
  function getPrefixMap();

  /**
   * @return GenericPrefixMap
   */
  function getNamespaceMap();

  //                                                             Class map stuff
  // ---------------------------------------------------------------------------

  /**
   * Register a filepath for an individual class.
   *
   * @param string $class
   *   The class, e.g. My_Class
   * @param string $file_path
   *   The path, e.g. "../lib/My/Class.php".
   */
  function registerClass($class, $file_path);

  /**
   * Register an array ("map") of classes to file paths.
   *
   * @param string[] $classes
   *   The map of classes to file paths.
   */
  function registerClasses($classes);

  //                                                                Prefix stuff
  // ---------------------------------------------------------------------------

  /**
   * Register a PEAR-style root path for a given class prefix.
   *
   * @param string $prefix
   *   Prefix, e.g. "My_Prefix", for classes like "My_Prefix_SomeClass".
   *   This does ALSO cover the class named "My_Prefix" itself.
   * @param string $root_path
   *   Root path, e.g. "../lib" or "../src", so that classes can be placed e.g.
   *   My_Prefix_SomeClass -> ../lib/My/Prefix/SomeClass.php
   *   My_Prefix -> ../lib/My/Prefix.php
   * @param DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerPrefixRoot($prefix, $root_path, $behavior = NULL);

  /**
   * Register an array of PEAR-style deep paths for given class prefixes.
   *
   * Note:
   *   This actually goes beyond PEAR style, because it also allows "shallow"
   *   PEAR-like structures like
   *     my_library_Some_Class -> (library dir)/src/Some/Class.php
   *   instead of
   *     my_library_Some_Class -> (library dir)/src/my/library/Some/Class.php
   *   via
   *     $finder->registerPrefixDeep('my_library', "$library_dir/src");
   *
   * @param string[] $map
   *   Associative array, the keys are the prefixes, the values are the
   *   directories.
   *   This does NOT cover the class named $prefix itself.
   * @param DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerPrefixesRoot($map, $behavior = NULL);

  /**
   * Register a PEAR-style deep path for a given class prefix.
   *
   * Note:
   *   This actually goes beyond PEAR style, because it also allows things like
   *     my_library_Some_Class -> (library dir)/src/Some/Class.php
   *   instead of
   *     my_library_Some_Class -> (library dir)/src/my/library/Some/Class.php
   *   via
   *     $finder->registerPrefixDeep('my_library', "$library_dir/src");
   *
   * @param string $prefix
   *   Prefix, e.g. "My_Prefix", for classes like "My_Prefix_SomeClass".
   *   This does NOT cover the class named "My_Prefix" itself.
   * @param string $deep_path
   *   The deep path, e.g. "../lib/My/Prefix", for classes placed in
   *   My_Prefix_SomeClass -> ../lib/My/Prefix/SomeClass.php
   * @param DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerPrefixDeep($prefix, $deep_path, $behavior = NULL);

  /**
   * Register an array of PEAR-style deep paths for given class prefixes.
   *
   * Note:
   *   This actually goes beyond PEAR style, because it also allows "shallow"
   *   PEAR-like structures like
   *     my_library_Some_Class -> (library dir)/src/Some/Class.php
   *   instead of
   *     my_library_Some_Class -> (library dir)/src/my/library/Some/Class.php
   *   via
   *     $finder->registerPrefixDeep('my_library', "$library_dir/src");
   *
   * @param string[] $map
   *   Associative array, the keys are the prefixes, the values are the
   *   directories.
   *   This does NOT cover the class named $prefix itself.
   * @param \Drupal\xautoload\DirectoryBehavior\DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerPrefixesDeep($map, $behavior = NULL);

  /**
   * Register a filesystem location for a given class prefix.
   *
   * @param string $prefix
   *   The prefix, e.g. "My_Prefix"
   * @param string $deep_path
   *   The deep filesystem location, e.g. "../lib/My/Prefix".
   * @param DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerPrefixDeepLocation($prefix, $deep_path, $behavior = NULL);

  //                                                             Namespace stuff
  // ---------------------------------------------------------------------------

  /**
   * Register a PSR-0 root folder for a given namespace.
   *
   * @param string $namespace
   *   The namespace, e.g. "My\Namespace", to cover all classes within that,
   *   e.g. My\Namespace\SomeClass, or My\Namespace\Xyz\SomeClass. This does not
   *   cover the root-level class, e.g. My\Namespace
   * @param string $root_path
   *   The deep path, e.g. "../lib", if classes reside in e.g.
   *   My\Namespace\SomeClass -> ../lib/My/Namespace/SomeClass.php
   * @param \Drupal\xautoload\DirectoryBehavior\DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerNamespaceRoot($namespace, $root_path, $behavior = NULL);

  /**
   * Register PSR-0 root folders for given namespaces.
   *
   * @param string[] $map
   *   Associative array, the keys are the namespaces, the values are the
   *   directories.
   * @param \Drupal\xautoload\DirectoryBehavior\DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerNamespacesRoot($map, $behavior = NULL);

  /**
   * Alias for registerNamespaceDeepLocation()
   *
   * @param string $namespace
   *   The namespace, e.g. "My\Namespace"
   * @param string $path
   *   The deep path, e.g. "../lib/My/Namespace"
   * @param \Drupal\xautoload\DirectoryBehavior\DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerNamespaceDeep($namespace, $path, $behavior = NULL);

  /**
   * Register a number of "deep" namespace directories at once.
   *
   * @param string[] $map
   * @param DirectoryBehaviorInterface $behavior
   */
  function registerNamespacesDeep($map, $behavior = NULL);

  /**
   * Register a deep filesystem location for a given namespace.
   *
   * @param string $namespace
   *   The namespace, e.g. "My\Namespace"
   * @param string $path
   *   The deep path, e.g. "../lib/My/Namespace"
   * @param DirectoryBehaviorInterface $behavior
   *   If TRUE, then we are not sure if the directory at $path actually exists.
   *   If during the process we find the directory to be nonexistent, we
   *   unregister the path.
   */
  function registerNamespaceDeepLocation($namespace, $path, $behavior = NULL);
}
