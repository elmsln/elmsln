<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;


use Drupal\xautoload\Tests\Mock\MockDrupalSystem;

class DrupalEnvironment {

  /**
   * @var self
   */
  private static $staticInstance;

  /**
   * @var DrupalComponentContainer
   */
  private $components;

  /**
   * @var ExampleModulesInterface
   */
  private $exampleModules;

  /**
   * @param ExampleModulesInterface $exampleModules
   */
  function __construct(ExampleModulesInterface $exampleModules) {
    $this->components = new DrupalComponentContainer($exampleModules);
    $this->exampleModules = $exampleModules;
  }

  function setStaticInstance() {
    self::$staticInstance = $this;
  }

  /**
   * @return DrupalEnvironment
   */
  static function getInstance() {
    return self::$staticInstance;
  }

  /**
   * @return MockDrupalSystem
   */
  function getMockDrupalSystem() {
    return $this->components->MockDrupalSystem;
  }

  /**
   * @return Cache
   */
  function getCache() {
    return $this->components->Cache;
  }

  /**
   * @return SystemTable
   */
  function getSystemTable() {
    return $this->components->SystemTable;
  }

  /**
   * Simulates Drupal's \module_enable()
   *
   * @param string[] $module_list
   *   Array of module names.
   * @param bool $enable_dependencies
   *   TRUE, if dependencies should be enabled too.
   *
   * @return bool
   */
  function moduleEnable(array $module_list, $enable_dependencies = TRUE) {
    $this->components->ModuleEnable->moduleEnable($module_list, $enable_dependencies);
  }

  /**
   * Replicates the Drupal bootstrap.
   */
  public function boot() {
    $this->components->DrupalBoot->boot();
  }

  /**
   * Version of systemUpdateBootstrapStatus() with no side effects.
   *
   * @see _system_update_bootstrap_status()
   */
  public function initBootstrapStatus() {
    $bootstrap_modules = $this->exampleModules->getBootstrapModules();
    $this->components->SystemTable->setBootstrapModules($bootstrap_modules);
  }

  /**
   * @param string $name
   *
   * @return mixed
   */
  public function librariesLoad($name) {
    return $this->components->LibrariesLoad->librariesLoad($name);
  }

}
