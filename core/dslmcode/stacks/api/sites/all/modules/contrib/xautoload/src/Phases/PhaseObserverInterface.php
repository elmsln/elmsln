<?php


namespace Drupal\xautoload\Phases;


use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;

/**
 * Observes switching into specific "phases" of a Drupal process.
 *
 * @see \Drupal\xautoload\Phases\DrupalPhaseControl
 *
 * These phases only fire after the class loader had a cache fail.
 * This way, all the initialization logic, subscribing module namespaces etc,
 * will not be executed on an average request.
 *
 * Phase switching events can hit the observer later in the request, even if the
 * respective phase has already started long ago. E.g. the enterBootPhase() will
 * still fire even if the cache miss happens during the "main phase".
 *
 * However, the order of phase events being called on an observer will always be
 * the same. And wakeUp() will always be called before any other phase event,
 * giving the observer the chance to set up the finder object.
 */
interface PhaseObserverInterface {

  /**
   * Wake up after a cache fail.
   *
   * @param ExtendedClassFinderInterface $finder
   *   The class finder object, with any cache decorator peeled off.
   * @param string[] $extensions
   *   Currently enabled extensions. Extension type by extension name.
   */
  public function wakeUp(ExtendedClassFinderInterface $finder, array $extensions);

  /**
   * Enter the boot phase of the request, where all bootstrap module files are included.
   */
  public function enterBootPhase();

  /**
   * Enter the main phase of the request, where all module files are included.
   */
  public function enterMainPhase();

  /**
   * React to new extensions that were just enabled.
   *
   * @param string $name
   * @param string $type
   */
  public function welcomeNewExtension($name, $type);

  /**
   * React to xautoload_modules_enabled()
   *
   * @param string[] $modules
   *   New module names.
   */
  public function modulesEnabled($modules);
}
