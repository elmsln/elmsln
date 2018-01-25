<?php

namespace Drupal\xautoload\DIC;

use Drupal\xautoload\Adapter\ClassFinderAdapter;
use Drupal\xautoload\Adapter\DrupalExtensionAdapter;
use Drupal\xautoload\ClassFinder\ClassFinder;
use Drupal\xautoload\ClassFinder\ClassFinderInterface;
use Drupal\xautoload\CacheManager\CacheManager;
use Drupal\xautoload\ClassFinder\ProxyClassFinder;
use Drupal\xautoload\Discovery\CachedClassMapGenerator;
use Drupal\xautoload\Discovery\ClassMapGenerator;
use Drupal\xautoload\DrupalSystem\DrupalSystem;
use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;
use Drupal\xautoload\Libraries\LibrariesInfoAlter;
use Drupal\xautoload\Phases\DrupalCoreRegistryRegistrator;
use Drupal\xautoload\Phases\DrupalPhaseControl;
use Drupal\xautoload\Phases\ExtensionNamespaces;
use Drupal\xautoload\Phases\HookXautoload;
use Drupal\xautoload\Libraries\LibrariesOnInit;
use Drupal\xautoload\Main;

/**
 * @see ServiceContainerInterface
 * @see ServiceContainer
 */
class ServiceFactory {

  /**
   * @param ServiceContainer $services
   *
   * @return Main
   */
  function main($services) {
    return new Main($services);
  }

  /**
   * @param ServiceContainer $services
   *
   * @return ClassFinderAdapter
   */
  function adapter($services) {
    return new ClassFinderAdapter($services->finder, $services->classMapGenerator);
  }

  /**
   * @param ServiceContainer $services
   *
   * @return ClassMapGenerator
   */
  function classMapGenerator($services) {
    return new CachedClassMapGenerator($services->classMapGeneratorRaw, $services->system);
  }

  /**
   * @param ServiceContainer $services
   *
   * @return ClassMapGenerator
   */
  function classMapGeneratorRaw($services) {
    return new ClassMapGenerator();
  }

  /**
   * @param ServiceContainer $services
   *
   * @return DrupalExtensionAdapter
   */
  function extensionRegistrationService($services) {
    return new DrupalExtensionAdapter($services->system, $services->finder);
  }

  /**
   * @param ServiceContainer $services
   *
   * @return CacheManager
   */
  function cacheManager($services) {
    return CacheManager::create($services->system);
  }

  /**
   * Proxy class finder.
   *
   * @param ServiceContainer $services
   *
   * @return ClassFinderInterface
   *   Proxy object wrapping the class finder.
   *   This is used to delay namespace registration until the first time the
   *   finder is actually used.
   *   (which might never happen thanks to the APC cache)
   */
  function proxyFinder($services) {
    // The class finder is cheap to create, so it can use an identity proxy.
    return new ProxyClassFinder($services->finder);
  }

  /**
   * The class finder (alias for 'finder').
   *
   * @param ServiceContainer $services
   *
   * @return ClassFinderInterface
   *   Object that can find classes,
   *   and provides methods to register namespaces and prefixes.
   *   Note: The findClass() method expects an InjectedAPI argument.
   */
  function classFinder($services) {
    return $services->finder;
  }

  /**
   * The class finder (alias for 'classFinder').
   *
   * @param ServiceContainer $services
   *
   * @return ClassFinderInterface
   *   Object that can find classes,
   *   and provides methods to register namespaces and prefixes.
   *   Notes:
   *   - The findClass() method expects an InjectedAPI argument.
   *   - namespaces are only supported since PHP 5.3
   */
  function finder($services) {
    return new ClassFinder();
  }

  /**
   * @param ServiceContainer $services
   *
   * @return DrupalSystemInterface
   */
  function system($services) {
    return new DrupalSystem();
  }

  /**
   * @param ServiceContainer $services
   *
   * @return DrupalPhaseControl
   */
  function phaseControl($services) {
    $observers = array(
      $services->extensionNamespaces,
      new HookXautoload($services->system),
      new LibrariesOnInit($services->system),
    );
    if ($services->system->variableGet(XAUTOLOAD_VARNAME_REPLACE_CORE, FALSE)) {
      $observers[] = new DrupalCoreRegistryRegistrator();
    }
    return new DrupalPhaseControl($services->system, $observers);
  }

  /**
   * @param ServiceContainer $services
   *
   * @return ExtensionNamespaces
   */
  function extensionNamespaces($services) {
    return new ExtensionNamespaces($services->system);
  }

  /**
   * @param ServiceContainer $services
   *
   * @return LibrariesInfoAlter
   */
  function librariesInfoAlter($services) {
    return new LibrariesInfoAlter();
  }

}

