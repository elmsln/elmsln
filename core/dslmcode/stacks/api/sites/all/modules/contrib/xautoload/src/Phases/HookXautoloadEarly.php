<?php


namespace Drupal\xautoload\Phases;


use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;
use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;

/**
 * A variation of hook_xautoload() that fires very early, as soon as a *.module
 * file is included, but only once per module / request.
 */
class HookXautoloadEarly implements PhaseObserverInterface {

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
    // @todo Call hook_xautoload() on bootstrap modules, if in bootstrap phase.
  }

  /**
   * Enter the main phase of the request, where all module files are included.
   */
  public function enterMainPhase() {
    // @todo Don't use moduleImplements(), to prevent hook_module_implements_alter()
    $modules = $this->system->moduleImplements('xautoload');
    // @todo Remove boot modules from the list.
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
    $function = $name . '_xautoload';
    if (!function_exists($function)) {
      return;
    }
    $dir = $this->system->drupalGetPath($type, $name);
    $adapter = \xautoload_InjectedAPI_hookXautoload::create($this->finder, $dir);
    $function($adapter, $dir);
  }

  /**
   * React to xautoload_modules_enabled()
   *
   * @param string[] $modules
   *   New module names.
   */
  public function modulesEnabled($modules) {
    // Nothing.
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
