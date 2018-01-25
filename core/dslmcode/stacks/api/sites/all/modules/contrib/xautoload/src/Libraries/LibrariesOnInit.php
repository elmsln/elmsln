<?php


namespace Drupal\xautoload\Libraries;


use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;
use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;
use Drupal\xautoload\Phases\PhaseObserverInterface;


/**
 * Registers autoload mappings from all libraries on hook_init(), or after the
 * first cache miss.
 */
class LibrariesOnInit implements PhaseObserverInterface {

  /**
   * @var DrupalSystemInterface
   */
  private $system;

  /**
   * @var ExtendedClassFinderInterface
   */
  private $finder;

  /**
   * @param DrupalSystemInterface $system
   */
  function __construct(DrupalSystemInterface $system) {
    $this->system = $system;
  }

  /**
   * Wake up after a cache fail.
   *
   * @param ExtendedClassFinderInterface $finder
   * @param string[] $extensions
   *   Extension type by extension name.
   */
  public function wakeUp(ExtendedClassFinderInterface $finder, array $extensions) {
    $this->finder = $finder;
  }

  /**
   * Enter the boot phase of the request, where all bootstrap module files are included.
   */
  public function enterBootPhase() {
    // Nothing.
  }

  /**
   * Enter the main phase of the request, where all module files are included.
   */
  public function enterMainPhase() {
    $this->registerLibrariesFinderPlugin();
  }

  /**
   * React to new extensions that were just enabled.
   *
   * @param string $name
   * @param string $type
   */
  public function welcomeNewExtension($name, $type) {
    // Nothing.
  }

  /**
   * React to xautoload_modules_enabled()
   *
   * @param string[] $modules
   *   New module names.
   */
  public function modulesEnabled($modules) {
    $this->system->drupalStaticReset('libraries_info');
    $this->system->cacheClearAll(XAUTOLOAD_CACHENAME_LIBRARIES_INFO, 'cache');
    $this->registerLibrariesFinderPlugin();
  }

  /**
   * Registers all libraries that have an "xautoload" setting.
   */
  private function registerLibrariesFinderPlugin() {
    $plugin = new LibrariesFinderPlugin($this->finder, $this->system);
    $this->finder->getPrefixMap()->registerDeepPath('', '', $plugin);
    $this->finder->getNamespaceMap()->registerDeepPath('', '', $plugin);
  }

}
