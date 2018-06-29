<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;

use Drupal\xautoload\Tests\Mock\MockDrupalSystem;

/**
 *
 * @property ModuleEnable ModuleEnable
 * @property DrupalGetFilename DrupalGetFilename
 * @property SystemUpdateBootstrapStatus SystemUpdateBootstrapStatus
 * @property SystemRebuildModuleData SystemRebuildModuleData
 * @property SystemListReset SystemListReset
 * @property SystemTable SystemTable
 * @property ModuleList ModuleList
 * @property HookSystem HookSystem
 * @property DrupalStatic DrupalStatic
 * @property SystemList SystemList
 * @property Cache Cache
 * @property ModuleBuildDependencies ModuleBuildDependencies
 * @property SystemBuildModuleData SystemBuildModuleData
 * @property LibrariesInfo LibrariesInfo
 * @property LibrariesLoad LibrariesLoad
 * @property DrupalBootstrap DrupalBoot
 * @property DrupalLoad DrupalLoad
 * @property MockDrupalSystem MockDrupalSystem
 */
class DrupalComponentContainer {

  /**
   * @var object[]
   */
  private $components = array();

  /**
   * @var ExampleModulesInterface
   */
  private $exampleModules;

  /**
   * @param ExampleModulesInterface $exampleModules
   */
  function __construct(ExampleModulesInterface $exampleModules) {
    $this->exampleModules = $exampleModules;
  }

  /**
   * Magic getter for a Drupal component.
   *
   * @param string $key
   *
   * @return object
   *
   * @throws \Exception
   */
  function __get($key) {
    if (array_key_exists($key, $this->components)) {
      return $this->components[$key];
    }
    $method = 'get' . $key;
    if (!method_exists($this, $method)) {
      throw new \Exception("Unsupported key '$key' for DrupalComponentContainer.");
    }
    return $this->components[$key] = $this->$method($this);
  }

  /**
   * @return SystemTable
   *
   * @see DrupalComponentContainer::SystemTable
   */
  protected function getSystemTable() {
    return new SystemTable();
  }

  /**
   * @return Cache
   *
   * @see DrupalComponentContainer::Cache
   */
  protected function getCache() {
    return new Cache();
  }

  /**
   * @return DrupalStatic
   *
   * @see DrupalComponentContainer::DrupalStatic
   */
  protected function getDrupalStatic() {
    return new DrupalStatic();
  }

  /**
   * @return DrupalGetFilename
   *
   * @see DrupalComponentContainer::DrupalGetFilename
   */
  protected function getDrupalGetFilename() {
    return new DrupalGetFilename($this->SystemTable, $this->exampleModules);
  }

  /**
   * @return HookSystem
   *
   * @see DrupalComponentContainer::HookSystem
   */
  protected function getHookSystem() {
    return new HookSystem(
      $this->DrupalStatic,
      $this->Cache,
      $this->ModuleList);
  }

  /**
   * @return ModuleEnable
   *
   * @see DrupalComponentContainer::ModuleEnable
   */
  protected function getModuleEnable() {
    return new ModuleEnable(
      $this->DrupalGetFilename,
      $this->HookSystem,
      $this->ModuleList,
      $this->SystemTable,
      $this->SystemListReset,
      $this->SystemRebuildModuleData,
      $this->SystemUpdateBootstrapStatus);
  }

  /**
   * @return ModuleList
   *
   * @see DrupalComponentContainer::ModuleList
   */
  protected function getModuleList() {
    return new ModuleList(
      $this->DrupalGetFilename,
      $this->SystemList,
      $this->DrupalStatic);
  }

  /**
   * @return SystemListReset
   *
   * @see DrupalComponentContainer::SystemListReset
   */
  protected function getSystemListReset() {
    return new SystemListReset(
      $this->Cache,
      $this->DrupalStatic);
  }

  /**
   * @return ModuleBuildDependencies
   *
   * @see DrupalComponentContainer::ModuleBuildDependencies
   */
  protected function getModuleBuildDependencies() {
    return new ModuleBuildDependencies();
  }

  /**
   * @return SystemBuildModuleData
   *
   * @see DrupalComponentContainer::SystemBuildModuleData
   */
  protected function getSystemBuildModuleData() {
    return new SystemBuildModuleData(
      $this->exampleModules,
      $this->HookSystem);
  }

  /**
   * @return SystemRebuildModuleData
   *
   * @see DrupalComponentContainer::SystemRebuildModuleData
   */
  protected function getSystemRebuildModuleData() {
    return new SystemRebuildModuleData(
      $this->DrupalStatic,
      $this->ModuleBuildDependencies,
      $this->SystemTable,
      $this->SystemBuildModuleData,
      $this->SystemListReset);
  }

  /**
   * @return SystemUpdateBootstrapStatus
   *
   * @see DrupalComponentContainer::SystemUpdateBootstrapStatus
   */
  protected function getSystemUpdateBootstrapStatus() {
    return new SystemUpdateBootstrapStatus(
      $this->HookSystem,
      $this->SystemTable,
      $this->SystemListReset);
  }

  /**
   * @return SystemList
   *
   * @see DrupalComponentContainer::SystemList
   */
  protected function getSystemList() {
    return new SystemList(
      $this->Cache,
      $this->SystemTable,
      $this->DrupalGetFilename,
      $this->DrupalStatic);
  }

  /**
   * @return LibrariesInfo
   *
   * @see DrupalComponentContainer::LibrariesInfo
   */
  protected function getLibrariesInfo() {
    return new LibrariesInfo(
      $this->DrupalStatic,
      $this->HookSystem);
  }

  /**
   * @return LibrariesLoad
   *
   * @see DrupalComponentContainer::LibrariesLoad
   */
  protected function getLibrariesLoad() {
    return new LibrariesLoad(
      $this->DrupalStatic,
      $this->Cache,
      $this->LibrariesInfo);
  }

  /**
   * @return DrupalBootstrap
   *
   * @see DrupalComponentContainer::DrupalBoot
   */
  protected function getDrupalBoot() {
    return new DrupalBootstrap(
      $this->DrupalLoad,
      $this->HookSystem,
      $this->ModuleList);
  }

  /**
   * @return MockDrupalSystem
   *
   * @see DrupalComponentContainer::MockDrupalSystem
   */
  protected function getMockDrupalSystem() {
    return new MockDrupalSystem($this);
  }

  /**
   * @return DrupalLoad
   *
   * @see DrupalComponentContainer::DrupalLoad
   */
  protected function getDrupalLoad() {
    return new DrupalLoad(
      $this->DrupalGetFilename);
  }

} 
