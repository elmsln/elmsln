<?php


namespace Drupal\xautoload\Phases;


use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;
use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;


/**
 * A variation of hook_xautoload() that fires
 * - when all *module file are included:
 *   - xautoload_custom_theme(), or
 *   - xautoload_init(), whichever is first.
 * - when module_enable() has finished:
 *   - xautoload_modules_enabled()
 *
 * This can cause any implementation to be fired multiple times per request.
 */
class HookXautoload implements PhaseObserverInterface {

  /**
   * @var ExtendedClassFinderInterface|null
   */
  private $finder = NULL;

  /**
   * @var DrupalSystemInterface
   */
  private $system;

  /**
   * @var string[]
   */
  private $extensions;

  /**
   * @param DrupalSystemInterface $system
   */
  public function __construct(DrupalSystemInterface $system) {
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
    $this->extensions = $extensions;
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
    $modules = $this->system->moduleImplements('xautoload');
    $this->runHookXautoload($modules);
  }

  /**
   * New extensions were enabled/installed.
   *
   * @param string $name
   *   Extension type by name.
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
    $modules = $this->system->moduleImplements('xautoload');
    $this->runHookXautoload($modules);
  }

  /**
   * Runs hook_xautoload() on all enabled modules.
   *
   * This may occur multiple times in a request, if new modules are enabled.
   *
   * @param array $modules
   */
  private function runHookXautoload(array $modules) {
    // Let other modules register stuff to the finder via hook_xautoload().
    $adapter = \xautoload_InjectedAPI_hookXautoload::create($this->finder, '');
    foreach ($modules as $module) {
      $adapter->setExtensionDir($dir = $this->system->drupalGetPath('module', $module));
      $function = $module . '_xautoload';
      $function($adapter, $dir);
    }
  }

}
