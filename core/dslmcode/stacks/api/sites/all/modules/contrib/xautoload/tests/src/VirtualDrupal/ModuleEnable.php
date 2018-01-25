<?php


namespace Drupal\xautoload\Tests\VirtualDrupal;



class ModuleEnable {

  /**
   * @var DrupalGetFilename
   */
  private $drupalGetFilename;

  /**
   * @var SystemTable
   */
  private $systemTable;

  /**
   * @var HookSystem
   */
  private $hookSystem;

  /**
   * @var SystemListReset
   */
  private $systemListReset;

  /**
   * @var ModuleList
   */
  private $moduleList;

  /**
   * @var SystemUpdateBootstrapStatus
   */
  private $systemUpdateBootstrapStatus;

  /**
   * @var SystemRebuildModuleData
   */
  private $systemRebuildModuleData;

  /**
   * @param DrupalGetFilename $drupalGetFilename
   * @param HookSystem $hookSystem
   * @param ModuleList $moduleList
   * @param SystemTable $systemTable
   * @param SystemListReset $systemListReset
   * @param SystemRebuildModuleData $systemRebuildModuleData
   * @param SystemUpdateBootstrapStatus $systemUpdateBootstrapStatus
   */
  function __construct(
    DrupalGetFilename $drupalGetFilename,
    HookSystem $hookSystem,
    ModuleList $moduleList,
    SystemTable $systemTable,
    SystemListReset $systemListReset,
    SystemRebuildModuleData $systemRebuildModuleData,
    SystemUpdateBootstrapStatus $systemUpdateBootstrapStatus
  ) {
    $this->drupalGetFilename = $drupalGetFilename;
    $this->hookSystem = $hookSystem;
    $this->moduleList = $moduleList;
    $this->systemTable = $systemTable;
    $this->systemListReset = $systemListReset;
    $this->systemRebuildModuleData = $systemRebuildModuleData;
    $this->systemUpdateBootstrapStatus = $systemUpdateBootstrapStatus;
  }

  /**
   * Simulates Drupal's module_enable()
   *
   * @see module_enable()
   *
   * @param string[] $module_list
   *   Array of module names.
   * @param bool $enable_dependencies
   *   TRUE, if dependencies should be enabled too.
   *
   * @return bool
   */
  function moduleEnable(array $module_list, $enable_dependencies = TRUE) {

    if ($enable_dependencies) {
      $module_list = $this->moduleEnableCheckDependencies($module_list);
    }

    if (empty($module_list)) {
      // Nothing to do. All modules already enabled.
      return TRUE;
    }

    $modules_installed = array();
    $modules_enabled = array();
    foreach ($module_list as $module) {
      if (1 == $this->systemTable->moduleGetStatus($module)) {
        // Already installed + enabled, do nothing.
        continue;
      }
      if (-1 == $this->systemTable->moduleGetSchemaVersion($module)) {
        // Install this module.
        $this->enableModule($module, TRUE);
        $modules_installed[] = $module;
        $modules_enabled[] = $module;
      }
      else {
        // Enable the module.
        $this->enableModule($module, FALSE);
        $modules_enabled[] = $module;
      }
    }

    // If any modules were newly installed, invoke hook_modules_installed().
    if (!empty($modules_installed)) {
      $this->hookSystem->moduleInvokeAll('modules_installed', $modules_installed);
    }

    // If any modules were newly enabled, invoke hook_modules_enabled().
    if (!empty($modules_enabled)) {
      $this->hookSystem->moduleInvokeAll('modules_enabled', $modules_enabled);
    }

    return TRUE;
  }

  /**
   * @param string[] $module_list
   *
   * @return string[]
   *   Module list with added dependencies, sorted by dependency.
   *
   * @throws \Exception
   */
  protected function moduleEnableCheckDependencies(array $module_list) {
    // Get all module data so we can find dependencies and sort.
    $module_data = $this->systemRebuildModuleData->systemRebuildModuleData();
    // Create an associative array with weights as values.
    $module_list = array_flip(array_values($module_list));

    while (list($module) = each($module_list)) {
      if (!isset($module_data[$module])) {
        // This module is not found in the filesystem, abort.
        throw new \Exception("Module '$module' not found.");
      }
      if ($module_data[$module]->status) {
        // Skip already enabled modules.
        unset($module_list[$module]);
        continue;
      }
      $module_list[$module] = $module_data[$module]->sort;

      // Add dependencies to the list, with a placeholder weight.
      // The new modules will be processed as the while loop continues.
      foreach (array_keys($module_data[$module]->requires) as $dependency) {
        if (!isset($module_list[$dependency])) {
          $module_list[$dependency] = 0;
        }
      }
    }

    if (!$module_list) {
      // Nothing to do. All modules already enabled.
      return array();
    }

    // Sort the module list by pre-calculated weights.
    arsort($module_list);
    return array_keys($module_list);
  }

  /**
   * @param string $extension
   * @param bool $install
   *
   * @see module_enable()
   */
  private function enableModule($extension, $install) {

    $filename = $this->drupalGetFilename->drupalGetFilename('module', $extension);

    // Include module files.
    require_once $filename;
    if (file_exists($install_file = dirname($filename) . '/' . $extension . '.install')) {
      require_once $install_file;
    }

    // Update status in system table
    $this->systemTable->moduleSetEnabled($extension);

    // Clear various caches, especially hook_module_implements()
    $this->systemListReset->systemListReset();
    $this->moduleList->moduleList(TRUE);
    $this->hookSystem->moduleImplementsReset();
    $this->systemUpdateBootstrapStatus->systemUpdateBootstrapStatus();

    // Update the registry to include it.
    # registry_update();
    // Refresh the schema to include it.
    # drupal_get_schema(NULL, TRUE);
    // Update the theme registry to include it.
    # drupal_theme_rebuild();
    // Clear entity cache.
    # entity_info_cache_clear();

    if ($install) {
      PureFunctions::moduleInvoke($extension, 'schema');
      $this->systemTable->moduleSetSchemaVersion($extension, 7000);
      PureFunctions::moduleInvoke($extension, 'update_last_removed');
      // Optional hook_install()..
      PureFunctions::moduleInvoke($extension, 'install');
      // Optional watchdog()
      $this->hookSystem->moduleInvokeAll('watchdog');
    }
    // hook_enable()
    PureFunctions::moduleInvoke($extension, 'enable');
    // watchdog()
    $this->hookSystem->moduleInvokeAll('watchdog');
  }
} 
