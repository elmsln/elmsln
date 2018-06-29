<?php

namespace Drupal\xautoload\Tests\Mock;

use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;
use Drupal\xautoload\Tests\VirtualDrupal\DrupalComponentContainer;
use Drupal\xautoload\Tests\VirtualDrupal\PureFunctions;

class MockDrupalSystem implements DrupalSystemInterface {

  /**
   * @var DrupalComponentContainer
   */
  private $components;

  /**
   * @var array
   */
  private $variables = array();

  /**
   * @param DrupalComponentContainer $components
   */
  function __construct(DrupalComponentContainer $components) {
    $this->components = $components;
  }

  /**
   * {@inheritdoc}
   */
  function variableSet($name, $value) {
    $this->variables[$name] = $value;
  }

  /**
   * {@inheritdoc}
   */
  function variableGet($name, $default = NULL) {
    return isset($this->variables[$name])
      ? $this->variables[$name]
      : $default;
  }

  /**
   * {@inheritdoc}
   */
  function drupalGetFilename($type, $name) {
    return $this->components->DrupalGetFilename->drupalGetFilename($type, $name);
  }

  /**
   * {@inheritdoc}
   */
  function drupalGetPath($type, $name) {
    return $this->components->DrupalGetFilename->drupalGetPath($type, $name);
  }

  /**
   * {@inheritdoc}
   */
  function getExtensionTypes($extension_names) {
    // Simply assume that everything is a module.
    return array_fill_keys($extension_names, 'module');
  }

  /**
   * {@inheritdoc}
   */
  function getActiveExtensions() {
    return $this->components->SystemTable->getActiveExtensions();
  }

  /**
   * Replicates module_list()
   *
   * @param bool $refresh
   * @param bool $bootstrap_refresh
   * @param bool $sort
   *
   * @return string[]
   */
  function moduleList($refresh = FALSE, $bootstrap_refresh = FALSE, $sort = FALSE) {
    return $this->components->ModuleList->moduleList($refresh, $bootstrap_refresh, $sort);
  }

  /**
   * @see module_invoke()
   *
   * @param string $module
   * @param string $hook
   *
   * @return mixed
   *
   * @throws \Exception
   */
  function moduleInvoke($module, $hook) {
    $args = func_get_args();
    switch (count($args)) {
      case 2:
        return PureFunctions::moduleInvoke($module, $hook);
      case 3:
        return PureFunctions::moduleInvoke($module, $hook, $args[2]);
      case 4:
        return PureFunctions::moduleInvoke($module, $hook, $args[2], $args[3]);
      default:
        throw new \Exception("More arguments than expected.");
    }
  }

  /**
   * @param string $hook
   */
  function moduleInvokeAll($hook) {
    $args = func_get_args();
    call_user_func_array(array($this->components->HookSystem, 'moduleInvokeAll'), $args);
  }

  /**
   * @param string $hook
   *
   * @throws \Exception
   * @return array
   */
  function moduleImplements($hook) {
    return $this->components->HookSystem->moduleImplements($hook);
  }

  /**
   * @param string $hook
   * @param mixed $data
   */
  function drupalAlter($hook, &$data) {
    $args = func_get_args();
    assert($hook === array_shift($args));
    assert($data === array_shift($args));
    while (count($args) < 3) {
      $args[] = NULL;
    }
    $this->components->HookSystem->drupalAlter($hook, $data, $args[0], $args[1], $args[2]);
  }

  /**
   * Replicates module_load_include()
   *
   * @param string $type
   * @param string $module
   * @param string|null $name
   *
   * @return bool|string
   */
  function moduleLoadInclude($type, $module, $name = NULL) {
    if (!isset($name)) {
      $name = $module;
    }
    $file = $this->drupalGetPath('module', $module) . "/$name.$type";
    if (is_file($file)) {
      require_once $file;
      return $file;
    }
    return FALSE;
  }

  /**
   * Resets the module_implements() cache.
   */
  public function resetModuleImplementsCache() {
    $this->components->HookSystem->moduleImplementsReset();
  }

  /**
   * @see libraries_info()
   *
   * @return mixed
   */
  function getLibrariesInfo() {
    $this->components->LibrariesInfo->resetLibrariesInfo();
    return $this->components->LibrariesInfo->getLibrariesInfo();
  }

  /**
   * @see libraries_get_path()
   *
   * @param string $name
   *   Name of the library.
   *
   * @return string|false
   */
  function librariesGetPath($name) {
    return $this->components->LibrariesInfo->librariesGetPath($name);
  }

  /**
   * Called from xautoload_install() to set the module weight.
   *
   * @param int $weight
   *   New module weight for xautoload.
   */
  public function installSetModuleWeight($weight) {
    $this->components->SystemTable->moduleSetWeight('xautoload', $weight);
    $this->components->SystemListReset->systemListReset();
  }

  /**
   * @param string $cid
   * @param string $bin
   *
   * @return object|false
   *   The cache or FALSE on failure.
   *
   * @see cache_get()
   */
  public function cacheGet($cid, $bin = 'cache') {
    return $this->components->Cache->cacheGet($cid, $bin);
  }

  /**
   * @param string $cid
   * @param mixed $data
   * @param string $bin
   *
   * @return mixed
   *
   * @see cache_set()
   */
  public function cacheSet($cid, $data, $bin = 'cache') {
    $this->components->Cache->cacheSet($cid, $data, $bin);
  }

  /**
   * @param string|null $cid
   * @param string|null $bin
   *
   * @see cache_clear_all()
   */
  public function cacheClearAll($cid = NULL, $bin = NULL) {
    $this->components->Cache->cacheClearAll($cid, $bin);
  }

  /**
   * @param string $key
   */
  public function drupalStaticReset($key) {
    $this->components->DrupalStatic->resetKey($key);
  }

}
